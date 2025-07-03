
#ifndef __NB__DETECT__
#define __NB__DETECT__


#include "nb_base.h"
#include "nb_track.h"




enum
{

	// 不输出debug信息
	NB__DEBUG_MODE_NO,	
	
	
	// 只输出错误信息
	NB__DEBUG_MODE_ERR,	
	
	// 输出全部的调试信息
	NB__DEBUG_MODE_DEBUG,	
	
	// 输出全部的调试信息 + 特征值信息
	NB__DEBUG_MODE_DEBUG_EIGENVALUE,	

	
	// 消耗时间
	NB__DEBUG_MODE_USE_CLK,	

	NB__DEBUG_MODE_END,
	
};


// 画框中心点位置

// 多宫格最多分成的组和每组参数的数量
#define NB__WIN_1AREA_MAX_G			6
#define NB__WIN_1G_MAX_ITEM			40




enum
{
	// 不使用宫格
	NB__WIN_AREA_NO,
	
	// 使用4宫格
	NB__WIN_AREA_MODE_4,


	// 使用9宫格 
	NB__WIN_AREA_MODE_9,
	
	// 使用16宫格
	NB__WIN_AREA_MODE_16,
	
	// 使用25宫格
	NB__WIN_AREA_MODE_25,	

	// 使用36宫格
	NB__WIN_AREA_MODE_36,	

	NB__WIN_AREA_MODE_END,
	
};


enum
{
	
	// 使用画面中心点
	NB__WIN_MID_WIN_MID = 0,
	
	// 使用四宫格
	NB__WIN_MID_4AREA_1 = 1,
	NB__WIN_MID_4AREA_2,
	NB__WIN_MID_4AREA_3,
	NB__WIN_MID_4AREA_4,
	
	
	// 使用九宫格
	NB__WIN_MID_9AREA_1 = 11,
	NB__WIN_MID_9AREA_2,
	NB__WIN_MID_9AREA_3,
	NB__WIN_MID_9AREA_4,
	NB__WIN_MID_9AREA_5,
	NB__WIN_MID_9AREA_6,
	NB__WIN_MID_9AREA_7,
	NB__WIN_MID_9AREA_8,
	NB__WIN_MID_9AREA_9,	
	
	// 使用16宫格
	NB__WIN_MID_16AREA_1 = 21,
	NB__WIN_MID_16AREA_2,
	NB__WIN_MID_16AREA_3,
	NB__WIN_MID_16AREA_4,
	NB__WIN_MID_16AREA_5,
	NB__WIN_MID_16AREA_6,
	NB__WIN_MID_16AREA_7,
	NB__WIN_MID_16AREA_8,
	NB__WIN_MID_16AREA_9,	
	NB__WIN_MID_16AREA_10,
	NB__WIN_MID_16AREA_11,
	NB__WIN_MID_16AREA_12,
	NB__WIN_MID_16AREA_13,
	NB__WIN_MID_16AREA_14,
	NB__WIN_MID_16AREA_15,
	NB__WIN_MID_16AREA_16,	

	// 使用25宫格
	NB__WIN_MID_25AREA_1 = 41,
	NB__WIN_MID_25AREA_2,
	NB__WIN_MID_25AREA_3,
	NB__WIN_MID_25AREA_4,
	NB__WIN_MID_25AREA_5,
	NB__WIN_MID_25AREA_6,
	NB__WIN_MID_25AREA_7,
	NB__WIN_MID_25AREA_8,
	NB__WIN_MID_25AREA_9,
	NB__WIN_MID_25AREA_10,
	NB__WIN_MID_25AREA_11,
	NB__WIN_MID_25AREA_12,
	NB__WIN_MID_25AREA_13,
	NB__WIN_MID_25AREA_14,
	NB__WIN_MID_25AREA_15,
	NB__WIN_MID_25AREA_16,
	NB__WIN_MID_25AREA_17,
	NB__WIN_MID_25AREA_18,
	NB__WIN_MID_25AREA_19,
	NB__WIN_MID_25AREA_20,
	NB__WIN_MID_25AREA_21,
	NB__WIN_MID_25AREA_22,
	NB__WIN_MID_25AREA_23,
	NB__WIN_MID_25AREA_24,
	NB__WIN_MID_25AREA_25,

	// 使用36宫格
	NB__WIN_MID_36AREA_1 = 71,
	NB__WIN_MID_36AREA_2,
	NB__WIN_MID_36AREA_3,
	NB__WIN_MID_36AREA_4,
	NB__WIN_MID_36AREA_5,
	NB__WIN_MID_36AREA_6,
	NB__WIN_MID_36AREA_7,
	NB__WIN_MID_36AREA_8,
	NB__WIN_MID_36AREA_9,
	NB__WIN_MID_36AREA_10,
	NB__WIN_MID_36AREA_11,
	NB__WIN_MID_36AREA_12,
	NB__WIN_MID_36AREA_13,
	NB__WIN_MID_36AREA_14,
	NB__WIN_MID_36AREA_15,
	NB__WIN_MID_36AREA_16,
	NB__WIN_MID_36AREA_17,
	NB__WIN_MID_36AREA_18,
	NB__WIN_MID_36AREA_19,
	NB__WIN_MID_36AREA_20,
	NB__WIN_MID_36AREA_21,
	NB__WIN_MID_36AREA_22,
	NB__WIN_MID_36AREA_23,
	NB__WIN_MID_36AREA_24,
	NB__WIN_MID_36AREA_25,
	NB__WIN_MID_36AREA_26,
	NB__WIN_MID_36AREA_27,
	NB__WIN_MID_36AREA_28,
	NB__WIN_MID_36AREA_29,
	NB__WIN_MID_36AREA_30,
	NB__WIN_MID_36AREA_31,
	NB__WIN_MID_36AREA_32,
	NB__WIN_MID_36AREA_33,
	NB__WIN_MID_36AREA_34,
	NB__WIN_MID_36AREA_35,
	NB__WIN_MID_36AREA_36,



	// 使用识别的中心点
	NB__WIN_MID_FOUND_MID = 120,	
	
	
	// 使用自定义的中心点
	NB__WIN_MID_CUSTOM_MID,	
	
	NB__WIN_MID_END,	
	
};
	
typedef struct NB__AREA_s_t
{
	u8 g_item;	// 每个多宫格有几组

	// 每组的信息
	u8 each_g_item[NB__WIN_1AREA_MAX_G];
	u8 each_g_table[NB__WIN_1AREA_MAX_G][NB__WIN_1G_MAX_ITEM];

	
}__attribute__((aligned(4))) NB__AREA_s;

typedef struct NB__AREA_MID_s_t
{

	u16 x0[NB__WIN_MID_END];
	u16 y0[NB__WIN_MID_END];
	u16 y[NB__WIN_MID_END];

}__attribute__((aligned(4))) NB__AREA_MID_s;





enum
{
	
	//NB__MB_FPS_120_100 = 0,
	NB__MB_FPS_60_50 = 0,
	NB__MB_FPS_30_25,
	NB__MB_FPS_15_12,
	NB__MB_FPS_8_6,
	NB__MB_FPS_4_3,
	NB__MB_FPS_2_1,
	NB__MB_FPS_END,
	
};



typedef struct NB__MB_MOTION_t
{
	// 0 无motion
	u8 state;

	// 0 未改变  1 左  2 右
	u8 direction;
	
	u32 f_id;
	u8 speed;
	u16 x;
	u16 y;
	u16 w;
	u16 h;
	u16 x0;
	u16 y0;

	// 亮度计算用到，节约算力
	u8 bx;
	u8 by;
	u8 bw;
	u8 bh;

	// 挥手
	u16 wave;
	u16 wave_x;
	u16 wave_y;
	u16 wave_w;
	u16 wave_h;
	//u16 wave_x0;
	//u16 wave_y0;
	
}__attribute__((aligned(4))) NB__MB_MOTION_t_s;


// motion leave
typedef struct NB__MB_MOTION_BODY_L_t_
{
	// 0 无
	// 1 左边
	// 2 右边
	u8 state;

	// 触发的fid
	u32 f_id;	
		
}__attribute__((aligned(4))) NB__MB_MOTION_BODY_L_t_s;



typedef struct NB__MB_Group_t
{
	int vts;
	
	int e;

	int ag;

	int dg;
	
}__attribute__((aligned(4))) NB__MB_Group_t_s;


extern u16 NB__MB_use_target;


extern u32 NB__environment_xs;

extern u16 NB__MB_b_low_item;
extern u16 NB__MB_b_narmal_item;
extern u16 NB__MB_b_hight_item;


extern u16 NB__MB_global_b;
extern u16 NB__MB_now_area_b;
extern u16 NB__MB_use_b;


extern u8 NB__MB_doaec_state;

extern u32 NB__MB_aec_globalb_h;

extern u8 NB__mb_fps;

extern u16 NB__set_v_v;
extern u16 NB__set_e_v;
extern u16 NB__set_ag_v;	
extern u16 NB__set_dg_v;


extern u16 NB__mb_do_target_times;


extern u8 NB__lv_score_item;

enum
{
	NB__MB_B_MESSAGE_ALL = 0,
	NB__MB_B_MESSAGE_HIGHT,
	NB__MB_B_MESSAGE_LOW,
	NB__MB_B_MESSAGE_NORMAL,
	NB__MB_B_MESSAGE_END,
	
};

// AEC各种版本选择
enum
{
	
	// 旧AEC 
	AEC_VER_OLD_NORMAL,
	
	// 旧AEC 云台项目，按照各种亮度策略调整亮度
	AEC_VER_OLD_CRADLE_B,
	
	AEG_GENERAL, // 標準模式
	
	AEG_PARTIAL, // 僅用畫面中心更新
	
	AEG_CUSTOM	 // 自定義模式
	
};

void NB__AEC_Fixed_Init(u8 model,u8 ag,u16 e);
void NB__AEC_Init(void);
void NB__MB_Sensor_Init(void);
void NB__MB_Init(void);
u8 NB__MB_always_doaec(u32 f_id,u16 x,u16 y,u16 w,u16 h);
void NB__AEC_Action(u8 motor_run,u32 *detected_cnt,u32 f_id,u16 x,u16 y,u16 w,u16 h);
void NB__New_MB_Action(u8 motor_run);
void NB__MB_do_aec(u32 f_id,u8 now_b,u8 set_b);

u8 NB__MB_area_b(u8 bx,u8 by,u8 bw,u8 bh,u16 b_message[NB__MB_B_MESSAGE_END][2]);
u8 NB__MB_b_distribution(u8 * p_btable,u16 b_len);

void NB__b_filter(u8 m_g,u16 b_x,u16 b_y,u16 b_w,u16 b_h);
u8 NB__motion_filter(u16 in_x,u16 in_y,u16 in_w,u16 in_h,u16 x,u16 y,u16 w,u16 h);

// void NB__last_found_b_filter(u8 m_g,u16 b_x,u16 b_y,u16 b_w,u16 b_h);

#define NB__MG_GROUP_MAX_ITEM						3 // 4


#define NB__GAMA_BASE_ADDR			0x40092800

#define NB__GAMA_ADDR_O_S				0x40
#define NB__GAMA_ADDR_O_E				0x74






enum
{
	
	NB__MB_GAMA_DEFAULT = 0,
	NB__MB_GAMA_L = 100,
	NB__MB_GAMA_M,
	NB__MB_GAMA_H,
	NB__MB_GAMA_HB_MB,
	NB__MB_GAMA_AUTO = 120,
	
};

extern u8 NB__MG_Mode;


void NB__MG_Init(void);
void NB__MG_Eable(u8 value);
void NB__MG_Set(u8 index);
void NB__MG_DGSet(u8 index);
void NB__MG_Data_AutoConfig(u8 min,u8 max,u8 to_min,u8 to_max);



#define		NB__USE_TYPE		char

// 硬件提供最多5个框可以使用
#define NB__PLANWIN_EACH_ID_ITEM														5

#define NB__SCALER_MAX																			160
#define 	add_scaler_w																			0//24
#define		add_scaler_h																			0//16


#define NB__ADD_SCALER_W_MAX																0
#define NB__ADD_SCALER_H_MAX																0



// 最多小框的数量
// (160 - 24) / 8 + 1    18 * 18
#define NB__1WIN_MAX_ITEM																		225
#define NB__USE_WIN_ITEM																		2


// 模型的组和层
#define NB__MODEL_MAX_GROUP																	5
#define NB__MODEL_MAX_LEVEL																	1

// 每种模型单位时间记录的数据
#define NB__RESULT_SAVE_MAX_ITEM														3


// 画框的组和层
#define NB__WINW_MAX_GROUP																	4
#define NB__WINW_MAX_ITEM																		10



// 预留的最大支持模型buf    3Xbuf(归一化之前char和之后shorts)
// 1152支持到模型最大64X128 32X32特征数据144 64X64特征数据576
// 96X96===>1296
//#define NB__MODEL_BUF_SIZE																1300//577//225


// 防止配置错误，增加检测功能
//#define NB__PLAN_WIN_CHECK_ERROR

// 采用偏移获取特征值，每次偏移像素  8的倍数
#define NB__RESULT_OFFSET_MIN_VALUE													8
#define NB__RESULT_OFFSET_MIN_VALUE_D(a)										((a)>> 3)


// 一次最少特征值数量   8X8===>9
#define NB__EIGENVALUE_MIN_NUMBER														9



/*
TRACK
*/
typedef enum 
{
	NB__TRACK_DATA_G_L_M = 0,
	NB__TRACK_DATA_G_L = 8,
	NB__TRACK_DATA_G_M,
	NB__TRACK_DATA_G_H,			 
	
	
}NB__TRACK_DATA_G_ENUM;


#define NB__TRACK_TARGET_ITEM			1


// 跟踪结果选择最有数据
#define NB__SORT_GOOD_ITEM			2// 9





// 获取硬件提供的buffer
//#define NB__RESULT_FE_BUF_SIZE														7300 //8000
#define NB__FE_BUF_ITEM																		  2//4
u8 NB__get_febuf_item(void);
void NB__febuf_full_action(void);

typedef struct NB__Fe_PPBuf_s_t
{

	// buf的索引
	u8 write_index;
	u8 read_index;

	// 读写数据的项，用来判断队列空/满
	u32 write_item;
	u32 read_item;
	
	
	u32 f_id[NB__FE_BUF_ITEM];
	
	// 实现pqbuf
	u8 in[NB__FE_BUF_ITEM];
	u8 out[NB__FE_BUF_ITEM];
	u8 read[NB__FE_BUF_ITEM];
	
	// 0 有数据 1 有数据
	u8 state[NB__FE_BUF_ITEM];

	// char 类型的个数
	u16 ch_size[NB__FE_BUF_ITEM];
	u8 *buf_ch[NB__FE_BUF_ITEM];
	int *buf_square;

	//u8 temp_data[NB__FE_BUF_ITEM][6];

	/******************坐标等信息*******************/
	// 设置的5个识别框的坐标  大小  使用的检测标本的模式
	short set_x[NB__FE_BUF_ITEM];
	short set_y[NB__FE_BUF_ITEM];

	// 宽高 
	short set_w[NB__FE_BUF_ITEM];
	short set_h[NB__FE_BUF_ITEM];
	
	// 画框的时候设置的scaler值
	u8 set_scalerw[NB__FE_BUF_ITEM]; 
	u8 set_scalerh[NB__FE_BUF_ITEM]; 

	// 画框传递到fe的参数

	// 保存的信息索引
	u16 win_to_fe_save_index[NB__FE_BUF_ITEM];
	//u16 index_u16[NB__FE_BUF_ITEM];
	
	#if 0
	// 保存识别的第一套模型的原始大小
	short real_w[NB__FE_BUF_ITEM][NB__PLANWIN_EACH_ID_ITEM]; 
	short real_h[NB__FE_BUF_ITEM][NB__PLANWIN_EACH_ID_ITEM]; 

	
	// scaler后可以进行的偏移次数
	u8 set_scalerw_t[NB__FE_BUF_ITEM][NB__PLANWIN_EACH_ID_ITEM][NB__MODEL_MAX_ITEM]; 
	u8 set_scalerh_t[NB__FE_BUF_ITEM][NB__PLANWIN_EACH_ID_ITEM][NB__MODEL_MAX_ITEM]; 
	#endif



}__attribute__((aligned(4))) NB__Fe_PPBuf_s;




typedef enum NB__Detect_Ret_Enum
{
	NB__DETECT_FAIL = 0,
	NB__DETECT_SUCCESS = 1,
}NB__Detect_Ret;


typedef enum NB__LENS_s_t
{
	
	
	NB__LENS_8P5_8P5,
	NB__LENS_8P499,

	
}NB__LENS_s;


typedef enum NB__Model_LV1_STATE_s_t
{
	
	NB_MODEL_LV1_STATE_START,
	NB_MODEL_LV1_STATE_NO,
	NB_MODEL_LV1_STATE_MAYBE,
	NB_MODEL_LV1_STATE_FOUND,
	
}NB__Model_LV1_STATE_s;



typedef enum NB__Model_Type_Lv_s_t
{
	
	NB_MODEL_TYPE_LV_START,
	NB_MODEL_TYPE_LV_1 = NB_MODEL_TYPE_LV_START,
	NB_MODEL_TYPE_LV_2,
	NB_MODEL_TYPE_LV_END,
	
}NB__Model_Type_Lv_s;


// 每种模型依次编号
// END模型种类的数量
// 手势-》耶
#define 	NB_MODEL_TYPE_GESTURE_YE							0
// 手势-》OK
//#define 	NB_MODEL_TYPE_GESTURE_OK						0
// 手势-》手掌
#define 	NB_MODEL_TYPE_GESTURE_FIVE						1
// 手势-》点赞
//#define 	NB_MODEL_TYPE_GESTURE_GOOD					0

// 手势-》拳头
//#define 	NB_MODEL_TYPE_GESTURE_FIST					0
// 脸
//#define 	NB_MODEL_TYPE_FACE									0
// 头	
#define 	NB_MODEL_TYPE_HEAD										2	
// 头肩
#define 	NB_MODEL_TYPE_HEADADD									3
// 半身
#define 	NB_MODEL_TYPE_TORSO										4
// 全身
//#define 	NB_MODEL_TYPE_FULLBODY							0

// 符号 -》左
//#define 		NB_MODEL_TYPE_SYMBOL_LEFT					0
// 符号 -》右
//#define 		NB_MODEL_TYPE_SYMBOL_RIGHT				1
// 符号 -》手掌
//#define 		NB_MODEL_TYPE_SYMBOL_FIVE					2
// 其他目标
//#define 	NB_MODEL_TYPE_OTHER									0

#define 		NB_MODEL_TYPE_END										5	



// 切换模型的原因
typedef enum NB__CHANGE_LOAD_BECAUSE_s_t
{
	
	CHANGE_LOAD_BECAUSE_NO,			// 
	CHANGE_LOAD_BECAUSE_CLOSE_OPEN,			// 
	CHANGE_LOAD_BECAUSE_TIMEOUE,			// 
	CHANGE_LOAD_BECAUSE_MOTION,	// 
	CHANGE_LOAD_BECAUSE_FOUND_SIZE,		// 
	CHANGE_LOAD_BECAUSE_NOFOUND_FN,			// 
	CHANGE_LOAD_BECAUSE_NOFOUND_HB,			// 
		
}NB__CHANGE_LOAD_BECAUSE_s;




typedef enum NB__SET_LOAD_STATE_s_t
{

	SET_LOAD_NO = 0,	// 未设置
	SET_LOAD_SAME,		// 设置相同
	SET_LOAD_OK,			// 设置成功
	
		
}NB__SET_LOAD_STATE_s_t;



typedef enum NB__Project_Type_s_t
{
	
	NB_PROJECT_START = 10,
	
	// 检测人
	NB_PROJECT_PEOPLE,

	// 检测手势+人
	NB_PROJECT_GESTURE_PEOPLE,

	
	// 姿态检测
	NB_PROJECT_POSTURE,
	
	// 跟随风扇
	NB_PROJECT_FOLLOW_FAN,
	
	// 手势
	NB_PROJECT_GESTURE,

	
	NB_PROJECT_END,
	
	
	// 婴儿监视器
	NB_PROJECT_BABY_MONITOR,
	
	// 智能开关
	NB_PROJECT_SMART_SWITCH,
	
	// 条形码检测
	NB_PROJECT_BAR_CODE,

	// 其他项目
	NB_PROJECT_OTHER,
	
}NB__Project_Type_s;


typedef enum NB__Far_Nearly_Change_s_t
{

	Far_Nearly_Change_NO = 0,
	Nearly_Far_Change,
	Far_Nearly_Change,
	
		
}NB__Far_Nearly_Change_s;


typedef enum NB__Headadd_Body_Change_s_t
{

	Headadd_Body_Change_NO = 0,
	Headadd_Body_Change,
	Body_Headadd_Change,
	
		
}NB__Headadd_Body_Change_s;




typedef enum NB__Found_Follow_s_t
{

	NB_FOUND_FOLLOW_START = 0,

	// 不使用
	NB_FOUND_FOLLOW_NOUSE = 10,

	// 使用
	NB_FOUND_FOLLOW_USE = 20,
	
	NB_FOUND_FOLLOW_END = 30,
	
}NB__Found_Follow_s;



extern u16 NB__search_1_w;

extern u8 NB__win_use_ofset;
//extern u8 NB__motion_loop_times;
extern u8 NB__found_follow_model;
extern u32 NB__found_run_f_id;

// 识别模式画框循环状态
typedef enum NB__Motion_Win_loop_State_s_t
{
	
	NB__MOTION_WIN_LOOP_NULL,
	
	// 有识别当前
	NB__MOTION_WIN_LOOP_FOUND_START,				// 1

	// 当前
	NB__MOTION_WIN_LOOP_START,							// 2
		
	// 最优策略
	NB__MOTION_WIN_LOOP_MUST,								// 3
	
	// 其他策略
	NB__MOTION_WIN_LOOP_OTHER,							// 4
	
	NB__MOTION_WIN_LOOP_END,
	
}NB__Motion_Win_loop_State_s;


extern u8 NB__found_loop_times;

// 识别模式画框循环状态
typedef enum NB__Found_Win_loop_State_s_t
{
	
	NB__FOUND_WIN_LOOP_NULL,
	
	// 首次识别开始
	NB__FOUND_WIN_LOOP_START = 10, // 10

	// 执行偏移画框
	NB__FOUND_WIN_LOOP_OFFSET = 20, // 20
	
	// 基于当前识别最优策略
	NB__FOUND_WIN_LOOP_FOUND = 30, // 30

	// 基于猜测最优策略
	NB__FOUND_WIN_LOOP_GUESS = 40, // 40
	
	// 其他策略
	NB__FOUND_WIN_LOOP_OTHER = 50, // 50
	
	
	NB__FOUND_WIN_LOOP_END,
	
}NB__Found_Win_loop_State_s;



/*  Detect Config  识别的配置文件*/
typedef struct NB__Detect_Config_s_t
{    
	
	u8 sys_clock;
	
	// 项目类型
	// 根据不同的项目，底层做不同处理
	u8 project_type;

	u8 lens;

	// 最大像素点
	u16 detect_max_xpiont;
	u16 detect_max_ypiont;

	u8 debug_model_mode;
	
	// Detect用的识别模式
	// NB__Detect_Mode_s_t
	u8 mode;

	
	// 亮度滤波   
	u8 b_filter;
	u8 b_filter_low_value;
	u8 b_filter_hight_value;

	
	// 特征值滤波
	// 1 归一化之后的特征值连续0
	// 2 中间得分小于四周得分
	u8 eigenvalue_filter;
	u8 eigenvalue_all_0; // 占总数的百分比
	u8 eigenvalue_continuous_0; // 连续0的项

	u16 eigenvalue_ye_min_value; // ye模型特定的点的特征值总和必须大于此值

	u8 eigenvalue_max_limit; // 最大值最小阈值
	
	// sensor滤波   
	u8 sensor_filter;
		
	// 数据阈值
	u16 eigenvalue_bigvalue;
	// 数据大于阈值的最少项
	u8 eigenvalue_bigitem;

	// 最小归一化norm值
	u16 eigenvalue_norm_limt;
	
	// 相同数据太多滤除
	u8 eigenvalue_same;
	
	// filter

	// motion滤波  ---> 输出一帧得分里最靠近motion的得分
	u8 motion_filter;

	
	// 上次识别滤波亮度---->检查上次识别是否改变，未改变不使用新的识别
	u8 lock_found;

	#define LAST_FOUND_B_ITEM			6
	// 上次识别亮度信息
	u8 last_found_state;
	u8 last_found_x;
	u8 last_found_y;
	u8 last_found_w;
	u8 last_found_h;
	u16 aec_e;
	u8 aec_ag;
	u8 last_found_b[LAST_FOUND_B_ITEM];  	// 6个位置的平均亮度
	

	// 识别位置滤波
	u8 location_filter;
	u8 each_fid_piex;
	
	
	// 每个循环使用多少帧
	//u8 loop_use_id;

	// 解决误识别的滤波设置
	// 滤波等级
	// 0 不滤，直接使用  输出一帧里最靠近上次识别的得分或者最高得分
	// 1 X或Y满足
	// 2 X和Y同时满足
	// 3 满足X的项并且满足Y
	u8 loop_findlv;
	// 最少得分数量
	//u8 loop_aitem;
	// 坐标最大误差
	u8 loop_errvalue;
	// 满足坐标误差后的最少得分项
	u8 loop_okitem;
	
	// 跟随功能
	u8 follow;
	// 跟随最大误差功能
	u8 follow_errvalue;

	// 脸部注册，需要保存buf
	u8 save_buf;

	u8 use_found;
	
	u8 use_found_follow;
	u8 use_found_follow_times;
	int use_found_follow_score;
	
	u8 use_track;
	u8 use_track_times;
	u8 use_track_score;
	
	
	u8 track_update_targe;
	u8 track_frequency;
	u8 track_1_fid_limit_max;
	u8 use_motion;
	u8 use_motion_body_l;

	// 猜距离大小
	u8 guess_Nearly_w;
	u8 guess_Far_w;
	
	// DEBUG等级
	// 0 不输出debug信息
	// 1 只输出错误信息
	// 2 输出全部的调试信息
	// 3 输出全部的调试信息 + 特征值信息
	u8 debug_lv;

	u8 debug_win;

	
	// W最大画框scaler
	u8 max_scaler_w[NB__DETECT_SYS_MODE_END];
	u8 max_scaler_h[NB__DETECT_SYS_MODE_END];

	// 有方向的时候，运算到上次识别的位置
	// 没方向的时候，识别为中心，运算配置数量
	u8 max_do_1win_item;

	u8 all_max_scaler_w;
	u8 all_max_scaler_h;
	
	u16 max_fe_buf_len;

	
	
	/************************
	识别距离配置
	************************/
	// 0 默认值向两边变化
	// 1 最小向最大变化    // 百分比增加
	// 2 最大向最小变化
	u8 chagemode;

	// 0 大小一直按照chagemode变化
	// 1 大小在有可能识别的时候固定
	u8 automode;

	// 过小的头不识别
	u16 use_min_head;
	
	// 过小的头不识别
	u16 use_max_shoulder;


	// 画框分组
	u8 winw_group;
	
	// 每组大小数量
	u8 winw_group_item[NB__WINW_MAX_GROUP]; 

	// 所有组大小的最大/最小
	u16 winw_max; 
	u16 winw_min;
	u16 winw_each_w[NB__WINW_MAX_GROUP][NB__WINW_MAX_ITEM]; // 每个大小

	// 从小到大排序
	u16 winw_sort_w[NB__WINW_MAX_GROUP * NB__WINW_MAX_ITEM];
	u16 winw_sort_w_item;

	// 聚焦使用的项
	// 初步定位后的策略持续时间
	u8 winw_focus_item;
	
	// 画框位置的模式
	// 0 始终全屏画框
	// 1 自动画框(全屏 + motion + 识别)
	// 2 固定位置画框
	u8 win_location_mode; // 使用全屏模式的画框控制
	
	// 固定位置画框的中心点
	u16 win_f_id_x0;
	u16 win_f_id_y0;//0;
	u16 win_f_id_y;//0;

	u16 mode_motion_default_wait_f;
	u16 mode_motion_wait_f;

	u32 mode_found_default_wait_f;
	u32 mode_found_motion_wait_f;
	u32 mode_found_wait_f;


	// FPS控制
	u8 default_fps;
	u8 min_fps;
	u8 max_fps;

	// 暗态边缘强化
	u8 Dark_edge_enhancement;

	
	// 亮度
	u8 mb_max_ag;
	u8 mb_max_dg;	

	u8 mb_bmin; 
	u8 mb_bmax; 
	u8 mb_btarget;


	// 亮度控制的模式
	// 0 设置标准亮度，aec调整到标准亮度
	// 1 云台项目，按照各种亮度策略调整亮度
	u8 mb_control_mode;  

	u8 pal_ntsc_mode;

	
	// 亮度循环周期及大小
	u8 mb_loop_global_f;    
	u8 mb_loop_found_f;    
	signed char mb_loop_b1;
	signed char mb_loop_b2;

	u8 gama_eable;
	
		
	//u8 mb_item;
	//u8 mb_table[10];

	// gama eable
	u8 mg_eable;

	u8 *mg_data;
	
	// gama range
	u8 mg_range;
	

	u8 get_buf;

	// 使用手势的时机
	u8 use_gesture_times;
	


	u8 get_result_fid;

	
	// 预留	
	//u8 config_rev3;
	//u8 config_rev4;
	//u8 config_rev5;
	//u8 config_rev6;
	//u8 config_rev7;
	//u8 config_rev8;
	//u8 config_rev9;

}__attribute__((aligned(4))) NB__Detect_Config_s;



/*  Plan Win In Shape */
typedef struct NB__PlanWin_In_Shape_s_t
{    
	//u16 motion_x;
	//u16 motion_y;

	// 需要使用者考虑宽高比的问题，此处的设置就是用作Scaler的宽高，不再做任何处理
	//u16 motion_w;
	//u16 motion_h;
	
	u16 x;
	u16 y;

	// 需要使用者考虑宽高比的问题，此处的设置就是用作Scaler的宽高，不再做任何处理
	u16 w;
	u16 h;
	//signed char size;


}__attribute__((aligned(4))) NB__PlanWin_In_Shape_s;

enum
{

	// 正识别模型
	NB__MODEL_POS,
	
	// 负识别模型
	NB__MODEL_NEG,
	
	
};



// 画框只会使用[0][0]来画框
typedef struct NB__User_Model_s_t
{    	
	// 支持模型组
	u8 group_item;

	// 模型组使用排序
	u8 group_use_index[NB__MODEL_MAX_GROUP];
	
			
	// 每组配置
	

	// 使能
	u8 eable[NB__MODEL_MAX_GROUP];
	u8 linear[NB__MODEL_MAX_GROUP];

	// 使用u8类型的模型
	u8 model_char[NB__MODEL_MAX_GROUP];

	
	// 模型种类
	u8 group_type[NB__MODEL_MAX_GROUP];
	

	// 是否使用   初始化设置为使用
	//u8 group_use[NB__MODEL_MAX_GROUP];

	
	// 大的模型在前面，先配置。画面会基于第一组模型
	u16 group_w[NB__MODEL_MAX_GROUP];
	u16 group_h[NB__MODEL_MAX_GROUP];
	u16 group_size[NB__MODEL_MAX_GROUP];


	// m_g使用顺序
	//u8 group_sort_item; // 数量
	//u8 group_sort_index[NB__MODEL_MAX_GROUP];
	
	
	// 使用顺序排序后，是否已经比较过 
	// 0 没有比较过  
	// 1比较过
	u8 group_compare_use[NB__MODEL_MAX_GROUP];
	

	// 所有模型最大特征值数量
	u16 group_max_datasize;

	// 所有组最大小框数量；
	u16 group_max_1winsize;

	u16 group_winw_min[NB__MODEL_MAX_GROUP];
	u16 group_winw_max[NB__MODEL_MAX_GROUP];

	// 模型层级
	u8 group_lv[NB__MODEL_MAX_GROUP];
	

	// 一次偏移改变的占原始大小的比值
	u8 group_1offset_w[NB__MODEL_MAX_GROUP];
	u8 group_eigenvalue_w_number[NB__MODEL_MAX_GROUP];	// 一行特征值数量
	u8 group_1offset_h[NB__MODEL_MAX_GROUP];

	
	// 每组层级及每级配置
	u8 group_level[NB__MODEL_MAX_GROUP];

	// 正负模型类型
	//u8 lv_type[NB__MODEL_MAX_GROUP][NB__MODEL_MAX_LEVEL];
	int *lv_buf[NB__MODEL_MAX_GROUP][NB__MODEL_MAX_LEVEL];

	
	int *lv_buf_linear1;

	#define		MAX_MODEL_BUF				75600//87040 // 85K	92160 // 90K	81920// 80K		87040 // 85K
	signed char *lv_buf_temp;


	
	// 使用int类型模型
	int *lv_buf_new_linear1[NB__MODEL_MAX_GROUP];
	int *lv_buf_new_linear1_check[NB__MODEL_MAX_GROUP];

	

	// 使用u8类型的模型
	signed char *lv_buf_new_linear1_char[NB__MODEL_MAX_GROUP];
	signed char *lv_buf_new_linear1_check_char[NB__MODEL_MAX_GROUP];


	int *lv_buf_new_linear1_bias[NB__MODEL_MAX_GROUP];	
	int *lv_buf_linear2[NB__MODEL_MAX_GROUP];
	long long int lv_buf_linear2_bias[NB__MODEL_MAX_GROUP];

	int lv_buf_new_linear1_len[NB__MODEL_MAX_GROUP];
	u8 lv_linear_num[NB__MODEL_MAX_GROUP];
	u8 lv_buf_new_linear1_db_index[NB__MODEL_MAX_GROUP];	// 模式存储在db中的位置，找到模型数据
	u8 lv_buf_new_linear1_load_sn[NB__MODEL_MAX_GROUP]; 	// 模型加载顺序，决定加载那个模型	1开始

	

	// 识别的分数
	// 跟随的时候的分数
	// 也许有识别的分数
	int lv_foundscore[NB__MODEL_MAX_GROUP][NB__MODEL_MAX_LEVEL];
	int lv_followscore[NB__MODEL_MAX_GROUP][NB__MODEL_MAX_LEVEL];
	int lv_maybescore[NB__MODEL_MAX_GROUP][NB__MODEL_MAX_LEVEL];
	//int lv_item[NB__MODEL_MAX_GROUP][NB__MODEL_MAX_LEVEL];

	// 使用模型的模式
	// 0 识别到不再匹配其他模型
	// 1 无论识别情况，匹配完全部模型
	u8 use_model_mode;

	
}__attribute__((aligned(4))) NB__User_Model_s;

/*  Plan Win In Scaler */
typedef struct NB__PlanWin_Scaler_s_t
{    
	// 画框的时候的Scaler大小
	/*
	和设置的画框的宽高对应
	硬件提供5个框，每个框w不能超过32，如果超过32，每32个大小会消耗一个硬件框，被占用的框就不能再使用
	h不受限制
	*/
	u16 set_w;
	u16 set_h;
	
}__attribute__((aligned(4))) NB__PlanWin_Scaler_s;


#define FOUND_DIRECTION_CHECK_ITEM		8
typedef struct NB__Found_Direction_s_t
{
	
	// 0 未改变	1 左  2 右
	u8 direction;

	// 现有的数据
	u8 item;
	
	u16 x0[FOUND_DIRECTION_CHECK_ITEM];
	
	//u16 y0[FOUND_DIRECTION_CHECK_ITEM];
	u16 y[FOUND_DIRECTION_CHECK_ITEM];
	
}__attribute__((aligned(4))) NB__Found_Direction_s;






/**********************************************************************/
/**********************************************************************/
/***********************保存识别信息的功能 START********************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
#define	NB_SAVE_DATA_ITEM																		25
#define	NB_SAVE_DATA_GUESS_ITEM															3//5

// DB数据加载模型的index
#define	NB_SAVE_DATA_MODEL_DB_INDEX_ITEM										100



typedef struct NB__SaveData_s_t
{
	// 识别信息
	// 模型类型
	u8 type;
	
	u32 f_id;
	
	u16 x0;
	u16 y0;
	u16 w;
	u8 b;
	

	
}__attribute__((aligned(4))) NB__SaveData_s;


extern u8 nb_savedata_item;
extern NB__SaveData_s NB__savedata[];
extern NB__SaveData_s NB__savedata_guess[];

// 每个模型识别次数
//extern u32 NB__savedata_modelfound[];
// 识别次数按照DB加载索引排序
//extern u32 NB__savedata_modelfound_guess[];


void NB__savedata_clean(void);
void NB__savedata_add(void);
void NB__savedata_guess_action(u8 type,u16 check_f_id);


/**********************************************************************/
/**********************************************************************/
/***********************保存识别信息的功能		END********************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/



typedef struct NB__Found_Message_s_t
{

	// 状态  0 没有识别
	u8 state;

	// 全部识别项
	u16 all_item;

	
	// 基于每种模型的识别结果
	int item[NB_MODEL_TYPE_END];
	
	u32 get_id[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];// 得到数据时的ID // 真正识别的ID
	u8 m_g[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	u8 m_l[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	u16 x[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	u16 y[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	u16 w[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	u16 h[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	u16 x0[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	u16 y0[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	int score[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];
	u8 angle[NB_MODEL_TYPE_END][NB__RESULT_SAVE_MAX_ITEM];

	// 选择的项
	u8 result_type;
	u8 result_item;


	
	u32 result_get_id;
	u8 result_m_g;
	u8 result_m_l;
	u16 result_x;
	u16 result_y;
	u16 result_w;
	u16 result_h;
	u16 result_x0;
	u16 result_y0;
	int result_score;
	u8 result_angle;

	u8 *after_buf;

	
	
}__attribute__((aligned(4))) NB__Found_Message_s;

// 投票信息
typedef struct NB__Vote_Message_s_t
{
	u8 state;

	// 参与项
	u8 item;
	
	// 存放分数最高的
	u8 m_g;
	u16 w;

	// 当前位置的信息
	//u8 item;
	u16 x0;
	u16 y;
	int score;

	// 总分
	int ascore;

	
}__attribute__((aligned(4))) NB__Vote_Message_s;


extern void debug_init(void);
extern void debug_enable(int enable);
extern void debug_enable_box(int id, int en, int sx, int sy, int ex, int ey);
extern void debug_enable_frame_bcd(int en, int sx, int sy);
extern unsigned int debug_get_frame_id_hex(void);
extern void debug_set_color(int color);
extern unsigned long intToBcd(int input);
extern void debug_enable_label(int id, int en, int value, int sx, int sy);


// 检测data2是否满足误差值
// 1 满足误差
u8 NB__check_value_error(u16 data1,u16 data2,u16 value);

void NB__detect_bottom_init(void);
void NB__detect_bottom_uninit(void);

NB__Detect_Ret NB__detect_bottom_win(u32 Frame_Id,u8 Item,NB__PlanWin_In_Shape_s Shape[],
	NB__PlanWin_Scaler_s Scaler[]);
void NB__detect_bottom_febuf(void);
void NB__detect_bottom_result(u8 select);


void NB__detect_bottom_test(void);


void NB__data_copy(char*a,char*b,u16 len);


void NB__sensor_mem_reset(void);
u8 *NB__sensor_data_get(u16 x,u16 y,u16 w,u16 h);



extern u16 *NB__buf_before_t;
extern NB__USE_TYPE *NB__buf_after_t;

extern NB__Fe_PPBuf_s NB__febuf;


extern NB__MB_MOTION_t_s NB__filter_motion;
extern NB__MB_MOTION_t_s NB__motor_motion;
extern NB__MB_MOTION_t_s NB__motion_head;
extern NB__MB_MOTION_t_s NB__motion_base;

typedef enum NB__Find_State_Enum
{

	// 	 未找到
	NB__Find_State_No,			   

	//   找到  
	NB__Find_State_Find, 		
	
	NB__Find_State_Find_Follow, 		

	NB__Find_State_Track, 		 

	NB__Find_State_motion,

	// 通过motion检测到人离开
	NB__Find_State_motion_body_l,
	
	
}NB__Find_State;


typedef enum NB__Track_State_Enum
{

	NB__Track_State_No,			   

	NB__Track_State_Wait, 		
	
	NB__Track_State_Doing, 		
 
	
	
}NB__Track_State;


#if 0

// win传参到fe
typedef enum NB__WIN_TO_FE_DATA_Enum
{

	// 全局画框
	NB__WIN_TO_FE_GLOBAL_START = 10,
	NB__WIN_TO_FE_GLOBAL = 20,

	// motion定位画框
	NB__WIN_TO_FE_MOTION_START = 30,
	NB__WIN_TO_FE_MOTION = 40,

	// found成功画框
	NB__WIN_TO_FE_FOUND_START = 50,
	NB__WIN_TO_FE_FOUND = 60,
	
	
}NB__WIN_TO_FE_DATA;


#endif


typedef enum NB__Motion_State_Enum
{

	// 	 未找到
	NB__Motion_State_No,

	NB__Motion_State_Found,
	
	NB__Motion_State_Soon_Wait, 

	
	NB__Motion_Body_Leave_Left, 
	NB__Motion_Body_Leave_Right, 
	
	//direction
	// 8421
	NB__Motion_Direction_Letf = 0x80, 		// 5	
	NB__Motion_Direction_Right = 0X40, 	// 6	

	NB__Motion_Direction_Up = 0X20, 			// 7	
	NB__Motion_Direction_Down = 0X10, 		// 8	


	// 加载模型使用
	NB__Motion_Model_Nouse, 		 	// 近
	NB__Motion_Model_Nearly, 		 	// 近
	NB__Motion_Model_Far, 				// 远
	
	
	
}NB__Motion_State;

typedef struct NB__save_buf_s_t
{
		
	//u8 buffer_item;
	
	// 每个CH得分索引+1
	u16 buffer_index;

	// 归一话之前的数据
	short *buf_bef;//[NB__MODEL_SAVE_BUF_SIZE];

	// 归一化之后的数据
	char *buf_aft;//[NB__MODEL_SAVE_BUF_SIZE];
	


}__attribute__((aligned(4))) NB__save_buf_s;


typedef struct NB__nobuf_location_rec_s_t
{

	u8 state; 
	//u16 size;
	
	u16 x;
	u16 y;
	u16 w;
	u16 h;

	// 中心点
	u16 x0;
	u16 y0;
 	
	int score;
 
}__attribute__((aligned(4))) NB__nobuf_location_rec_s;


typedef struct NB__result_filter_s_t
{
	u32 f_id;
	
	u16 x;
	u16 y;
	u16 w;
	u16 h;	
	
	//u16 x0;
	//u16 y0;	

	
	
}__attribute__((aligned(4))) NB__result_filter_s;


int sensor_mem_init(int endian_mode);
void sensor_mem_save_frame(void);
void * sensor_mem_get_ch_buf(int ch);
int save_pgm_to_host(char* name, uint8_t*buf,int width, int height);
void sensor_mem_save_sacler(struct scaler_wins_t *pwins);
void scaler_change_wins(struct scaler_wins_t *pwins);
int sensor_mem_wait_for_interrupt(unsigned int timeout);


//extern int *NB__found_follow_score_table[][];


extern NB__PlanWin_In_Shape_s NB__shape[];
extern NB__PlanWin_Scaler_s NB__scaler[];

extern NB__Detect_Config_s NB__config;
extern NB__User_Model_s NB__model;
extern NB__AREA_s NB__area_table[];
extern NB__AREA_MID_s NB__winmid;

extern NB__Found_Message_s *NB__Found_M;

//extern u8 NB__size_loop_times;
extern u8 NB__size_group;
extern u8 NB__size_group_w_index;

extern u8 NB__area_index;

extern u8 NB__found_change_times;
extern u8 NB__found_change_target;

extern u8 NB__motion_w_item;
extern u8 NB__motion_loop_w_index;

extern u8 NB__motion_x0y0item;
extern u8 NB__motion_loop_x0y0_index;


extern u8 NB__found_w_item;
extern u8 NB__found_loop_w_index;

extern u8 NB__found_x0y0_item;
extern u8 NB__found_loop_x0y0_index;


extern u8 NB__win_to_fe_save_index;



void NB__detect_mid_init(void);
void NB__detect_mid_uninit(void);
	
void NB__detect_mid_febuf(void);


void NB__detect_mid_win(u32 Frame_Id);

void NB__detect_mid_result(u8 select);

extern u16 NB__win_seach_w;
extern NB__Found_Message_s *NB__Found;
extern NB__Found_Direction_s NB__Found_Direction;

extern u8 NB__detect_buf_state;
extern u32 NB__detect_buf_stop_wait;

extern int NB__PlanWin_T;
extern int NB__FeW_T;
extern int NB__DetectW_T;
extern int NB__FoundW_T;

extern u32 NB__ATrack_T;
extern u32 NB__ADetectFollow_T;

extern u8 NB__run_win_f;
extern u8 NB__run_detect_f;

extern u8 NB__found_f;
extern u16 NB__loast;


extern u8 NB__filter_found_type[];

void NB__detect_location_filter(u8 select,u8 m_g,u16 x,u16 y,u16 w,u16 h);

void NB__detect_top_init(void);
void NB__detect_top_febuf(void);
void NB__detect_top(u8 select,u32 *detected_cnt,u32 *win_flow,u32 Frame_Id);
void NB__detect_top_win(u8 Enable,u32 *detected_cnt,u32 *win_flow,u32 Frame_Id);

uint16_t NB__cal_crc16(uint16_t crc, const uint8_t *buf, uint32_t len);


void NB__detect_buf_init(void);
void NB__detect_buf_deinit(void);



typedef struct NB__WinToFeData_s_t
{
	// 0 不可用
	// 1 可用
	u8 state;
	
	u32 f_id;

	u8 sys_state;

	u8 found_loop_times;
	
	u8 follow_state;
	u8 follow_model;

	
	u8 found_direction;
	
	
	// 亮度相关信息
	u8 b;  // 全局亮度
	u16 e; 
	u8 ag;
	u8 fps;

	// 画框信息
	u16 sx;
	u16 sy;
	u16 ex;
	u16 ey;

	u8 hsize;
	u8 vsize;	
	
}__attribute__((aligned(4))) NB__WinToFeData_s;




typedef struct NB__FoundData_s_t
{
	
	// 识别成功信息
	// START//

	// 识别时触发一次
	u8 trigger;

	u8 found_state;

	// 当前数据的帧ID
	u32 id; 
	u32 m_found_id;
	
	u8 type;

	u8 group;
	u8 level;
		
	u16 win_x;
	u16 win_y;
	u16 win_w;
	u16 win_h;
	
	u16 win_x0;
	u16 win_y0;
	// END//

	
	

}__attribute__((aligned(4))) NB__FoundData_s;


extern NB__WinToFeData_s NB__win_to_fedata[];
extern NB__FoundData_s NB__founddata;
extern NB__FoundData_s NB__tempfounddata;


extern u8 NB__found_run_times;

void NB__Set_Win_To_Fedata(void);
//NB__WinToFeData_s *NB__Get_Win_To_Fedata(void);


u8 NB__detect_top_check_result(void);




u8 NB__detect_mid_winsize_found_start(u16 *found_w);
void NB__detect_far_nearly_change(void);
u8 NB__nodetect_far_nearly_change(void);
u8 NB__nodetect_headadd_body_change(void);


void NB__sort(int *in_data,u8 *in_data_index,u16 len);
u16 NB__sort_max(int *in_data,u16 len);
float NB__invSqrt(float x);



u8 NB__load_model(u8 model_type,u8 model_id,NB__User_Model_s *model);
void NB__release_model(u8 model_type,NB__User_Model_s *model);

void NB__queue_del_item(u8 del_item,u8 a_item,u8 *queue_addr,u16 each_item_len);
void NB__queue_del_front_item(u8 del_item,u8 *a_item,u8 *queue_addr,u16 each_item_len);

u8 Seach_is_same(short in,short *table,u8 len, u8 per);




#endif


