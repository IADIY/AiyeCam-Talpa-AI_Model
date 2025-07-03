/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/

#ifndef __USER_DETECT_CONFIG__
#define __USER_DETECT_CONFIG__

#include "nb_detect.h"
#include "nb_base.h"



// 输出图像到屏幕
#define SUPPORT_OUTLCD

//图像上画框
#define USE_DRAW_DEBUG_WIN


// 支持看门狗
#define SUPPORT_WATCHDOG


// #define SUPPORT_BINNING2
#ifdef SUPPORT_BINNING2
#define SENSOR_OUTPUT_SIZE  160
#else
#define SENSOR_OUTPUT_SIZE  320
#endif

void User_Detect_Project_Config(void);
void User_Detect_Config_Init(void);


void User_Detect_Buf_Init(void);
void User_Detect_Buf_UnInit(void);
void User_Detect_Buf_UnInit_Action(void);

void User_Detect_Config_Set_Win(int min,int max);

#endif


