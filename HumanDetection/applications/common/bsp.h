/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#ifndef __BSP_H__
#define __BSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nb_file_id.h"

#ifdef NB_EVALBOARD
#include "board_EVALBOARD.h"
#endif

#ifdef NB_JABBERBOARD
#include "board_JABBERBOARD.h"
#endif

#ifdef NB_TESTBOARD
#include "board_TESTBOARD.h"
#endif

int board_sensor_init(void);
int board_led_init(void);

int bsp_init(void);

#ifdef __cplusplus
}
#endif

#endif