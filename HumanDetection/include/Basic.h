//******************************************************************************
// Copyright (C) 2022 NeuronBasic Co., Ltd. All rights reserved.
//
// File        : Basic.c
// Author      : SP, DK
// Creat Date  : 2022-03-07
// Last Update : 2022-11-02
// Version     : V1.6
// Description : Basic relevant features.
//               1. Bit calculation related
//                  a. Fixed-point. (Get754Field32, Get754Field64, Set754Field32, Set754Field64)
//                  b. Format transformation.(bin32, bin64, hex32, hex64)
//               2. Math calculation related.
//                  a. Exponentiation. (pow2)
//               3. PWM setting.
//                  a. PWM design by gpio.(softPWM, softPWM_EX)
//                  b. PWM design by hardware configuration.(HardPWM)
//               4. Initialize related.
//                  a. Initization.(InitializeBase)
//                  b. GPIO.(InitializeGpioPorting)
//               5. Debug related.
// Note        : Add parameter,
//               1. Level and Function token.
//               2. Return value and error code.(9000-9005)
//                           
// Known issues: 
//               1. Software pwm will keep into loop cause system hang.
//******************************************************************************
// ensure this library description is only included once
#ifndef Basic_h
#define Basic_h
#include "nbsdk.h"

#define HIGH        (1)
#define LOW         (0)

// Function token
// #define DISABLE      (0)
// #define ENABLE       (1)
#define FUNC_DISABLE (0)
#define FUNC_ENABLE  (1)

typedef enum { FALSE, TRUE } boolean;
#define Boolean boolean
#define VOID        void

// Return value and error code table.
typedef enum{
    FUNC_SUCCESS = 9000,          // Function success.
    FUNC_ERROR,                   // Function failed, and have some unexplained errors.
    FUNC_NULL_POINTER,            // The input parameter is NULL.
    FUNC_ILLEGAL_PARAM,           // Illegal argument value.
    FUNC_OUT_OF_RANGE,            // Argument value out of bounds.
    FUNC_MAX_STATUS               // It cannot be used as a return value status, it is only used for enumerating the most value.
}FUNC_STATUS;

// #define PERF_TIMER_US_CNT (system_clock()/2000000)

typedef unsigned uint;
typedef unsigned long long ull;

#define SUPPORT_SYS_80M     0
#define SUPPORT_SYS_96M     1  

typedef enum{
    BAUDRATE_9600 = 9600,
    BAUDRATE_19200 = 19200,
    BAUDRATE_115200 = 115200
}BAUDRATE_LIST;

struct softpwm_conf_t
{
    int gpio_no;
    uint16_t frequency;
    uint8_t duty_cycle;
    uint8_t val;
    TimerHandle_t tid;
};

struct softpwm_para_t
{
    struct softpwm_conf_t *conf;
};

typedef enum{
    DEFAULT_IO_MODE,
    CUSTOM_IO_MODE,
    GPIO_IO_MODE,
    CIS_IO_MODE
}IO_CONFIG;

/******************************************************************************/
/*                         Bit calculation related                            */
/******************************************************************************/
/**
 * @brief    Convert 32 bits float to IEEE754 fixed-point format.
 * 
 * @param    v            32-bit float value.
 * @param    sign         sign part.
 * @param    exp          exponent part.
 * @param    mat          mantissa part
 *
 * @return   Null
 * @note     Single-precision floating-point IEEE754 format (32bit)
 *            ___________________________________________
 *           |s(1)|  exponent(8)  |     mantissa(23)     |           
 *            ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ 
 */
void   Get754Field32(float v, uint* sign, uint* exp, uint* mat);

/**
 * @brief    Convert 64 bits float to IEEE754 fixed-point format.
 * 
 * @param    v            64-bit double value.
 * @param    sign         sign part.
 * @param    exp          exponent part.
 * @param    mat          mantissa part
 *
 * @return   Null
 * @note     Double-precision floating-point IEEE754 format (64bit)
 *            ___________________________________________________________
 *           |s(1)|     exponent(11)     |              mantissa(52)     |           
 *            ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 */
void   Get754Field64(double v, uint* sign, uint* exp, ull* mat);

/**
 * @brief    Convert IEEE754 fixed-point format to 32 bits float value.
 * 
 * @param    sign         sign part.
 * @param    exp          exponent part.
 * @param    mat          mantissa part
 *
 * @return   value        float value.
 * @note     
 */
float  Set754Field32(uint sign, uint exp, uint mat);

/**
 * @brief    Convert IEEE754 fixed-point format to 64 bits float value.
 * 
 * @param    sign         sign part.
 * @param    exp          exponent part.
 * @param    mat          mantissa part
 *
 * @return   value        double value.
 * @note     
 */
double Set754Field64(uint sign, uint exp, ull  mat);

/**
 * @brief    Display 32 bits data by binary format.
 * 
 * @param    v            float value.
 *
 * @return   value        binary value.
 * @note     
 */
void bin32(void* v);

/**
 * @brief    Display 64 bits data by binary format.
 * 
 * @param    v            double value.
 *
 * @return   value        binary value.
 * @note     
 */
void bin64(void* v);

/**
 * @brief    Display 32 bits data in hexadecimal format.
 * 
 * @param    v            float value.
 *
 * @return   value        hexadecimal value.
 * @note     
 */
void hex32(void* v);

/**
 * @brief    Display 64 bits data in hexadecimal format
 * 
 * @param    v            double value.
 *
 * @return   value        hexadecimal value.
 * @note     
 */
void hex64(void* v);

/******************************************************************************/
/*                         Math calculation related                           */
/******************************************************************************/
/**
 * @brief    Implement the Exponential function and precision supports up to six decimal places.
 * 
 * @param    base         Base.
 * @param    exp          Exponential.
 * @return   value                      Calculated result.
 * @note     a^b
 */
double pow2(double base,double exp);

/******************************************************************************/
/*                         CIS related                                        */
/******************************************************************************/
//BASIC_DK_004+++>>>
/**
 * @brief       Enable cis bin2.
 * @return		
 */
void CIS_bin2(void);

/******************************************************************************/
/*                         ISP related                                        */
/******************************************************************************/
/**
 * @brief    black level calibration
 * @param    blc_ctrl_flag   1 enable/ 0 disable 
 * @note     Enable: Calibrate from 16 to 5; Disable : Set as zero;
 */
void blc_ctrl(char blc_ctrl_flag);

/**
 * @brief      Get BLC value.
 * @return	   BLC value.
 */
unsigned int blc_get_value(void);


/******************************************************************************/
/*                              PWM related                                   */
/******************************************************************************/
// #define FREQ_100M_HZ          (0)  //freq : 100mHz
// #define FREQ_1_HZ             (1)  //freq : 1Hz
// #define FREQ_10_HZ            (2)  //freq : 10Hz
// #define FREQ_100_HZ           (3)  //freq : 100Hz
// #define FREQ_200_HZ           (4)  //freq : 200Hz
// #define FREQ_500_HZ           (5)  //freq : 500Hz
// #define FREQ_1000_HZ          (6)  //freq : 1kHz

// PWM group number.
typedef enum{
    PWM_Group_0,
    PWM_Group_1,
    PWM_Group_2,
    PWM_Group_3,
    PWM_Group_4,
    PWM_Group_5,
    PWM_Group_6,
    PWM_Group_7
}PWM_GROUP;

/**
 * @brief    Set PWM signal wave(frequency range : 1 ~ 100Hz) and the gpio direction has been set inside the program, user does not need to set it again.
 * 
 * @param    pin          GPIO pin.
 * @param    duty_cycle   A duty cycle or power cycle is the fraction of one period in which a signal or system is active.
 *                        Duty cycle is commonly expressed as a percentage(%).
 *                        It should set in multiples of 10, like 0%, 10%, 20%,...,50%,...,90%,100%.
 * @param    frequency    1~100Hz
 *
 * @note     Produce by freeRtos timer (1kHz)
 */
void softPWM(int pin, int duty_cycle, int frequency);

/**
 * @brief    Trigger hardware PWM function.(Suggest frequency range : 2K - 10M)
 * 
 * @param    pin            GPIO pin.
 * @param    frequency      Pwm frequency.(uint : k)
 * @param    duty_cycle     A duty cycle or power cycle is the fraction of one period in which a signal or system is active.
 *                          Duty cycle is commonly expressed as a percentage(%).(uint : %)
 * @param    drive_strength 0 : 8mA, 1: 12mA
 * 
 * @return   NULL                      Function success.
 * @return   FUNC_ERROR                Error pin, the pin dosen't support pwm function.
 * @note     This API will set the pin to "pwm" function automatically.
 */
int HardPWM(uint8_t pin, int frequency, int duty_cycle, int drive_strength);


/******************************************************************************/
/*                            Initialize related                              */
/******************************************************************************/
//BASIC_SP_022+++>>
struct Init_Config{
    u_int8_t      IOPortingMode;
    u_int32_t     BaudRate;
    u_int32_t     SPISpeed;
    Boolean       CISWorkFreq;
    Boolean       SystemInfoDump;
    Boolean       DebugMode;
    Boolean       BLCEnable;    
}__attribute__((aligned(4),packed));

struct Init_Config *get_init_config(void);
//BASIC_SP_022+++<<
//BASIC_SP_023+++>>
typedef enum{
    FREQ_5MHZ   = 5000000,
    FREQ_10MHZ  = 10000000,
    FREQ_20MHZ  = 20000000,
    FREQ_40MHZ  = 40000000,
    FREQ_50MHZ  = 50000000,
    FREQ_60MHZ  = 60000000,
    FREQ_80MHZ  = 80000000,
    FREQ_120MHZ = 120000000
}SPI_SPEED_LIST;
//BASIC_SP_023+++<<
//BASIC_SP_022***>>
/**
 * @brief    NB1001 bootup initialize program.
 * 
 * @param    Init_Config          Initilization Configuration.
 *                                BaudRate -> Serial baudrate.
 *                                - BAUDRATE_9600
 *                                - BAUDRATE_19200
 *                                - BAUDRATE_115200
 *                                Maximum speed table of the flash,
 *                                FREQ_40MHZ - ZB25VQ16, ZB25VQ64.
 *                                FREQ_50MHZ - W25Q32JV, W25Q80DV, W25Q16JV, W25Q32JW, W25Q16DW, N25Q256A
 *                                FREQ_60MHZ - GD25Q16C, GD25Q32C
 *                                FREQ_80MHZ - GD25Q80C, XT25F16B
 *                                FREQ_120MHZ - GD25Q64C
 *                                CIS_WORK_FREQ -> Sensor work frequency.          
 *                                - SUPPORT_SYS_96M
 *                                - SUPPORT_SYS_80M
 *                                SystemInfoDump -> Dump more system information swtich.
 *                                - Enable
 *                                - Disable
 *                                IOPortingMode -> IO-Mode select.
 *                                - DEFAULT_IO_MODE
 *                                - CUSTOM_IO_MODE
 *                                - GPIO_IO_MODE
 *                                - CIS_IO_MODE
 *                                DebugMode -> Debug mode switch.
 *                                - Enable
 *                                - Disable
 *                                BLCEnable -> BLC swtich.
 *                                - Enable
 *                                - Disable
 *                              
 * @return   NULL                 Function success.
 * @note     Initialize the function include bsp_init_core(), bsp_init_clock(), bsp_enable_pclk(), system_config_stack(),
 *           sf_init(), sf_config_speed(), internal_sensor_init(), internal_sensor_config(), 
 *           PMU, CIS_TOP, CIS_DIGI, SYS_CTRL fixed issue,
 *           Image flip, sensor_mem_init(), crop_init(), debug_init(), debug_enable(), 
 *           md_init(), internal_sensor_output_enable().
 */
VOID InitializeBase( struct Init_Config * );
/**
 * @brief     GPIO initialization settings table.
 * 
 * @param[in] IOPortingMode IO-Mode select.
 *                          - DEFAULT_IO_MODE
 *                          - CUSTOM_IO_MODE
 *                          - GPIO_IO_MODE
 *                          - CIS_IO_MODE
 * @param[in] DebugMode     Debug mode switch.
 *                          - Enable
 *                          - Disable    
 * @return    NULL     
 * @note      I2C1 - IOA3, IOA4 ;; UART - IOA5, IOA6 ;; SPI - IOB1-6 ;; PWM - IOA7, IOC3, IOC6 ;;
 *            GPIO KEY - IOB7   ;; DMIC - IOC0-2     ;; I2C0 - IOC4, IOC5
 */
VOID InitializeGpioPorting(uint8_t IOPortingMode, Boolean DebugMode);
//BASIC_SP_022***<<
/******************************************************************************/
/*                               Debug related                                */
/******************************************************************************/
#define DEBUG     	 debug_print
#define DEBUG_EX     debug_print_EX
typedef enum
{
    DEBUG_ALL = 0,
    DEBUG_FATAL,
    DEBUG_ERROR,
    DEBUG_WARNING,
    DEBUG_INFO,
    DEBUG_TRACE,
    DEBUG_OFF
}DEBUG_LEVEL;
/**
 * @brief    Set the debug message level to show with UART.
 * 
 * @param    Debug_Level		  Debug message level.
 *                                -	DEBUG_ALL : Show all debug message.
 *                                -	DEBUG_FATAL : Very severe error events that will presumably lead the application to abort.
 *                                -	DEBUG_ERROR : error event that might still allow the application to continue running.
 *                                -	DEBUG_WARNING : potentially harmful situations.
 *                                -	DEBUG_INFO : informational messages that highlight the progress of the application at coarse-grained level.
 *                                -	DEBUG_TRACE : fin-grained informational events that are most useful to debug an application.
 *                                -	DEBUG_OFF : Close all debug message.   
 * @param    Debug_Info_Level     The level of detail of the debug message.
 *                                - ENABLE : Enbale detail message, [Time] @File [Function] line : [DEBUG_LEVEL]...
 *                                - DISABLE : Disable detail message, [DEBUG_LEVEL]...
 * @return   NULL     
 * @note     
 */
VOID SetDebugLevel(const unsigned char Debug_Level, boolean Debug_Info_Level);

/**
 * @brief    Print debug messages for the specified level.
 * 
 * @param    Debug_Level		  Debug message level.
 *                                -	DEBUG_ALL : Show all debug message.
 *                                -	DEBUG_FATAL : Very severe error events that will presumably lead the application to abort.
 *                                -	DEBUG_ERROR : error event that might still allow the application to continue running.
 *                                -	DEBUG_WARNING : potentially harmful situations.
 *                                -	DEBUG_INFO : informational messages that highlight the progress of the application at coarse-grained level.
 *                                -	DEBUG_TRACE : fin-grained informational events that are most useful to debug an application.
 *                                -	DEBUG_OFF : Close all debug message.   
 * @param    Format		          Debug message.
 *
 * @return   NULL     
 * @note     Please use "DEBUG(Debug_Level, *Format)" replace this function.
 */
VOID debug_print(const unsigned char Debug_Level, const char *Format, ...);

/**
 * @brief    Print debug messages for the specified level, and include timer, file location, function name and code line number.
 * 
 * @param    Debug_Level		  Debug message level.
 *                                -	DEBUG_ALL : Show all debug message.
 *                                -	DEBUG_FATAL : Very severe error events that will presumably lead the application to abort.
 *                                -	DEBUG_ERROR : error event that might still allow the application to continue running.
 *                                -	DEBUG_WARNING : potentially harmful situations.
 *                                -	DEBUG_INFO : informational messages that highlight the progress of the application at coarse-grained level.
 *                                -	DEBUG_TRACE : fin-grained informational events that are most useful to debug an application.
 *                                -	DEBUG_OFF : Close all debug message.   
 * @param    time                 __TIME__
 * @param    file                 __FILE__
 * @param    function             __FUNCTION__
 * @param    line                 __LINE__
 * @param    Format		          Debug message.
 *
 * @return   NULL     
 * @note     Please use "DEBUG_EX(Debug_Level,__TIME__,__FILE__,__FUNCTION__,__LINE__, *Format)" replace this function.
 */
VOID debug_print_EX(const unsigned char Debug_Level,char time[], char file[], char function[], int line, const char *Format, ...);

/**
 * @brief    Print debug messages for the current task list.
 * 
 * @param    NULL
 *
 * @return   NULL     
 * @note     
 */
VOID debug_task(VOID);

/**
 * @brief    Print the image row data at specified frame by UART interface.
 * 
 * @param    frame_num            Specified frame.
 * @return   NULL     
 * @note     
 */
VOID debug_image_uart(uint frame_num);
#endif //#ifndef Basic_h
