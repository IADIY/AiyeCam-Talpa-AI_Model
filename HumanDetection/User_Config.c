/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/

#include "User_Config.h"
#include "bsp.h"
#include "nb_motion.h"
#include "nbsdk.h"
//#include "User_Model_Table.h"

#include "resource/data/model/module.h"




void User_Detect_Config_Calculate(void);
void User_Area_Config(void);
size_t xPortGetFreeHeapSize(void);


// 多宫格使用配置
void User_Area_Config(void)
{	

	
	u8 m_g = 0;
	u8 m_l = 0;
	u8 index = 0;


	// 配置每个中心点
	u16 temp_x0 = 0;
	u16 temp_y0 = 0;
	u16 temp_y = 0;
	

	#if 1 // 全部位置

	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_NO;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_WIN_MID;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;

	NB__area_table[index].g_item = m_g;

			
	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_4;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_4AREA_1;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_4AREA_3;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_4AREA_2;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_4AREA_4;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;

	NB__area_table[index].g_item = m_g;

	

	
	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_9;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_3;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_4;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_9;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_1;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_6;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_7;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_2;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_5;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_8;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++; 		

	NB__area_table[index].g_item = m_g;

	

	
	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_16;	
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_1;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_4;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_9;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_12;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_2;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_5;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_3;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_6;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_7;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_10;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_13;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_8;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_11;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_14;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_15;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_16;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
			
	NB__area_table[index].g_item = m_g;
	


	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_25;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_1;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_5;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_11;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_15;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_6;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_10;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_2;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_9;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_12;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_19;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_3;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_8;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_4;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_7;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_14;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_17;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_21;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_22;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_23;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_16;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_20;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_13;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_18;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_24;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_25;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;

	NB__area_table[index].g_item = m_g;



	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_36;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_1;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_6;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_13;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_18;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_8;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_11;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_20; 
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_7;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_12;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_19;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_24;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_4;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_9;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_16; 
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_2;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_5;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_14;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_17;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_25;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_26;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_31;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_3;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_10;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_15;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_22;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_29;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_30;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_35;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	m_l = 0;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_32;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_28;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_21;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_33;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_23;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_34;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_36;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_27;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	NB__area_table[index].g_item = m_g;




	

	temp_x0 = NB__config.detect_max_xpiont / (1 + 1);
	temp_y0 = NB__config.detect_max_ypiont / (1 + 1);
	temp_y = 0;
	NB__winmid.x0[NB__WIN_MID_WIN_MID] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_WIN_MID] = temp_y0;
	NB__winmid.y[NB__WIN_MID_WIN_MID] = temp_y;

	temp_x0 = NB__config.detect_max_xpiont / (2 + 1);
	temp_y0 = NB__config.detect_max_ypiont / (2 + 1);
	temp_y = NB__config.detect_max_ypiont / 2;
	NB__winmid.x0[NB__WIN_MID_4AREA_1] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_4AREA_1] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_4AREA_1] = 0;
	
	NB__winmid.x0[NB__WIN_MID_4AREA_2] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_4AREA_2] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_4AREA_2] = 0;
	
	NB__winmid.x0[NB__WIN_MID_4AREA_3] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_4AREA_3] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_4AREA_3] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_4AREA_4] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_4AREA_4] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_4AREA_4] = temp_y * 1;

	temp_x0 = NB__config.detect_max_xpiont / (3 + 1);
	temp_y0 = NB__config.detect_max_ypiont / (3 + 1);
	temp_y = NB__config.detect_max_ypiont / 3;
	NB__winmid.x0[NB__WIN_MID_9AREA_1] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_9AREA_1] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_9AREA_1] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_9AREA_2] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_9AREA_2] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_9AREA_2] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_9AREA_3] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_9AREA_3] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_9AREA_3] = temp_y * 0;

	NB__winmid.x0[NB__WIN_MID_9AREA_4] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_9AREA_4] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_9AREA_4] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_9AREA_5] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_9AREA_5] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_9AREA_5] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_9AREA_6] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_9AREA_6] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_9AREA_6] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_9AREA_7] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_9AREA_7] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_9AREA_7] = temp_y * 2;

	NB__winmid.x0[NB__WIN_MID_9AREA_8] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_9AREA_8] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_9AREA_8] = temp_y * 2;

	NB__winmid.x0[NB__WIN_MID_9AREA_9] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_9AREA_9] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_9AREA_9] = temp_y * 2;

	temp_x0 = NB__config.detect_max_xpiont / (4 + 1);
	temp_y0 = NB__config.detect_max_ypiont / (4 + 1);
	temp_y = NB__config.detect_max_ypiont / 4;
	NB__winmid.x0[NB__WIN_MID_16AREA_1] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_16AREA_1] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_16AREA_1] = temp_y * 0;

	NB__winmid.x0[NB__WIN_MID_16AREA_2] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_16AREA_2] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_16AREA_2] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_16AREA_3] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_16AREA_3] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_16AREA_3] = temp_y * 0;

	NB__winmid.x0[NB__WIN_MID_16AREA_4] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_16AREA_4] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_16AREA_4] = temp_y * 0;

	NB__winmid.x0[NB__WIN_MID_16AREA_5] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_16AREA_5] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_16AREA_5] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_16AREA_6] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_16AREA_6] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_16AREA_6] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_16AREA_7] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_16AREA_7] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_16AREA_7] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_16AREA_8] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_16AREA_8] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_16AREA_8] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_16AREA_9] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_16AREA_9] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_16AREA_9] = temp_y * 2;

	NB__winmid.x0[NB__WIN_MID_16AREA_10] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_16AREA_10] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_16AREA_10] = temp_y * 2;

	NB__winmid.x0[NB__WIN_MID_16AREA_11] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_16AREA_11] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_16AREA_11] = temp_y * 2;

	NB__winmid.x0[NB__WIN_MID_16AREA_12] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_16AREA_12] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_16AREA_12] = temp_y * 2;

	NB__winmid.x0[NB__WIN_MID_16AREA_13] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_16AREA_13] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_16AREA_13] = temp_y * 3;

	NB__winmid.x0[NB__WIN_MID_16AREA_14] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_16AREA_14] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_16AREA_14] = temp_y * 3;

	NB__winmid.x0[NB__WIN_MID_16AREA_15] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_16AREA_15] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_16AREA_15] = temp_y * 3;

	NB__winmid.x0[NB__WIN_MID_16AREA_16] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_16AREA_16] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_16AREA_16] = temp_y * 3;



	temp_x0 = NB__config.detect_max_xpiont / (5 + 1);
	temp_y0 = NB__config.detect_max_ypiont / (5 + 1);
	temp_y = NB__config.detect_max_ypiont / 5;
	NB__winmid.x0[NB__WIN_MID_25AREA_1] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_25AREA_1] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_25AREA_1] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_2] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_25AREA_2] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_25AREA_2] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_3] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_25AREA_3] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_25AREA_3] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_4] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_25AREA_4] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_25AREA_4] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_5] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_25AREA_5] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_25AREA_5] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_6] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_25AREA_6] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_25AREA_6] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_7] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_25AREA_7] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_25AREA_7] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_8] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_25AREA_8] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_25AREA_8] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_9] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_25AREA_9] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_25AREA_9] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_10] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_25AREA_10] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_25AREA_10] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_11] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_25AREA_11] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_25AREA_11] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_12] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_25AREA_12] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_25AREA_12] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_13] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_25AREA_13] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_25AREA_13] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_14] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_25AREA_14] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_25AREA_14] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_15] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_25AREA_15] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_25AREA_15] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_16] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_25AREA_16] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_25AREA_16] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_17] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_25AREA_17] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_25AREA_17] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_18] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_25AREA_18] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_25AREA_18] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_19] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_25AREA_19] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_25AREA_19] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_20] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_25AREA_20] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_25AREA_20] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_21] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_25AREA_21] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_25AREA_21] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_22] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_25AREA_22] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_25AREA_22] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_23] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_25AREA_23] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_25AREA_23] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_24] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_25AREA_24] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_25AREA_24] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_25] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_25AREA_25] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_25AREA_25] = temp_y * 4;
	

	temp_x0 = NB__config.detect_max_xpiont / (6 + 1);
	temp_y0 = NB__config.detect_max_ypiont / (6 + 1);
	temp_y = NB__config.detect_max_ypiont / 6;
	NB__winmid.x0[NB__WIN_MID_36AREA_1] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_36AREA_1] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_36AREA_1] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_2] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_36AREA_2] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_36AREA_2] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_3] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_36AREA_3] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_36AREA_3] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_4] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_36AREA_4] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_36AREA_4] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_5] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_36AREA_5] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_36AREA_5] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_6] = temp_x0 * 6;
	NB__winmid.y0[NB__WIN_MID_36AREA_6] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_36AREA_6] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_7] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_36AREA_7] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_36AREA_7] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_8] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_36AREA_8] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_36AREA_8] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_9] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_36AREA_9] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_36AREA_9] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_10] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_36AREA_10] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_36AREA_10] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_11] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_36AREA_11] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_36AREA_11] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_12] = temp_x0 * 6;
	NB__winmid.y0[NB__WIN_MID_36AREA_12] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_36AREA_12] = temp_y * 1;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_13] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_36AREA_13] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_36AREA_13] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_14] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_36AREA_14] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_36AREA_14] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_15] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_36AREA_15] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_36AREA_15] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_16] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_36AREA_16] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_36AREA_16] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_17] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_36AREA_17] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_36AREA_17] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_18] = temp_x0 * 6;
	NB__winmid.y0[NB__WIN_MID_36AREA_18] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_36AREA_18] = temp_y * 2;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_19] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_36AREA_19] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_36AREA_19] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_20] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_36AREA_20] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_36AREA_20] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_21] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_36AREA_21] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_36AREA_21] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_22] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_36AREA_22] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_36AREA_22] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_23] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_36AREA_23] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_36AREA_23] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_24] = temp_x0 * 6;
	NB__winmid.y0[NB__WIN_MID_36AREA_24] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_36AREA_24] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_25] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_36AREA_25] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_36AREA_25] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_26] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_36AREA_26] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_36AREA_26] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_27] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_36AREA_27] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_36AREA_27] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_28] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_36AREA_28] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_36AREA_28] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_29] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_36AREA_29] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_36AREA_29] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_30] = temp_x0 * 6;
	NB__winmid.y0[NB__WIN_MID_36AREA_30] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_36AREA_30] = temp_y * 4;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_31] = temp_x0 * 1;
	NB__winmid.y0[NB__WIN_MID_36AREA_31] = temp_y0 * 6;
	NB__winmid.y[NB__WIN_MID_36AREA_31] = temp_y * 5;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_32] = temp_x0 * 2;
	NB__winmid.y0[NB__WIN_MID_36AREA_32] = temp_y0 * 6;
	NB__winmid.y[NB__WIN_MID_36AREA_32] = temp_y * 5;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_33] = temp_x0 * 3;
	NB__winmid.y0[NB__WIN_MID_36AREA_33] = temp_y0 * 6;
	NB__winmid.y[NB__WIN_MID_36AREA_33] = temp_y * 5;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_34] = temp_x0 * 4;
	NB__winmid.y0[NB__WIN_MID_36AREA_34] = temp_y0 * 6;
	NB__winmid.y[NB__WIN_MID_36AREA_34] = temp_y * 5;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_35] = temp_x0 * 5;
	NB__winmid.y0[NB__WIN_MID_36AREA_35] = temp_y0 * 6;
	NB__winmid.y[NB__WIN_MID_36AREA_35] = temp_y * 5;
	
	NB__winmid.x0[NB__WIN_MID_36AREA_36] = temp_x0 * 6;
	NB__winmid.y0[NB__WIN_MID_36AREA_36] = temp_y0 * 6;
	NB__winmid.y[NB__WIN_MID_36AREA_36] = temp_y * 5;
	

	#endif


	

	#if 0 // 固定位置
	
	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_NO;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_WIN_MID;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;

	NB__area_table[index].g_item = m_g;

			
	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_4;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_4AREA_1;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_4AREA_3;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;

	NB__area_table[index].g_item = m_g;

	

	
	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_9;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_2;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_5;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_9AREA_8;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;			

	NB__area_table[index].g_item = m_g;

	

	
	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_16;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_2;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_6;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_10;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_16AREA_14;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
			
	NB__area_table[index].g_item = m_g;
	


	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_25;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_3;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_8;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_13;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_18;
	//NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_25AREA_23;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;				

	NB__area_table[index].g_item = m_g;



	m_g = 0;
	m_l = 0;
	index = NB__WIN_AREA_MODE_36;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_3;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_9;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_15;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_21;
	NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_27;
	//NB__area_table[index].each_g_table[m_g][m_l ++] = NB__WIN_MID_36AREA_33;
	NB__area_table[index].each_g_item[m_g] = m_l;
	m_g ++;
	
	NB__area_table[index].g_item = m_g;









	temp_x0 = 100;//NB__config.detect_max_xpiont / (1 + 1);
	
	temp_y0 = NB__config.detect_max_ypiont / (1 + 1);
	temp_y = 0;
	NB__winmid.x0[NB__WIN_MID_WIN_MID] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_WIN_MID] = temp_y0;
	NB__winmid.y[NB__WIN_MID_WIN_MID] = temp_y;



	temp_y0 = NB__config.detect_max_ypiont / (1 + 1);
	temp_y = NB__config.detect_max_ypiont / 2;
	NB__winmid.x0[NB__WIN_MID_4AREA_1] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_4AREA_1] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_4AREA_1] = 0;
	
	
	NB__winmid.x0[NB__WIN_MID_4AREA_3] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_4AREA_3] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_4AREA_3] = temp_y * 1;



	

	temp_y0 = NB__config.detect_max_ypiont / (3 + 1);
	temp_y = NB__config.detect_max_ypiont / 3;
	NB__winmid.x0[NB__WIN_MID_9AREA_2] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_9AREA_2] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_9AREA_2] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_9AREA_5] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_9AREA_5] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_9AREA_5] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_9AREA_8] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_9AREA_8] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_9AREA_8] = temp_y * 2;





	temp_y0 = NB__config.detect_max_ypiont / (4 + 1);
	temp_y = NB__config.detect_max_ypiont / 4;
	NB__winmid.x0[NB__WIN_MID_16AREA_2] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_16AREA_2] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_16AREA_2] = temp_y * 0;
	
	NB__winmid.x0[NB__WIN_MID_16AREA_6] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_16AREA_6] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_16AREA_6] = temp_y * 1;

	NB__winmid.x0[NB__WIN_MID_16AREA_10] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_16AREA_10] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_16AREA_10] = temp_y * 2;

	NB__winmid.x0[NB__WIN_MID_16AREA_14] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_16AREA_14] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_16AREA_14] = temp_y * 3;




	temp_y0 = NB__config.detect_max_ypiont / (5 + 1);
	temp_y = NB__config.detect_max_ypiont / 5;	
	NB__winmid.x0[NB__WIN_MID_25AREA_3] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_25AREA_3] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_25AREA_3] = temp_y * 0;

	NB__winmid.x0[NB__WIN_MID_25AREA_8] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_25AREA_8] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_25AREA_8] = temp_y * 1;
		
	NB__winmid.x0[NB__WIN_MID_25AREA_13] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_25AREA_13] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_25AREA_13] = temp_y * 2;
		
	NB__winmid.x0[NB__WIN_MID_25AREA_18] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_25AREA_18] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_25AREA_18] = temp_y * 3;
	
	NB__winmid.x0[NB__WIN_MID_25AREA_23] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_25AREA_23] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_25AREA_23] = temp_y * 4;
	

	

	temp_y0 = NB__config.detect_max_ypiont / (6 + 1);
	temp_y = NB__config.detect_max_ypiont / 6;
	NB__winmid.x0[NB__WIN_MID_36AREA_3] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_36AREA_3] = temp_y0 * 1;
	NB__winmid.y[NB__WIN_MID_36AREA_3] = temp_y * 0;
		
	NB__winmid.x0[NB__WIN_MID_36AREA_9] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_36AREA_9] = temp_y0 * 2;
	NB__winmid.y[NB__WIN_MID_36AREA_9] = temp_y * 1;
		
	NB__winmid.x0[NB__WIN_MID_36AREA_15] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_36AREA_15] = temp_y0 * 3;
	NB__winmid.y[NB__WIN_MID_36AREA_15] = temp_y * 2;
		
	NB__winmid.x0[NB__WIN_MID_36AREA_21] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_36AREA_21] = temp_y0 * 4;
	NB__winmid.y[NB__WIN_MID_36AREA_21] = temp_y * 3;
		
	NB__winmid.x0[NB__WIN_MID_36AREA_27] = temp_x0;
	NB__winmid.y0[NB__WIN_MID_36AREA_27] = temp_y0 * 5;
	NB__winmid.y[NB__WIN_MID_36AREA_27] = temp_y * 4;
		
	//NB__winmid.x0[NB__WIN_MID_36AREA_33] = temp_x0;
	//NB__winmid.y0[NB__WIN_MID_36AREA_33] = temp_y0 * 6;
	//NB__winmid.y[NB__WIN_MID_36AREA_33] = temp_y * 5;
	
	#endif



	
}


void User_Detect_Config_Calculate(void)
{
	u16 i = 0;
	u16 j = 0;
	u16 k = 0;
	u8 insert = 0;
	u16 indata = 0;
	

	u16 temp = 0;
	u16 temp1 = 0;
	u16 temp2 = 0;

	

	NB__config.winw_min = 320;
	NB__config.winw_max = 0;
	NB__config.winw_sort_w_item = 0;
	//printf("NB__config.winw_group %d \n",NB__config.winw_group);
	for(i = 0;i < NB__config.winw_group;i ++)
	{
		//printf("NB__config.winw_group_item[%d] %d \n",i,NB__config.winw_group_item[i]);
		for(j = 0;j < NB__config.winw_group_item[i];j ++)
		{
			indata = NB__config.winw_each_w[i][j];
			//printf("i:%d j:%d %d \n",i,j,indata);
			if(indata < NB__config.winw_min)
			{
				NB__config.winw_min = indata;
			}
			
			if(indata > NB__config.winw_max)
			{
				NB__config.winw_max = indata;
			}

			// 排序插入
			insert = NB__config.winw_sort_w_item + 1;
			for(k = 0;k < NB__config.winw_sort_w_item;k ++)
			{
				// 要插入的数据相同
				if(NB__config.winw_sort_w[k] == indata)
				{
					insert = 0;
					break;
				}
				else if(NB__config.winw_sort_w[k]> indata)
				{
					insert = k + 1;
					break;
				}
			}

			if(insert)
			{
				// 数据后移
				for(k = NB__config.winw_sort_w_item;k >= insert;k --)
				{
					NB__config.winw_sort_w[k] = NB__config.winw_sort_w[k - 1];
				}
				
				NB__config.winw_sort_w[insert - 1] = indata;
				NB__config.winw_sort_w_item ++;
			}
			
			
		}
	}

	
	// printf("Set Win min:%d max:%d \n",NB__config.winw_min,NB__config.winw_max);

	NB__config.all_max_scaler_w = 0;
	NB__config.all_max_scaler_h = 0;
	for(i = 0;i < NB__DETECT_SYS_MODE_END;i ++)
	{

		if((i == NB__DETECT_SYS_MODE_FOUND_START) || (i == NB__DETECT_SYS_MODE_FOUND_START))
		{
			if(NB__config.all_max_scaler_w < NB__config.max_scaler_w[i] + add_scaler_w)
			{
				NB__config.all_max_scaler_w = NB__config.max_scaler_w[i] + add_scaler_w;
			}

			if(NB__config.all_max_scaler_h < NB__config.max_scaler_h[i] + add_scaler_h)
			{
				NB__config.all_max_scaler_h = NB__config.max_scaler_h[i] + add_scaler_h;
			}	
			
		}
		else
		{
			if(NB__config.all_max_scaler_w < NB__config.max_scaler_w[i])
			{
				NB__config.all_max_scaler_w = NB__config.max_scaler_w[i];
			}

			if(NB__config.all_max_scaler_h < NB__config.max_scaler_h[i])
			{
				NB__config.all_max_scaler_h = NB__config.max_scaler_h[i];
			}	
		}
	

	
			
	}
	
	
	//NB__config.all_max_scaler_w += NB__ADD_SCALER_W_MAX;
	if(NB__config.all_max_scaler_w > NB__SCALER_MAX)
	{
		NB__config.all_max_scaler_w = NB__SCALER_MAX;
	}
	
	//NB__config.all_max_scaler_h += NB__ADD_SCALER_H_MAX;
	if(NB__config.all_max_scaler_h > NB__SCALER_MAX)
	{
		NB__config.all_max_scaler_h = NB__SCALER_MAX;
	}

	NB__config.max_fe_buf_len = ((NB__config.all_max_scaler_w * NB__config.all_max_scaler_h * 9) >> 5);
	// printf("scaler_w:%d add:%d  scaler_h:%d add:%d max_fe_buf_len:%d \n",NB__config.all_max_scaler_w,NB__ADD_SCALER_W_MAX,
	// 	NB__config.all_max_scaler_h,NB__ADD_SCALER_H_MAX,
	// 	NB__config.max_fe_buf_len);



	
	// 相关数据计算
	NB__model.group_max_datasize = 0;
	NB__model.group_max_1winsize = 5 * 5;
	for(i = 0;i < NB__model.group_item;i ++)
	{				
		// 模型组使用排序
		NB__model.group_use_index[i] = i;
	
		NB__model.group_1offset_w[i] = NB__RESULT_OFFSET_MIN_VALUE_D(NB__model.group_w[i]);
		NB__model.group_eigenvalue_w_number[i] = NB__model.group_1offset_w[i] * 9;

		
		NB__model.group_1offset_h[i] = NB__RESULT_OFFSET_MIN_VALUE_D(NB__model.group_h[i]);
		NB__model.group_size[i] = NB__model.group_w[i] * NB__model.group_h[i] * 9 >> 6;

		NB__model.lv_buf_new_linear1_len[i] = NB__model.group_size[i] * NB__model.lv_linear_num[i];

		

		if(NB__model.group_max_datasize < NB__model.group_size[i])
		{
			NB__model.group_max_datasize = NB__model.group_size[i];
		}

		temp1 = NB__config.all_max_scaler_w;
		temp2 = NB__config.all_max_scaler_h;
		temp = (NB__RESULT_OFFSET_MIN_VALUE_D(temp1 - NB__model.group_w[i]) + 1) * 
			(NB__RESULT_OFFSET_MIN_VALUE_D(temp2 - NB__model.group_h[i]) + 1);
		if(NB__model.group_max_1winsize < temp)
		{
			NB__model.group_max_1winsize = temp;
		}
				
	}

	//printf("group_max_1winsize:%d group_max_datasize:%d \n",NB__model.group_max_1winsize,NB__model.group_max_datasize);


	
}


// min == max			75%-》125%
void User_Detect_Config_Set_Win(int min,int max)
{
	#define		MAX			320
	#define 	MIN			32


	// 框的大小按照MIN放大，STEP为系数（放大128倍）
	#define 	STEP		154   // 1.1 * 128 141	// 1.05 *128 134	// 1.2 * 128 154

	int i = 0;
	int item = 0;

	int temp_w = 0;
	int temp_1w = 0;
	int offset[NB__WINW_MAX_ITEM] = {0};

	int step = STEP;
	
	int m_g = 0;
	
	if(min == max)
	{
		step = 137;
		
		// 确定识别范围
		min = (min * 96) >> 7; // 0.75
		max = (max * 160) >> 7; // 1.25
		
	}

	
	if((min < MIN) ||(min >= MAX))
	{
		min = MIN;
	}
	
	if((max > MAX) ||(max <= MIN))
	{
		max = MAX;
	}

	if(max < min + 24)
	{
		max = min + 24;
	}


	
	// area message  vts:400 use_scaler_w:96 use1:160 ues4:106 ues9/2:80 ues16/2:64 ues25/2:53 ues36/2:45 
	// 130-80像素
	m_g = 0;
	temp_w = min;
	for(;;)
	{
		
		if(item >= NB__WINW_MAX_ITEM)
		{
			break;
		}
		NB__config.winw_each_w[m_g][item] = temp_w; // 7
		temp_1w = temp_w * step >> 7;
		offset[item] = temp_1w - temp_w;
		temp_w = temp_1w;
		item ++;
		
		if(temp_w >= max)
		{
			//printf("break %d/%d \n",temp_w,max);
			break;
		}

	}
	
	NB__config.winw_group_item[m_g] = item;
	
	
	// 偏移二分之一
	m_g ++;
	if(m_g < NB__WINW_MAX_GROUP)
	{
		for(i= 0;i < item;i ++)
		{
			temp_w = (offset[i] >> 1);
			if(temp_w <= 0)
			{
				temp_w = 1;
			}
			NB__config.winw_each_w[m_g][i] = NB__config.winw_each_w[0][i] + temp_w; // 7
		}
		NB__config.winw_group_item[m_g] = item;
	}
	


	#if 1

	// 偏移四分之一
	m_g ++;
	if(m_g < NB__WINW_MAX_GROUP)
	{
		for(i= 0;i < item;i ++)
		{
			temp_w = (offset[i] >> 2);
			if(temp_w <= 0)
			{
				temp_w = 1;
			}
			NB__config.winw_each_w[m_g][i] = NB__config.winw_each_w[0][i] + temp_w ; // 7
		}
		NB__config.winw_group_item[m_g] = item;
	}
	


	
	// 偏移四分之三
	m_g ++;
	if(m_g < NB__WINW_MAX_GROUP)
	{
		for(i= 0;i < item;i ++)
		{
			temp_w = (offset[i] >> 1) + (offset[i] >> 2);
			if(temp_w <= 0)
			{
				temp_w = 1;
			}
			NB__config.winw_each_w[m_g][i] = NB__config.winw_each_w[0][i] + temp_w ; // 7
		}
		NB__config.winw_group_item[m_g] = item;
	}
	
	#endif


	if(m_g >= NB__WINW_MAX_GROUP)
	{
		m_g = NB__WINW_MAX_GROUP - 1;
	}
	NB__config.winw_group = m_g + 1;
	NB__config.winw_focus_item = 30;



	#if 0 // debug

	int j = 0;

	for(i = 0;i < NB__config.winw_group;i ++)
	{
		//printf("config win table min:%d max:%d item:%d i:%d ",min,max,item,i);
		for(j = 0;j < item;j ++)
		{
			//printf("%d ",NB__config.winw_each_w[i][j]);
		}
		printf("\n");
	}
	
	#endif

	
}
	


// 项目配置
void User_Detect_Config_Init(void)
{


	#define SCORE_BASE	11640
	
	u8 m_g = 0;
	u8 m_l = 0;
		
	

	
	/**************************************
	识别模型配置
	***************************************/ 

	m_g = 0;
	NB__model.group_type[m_g] = NB_MODEL_TYPE_HEAD;
	NB__model.eable[m_g] = 0;
	NB__model.linear[m_g] = 3;
	NB__model.model_char[m_g] = 1;
	NB__model.group_w[m_g] = 48;
	NB__model.group_h[m_g] = 48;
	NB__model.group_winw_min[m_g] = NB__model.group_w[m_g];
	NB__model.group_winw_max[m_g] = 136;
	NB__model.group_lv[m_g] = NB_MODEL_TYPE_LV_1;  // 大模型在第一层，小模型放下一层

	m_l = 0;
	NB__model.lv_buf_new_linear1_char[m_g] = NULL;//model_L1_W_0;
	NB__model.lv_buf_new_linear1_check_char[m_g] = model_L1_W_2_check;	
	NB__model.lv_buf_new_linear1_bias[m_g] = model_L1_B_2;
	NB__model.lv_buf_linear2[m_g] = model_L2_W_2;
	NB__model.lv_buf_linear2_bias[m_g] = model_L2_B_2[0];

	NB__model.lv_buf_new_linear1_db_index[m_g] = 1;
	NB__model.lv_buf_new_linear1_load_sn[m_g] = 1;
	
	NB__model.lv_linear_num[m_g] = 100;

	NB__model.lv_foundscore[m_g][m_l] = 0 * SCORE_BASE;//0;//500000;
	NB__model.lv_maybescore[m_g][m_l] = 2000000;//0;// NORMAL_SCORE;//0;

	NB__model.group_level[m_g] = m_l + 1;
	

	//半身 240314版本
	m_g ++;
	NB__model.group_type[m_g] = NB_MODEL_TYPE_TORSO;
	NB__model.eable[m_g] = 0;
	NB__model.linear[m_g] = 3;
	NB__model.model_char[m_g] = 1;
	NB__model.group_w[m_g] = 48;
	NB__model.group_h[m_g] = 56;
	NB__model.group_winw_min[m_g] = NB__model.group_w[m_g];
	NB__model.group_winw_max[m_g] = 136;
	NB__model.group_lv[m_g] = NB_MODEL_TYPE_LV_1;  // 大模型在第一层，小模型放下一层

	m_l = 0;
	NB__model.lv_buf_new_linear1_char[m_g] = NULL;//model_L1_W_0;
	NB__model.lv_buf_new_linear1_check_char[m_g] = model_L1_W_1_check;	
	NB__model.lv_buf_new_linear1_bias[m_g] = model_L1_B_1;
	NB__model.lv_buf_linear2[m_g] = model_L2_W_1;
	NB__model.lv_buf_linear2_bias[m_g] = model_L2_B_1[0];

	NB__model.lv_buf_new_linear1_db_index[m_g] = 0;
	NB__model.lv_buf_new_linear1_load_sn[m_g] = 1;
	
	NB__model.lv_linear_num[m_g] = 100;

	NB__model.lv_foundscore[m_g][m_l] = 0 * SCORE_BASE;//0;//500000;
	NB__model.lv_maybescore[m_g][m_l] = 2000000;//0;// NORMAL_SCORE;//0;

	NB__model.group_level[m_g] = m_l + 1;

	
	NB__model.group_item = m_g + 1;
		
	
	
	
	/**************************************
	配置识别的距离，不能小于模型
	距离的配置是基于第一组模型的W作为基础
	***************************************/
	
	/*
	3008
							胖					瘦
	50cm		脸			100					90
				头			160					140
				
	100cm		脸			45					40
				头			70					90
				半身		130					160
				
	150cm		脸			35					35
				头			65					55
				半身		110					95
				
	200cm		半身							80
	
	250cm		半身							70
	
	300cm 		半身							60
	
	*/		
	// 配置识别范围（W标准 实际像素）
	// min == max 		75%-》125%
	// min ！= max 		min-》max，每次递增，基于配置的数量
	NB__config.guess_Nearly_w = 180;//160; // 近距离大小/基于此判断使用远近模型
	NB__config.guess_Far_w = 64;
	User_Detect_Config_Set_Win(NB__config.guess_Far_w,NB__config.guess_Nearly_w);
	
	
	/**************************************
	按照支持的最高60HZ配置
	系统不同状态使用不同的大小
	最小模型大小，最大160，必须是8的倍数
	配置最小值必须大于等于全部模型中的最大值
	***************************************/
	NB__config.max_scaler_w[NB__DETECT_SYS_MODE_GLOBAL] = 104;//104;//120;//
	NB__config.max_scaler_h[NB__DETECT_SYS_MODE_GLOBAL] = 96;//88;//88;//120;//
	
	NB__config.max_scaler_w[NB__DETECT_SYS_MODE_MOTION] = 104;//120;////104;
	NB__config.max_scaler_h[NB__DETECT_SYS_MODE_MOTION] = 96;//88;//120;////104;

	// 根据识别逐步增加框大小
	NB__config.max_scaler_w[NB__DETECT_SYS_MODE_FOUND] = 88;//120;////120;//144;//128;
	NB__config.max_scaler_h[NB__DETECT_SYS_MODE_FOUND] = 96;//112;//128;//88;//120;////96;



	// 1帧最多比较得分次数
	NB__config.max_do_1win_item = 45;
	if(NB__config.max_do_1win_item < 25)
	{
		NB__config.max_do_1win_item = 25;
	}

	// 暗态(小于等于25fps)边缘强化功能
	NB__config.Dark_edge_enhancement = 0; 

	
	// 画框的模式
	// other	自动画框(全屏 + motion + 识别)
	// 2 			固定位置画框
	NB__config.win_location_mode = 1;


	// 是否使用motion
	NB__config.use_motion = 1;

	// 是否使用motion检测人离开
	NB__config.use_motion_body_l = 1;

	

	// motion在画框功能中使用的帧数
	// 0 			不使用次功能
	// 0xffff	画框策略使用完退出
	NB__config.mode_motion_wait_f = 100;//0xffff;//100; 
	NB__config.mode_motion_default_wait_f = NB__config.mode_motion_wait_f;


	// 识别信息在画框功能中使用的帧数
	// 0 			不使用次功能
	// 0xffff	画框策略使用完退出
	NB__config.mode_found_wait_f = 50;  
	NB__config.mode_found_default_wait_f = NB__config.mode_found_wait_f;
	// 无识别出现motion退出当前模式的帧数
	NB__config.mode_found_motion_wait_f = 6;

	
	// 固定位置画框的中心点
	NB__config.win_f_id_x0 = SENSOR_OUTPUT_SIZE / 2;
	NB__config.win_f_id_y0 = NB__config.win_f_id_x0;
	NB__config.win_f_id_y = 0;


	
	// 是否使用识别			0 不进行模型比较
	NB__config.use_found = 1;
	
	
	// 使用模型的模式
	// 0 任意识别成功停止当前帧后续运算
	// 1 匹配完全部模型
	NB__model.use_model_mode = 0;


	// 设置输出识别信息的周期
	NB__config.get_result_fid = 0;


	// 识别后的跟随功能
	NB__config.use_found_follow = 1; 
	NB__config.use_found_follow_times = 6;//10;//15; // 此功能执行的次数
	NB__config.use_found_follow_score = 1000000; // 最低分数
	
	
	// 识别范围
	NB__config.detect_max_xpiont = SENSOR_OUTPUT_SIZE; // 结束坐标
	NB__config.detect_max_ypiont = SENSOR_OUTPUT_SIZE;

	

	
	// 识别结果，是否使用亮度滤波
	NB__config.b_filter = 0;
	// 平均亮度的极限
	NB__config.b_filter_low_value = 30;
	NB__config.b_filter_hight_value = 220;


	
	// 特征值滤波   特征值中心区域
	NB__config.eigenvalue_filter = 1;  // 0 关闭   1 打开  
	
	NB__config.eigenvalue_all_0 = 90; // 数值0百分比  超过认为是误识别
	NB__config.eigenvalue_continuous_0 = 18; // 连续0的数量  超过认为是误识别
	
	NB__config.eigenvalue_bigitem = 1; // 大于平均值的百分比 小于是误识别
 	NB__config.eigenvalue_max_limit = 1; // 最大值最小阈值 小于是误识别
	NB__config.eigenvalue_ye_min_value = 1; // ye模型特定的点的特征值总和必须大于此值
	
	NB__config.eigenvalue_norm_limt = 500;//600; // 最小归一化norm值 小于是误识别


	
	/*
	跟踪功能
	*/
	// 是否使用跟踪
	NB__config.use_track = 0;
	// 跟踪功能使用帧数  
	NB__config.use_track_times = 10;//15;
	NB__config.use_track_score = 90;//15;
	
	// 识别结果，是否使用motion滤波
	NB__config.motion_filter = 0;
	if(NB__config.use_motion == 0)
	{
		NB__config.motion_filter = 0;
	}

	// 锁定跟踪的人
	NB__config.lock_found = 0;

	
	// 识别位置滤波
	NB__config.location_filter = 1;
	NB__config.each_fid_piex = 6;

	
	NB__config.get_buf = 0;

	
	NB__config.debug_win = 0;
	
	NB__config.debug_lv = NB__DEBUG_MODE_NO;//NB__DEBUG_MODE_USE_CLK;//NB__DEBUG_MODE_NO NB__DEBUG_MODE_DEBUG

	// 全局搜索的状况下使用
	// 多宫格使用配置
	User_Area_Config();

	// 计算需要的数据
	User_Detect_Config_Calculate();

	
	NB__detect_sys_mode = NB__DETECT_SYS_MODE_GLOBAL_START;
	NB__founddata.trigger = 0;	
	
	
}





void User_Detect_Project_Config(void)
{
	

	// 选择使用的项目
	// 需要确保在User_Config.h里打开了项目
	//NB__config.project_type = NB_PROJECT_GESTURE; // 手势 项目
	NB__config.project_type = NB_PROJECT_PEOPLE; // 人形项目
	// NB__config.project_type = NB_PROJECT_GESTURE_PEOPLE; // 手势人形

	
	//NB__config.project_type = NB_PROJECT_FOLLOW_FAN; // 风扇项目
	//NB__config.project_type = NB_PROJECT_POSTURE; // 姿态项目
	
	// printf("Updata Project:%d \n",NB__config.project_type);
	
	
}




void User_Detect_Buf_Init(void)
{
	
	if(NB__detect_buf_state == 1)
	{
		return;
	}

	
	// 16K
	/*init fe*/
	if(fe_init(FE_MODE_FE, 1, 0)) // 3
	{
		printf( "fe init fail\n");
	}
	fe_start();
	#if 0
	// 识别相关配置
	// 根据黑框设置画框策略

	if(user_bwin_w)
	{
		//user_bwin_w = (user_bwin_w * 39) >> 7;// 30%	 黑框确定大小后识别图标大小
		user_bwin_w = (user_bwin_w * 102) >> 7;// 80% 	黑框确定大小后识别图标大小
		User_Detect_Config_Set_Win(1,user_bwin_w );
		NB__config.win_f_id_x0 = user_bwin_x0;
		NB__config.win_f_id_y0 = user_bwin_y0;
		NB__config.win_f_id_y = user_bwin_y;
	}
	else
	{
		User_Detect_Config_Set_Win(0,0 );
		NB__config.win_f_id_x0 = SENSOR_OUTPUT_SIZE / 2;
		NB__config.win_f_id_y0 = NB__config.win_f_id_x0 + 20;
		NB__config.win_f_id_y = 0;
	}
	User_Detect_Config_Calculate();
	#endif

	// 清除识别用到的buf
	NB__detect_buf_deinit();

	// 申请识别用到的buf
	NB__detect_buf_init();

	
	//printf("-----------------User_Detect_Buf_Init xPortGetFreeHeapSize:%d buf state:%d wait:%ld  \n",xPortGetFreeHeapSize(),NB__detect_buf_state,NB__detect_buf_stop_wait);

	
	
}

void User_Detect_Buf_UnInit(void)
{
	
	if(NB__detect_buf_state == 0)
	{
		NB__detect_buf_stop_wait = 0;
		return;
	}

	NB__detect_buf_stop_wait = 1;	
	//printf("--------------User_Detect_Buf_UnInit xPortGetFreeHeapSize:%d buf state:%d wait:%ld \n",xPortGetFreeHeapSize(),NB__detect_buf_state,NB__detect_buf_stop_wait);

	
	
}

void User_Detect_Buf_UnInit_Action(void)
{
	//u8 i = 0;

	if(NB__detect_buf_stop_wait >= 5)
	{

		// 清除识别用到的buf
		NB__detect_buf_deinit();
			
		NB__febuf.write_item = 0;
		NB__febuf.read_item = 0;
		NB__febuf.read_index = 0;
		NB__febuf.write_index = 0;

		fe_stop();
		fe_uninit();
		
		//printf("--------------User_Detect_Buf_UnInit_Action xPortGetFreeHeapSize:%d buf state:%d wait:%ld \n",xPortGetFreeHeapSize(),NB__detect_buf_state,NB__detect_buf_stop_wait);
		NB__detect_buf_stop_wait = 0;

		#if 0
		// 识别相关配置
		user_bwin_w = 0;
		user_bwin_x0 = 0;
		user_bwin_y0 = 0;
		user_bwin_y = 0;
		#endif
	}
	else if(NB__detect_buf_stop_wait >= 2)
	{
		NB__detect_buf_stop_wait ++;
	}
	
	
	
}




