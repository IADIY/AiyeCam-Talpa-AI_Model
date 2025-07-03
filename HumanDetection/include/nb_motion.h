/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2020 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/


#ifndef __NB__MOTION__
#define __NB__MOTION__

#include "nb_detect.h"


extern void md_fixed_set_win(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);
extern void md_fixed_set_detect_win( int wlow, int whigh, int hlow, int hhigh );
extern void md_fixed_set_cmp_threshold(uint16_t high,uint16_t low,uint16_t high_ratio,uint16_t low_ratio );

extern u8 NB__Motion_Eable;

extern NB__MB_MOTION_t_s NB__motion_base;
extern NB__MB_MOTION_t_s NB__motion_gesture;
extern NB__MB_MOTION_t_s NB__motion;
extern NB__MB_MOTION_t_s NB__motion_head;
extern NB__MB_MOTION_t_s NB__new_motion;

extern NB__MB_MOTION_t_s NB__motion_load_model;

extern u32 NB__motion_five_stop_times;
extern u8 NB__motion_five_wait_t;


extern u8 NB__motion_queue_item; 

void NB__Motion_Init(void);
void NB__Motion_Action(u32 *detected_cnt,u32 f_id);
u8 NB__motion_filter(u16 in_x,u16 in_y,u16 in_w,u16 in_h,u16 x,u16 y,u16 w,u16 h);
void NB__Motion_Get_BaseMotion(void);


void NB__Motion_check_reset(void);

void NB__Motion_check_distance(u32 f_id);


#endif



