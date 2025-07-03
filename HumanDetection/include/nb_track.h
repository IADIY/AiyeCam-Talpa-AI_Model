/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2020 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/


#ifndef __NB__TRACK__
#define __NB__TRACK__

#include "nb_detect.h"




void NB__track_init(void);


float nb__track_lerp(float s, float e, float t);
float nb__track_blerp(float c00, float c10, float c01, float c11, float tx, float ty);

float nb__track_ssim_mean(u8 arr[], int n);

void nb__track_ahash(u8 *in_buf,u8 *out_buf,u16 len);
void nb__track_dhash(u8 *in_buf,u8 *out_buf,u16 len_w,u16 len_h);
void nb__track_cosine(u8 *in_buf,u8 *out_buf,u16 len);
void nb__track_ssim(u8 *in_buf,u8 *out_buf,u16 len);
void nb__track_histogram(u8 *in_buf,u16 in_len,u8 *out_buf,u16 len);

void NB__track_image_get_buf(u8 *in_buf,u16 x,u16 y,u16 w,u16 h);
void nb__track_scale(u8 *in_buf,u16 in_w,u16 in_h,u8 *out_buf,u8 *out_w,u8 *out_h,u16 *out_len);
void NB__track_image_target(u16 x,u16 y,u16 w,u16 h);
void NB__track_set_target(u16 x,u16 y,u16 w,u16 h);





float nb__track_cosine_compare(u8 *in_buf,u8 *base_buf,u16 len);
float nb__track_ssim_compare(u8 *in_buf,u8 *base_buf,u16 len);
u16 nb__track_hamming_distance_compare(u8 *in_buf,u8 *base_buf,u16 len);
u16 nb__track_histogram_hamming_distance_compare(u8 *in_buf,u8 *base_buf,u16 len);

void NB__track_image_compare(u8 select,u16 fewin_x,u16 fewin_y,u16 fewin_w,u16 fewin_h);
void NB__track_compare(u8 select,u16 fewin_x,u16 fewin_y,u16 fewin_w,u16 fewin_h);




void NB__NB__model_set_track_found(u8 state,u8 select,u16 x,u16 y,u16 w,u16 h);




#endif



