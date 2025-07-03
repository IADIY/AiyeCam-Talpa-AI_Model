/*------------------------------------------------------------------------------------------------*/
/* */
/* Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                                  */
/* */
/*------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "nbsdk.h"
#include "bsp.h"
#include "nbsdk_api.h"

#include "User_Config.h"
#include "include/sensor_aeg.h"
#include "include/Basic.h"
#include "Token.h"

/**************************************************************************
 * Constants
 **************************************************************************/
#define HOST_SECTION __attribute__((section(".ver_host")))

#define TASK_DELAY_TIME 2

#define TRUE 1
#define FALSE 0

#define UART_OUTPUT
#ifdef UART_OUTPUT
char detect_type = 0;
#endif

/**************************************************************************
 * External Function
 **************************************************************************/
extern void debug_enable_box(int id, int en, int sx, int sy, int ex, int ey);
extern void debug_set_color(int color); // change word color black 0, white 255
extern void debug_enable_label(int id, int en, int value, int sx, int sy);
extern unsigned long intToBcd(int input);

/**************************************************************************
 * Function Declaration
 **************************************************************************/

/**************************************************************************
 * Global Data
 **************************************************************************/
static const char HOST_SECTION host_ver[] = "HOST-"__DATE__
                                            "-"__TIME__;

static TaskHandle_t xHandle_Win = NULL;
static TaskHandle_t xHandle_User = NULL;
static TaskHandle_t xHandle_Feature = NULL;
static TaskHandle_t xHandle_Result = NULL;

unsigned char detect_enable = FALSE;
unsigned long int win_flow = 0;
unsigned long int detected_flow = 0;
unsigned long int frame_id = 0;

u32 Sys_Tick = 0;

u8 task_init = FALSE;

/**************************************************************************
 * Function
 **************************************************************************/

/**
 * @brief Configures custom GPIO pins.
 *
 * This function sets up specific GPIO pins (IOA4, IOC5, IOC6) for output
 * with pull-up disabled and strength disabled.
 */
static void customer_gpio(void) {
    sys_set_padshare(IOA4, PAD_FUNC5, PAD_PULL_UP, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA4, GPIO_OUTPUT_DIRECTION);

    sys_set_padshare(IOC5, PAD_FUNC5, PAD_PULL_UP, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC5, GPIO_OUTPUT_DIRECTION);

    sys_set_padshare(IOC6, PAD_FUNC5, PAD_PULL_UP, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC6, GPIO_OUTPUT_DIRECTION);
}

/**
 * @brief Initializes the sensor and related modules.
 *
 * This function retrieves and logs NBSDK and AEG versions, then configures
 * sensor cropping or binning based on defined macros, and initializes
 * Auto Exposure Gain (AEG) settings.
 *
 * @return FALSE on successful setup, TRUE if crop mode is not set.
 */
static int sensor_setup(void) {
    uint8_t *pinfo = nb_malloc(64);
    ASSERT(pinfo);
    verNbsdkGet(pinfo);
    DEBUG(DEBUG_INFO, "NBSDK_VERSION:%s", pinfo);
    DEBUG(DEBUG_INFO, "Build @%s", host_ver);

#if (SENSOR_OUTPUT_SIZE == 160)
#ifdef CIS_BINNING
    CIS_bin2();
#elif defined ISP_BINNING
    crop_config_mode(1, 0, 1, 0);
    crop_enable(1, 1);
    debug_init();
    debug_enable(1);
    md_init(MD_AREA_FIXED);
    md_start();
#elif defined ISP_SKIP
    crop_config_mode(0, 1, 0, 1);
    crop_enable(1, 1);
    debug_init();
    debug_enable(1);
    md_init(MD_AREA_FIXED);
    md_start();
#else
    DEBUG(DEBUG_FATAL, "crop mode not set\n");
    return TRUE;
#endif
    md_fixed_set_bin_mode(5, 5);
#endif

    unsigned int aeg_ver_len;
    aeg_ver_len = sensor_aeg_get_version(pinfo, 64);

    if (aeg_ver_len > 0) {
        DEBUG(DEBUG_INFO, "AEG Version: %s", pinfo);
    } else {
        DEBUG(DEBUG_ERROR, "AEG Version is Error!!!");
    }
    nb_free(pinfo);
#if (AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM)
    sensor_aeg_custom_app_info_structure *app_info_str = (sensor_aeg_custom_app_info_structure *)nb_malloc(sizeof(sensor_aeg_custom_app_info_structure));
    app_info_str->adjust_strategy = AEG_LIGHT_DETECT_TYPE;
    app_info_str->frm_rate_max = AEG_FRAME_RATE_MODE_MAX;
    app_info_str->frm_rate_min = AEG_FRAME_RATE_MODE_MIN;
    app_info_str->lpm_opt = AEG_POWER_MANAGEMENT_MODE;
    app_info_str->light_level_max = AEG_LED_LIGHT_CTRL_MAX;
    app_info_str->light_level_min = AEG_LED_LIGHT_CTRL_MIN;
    app_info_str->ana_gain_max = AEG_ANALOG_GAIN_MAX;
    app_info_str->md_info_filter = AEG_MOTION_LOCATION_FILTER;
    app_info_str->dete_info_filter = AEG_DETECT_LOCATION_FILTER;
    app_info_str->test_mode_valid_flag = AEG_TEST_MODE_VALID_SUPPORT;
    app_info_str->valid_flag = AEG_CUSTOM_VALID_SUPPORT;
    sensor_aeg_update_custom_application_info(*app_info_str);
    nb_free(app_info_str);
#endif // #if (AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM )
    sensor_aeg_init(AEG_MODE, AEG_AC_POWER_FREQ, AEG_GAMMA_MODE);

    sensor_aeg_video_debug_label_enable(TRUE);

    return FALSE;
}

/**
 * @brief Initializes the detector modules.
 *
 * This function initializes the Feature Extraction, scaler, and various
 * detection modules (top, mid, bottom). It also initializes the base detection
 * and motion modules.
 */
static void detector_init(void) {
    /* Initialize FE (Feature Extraction) */
    if (fe_init(FE_MODE_FE, 3, 0)) {
        DEBUG(DEBUG_ERROR, "fe init fail");
    }
    fe_start();

    scaler_init(0);
    scaler_start();

    DEBUG(DEBUG_INFO, "Detection Version:%s", NB_Version);

    NB_Base_Init();

    User_Detect_Config_Init();
    NB_detect_buf_init();
    NB_detect_top_init();
    NB_detect_mid_init();
    NB_detect_bottom_init();

    NB_Motion_Init();

    return;
}

/**
 * @brief Main task loop for window processing.
 *
 * This task continuously waits for frame completion, updates the frame ID,
 * adjusts sensor brightness, and performs base action and motion detection
 * if detection is enabled and tasks are initialized.
 *
 * @param parameters Task parameters (unused).
 */
static void Win_Task(void *parameters) {
    sensor_setup();
    detector_init();

    u8 disable_motion = 0;
    u8 found_mode_exit = 0;

    for (;;) {
        if (detect_enable && task_init) {
            if (md_wait_for_frame_finish(0) == 0) { // True if in frame-end, else False. // Timeout in MS
                frame_id = debug_get_frame_id_hex();

#if AEG_SUPPORT
                sensor_aeg_brightness(AEG_BRIGHTNESS_TARGET_VAULE);
#endif

                if (NB_buf_state) {
                    NB_Base_Action_start(frame_id, disable_motion, found_mode_exit);

                    NB_detect_top_win(1, &detected_flow, &win_flow, frame_id);

                    // Get Motion
                    NB_Motion_Action(&detected_flow, frame_id);
                }
            }
        }
        vTaskDelay(TASK_DELAY_TIME);
    }

    vTaskDelete(NULL);
}

/**
 * @brief User task loop for custom actions based on detection.
 *
 * This task continuously checks for new detection results. If a detection
 * is found, it updates the AEG module with detection information and
 * controls GPIOs. It also sends detection or motion coordinates over UART
 * if `UART_OUTPUT` is defined.
 *
 * @param parameters Task parameters (unused).
 */
static void User_Task(void *parameters) {
    static int DetectW_T_old = 0;

    u32 now_tick = 0;

    detect_enable = TRUE; // Must wait the md_wait_for_frame_finish() before setting to TRUE

    for (;;) {
        if (task_init) {
            now_tick = xTaskGetTickCount();
            if (DetectW_T_old != NB_DetectW_T) {
                DetectW_T_old = NB_DetectW_T;

                // Handle different recognition scenarios
                if ((NB_Found->state == NB_Find_State_Find) || (NB_Found->state == NB_Find_State_Find_Follow)) {
#ifdef UART_OUTPUT
                    detect_type = 'F';
#endif

                    // Update recognition information to the internal AEG module
                    gpio_set_value(IOC6, 0);
                    gpio_set_value(IOC5, 0);
                    gpio_set_value(IOA4, 0);
                    NB_Model_Type_s dete_type = NB_MODEL_TYPE_OTHER;
                    int dete_score = NB_Found->score[NB_Found->get_group][NB_Found->get_level];
                    char aeg_dete_mode = MACR_AEG_APP_DETE_MODE_NONE;

                    // If directly recognized by the model, take data from Group; otherwise, extract data from Level (e.g., Follow)
                    dete_type = (NB_Found->state == NB_Find_State_Find) ? detect_model.group_type[NB_Found->get_group] : detect_model.group_type[NB_Found->get_level];

                    // Convert the current detection type to the detection mode defined by the AEG module
                    switch (dete_type) {
                        case NB_MODEL_TYPE_FACE:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_FACE;
                            break;
                        case NB_MODEL_TYPE_HEAD:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_HEAD;
                            break;
                        case NB_MODEL_TYPE_HEADADD:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_HEADADD;
                            break;
                        case NB_MODEL_TYPE_TORSO:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_TORSO;
                            break;
                        case NB_MODEL_TYPE_GESTURE_GIVE_ME_FIVE:
                        case NB_MODEL_TYPE_GESTURE_GOOD:
                        case NB_MODEL_TYPE_GESTURE_YE:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_GESTURE;
                            break;
                        default:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_UND_NREF;
                            break;
                    }

                    // Update recognition information to the internal AEG module
                    sensor_aeg_update_dete_info(aeg_dete_mode, NB_Found->get_id,
                                                NB_Found->x0, NB_Found->y0,
                                                NB_Found->w, NB_Found->h,
                                                dete_score);

#ifdef DEBUG_FOUND_DATA
                    // Update recognition data to this function
                    User_Debug_Found_Data_Updata();
#endif

                    debug_enable_box(NB_DEBUG_FOUND_BOX_ID,
                                     DEBUG_BOX_NUM_4_ENABLE,
                                     NB_Found->x, NB_Found->y,
                                     NB_Found->x + NB_Found->w, NB_Found->y + NB_Found->h);

                    NB_Found->state = NB_Find_State_No;
                }
            } else if (frame_id > NB_Found->get_id + 4) {
#ifdef UART_OUTPUT
                detect_type = '0';
#endif
                gpio_set_value(IOC6, 1);
                gpio_set_value(IOC5, 1);
                gpio_set_value(IOA4, 1);
            }

#ifdef UART_OUTPUT
            uart_putc('#');
            uart_putc(detect_type);

            // Coordinate
            static char coordinate_str[9]; // Reserve space for eight digits, and add a null terminator
            int x, y, w, h;

            if (detect_type != '0') {
                x = NB_Found->x / 10;
                y = NB_Found->y / 10;
                w = NB_Found->w / 10;
                h = NB_Found->h / 10;
            } else {
                if (NB_motion_rd.state == NB_Motion_State_Found && sensor_aeg_is_para_active_frame(frame_id) == 0) {
                    x = NB_motion_rd.x / 10;
                    y = NB_motion_rd.y / 10;
                    w = NB_motion_rd.w / 10;
                    h = NB_motion_rd.h / 10;
                } else {
                    x = 0;
                    y = 0;
                    w = 0;
                    h = 0;
                }
            }

            sprintf(coordinate_str, "%02d%02d%02d%02d", x, y, w, h);

            uart_putc('$');

            for (int i = 0; i < 9; i++) uart_putc(coordinate_str[i]);

            uart_putc('\n');

#endif

            // if (now_tick > Sys_Tick + 10000)
            // {
            //  Sys_Tick = now_tick;

            //  DEBUG(DEBUG_TRACE, "Run %lds PlanWin_T:%d FeW_T:%d DetectW_T:%d FoundW_T:%d",
            //       Sys_Tick / 1000, NB_PlanWin_T, NB_FeW_T, NB_DetectW_T, NB_FoundW_T);
            // }
        }
        vTaskDelay(TASK_DELAY_TIME);
    }
    vTaskDelete(NULL);
}

/**
 * @brief Task for processing detection results.
 *
 * This task continuously checks if the detection buffer is ready and
 * processes the top-level detection results.
 *
 * @param parameters Task parameters (unused).
 */
static void Result_Task(void *parameters) {
    u8 select = 0;

    for (;;) {
        if (detect_enable && task_init && NB_buf_state) {
            select = NB_detect_top_check_result();

            if (select) {
                // detect
                NB_detect_top(select - 1, &detected_flow, &win_flow, frame_id);
            }
        }

        vTaskDelay(TASK_DELAY_TIME);
    }

    vTaskDelete(NULL);
}

//////////////////////////////////////////////////////////////////
// Get Feature task loop
//////////////////////////////////////////////////////////////////
/**
 * @brief Task for extracting features from the detection buffer.
 *
 * This task continuously checks if the detection buffer is ready and
 * extracts features using `NB_detect_top_febuf()`.
 *
 * @param parameters Task parameters (unused).
 */
static void Feature_Task(void *parameters) {
    for (;;) {
        if (task_init) {
            NB_detect_top_febuf();
        }
        vTaskDelay(TASK_DELAY_TIME);
    }
    vTaskDelete(NULL);
}

/**
 * @brief Initializes the Win_Task.
 *
 * Creates and starts the `Win_Task` with a specified stack size and priority.
 */
static void winTaskInit(void) {
    BaseType_t xTask_Win;
    xTask_Win = xTaskCreate(
        Win_Task,
        "Win_Task",
        configMINIMAL_STACK_SIZE * 10,
        NULL,
        tskIDLE_PRIORITY + 5,
        &xHandle_Win);
    if (xTask_Win != pdPASS) {
        DEBUG(DEBUG_ERROR, "Win_Task is NULL!");
        exit(FALSE);
    }
}

/**
 * @brief Initializes the User_Task.
 *
 * Creates and starts the `User_Task` with a specified stack size and priority.
 */
static void userTaskInit(void) {
    BaseType_t xTask_User;
    xTask_User = xTaskCreate(
        User_Task,
        "User_Task",
        configMINIMAL_STACK_SIZE * 5,
        NULL,
        tskIDLE_PRIORITY + 5,
        &xHandle_User);
    if (xTask_User != pdPASS) {
        DEBUG(DEBUG_ERROR, "User_Task is NULL!");
        exit(FALSE);
    }
}

/**
 * @brief Initializes the Feature_Task.
 *
 * Creates and starts the `Feature_Task` with a specified stack size and priority.
 */
static void featureTaskInit(void) {
    BaseType_t xTask_Feature;
    xTask_Feature = xTaskCreate(
        Feature_Task,
        "Feature_Task",
        configMINIMAL_STACK_SIZE * 5,
        NULL,
        tskIDLE_PRIORITY + 5,
        &xHandle_Feature);
    if (xTask_Feature != pdPASS) {
        DEBUG(DEBUG_ERROR, "Feature_Task is NULL!");
        exit(FALSE);
    }
}

/**
 * @brief Initializes the Result_Task.
 *
 * Creates and starts the `Result_Task` with a specified stack size and priority.
 */
static void resultTaskInit(void) {
    BaseType_t xTask_Result;
    xTask_Result = xTaskCreate(
        Result_Task,
        "Result_Task",
        configMINIMAL_STACK_SIZE * 5,
        NULL,
        tskIDLE_PRIORITY + 5,
        &xHandle_Result);
    if (xTask_Result != pdPASS) {
        DEBUG(DEBUG_ERROR, "Result_Task is NULL!");
        exit(FALSE);
    }
}

/**
 * @brief Main entry point of the application.
 *
 * This function initializes basic configurations, sets up custom GPIOs (if
 * UART_OUTPUT is enabled), creates and starts all necessary FreeRTOS tasks
 * (Win_Task, Feature_Task, Result_Task, User_Task), and sets `task_init` to
 * TRUE to signal task readiness.
 *
 * @return 0 on successful execution.
 */
int main(void) {
    // SetDebugLevel(DEBUG_LEVEL, DETAIL_INFO_SUPPORT);

    struct Init_Config *BasicInitConfig = get_init_config();
    BasicInitConfig->BaudRate = UART_DEFAULT_BAUD_RATE_INDEX;
    BasicInitConfig->SPISpeed = FLASH_SPI_SPEED;
    BasicInitConfig->CISWorkFreq = SYS_WORK_FREQ;
    BasicInitConfig->SystemInfoDump = SYS_INFO_DUMP_SW;
    BasicInitConfig->IOPortingMode = IO_PORTING_MODE;
    BasicInitConfig->DebugMode = DEBUG_MODE;
    BasicInitConfig->BLCEnable = BLC_SW;
    InitializeBase(BasicInitConfig);
#ifdef UART_OUTPUT
    customer_gpio();
#endif
    winTaskInit();
    featureTaskInit();
    resultTaskInit();
    userTaskInit();

    task_init = TRUE;
    return 0;
}
