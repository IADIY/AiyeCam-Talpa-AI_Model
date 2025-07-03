/*------------------------------------------------------------------------------------------------*/
/* */
/* Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                                  */
/* */
/*------------------------------------------------------------------------------------------------*/
#include "User_Config.h"
#include "nb_motion.h"
#include "nbsdk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Token.h"
#include "include/Basic.h"
#include "include/sensor_aeg.h"



/**************************************************************************
 * Constants
 **************************************************************************/

#define TASK_DELAY_TIME 2
/**************************************************************************
 * External Function
 **************************************************************************/
;
extern void debug_init(void);
extern void debug_enable(int enable);
extern void debug_enable_box(int id, int en, int sx, int sy, int ex, int ey);
extern void debug_enable_frame_bcd(int en, int sx, int sy);
extern void debug_set_color(int color); // change word color black 0, white 255
extern void debug_enable_label(int id, int en, int value, int sx, int sy);
extern unsigned long intToBcd(int input);
extern void md_local_set_range(int bins, int thr);

size_t xPortGetFreeHeapSize(void);

/**************************************************************************
 * Function Declaration
 **************************************************************************/
void customer_gpio(void);

TaskHandle_t xHandle_Win = NULL;
TaskHandle_t xHandle_User = NULL;
TaskHandle_t xHandle_Feature = NULL;
TaskHandle_t xHandle_Result = NULL;
TaskHandle_t xHandle_SystemControl = NULL;


/* Functions/variables defined outside, use extern to extend visibility */
// extern unsigned long intToBcd(int input);

/* Structs & Enums */

/* Global Variables */

unsigned long int win_flow = 0;
unsigned long int detected_flow = 0;
unsigned long int frame_id = 0;

u32 Sys_Tick = 0;

u8 task_init = FALSE;


#define UART_OUTPUT
#ifdef UART_OUTPUT
 char detect_type = 0;

#endif


/**
 * @brief Configures custom GPIO pins.
 *
 * This function sets up specific GPIO pins (IOA4, IOC5, IOC6) for output
 * with pull-up disabled and strength disabled.
 */
void customer_gpio() {
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
 * This function configures the SPI flash speed and mode, sets up sensor
 * cropping or binning based on defined macros, initializes debug features,
 * motion detection, and Auto Exposure Gain (AEG) settings.
 *
 * @return FALSE on successful setup, TRUE if crop mode is not set.
 */
static int sensor_setup(void) {

    /* Configure access speed: 20M */
    sf_config_speed(12000000);
    sf_config_mode(QSPI_MODE_STD);

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

    sensor_aeg_video_debug_label_enable(FALSE);

    md_local_set_range(1023, 30 * 4);

    debug_set_color(200);


    // audio_play_init(DEV_PWM, IOC6); //IOC6

    return FALSE;
}


/**
 * @brief Initializes the detector modules.
 *
 * This function initializes the Feature Extraction, scaler, and various
 * detection modules. It also allocates a buffer
 * for the model.
 */
static void detector_init(void) {

    /* Initialize FE */
    if (fe_init(FE_MODE_FE, 3, 0)) {
        DEBUG(DEBUG_ERROR, "fe init fail");
    }
    fe_start();

    scaler_init(0);
    scaler_start();

    /*************************************************/
    // Configure the project used
    User_Detect_Project_Config();
    User_Detect_Config_Init();

    // Allocate the full large buffer
    NB__model.lv_buf_temp = NULL;
    NB__model.lv_buf_temp = nb_malloc(MAX_MODEL_BUF);
    if (NB__model.lv_buf_temp == NULL) {
        // printf("--**---***___ERR nb_malloc %d NB__model.lv_buf_temp fail \n",
        //              MAX_MODEL_BUF);
    }

    // Initialize
    NB__Base_Init();
    NB__Motion_Init();
    NB__detect_top_init();
    NB__detect_mid_init();
    NB__detect_bottom_init();
    User_Detect_Buf_Init();


    return;
}


////////////////////////////////////////////////////////////////
// Motion_AEC & Set_Win task loop
//////////////////////////////////////////////////////////////////
/**
 * @brief Main task for window processing and motion/AEG handling.
 *
 * This task continuously waits for frame completion, updates frame ID,
 * adjusts sensor brightness based on frame ID, handles debug labels,
 * performs motion detection, and processes detection buffers.
 *
 * @param parameters Task parameters (unused).
 */
static void Win_Task(void *parameters) {

    u8 motor_run = 0;

    sensor_setup();
    detector_init();



    for (;;) {
        if (task_init) {
            // End of each frame
            if (md_wait_for_frame_finish(80) == 0) { // True if in frame-end, else False. // Timeout in MS

                frame_id = debug_get_frame_id_hex();

#if AEG_SUPPORT
                // Adjust sensor brightness based on frame ID
                if (frame_id < 100) sensor_aeg_brightness(AEG_BRIGHTNESS_TARGET_VAULE + 20);
                else sensor_aeg_brightness(AEG_BRIGHTNESS_TARGET_VAULE);
#endif

                /* Label */
                static int num = 0, label_regionVal = 0, regionVal = 0;
                get_global_area();
                get_partial_area_ave(0, 8, 0, 8, &num, &label_regionVal, &regionVal);
                if (label_regionVal > 150) {
                    debug_set_color(50);
                } else {
                    debug_set_color(200);
                }

                User_Detect_Buf_UnInit_Action();

                // Get Motion
                NB__Motion_Action(&detected_flow, frame_id);
                NB__Base_Action_start(frame_id, motor_run);

                // Buffer ready
                if ((NB__detect_buf_state == 1) && (NB__detect_buf_stop_wait <= 2)) {
                    // printf("win......\n");
                    NB__detect_top_win(1, &detected_flow, &win_flow, frame_id);
                }
            }
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
    // mdelay(1000);

    for (;;) {
        // Buffer ready
        if (task_init && NB__detect_buf_state) {
            select = NB__detect_top_check_result();
            if (select) {
                // printf("select:%d \n",select);
                //  detect
                NB__detect_top(select - 1, &detected_flow, &win_flow, frame_id);
            }
            // vTaskDelay(TASK_DELAY_TIME);

        } else {
            vTaskDelay(TASK_DELAY_TIME);
        }
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
 * extracts features using `NB__detect_top_febuf()`.
 *
 * @param parameters Task parameters (unused).
 */
static void Feature_Task(void *parameters) {
    for (;;) {
        if (task_init) {
            if ((NB__detect_buf_state == 1) && (NB__detect_buf_stop_wait <= 1)) {
                NB__detect_top_febuf();
                if (NB__detect_buf_stop_wait == 1) {
                    NB__detect_buf_stop_wait = 2;
                }
            }
            // vTaskDelay(TASK_DELAY_TIME);
        } else {
            vTaskDelay(TASK_DELAY_TIME);
        }
    }
    vTaskDelete(NULL);
}

//////////////////////////////////////////////////////////////////
// For customers to respond to detection of face/body/etc...
//////////////////////////////////////////////////////////////////
u8 task_user_delay = 10;
/**
 * @brief User task for handling detection and motion events.
 *
 * This task monitors frame ID changes, processes motion detection,
 * updates debug boxes and labels, and sends detection/motion coordinates
 * over UART if `UART_OUTPUT` is defined. It also updates AEG module
 * with detection information.
 *
 * @param parameters Task parameters (unused).
 */
static void User_Task(void *parameters) {

    static int DetectW_T_old = 0;

    // Detection
    _Bool detect_state = FALSE;
    unsigned long long int last_det_sec = 0l;
    unsigned int target_y = 0;
    unsigned int detect_cnt = 0;

    unsigned long long int pre_frame_id = 0l, now_sec = 0l;

    // Motion
#define MD_BUF_SIZE 30
    unsigned long long int md_last_sec = 0l;
    unsigned int md_buf[MD_BUF_SIZE] = {0}, p = -1, md_x = 0, md_y = 0, md_w = 0, md_h = 0;
    _Bool md_flag = FALSE, md_buf_ready = FALSE;
    unsigned int motion_cnt = 0, stable_cnt = 0;



    for (;;) {
        if (task_init) {
            now_sec = xTaskGetTickCount() / 1000;

            if (pre_frame_id != frame_id) {
                pre_frame_id = frame_id;

                // Motion
                // If not AEG active frame
                if (sensor_aeg_is_para_active_frame(frame_id) == FALSE) {
                    md_flag = md_wait_for_motion(5) == 0 ? TRUE : FALSE;
                    if (md_flag) {
                        md_get_motion_area(&md_x, &md_y, &md_w, &md_h);

                        if (md_w + md_h > 200 && md_w + md_h < 600) { // ignore small motion
                            p = (p + 1) % MD_BUF_SIZE;
                            if (!md_buf_ready && p == MD_BUF_SIZE - 1) md_buf_ready = TRUE;

                            md_buf[p] = md_y;
                            md_last_sec = now_sec;

                        } else {
                            md_flag = FALSE;
                        }

                        debug_enable_box(1, 1, md_x, md_y,
                                         (md_x + md_w), (md_y + md_h));
                    } else {
                        debug_enable_box(1, 0, md_x, md_y,
                                         (md_x + md_w), (md_y + md_h));
                    }
                } else {
                    md_flag = FALSE;
                }


#ifdef UART_OUTPUT
                uart_putc('#');
                uart_putc(detect_type);

                // Coordinate
                static char coordinate_str[9]; // Reserve space for eight digits, and add a null terminator
                int x, y, w, h;

                if (detect_type != '0') {
                    x = NB__Found->result_x / 10;
                    y = NB__Found->result_y / 10;
                    w = NB__Found->result_w / 10;
                    h = NB__Found->result_h / 10;
                } else {
                    if (md_flag) {
                        x = md_x / 10;
                        y = md_y / 10;
                        w = md_w / 10;
                        h = md_h / 10;
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

            } // end if(pre_frame_id != frame_id)


            debug_enable_label(0, 1, intToBcd(now_sec), 5, 5);

            debug_enable_label(2, 1, intToBcd(md_buf_ready * 1e7 + abs(md_buf[p] - md_buf[(p + 1) % MD_BUF_SIZE])), 5, 25);
            debug_enable_label(3, 1, intToBcd(motion_cnt), 5, 35);
            debug_enable_label(4, 1, intToBcd(detect_cnt), 5, 45);


            // If a recognition operation has occurred
            if (DetectW_T_old != NB__DetectW_T) {

                DetectW_T_old = NB__DetectW_T;

                // If recognized
                if (NB__Found->state != NB__Find_State_No) {

#ifdef UART_OUTPUT
                    detect_type = 'H';
#endif


                    // debug_enable_label(0, 1, intToBcd(-1), 5, 5);
                    debug_enable_box(4, 1,
                                     NB__Found->result_x,
                                     NB__Found->result_y,
                                     NB__Found->result_x + NB__Found->result_w,
                                     NB__Found->result_y + NB__Found->result_h);

                    // Update recognition information to the internal AEG module

                    static char dete_type = NB_MODEL_TYPE_END, aeg_dete_mode = MACR_AEG_APP_DETE_MODE_NONE;
                    static int dete_score = 0;

                    // If directly recognized by the model, take data from Group; otherwise, extract data from Level (e.g., Follow)
                    dete_type = (NB__Found->state == NB__Find_State_Find) ? NB__model.group_type[NB__Found->result_m_g] : NB__model.group_type[NB__Found->result_m_l];
                    dete_score = NB__Found->result_score;
                    aeg_dete_mode = MACR_AEG_APP_DETE_MODE_NONE;

                    // Convert the current detection type to the detection mode defined by the AEG module
                    switch (dete_type) {

                        case NB_MODEL_TYPE_HEAD:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_HEAD;
                            break;
                        case NB_MODEL_TYPE_HEADADD:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_HEADADD;
                            break;
                        case NB_MODEL_TYPE_TORSO:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_TORSO;
                            break;

                        default:
                            aeg_dete_mode = MACR_AEG_APP_DETE_MODE_UND_NREF;
                            break;
                    }

                    sensor_aeg_update_dete_info(aeg_dete_mode, NB__Found->result_get_id,
                                                NB__Found->result_x, NB__Found->result_y,
                                                NB__Found->result_w, NB__Found->result_h,
                                                dete_score);

                    NB__Found->state = NB__Find_State_No;

                } else if (frame_id > NB__Found->result_get_id + 2) {

#ifdef UART_OUTPUT
                    detect_type = '0';
#endif
                    debug_enable_box(4, 0,
                                     NB__Found->result_x,
                                     NB__Found->result_y,
                                     NB__Found->result_x + NB__Found->result_w,
                                     NB__Found->result_y + NB__Found->result_h);
                }

            }


            vTaskDelay(task_user_delay);
        } else {
            vTaskDelay(task_user_delay);
        }
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
    xTask_Win = xTaskCreate(Win_Task, "Win_Task",
                             configMINIMAL_STACK_SIZE * 2, // 8
                             NULL,
                             tskIDLE_PRIORITY + 9, // 5
                             &xHandle_Win);
    if (xTask_Win != pdPASS) {
        DEBUG(DEBUG_ERROR, "Win_Task is NULL!\n");
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
    xTask_User = xTaskCreate(User_Task, "User_Task", configMINIMAL_STACK_SIZE * 2,
                              NULL, tskIDLE_PRIORITY + 10, &xHandle_User);
    if (xTask_User != pdPASS) {
        DEBUG(DEBUG_ERROR, "User_Task is NULL!\n");
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
    xTask_Feature = xTaskCreate(Feature_Task, "Feature_Task",
                                 configMINIMAL_STACK_SIZE * 2, // 5
                                 NULL,
                                 tskIDLE_PRIORITY + 8, // 3 //5
                                 &xHandle_Feature);
    if (xTask_Feature != pdPASS) {
        DEBUG(DEBUG_ERROR, "Feature_Task is NULL!\n");
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
    xTask_Result =
        xTaskCreate(Result_Task, "Result_Task", configMINIMAL_STACK_SIZE * 2,
                    NULL, tskIDLE_PRIORITY + 6, &xHandle_Result);
    if (xTask_Result != pdPASS) {
        DEBUG(DEBUG_ERROR, "Result_Task is NULL!\n");
        exit(FALSE);
    }
}


/**
 * @brief Main entry point of the application.
 *
 * This function sets the debug level, initializes basic configurations,
 * sets up custom GPIOs (if UART_OUTPUT is enabled), creates and starts
 * all necessary FreeRTOS tasks (Win_Task, Feature_Task, User_Task, Result_Task),
 * and sets `task_init` to TRUE to signal task readiness.
 *
 * @return 0 on successful execution.
 */
int main(void) {

    SetDebugLevel(DEBUG_LEVEL, DETAIL_INFO_SUPPORT);

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
    userTaskInit();
    resultTaskInit();
    task_init = TRUE;

    return 0;
}
