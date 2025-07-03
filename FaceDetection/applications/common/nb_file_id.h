/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#ifndef __FILE_ID_H__
#define __FILE_ID_H__

/*FW file*/
#define FW_PMU                          0

/*SETTING*/
#define SET_BCF                         0
#define SET_SCF                         1

#define SET_SENSOR_AGC_TABLE_OV                10

#define SET_SENSOR_EXP_TABLE_7670_AC50         20
#define SET_SENSOR_I2C_TABLE_7670_AC50         21
#define SET_SENSOR_EXP_TABLE_7670_AC60         22
#define SET_SENSOR_I2C_TABLE_7670_AC60         23

#define SET_SENSOR_EXP_TABLE_7725_AC50         25
#define SET_SENSOR_I2C_TABLE_7725_AC50         26
#define SET_SENSOR_EXP_TABLE_7725_AC60         27
#define SET_SENSOR_I2C_TABLE_7725_AC60         28

#define SET_SENSOR_I2C_TABLE_BFA02             30


/*DB*/
#define DB_KWS_DEFAULT                  0
#define DB_KWS_EN                       1
#define DB_KWS_CN                       2

#define DB_FACE_VECTOR                  10
#define DB_FACE_VECTOR_EDGE_REMOVE      11
#define DB_DETECT_WIN_PARA              12

#define DB_HEAD_VECTOR                  20
#define DB_HEAD2_VECTOR                 21
#define DB_TORSO_VECTOR                 22
#define DB_BODY_VECTOR                  23

#define DB_MATH_RFFT_TABLE_Q15          40
#define DB_MATH_RFFT_TABLE_Q31          41
#define DB_MATH_RFFT_TABLE_F32          42

/*AUD file fid*/
#define PCM_BOOT_SOUND					0	// 我是 N B 1 00 1
#define PCM_FIND_YOU					1	// 我发现你了
#define PCM_HELLO_MASTER                2	// 主人你好
#define PCM_HELLO_MASTER_2              3	// 主人抱抱我
#define PCM_HELLO_SEE_ME                4   // 小朋友看着我,轻轻摇一摇头
#define PCM_I_CANOT_SEE                 5   // 小朋友我看不清楚
#define PCM_HUMANOID_DETECTION_MODE		6	// 人形检测模式
#define PCM_FACE_RECOGNITION_MODE		7	// 人脸识别模式
#define PCM_NOT_MASTER                  8	// 你不是我主人
#define PCM_NOT_MASTER_NOT_TOUCH_ME     9	// 你不是我主人，请不要碰我
#define PCM_BUZZER                      10	// 蜂鸣声
#define PCM_AUDIO_16K_16_STEREO         11	// 一段16K16bit的音乐文件
#define PCM_5S_NEXT                     12  // 5s 后开始下一个的注册
#define PCM_THE_FIRST                   13  // 第一个
#define PCM_THE_SECOND                  14  // 第二个
#define PCM_THE_THIRD                   15  // 第三个

#if 0
#define PCM_FIND_YOU					0	// 发现你了
#define PCM_HELLO						1	// 主人好
#define PCM_RECOGNIZE					2	// 我好像忘了重新认识一下吧
#define PCM_FIRST_TIME					3	// 初次见面请多指教
#define PCM_LOOK_ME						4	// 让我看见你
#define PCM_HELLO_MICHAEL				5	// Michael 你好
#define PCM_HUMANOID_DETECTION_MODE		6	// 人形检测模式
#define PCM_FACE_RECOGNITION_MODE		7	// 人脸识别模式
#define PCM_ENTRE_TRAINING_MODE			8	// 进入训练模式
#define PCM_SAVE_IMG					9	// 保存图片
#define PCM_END_SAVE_IMG				10	// 结束保存
#define PCM_IN_MEMORY					11	// 记忆中
#define PCM_END_MEMORY					12	// 记住啦
#define PCM_HERE                        13	// 我在这里
#define PCM_NOT_MASTER                  14	// 你不是我主人
#define PCM_HELLO_SEE_ME                15	// 你好小朋友请看着我轻轻摇摇头
#define PCM_ARE_YOU_MASTER              16	// 你是主人吗
#define PCM_NOT_MASTER_NOT_TOUCH_ME     17	// 你不是我主人，请不要碰我
#define PCM_RECORD_1_PEOPLE     		18	// 记录第一个人
#define PCM_RECORD_2_PEOPLE     		19
#define PCM_RECORD_3_PEOPLE     		20
#define PCM_RECORD_4_PEOPLE     		21
#define PCM_RECORD_5_PEOPLE     		22
#define PCM_DETECT_1_PEOPLE     		23	// 识别到是第一个人
#define PCM_DETECT_2_PEOPLE     		24
#define PCM_DETECT_3_PEOPLE     		25
#define PCM_DETECT_4_PEOPLE     		26
#define PCM_DETECT_5_PEOPLE     		27
#define PCM_WELCOME						28  // 欢迎光临
#define PCM_ROCK						29	// 我出拳
#define PCM_SCISSORS					30	// 我出剪
#define PCM_PAPER						31	// 我出布
#define PCM_YOU_WIN						32	// 你猜赢了
#define PCM_YOU_LOST					33	// 你猜输了
#define PCM_DRAW						34	// 和局
#define PCM_HELLO_CAROL					35	// hello, carol
#define PCM_FIND_YOU_CAROL				36	// I find you, carol
#define PCM_FIND_YOU_2				    37	// 发现你了(标准普通话)
#define PCM_I_AM_AI     				38	// 我是人工智能
#endif

#define PCM_KWS_CN  					20
#define PCM_KWS_EN  					21
#define PCM_KWS_UP  					22
#define PCM_KWS_DOWN  					23
#define PCM_KWS_LEFT  					24
#define PCM_KWS_RIGHT  					25
#define PCM_KWS_YES  					26
#define PCM_KWS_NO  					27

#define PCM_STARTUP_DOORBELL            30
#define PCM_STARTUP_KWS                 31
#define PCM_STARTUP_QR                  32
#define PCM_STARTUP_TOY                 33

#define PCM_QR_OK                       40

#define PCM_NONE						0xFF

#endif