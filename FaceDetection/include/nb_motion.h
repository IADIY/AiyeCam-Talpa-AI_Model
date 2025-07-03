/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2020 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/


#ifndef __NB__MOTION__
#define __NB__MOTION__

#include "nb_detect.h"

extern u8 NB_Motion_Eable;

extern NB_MB_MOTION_t_s NB_motion_rd;
extern NB_MB_MOTION_t_s NB_motion;
extern NB_MB_MOTION_t_s NB_motion_head;
extern NB_MB_MOTION_t_s NB_new_motion;

void NB_Motion_Init(void);
void NB_Motion_Action(u32 *detected_cnt,u32 f_id);
void NB_motion_filter(u8 m_g,u16 x,u16 y,u16 w,u16 h);
void NB_Motion_Get_RdMotion(void);



#endif



