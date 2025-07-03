/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/

#ifndef __USER_DETECT_CONFIG__
#define __USER_DETECT_CONFIG__

#include "include/nb_detect.h"
#include "include/nb_motion.h"

// #define SUPPORT_BINNING2
#ifdef SUPPORT_BINNING2
#define SENSOR_OUTPUT_SIZE 160
// #define CIS_BINNING
#define ISP_BINNING
// #define ISP_SKIP
#else
#define SENSOR_OUTPUT_SIZE 320
#endif

extern NB_User_Model_s detect_model;
extern NB_Detect_Config_s detect_config;

void User_Detect_Config_Init(void);
#endif
