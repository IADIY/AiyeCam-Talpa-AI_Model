AEG_SUPPORT//*************************************************************************
//*************************************************************************
//**                                                                     **
//**         (C)Copyright 2022, NeuronBasic Technology, Inc.             **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**             3120 Scott, Santa Clara, CA 95054, USA                  **
//**  No.371,Section 1,Guangfu Road.,East District Hsinchu City, Taiwan  **
//**                                                                     **
//**                       Phone: (03)-666-0188                          **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//******************************************************************************
// Copyright (C) 2022 NeuronBasic Co., Ltd. All rights reserved.
// File        : Token.h
// Author      : SP
// Creat Date  : 2022-08-22
// Last Update : 2022-09-01
// Version     : V1.6
// Dependency  : Module    version 
//                AEG        3.2
//               BASIC       1.6
//               
//******************************************************************************
#include "include/Basic.h"

/** 
 * TOKEN
 * @TokenName	PROJECT_SUPPORT 
 * @Range		[0 - AE_PureCode], 1 - FAE Detect Base Code.
 * @Help		Main switch to enable Custom Project.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  AE_PureCode version up than 4.0.
 */
#define PROJECT_SUPPORT				    AE_PureCode

// @END

/**
 * TOKEN
 * @Help		Project firmware image naming.
 * @TokenType   Expression
 * @Master		Yes
 * @Dependency  NULL
 */
#define PROJECT_TAG                     "human_detection_uart"

// @END

/**
 * TOKEN
 * @Help		Project firmware image major version(0, 1, 2, ...).
 * @TokenType   Expression
 * @Master		Yes
 * @Dependency  NULL
 */
#define PROJECT_MAJOR_VERSION           "1"

// @END

/**
 * TOKEN
 * @Help		Project firmware image minor version(01, 02, 03, ...).
 * @TokenType   Expression
 * @Master		Yes
 * @Dependency  NULL
 */
#define PROJECT_MINOR_VERSION           "1"

// @END

/**
 * TOKEN
 * @Help		Project firmware image test version(a, b, c,...).
 * @TokenType   Expression
 * @Master		Yes
 * @Dependency  NULL
 */
#define PROJECT_TEST_VERSION            "0a"

// @END

/******************************************************************************/
/*                                Init related                                */
/******************************************************************************/
/**
 * TOKEN
 * @TokenName	UART_DEFAULT_BAUD_RATE_INDEX 
 * @Range		9600 - BAUDRATE_9600, 19200 - BAUDRATE_19200, [115200 - BAUDRATE_115200]
 * @Help		Baud rate setting for the UART serial console port in bits per second (bps).
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  NULL
 */
#ifdef  UART_DEFAULT_BAUD_RATE_INDEX
#undef  UART_DEFAULT_BAUD_RATE_INDEX
#endif
#define UART_DEFAULT_BAUD_RATE_INDEX    BAUDRATE_115200

// @END

/**
 * TOKEN
 * @TokenName	FLASH_SPI_SPEED 
 * @Range		FREQ_5MHZ, [FREQ_10MHZ], FREQ_20MHZ, FREQ_40MHZ, FREQ_50MHZ, FREQ_60MHZ, FREQ_80MHZ, FREQ_120MHZ
 * @Help		Set the flash read data instruction speed.
 *              Maximum speed table of the flash,
 *              FREQ_40MHZ - ZB25VQ16, ZB25VQ64.
 *              FREQ_50MHZ - W25Q32JV, W25Q80DV, W25Q16JV, W25Q32JW, W25Q16DW, N25Q256A
 *              FREQ_60MHZ - GD25Q16C, GD25Q32C
 *              FREQ_80MHZ - GD25Q80C, XT25F16B
 *              FREQ_120MHZ - GD25Q64C
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  NULL
 */
#ifdef  FLASH_SPI_SPEED
#undef  FLASH_SPI_SPEED
#endif
#define FLASH_SPI_SPEED    FREQ_10MHZ

// @END

/**
 * TOKEN
 * @TokenName	SYS_WORK_FREQ 
 * @Range		0 - SUPPORT_SYS_80M, [1 - SUPPORT_SYS_96M]
 * @Help		System work frequency.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  NULL
 */
#ifdef  SYS_WORK_FREQ
#undef  SYS_WORK_FREQ
#endif
#define SYS_WORK_FREQ				    SUPPORT_SYS_96M

// @END

/**
 * TOKEN
 * @TokenName	SYS_INFO_DUMP_SW 
 * @Range		0 - DISABLE, [1 - ENABLE]
 * @Help		Dump more system information switch.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  NULL
 */
#ifdef  SYS_INFO_DUMP_SW
#undef  SYS_INFO_DUMP_SW
#endif
#define SYS_INFO_DUMP_SW			    ENABLE

// @END

/**
 * TOKEN
 * @TokenName	IO_PORTING_MODE 
 * @Range		[0 - DEFAULT_IO_MODE], 1 - CUSTOM_IO_MODE, 2 - GPIO_IO_MODE, 3 - CIS_IO_MODE
 * @Help		IO-mode configuration setting.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  NULL
 */
#ifdef  IO_PORTING_MODE
#undef  IO_PORTING_MODE
#endif
#define IO_PORTING_MODE				    CIS_IO_MODE

// @END

/**
 * TOKEN
 * @TokenName	BLC_SW 
 * @Range		[0 - DISABLE], 1 - ENABLE
 * @Help		BLC switch.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  NULL
 */
#ifdef  BLC_SW
#undef  BLC_SW
#endif
#define BLC_SW						    DISABLE

// @END

/******************************************************************************/
/*                               Debug related                                */
/******************************************************************************/
/**
 * TOKEN
 * @TokenName	DEBUG_MODE 
 * @Range		[0 - DISABLE], 1 - ENABLE
 * @Help		System debug mode enable token.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  NULL
 */
#ifdef  DEBUG_MODE
#undef  DEBUG_MODE
#endif
#define DEBUG_MODE  ENABLE

// @END

/**
 * TOKEN
 * @TokenName	DEBUG_LEVEL 
 * @Range		0 - DEBUG_ALL, 1 - DEBUG_FATAL, 2 - DEBUG_ERROR, 3 - DEBUG_WARNING, 4 - DEBUG_INFO, [5 - DEBUG_TRACE], 6 - DEBUG_OFF.
 * @Help		Show the level of debug message, and printf would invalid when DEBUG_OFF setting.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  NULL
 */
#define DEBUG_LEVEL					    DEBUG_OFF

// @END

/**
 * TOKEN
 * @TokenName	DETAIL_INFO_SUPPORT 
 * @Range		[0 - DISABLE], 1 - ENABLE
 * @Help		Show the debug message detail info like time, file, function, lines.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  NULL
 */
#define DETAIL_INFO_SUPPORT			    DISABLE

// @END

/**
 * TOKEN
 * @TokenName	DEBUG_BOX_TOTAL_ENABLE 
 * @Range		[0 - DISABLE], 1 - ENABLE
 * @Help		Enable debug boxes.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  NULL
 */
#define DEBUG_BOX_TOTAL_ENABLE		    DISABLE

// @END

/**
 * TOKEN
 * @TokenName	DEBUG_BOX_NUM_0_ENABLE 
 * @Range		0 - DISABLE, [1 - ENABLE]
 * @Help		Enable the debug box no.0.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  DEBUG_BOX_TOTAL_ENABLE = ENABLE
 */
#if DEBUG_BOX_TOTAL_ENABLE == ENABLE

#define DEBUG_BOX_NUM_0_ENABLE		    ENABLE

#endif //#if DEBUG_BOX_TOTAL_ENABLE == ENABLE
// @END

/**
 * TOKEN
 * @TokenName	DEBUG_BOX_NUM_1_ENABLE 
 * @Range		0 - DISABLE, [1 - ENABLE]
 * @Help		Enable the debug box no.1.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  DEBUG_BOX_TOTAL_ENABLE = ENABLE
 */
#if DEBUG_BOX_TOTAL_ENABLE == ENABLE

#define DEBUG_BOX_NUM_1_ENABLE		    ENABLE

#endif //#if DEBUG_BOX_TOTAL_ENABLE == ENABLE
// @END

/**
 * TOKEN
 * @TokenName	DEBUG_BOX_NUM_2_ENABLE 
 * @Range		0 - DISABLE, [1 - ENABLE]
 * @Help		Enable the debug box no.2.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  DEBUG_BOX_TOTAL_ENABLE = ENABLE
 */
#if DEBUG_BOX_TOTAL_ENABLE == ENABLE

#define DEBUG_BOX_NUM_2_ENABLE		    ENABLE

#endif //#if DEBUG_BOX_TOTAL_ENABLE == ENABLE
// @END

/**
 * TOKEN
 * @TokenName	DEBUG_BOX_NUM_3_ENABLE 
 * @Range		0 - DISABLE, [1 - ENABLE]
 * @Help		Enable the debug box no.3.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  DEBUG_BOX_TOTAL_ENABLE = ENABLE
 */
#if DEBUG_BOX_TOTAL_ENABLE == ENABLE

#define DEBUG_BOX_NUM_3_ENABLE		    ENABLE

#endif //#if DEBUG_BOX_TOTAL_ENABLE == ENABLE
// @END

/**
 * TOKEN
 * @TokenName	DEBUG_BOX_NUM_4_ENABLE 
 * @Range		0 - DISABLE, [1 - ENABLE]
 * @Help		Enable the debug box no.4.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  DEBUG_BOX_TOTAL_ENABLE = ENABLE
 */
#if DEBUG_BOX_TOTAL_ENABLE == ENABLE

#define DEBUG_BOX_NUM_4_ENABLE		    ENABLE

#endif //#if DEBUG_BOX_TOTAL_ENABLE == ENABLE
// @END

/******************************************************************************/
/*                             Feature related                                */
/******************************************************************************/
/**
 * TOKEN
 * @TokenName	AEG_SUPPORT 
 * @Range		0 - DISABLE, [1 - ENABLE]
 * @Help		AEG feature enable token.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  NULL
 */
#define AEG_SUPPORT					    ENABLE

// @END

/**
 * TOKEN
 * @TokenName	AEG_MODE 
 * @Range		1 - MACR_AEG_APPLICATION_PROJECT_GENERAL, 2 - MACR_AEG_APPLICATION_PROJECT_PARTIAL, [3 - MACR_AEG_APPLICATION_PROJECT_CUSTOM]
 * @Help		AEG mode select.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  
 */

#define AEG_MODE					    MACR_AEG_APPLICATION_PROJECT_GENERAL

// @END

/**
 * TOKEN
 * @TokenName	AEG_AC_POEWER_FREQ 
 * @Range		1 - MACR_AEG_AC_FREQ_CFG_50HZ, [2 - MACR_AEG_AC_FREQ_CFG_60HZ]
 * @Help		Selection of power supply frequency.
 *              AE suggestion : MACR_AEG_AC_FREQ_CFG_60HZ with MACR_AEG_FRM_RATE_60FPS, MACR_AEG_FRM_RATE_30FPS, MACR_AEG_FRM_RATE_15FPS
 *                              MACR_AEG_AC_FREQ_CFG_50HZ with MACR_AEG_FRM_RATE_50FPS, MACR_AEG_FRM_RATE_25FPS, MACR_AEG_FRM_RATE_12.5FPS
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  
 */

#define AEG_AC_POWER_FREQ			    MACR_AEG_AC_FREQ_CFG_60HZ

// @END

/**
 * TOKEN
 * @TokenName	AEG_GAMMA_MODE 
 * @Range		[0 - MACR_AEG_GAMMA_OPT_OFF], 1 - MACR_AEG_GAMMA_OPT_ON_GENERAL, 2 - MACR_AEG_GAMMA_OPT_ON_AUTO
 * @Help		Selection of gamma line.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  LINEAR_GAMMA only work in MACR_AEG_STRATEGY_METERING_MIX.         
 */

#define AEG_GAMMA_MODE			        MACR_AEG_GAMMA_OPT_OFF

// @END

/**
 * TOKEN
 * @TokenName	AEG_POWER_MANAGEMENT_MODE 
 * @Range		[0 - MACR_AEG_LPM_OPT_NONE], 1 - MACR_AEG_LPM_OPT_LOW, 2 - MACR_AEG_LPM_OPT_MID, 3 - MACR_AEG_LPM_OPT_HIGH
 * @Help		Selection of low power manage item.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  
 */

#define AEG_POWER_MANAGEMENT_MODE	        MACR_AEG_LPM_OPT_NONE

// @END

/**
 * TOKEN
 * @TokenName	AEG_LED_LIGHT_CTRL_MAX 
 * @Range		0 - 100, [100]
 * @Help		Maximum upper limit value of led control(PWM setting), AEG will fix the level when AEG_LED_LIGHT_CTRL_MAX = AEG_LED_LIGHT_CTRL_MIN.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  
 */

#define AEG_LED_LIGHT_CTRL_MAX				100

// @END

/**
 * TOKEN
 * @TokenName	AEG_LED_LIGHT_CTRL_MIN 
 * @Range		0 - 100, [0]
 * @Help		Minimum lower limit value of led control(PWM setting), AEG will fix the level when AEG_LED_LIGHT_CTRL_MAX = AEG_LED_LIGHT_CTRL_MIN.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  
 */

#define AEG_LED_LIGHT_CTRL_MIN				0

// @END

/**
 * TOKEN
 * @TokenName	AEG_ANALOG_GAIN_MAX 
 * @Range		2 - 15, [8]
 * @Help		Maximum upper limit value of gain.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  AEG_MODE = MACR_AEG_APPLICATION_PROJECT_CUSTOM   
 */
#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM

#define AEG_ANALOG_GAIN_MAX					12

#endif //#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM
// @END

/**
 * TOKEN
 * @TokenName	AEG_FRAME_RATE_MODE_MAX 
 * @Range		0 - MACR_AEG_FRM_RATE_NONE, 1 - MACR_AEG_FRM_RATE_12_5FPS, 2 - MACR_AEG_FRM_RATE_15FPS, 3 - MACR_AEG_FRM_RATE_25FPS, 4 - MACR_AEG_FRM_RATE_30FPS, 5 - MACR_AEG_FRM_RATE_50FPS, [6 - MACR_AEG_FRM_RATE_60FPS]
 * @Help		Selection image maximum frame rate.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  AEG_MODE = MACR_AEG_APPLICATION_PROJECT_CUSTOM
 */
#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM

#if AEG_AC_POWER_FREQ == MACR_AEG_AC_FREQ_CFG_60HZ
#define AEG_FRAME_RATE_MODE_MAX MACR_AEG_FRM_RATE_60FPS
#else
#define AEG_FRAME_RATE_MODE_MAX MACR_AEG_FRM_RATE_50FPS
#endif

#endif //#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM
// @END

/**
 * TOKEN
 * @TokenName	AEG_FRAME_RATE_MODE_MIN 
 * @Range		0 - MACR_AEG_FRM_RATE_NONE, 1 - MACR_AEG_FRM_RATE_12_5FPS, 2 - MACR_AEG_FRM_RATE_15FPS, 3 - MACR_AEG_FRM_RATE_25FPS, 4 - MACR_AEG_FRM_RATE_30FPS, 5 - MACR_AEG_FRM_RATE_50FPS, [6 - MACR_AEG_FRM_RATE_60FPS]
 * @Help		Selection image minimum frame rate.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  AEG_MODE = MACR_AEG_APPLICATION_PROJECT_CUSTOM
 */
#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM

#if AEG_AC_POWER_FREQ == MACR_AEG_AC_FREQ_CFG_60HZ
#define AEG_FRAME_RATE_MODE_MIN MACR_AEG_FRM_RATE_60FPS
#else
#define AEG_FRAME_RATE_MODE_MIN MACR_AEG_FRM_RATE_50FPS
#endif

#endif //#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM
// @END

/**
 * TOKEN
 * @TokenName	AEG_LIGHT_DETECT_TYPE 
 * @Range		0 - MACR_AEG_STRATEGY_METERING_MIX, [1 - MACR_AEG_STRATEGY_METERING_SPOT]
 * @Help		AEG detect light algorithm.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  AEG_MODE = MACR_AEG_APPLICATION_PROJECT_CUSTOM            
 */
#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM

#define AEG_LIGHT_DETECT_TYPE			MACR_AEG_STRATEGY_METERING_SPOT

#endif //#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM
// @END

/**
 * TOKEN
 * @TokenName	AEG_MOTION_LOCATION_FILTER 
 * @Range		[0 - DISABLE], 1 - ENABLE
 * @Help		Motion area will be filter when width at 40 to 160, and height more than 40.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  AEG_MODE = MACR_AEG_APPLICATION_PROJECT_CUSTOM
 */
#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM

#define AEG_MOTION_LOCATION_FILTER		DISABLE

#endif //#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM && AEG_LIGHT_DETECT_TYPE == MACR_AEG_STRATEGY_METERING_SPOT
// @END

/**
 * TOKEN
 * @TokenName	AEG_DETECT_LOCATION_FILTER 
 * @Range		[0 - DISABLE], 1 - ENABLE
 * @Help		Detect location filter.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  AEG_MODE = MACR_AEG_APPLICATION_PROJECT_CUSTOM       
 */
#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM

#define AEG_DETECT_LOCATION_FILTER		DISABLE

#endif //#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM && AEG_LIGHT_DETECT_TYPE == MACR_AEG_STRATEGY_METERING_SPOT
// @END


/**
 * TOKEN
 * @TokenName	AEG_CUSTOM_VALID_SUPPORT 
 * @Range		0 - DISABLE, [1 - ENABLE]
 * @Help		Set the valid flag to update custom setting within sensor_aeg_update_custom_application_info().
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  AEG_MODE = MACR_AEG_APPLICATION_PROJECT_CUSTOM          
 */
#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM

#define AEG_CUSTOM_VALID_SUPPORT		ENABLE

#endif //#if AEG_MODE == MACR_AEG_APPLICATION_PROJECT_CUSTOM
// @END

/**
 * TOKEN
 * @TokenName	AEG_TEST_MODE_VALID_SUPPORT 
 * @Range		[0 - DISABLE], 1 - ENABLE
 * @Help		For test, AEG control with global brightness only.
 * @TokenType   Boolean
 * @Master		Yes
 * @Dependency  
 */

#define AEG_TEST_MODE_VALID_SUPPORT		DISABLE

// @END

/**
 * TOKEN
 * @TokenName	AEG_BRIGHTNESS_TARGET_VAULE 
 * @Range		30 - 225, [130]
 * @Help		The target brightness to which the AEG function will adjust. AE suggested range: 60 - 180.
 * @TokenType   Integer
 * @Master		Yes
 * @Dependency  AEG_SUPPORT = ENABLE
 */
#if AEG_SUPPORT == ENABLE

#define AEG_BRIGHTNESS_TARGET_VAULE		145

#endif //#if AEG_SUPPORT == ENABLE
// @END
