
#ifndef __NB__DETECT__
#define __NB__DETECT__

#include "nb_base.h"

enum
{

	// 不输出debug信息
	NB_DEBUG_MODE_NO,

	// 只输出错误信息
	NB_DEBUG_MODE_ERR,

	// 输出全部的调试信息
	NB_DEBUG_MODE_DEBUG,

	// 输出全部的调试信息 + 特征值信息
	NB_DEBUG_MODE_DEBUG_EIGENVALUE,

	// 消耗时间
	NB_DEBUG_MODE_USE_CLK,

	NB_DEBUG_MODE_END,

};

// 画框中心点位置

// 多宫格最多分成的组和每组参数的数量
#define NB_WIN_1AREA_MAX_G 6
#define NB_WIN_1G_MAX_ITEM 40

enum
{
	// 不使用宫格
	NB_WIN_AREA_NO,

	// 使用4宫格
	NB_WIN_AREA_MODE_4,

	// 使用9宫格
	NB_WIN_AREA_MODE_9,

	// 使用16宫格
	NB_WIN_AREA_MODE_16,

	// 使用25宫格
	NB_WIN_AREA_MODE_25,

	// 使用36宫格
	NB_WIN_AREA_MODE_36,

	NB_WIN_AREA_MODE_END,

};

enum
{

	// 使用画面中心点
	NB_WIN_MID_WIN_MID = 0,

	// 使用四宫格
	NB_WIN_MID_4AREA_1 = 1,
	NB_WIN_MID_4AREA_2,
	NB_WIN_MID_4AREA_3,
	NB_WIN_MID_4AREA_4,

	// 使用九宫格
	NB_WIN_MID_9AREA_1 = 11,
	NB_WIN_MID_9AREA_2,
	NB_WIN_MID_9AREA_3,
	NB_WIN_MID_9AREA_4,
	NB_WIN_MID_9AREA_5,
	NB_WIN_MID_9AREA_6,
	NB_WIN_MID_9AREA_7,
	NB_WIN_MID_9AREA_8,
	NB_WIN_MID_9AREA_9,

	// 使用16宫格
	NB_WIN_MID_16AREA_1 = 21,
	NB_WIN_MID_16AREA_2,
	NB_WIN_MID_16AREA_3,
	NB_WIN_MID_16AREA_4,
	NB_WIN_MID_16AREA_5,
	NB_WIN_MID_16AREA_6,
	NB_WIN_MID_16AREA_7,
	NB_WIN_MID_16AREA_8,
	NB_WIN_MID_16AREA_9,
	NB_WIN_MID_16AREA_10,
	NB_WIN_MID_16AREA_11,
	NB_WIN_MID_16AREA_12,
	NB_WIN_MID_16AREA_13,
	NB_WIN_MID_16AREA_14,
	NB_WIN_MID_16AREA_15,
	NB_WIN_MID_16AREA_16,

	// 使用25宫格
	NB_WIN_MID_25AREA_1 = 41,
	NB_WIN_MID_25AREA_2,
	NB_WIN_MID_25AREA_3,
	NB_WIN_MID_25AREA_4,
	NB_WIN_MID_25AREA_5,
	NB_WIN_MID_25AREA_6,
	NB_WIN_MID_25AREA_7,
	NB_WIN_MID_25AREA_8,
	NB_WIN_MID_25AREA_9,
	NB_WIN_MID_25AREA_10,
	NB_WIN_MID_25AREA_11,
	NB_WIN_MID_25AREA_12,
	NB_WIN_MID_25AREA_13,
	NB_WIN_MID_25AREA_14,
	NB_WIN_MID_25AREA_15,
	NB_WIN_MID_25AREA_16,
	NB_WIN_MID_25AREA_17,
	NB_WIN_MID_25AREA_18,
	NB_WIN_MID_25AREA_19,
	NB_WIN_MID_25AREA_20,
	NB_WIN_MID_25AREA_21,
	NB_WIN_MID_25AREA_22,
	NB_WIN_MID_25AREA_23,
	NB_WIN_MID_25AREA_24,
	NB_WIN_MID_25AREA_25,

	// 使用36宫格
	NB_WIN_MID_36AREA_1 = 71,
	NB_WIN_MID_36AREA_2,
	NB_WIN_MID_36AREA_3,
	NB_WIN_MID_36AREA_4,
	NB_WIN_MID_36AREA_5,
	NB_WIN_MID_36AREA_6,
	NB_WIN_MID_36AREA_7,
	NB_WIN_MID_36AREA_8,
	NB_WIN_MID_36AREA_9,
	NB_WIN_MID_36AREA_10,
	NB_WIN_MID_36AREA_11,
	NB_WIN_MID_36AREA_12,
	NB_WIN_MID_36AREA_13,
	NB_WIN_MID_36AREA_14,
	NB_WIN_MID_36AREA_15,
	NB_WIN_MID_36AREA_16,
	NB_WIN_MID_36AREA_17,
	NB_WIN_MID_36AREA_18,
	NB_WIN_MID_36AREA_19,
	NB_WIN_MID_36AREA_20,
	NB_WIN_MID_36AREA_21,
	NB_WIN_MID_36AREA_22,
	NB_WIN_MID_36AREA_23,
	NB_WIN_MID_36AREA_24,
	NB_WIN_MID_36AREA_25,
	NB_WIN_MID_36AREA_26,
	NB_WIN_MID_36AREA_27,
	NB_WIN_MID_36AREA_28,
	NB_WIN_MID_36AREA_29,
	NB_WIN_MID_36AREA_30,
	NB_WIN_MID_36AREA_31,
	NB_WIN_MID_36AREA_32,
	NB_WIN_MID_36AREA_33,
	NB_WIN_MID_36AREA_34,
	NB_WIN_MID_36AREA_35,
	NB_WIN_MID_36AREA_36,

	// 使用识别的中心点
	NB_WIN_MID_FOUND_MID = 120,

	// 使用自定义的中心点
	NB_WIN_MID_CUSTOM_MID,

	NB_WIN_MID_END,

};

typedef struct NB_AREA_s_t
{
	u8 g_item;

	u8 each_g_item[NB_WIN_1AREA_MAX_G];
	u8 each_g_table[NB_WIN_1AREA_MAX_G][NB_WIN_1G_MAX_ITEM];

} __attribute__((aligned(4))) NB_AREA_s;

typedef struct NB_AREA_MID_s_t
{

	u16 x0[NB_WIN_MID_END];
	u16 y0[NB_WIN_MID_END];

} __attribute__((aligned(4))) NB_AREA_MID_s;

enum
{

	// NB_MB_FPS_120_100 = 0,
	NB_MB_FPS_60_50 = 0,
	NB_MB_FPS_30_25,
	NB_MB_FPS_15_12,
	NB_MB_FPS_8_6,
	NB_MB_FPS_4_3,
	NB_MB_FPS_2_1,
	NB_MB_FPS_END,

};

typedef struct NB_MB_MOTION_t
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

} __attribute__((aligned(4))) NB_MB_MOTION_t_s;

typedef struct NB_MB_Group_t
{
	int vts;

	int e;

	int ag;

	int dg;

} __attribute__((aligned(4))) NB_MB_Group_t_s;

extern u16 NB_MB_use_target;

extern u32 NB_environment_xs;

extern u16 NB_MB_b_low_item;
extern u16 NB_MB_b_narmal_item;
extern u16 NB_MB_b_hight_item;

extern u16 NB_MB_global_b;
extern u16 NB_MB_now_area_b;
extern u16 NB_MB_use_b;

extern u8 NB_MB_doaec_state;

extern u32 NB_MB_aec_globalb_h;

extern u8 NB_mb_fps;

extern u16 NB_set_v_v;
extern u16 NB_set_e_v;
extern u16 NB_set_ag_v;
extern u16 NB_set_dg_v;

extern u16 NB_mb_do_target_times;

enum
{
	NB_MB_B_MESSAGE_ALL = 0,
	NB_MB_B_MESSAGE_HIGHT,
	NB_MB_B_MESSAGE_LOW,
	NB_MB_B_MESSAGE_NORMAL,
	NB_MB_B_MESSAGE_END,

};

// AEC各种版本选择
enum
{

	// 旧AEC
	AEC_VER_OLD_NORMAL,

	// 旧AEC 云台项目，按照各种亮度策略调整亮度
	AEC_VER_OLD_CRADLE_B,

	// 新的常规AEC
	AEC_VER_NEW_GENERAL,

	// 新的姿势AEC
	AEC_VER_NEW_POSTURE,

};

void NB_AEC_Init(void);
void NB_MB_Sensor_Init(void);
void NB_MB_Init(void);
u8 NB_MB_always_doaec(u32 f_id, u16 x, u16 y, u16 w, u16 h);
void NB_AEC_Action(u8 motor_run, u32 *detected_cnt, u32 f_id, u16 x, u16 y, u16 w, u16 h);
void NB_New_MB_Action(u8 motor_run);
void NB_MB_do_aec(u32 f_id, u8 now_b, u8 set_b);

u8 NB_MB_area_b(u8 bx, u8 by, u8 bw, u8 bh, u16 b_message[NB_MB_B_MESSAGE_END][2]);
u8 NB_MB_b_distribution(u8 *p_btable, u16 b_len);

void NB_b_filter(u8 m_g, u16 b_x, u16 b_y, u16 b_w, u16 b_h);
void NB_motion_filter(u8 m_g, u16 x, u16 y, u16 w, u16 h);

#define NB_MG_GROUP_MAX_ITEM 3 // 4

#define NB_GAMA_BASE_ADDR 0x40092800

#define NB_GAMA_ADDR_O_S 0x40
#define NB_GAMA_ADDR_O_E 0x74

enum
{

	NB_MB_GAMA_DEFAULT = 0,
	NB_MB_GAMA_L = 100,
	NB_MB_GAMA_M,
	NB_MB_GAMA_H,
	NB_MB_GAMA_HB_MB,
	NB_MB_GAMA_AUTO = 120,

};

extern u8 NB_MG_Mode;

void NB_MG_Init(void);
void NB_MG_Eable(u8 value);
void NB_MG_Set(u8 index);
void NB_MG_DGSet(u8 index);
void NB_MG_Data_AutoConfig(u8 min, u8 max, u8 to_min, u8 to_max);

// 硬件提供最多5个框可以使用
#define NB_PLANWIN_EACH_ID_ITEM 5

#define NB_SCALER_MAX 160

#define NB_ADD_SCALER_W_MAX 24
#define NB_ADD_SCALER_H_MAX 16

// 最多小框的数量
// (160 - 24) / 8 + 1    18 * 18
#define NB_1WIN_MAX_ITEM 225

#define NB_USE_WIN_ITEM 2

// 模型的组和层
#define NB_MODEL_MAX_GROUP 6
#define NB_MODEL_MAX_LEVEL 20

// 画框的组和层
#define NB_WINW_MAX_GROUP 8
#define NB_WINW_MAX_ITEM 10

// 预留的最大支持模型buf    3Xbuf(归一化之前char和之后shorts)
// 1152支持到模型最大64X128 32X32特征数据144 64X64特征数据576
// 96X96===>1296
// #define NB_MODEL_BUF_SIZE																	1300//577//225

// 防止配置错误，增加检测功能
// #define NB_PLAN_WIN_CHECK_ERROR

// 采用偏移获取特征值，每次偏移像素  8的倍数
#define NB_RESULT_OFFSET_MIN_VALUE 8
#define NB_RESULT_OFFSET_MIN_VALUE_D(a) ((a) >> 3)

// 一次最少特征值数量   8X8===>9
#define NB_EIGENVALUE_MIN_NUMBER 9

/*
TRACK
*/
typedef enum
{
	NB_TRACK_DATA_G_L_M = 0,
	NB_TRACK_DATA_G_L = 8,
	NB_TRACK_DATA_G_M,
	NB_TRACK_DATA_G_H,

} NB_TRACK_DATA_G_ENUM;

#define NB_TRACK_TARGET_ITEM 1

// 跟踪结果选择最有数据
#define NB_SORT_GOOD_ITEM 4 // 9

// 获取硬件提供的buffer
// #define NB_RESULT_FE_BUF_SIZE														7300 //8000
#define NB_FE_BUF_ITEM 4

typedef struct NB_Fe_PPBuf_s_t
{
	u32 f_id[NB_FE_BUF_ITEM];

	// 实现pqbuf
	u8 in[NB_FE_BUF_ITEM];
	u8 out[NB_FE_BUF_ITEM];
	u8 read[NB_FE_BUF_ITEM];

	// 0 有数据 1 有数据
	u8 state[NB_FE_BUF_ITEM];

	// char 类型的个数
	u16 ch_size[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM];
	u8 *buf_ch[NB_FE_BUF_ITEM];

	// u8 temp_data[NB_FE_BUF_ITEM][6];

	/******************坐标等信息*******************/
	// 设置的5个识别框的坐标  大小  使用的检测标本的模式
	short set_x[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM];
	short set_y[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM];

	// 宽高
	short set_w[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM];
	short set_h[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM];

	// 画框的时候设置的scaler值
	u8 set_scalerw[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM];
	u8 set_scalerh[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM];

	// 画框传递到fe的参数

	// 系统状态
	u16 win_to_fe_sys_state[NB_FE_BUF_ITEM];

	// 识别状态下机制的位置
	u16 win_to_fe_found_loop_state[NB_FE_BUF_ITEM];

	// 识别状态下是否使用follow功能
	u16 win_to_fe_found_use_follow[NB_FE_BUF_ITEM];

	// 识别状态下模型的种类
	u16 win_to_fe_found_follow_model[NB_FE_BUF_ITEM];

	// 保存的信息索引
	u16 win_to_fe_save_index[NB_FE_BUF_ITEM];

#if 0
	// 保存识别的第一套模型的原始大小
	short real_w[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM]; 
	short real_h[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM]; 

	
	// scaler后可以进行的偏移次数
	u8 set_scalerw_t[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM][NB_MODEL_MAX_ITEM]; 
	u8 set_scalerh_t[NB_FE_BUF_ITEM][NB_PLANWIN_EACH_ID_ITEM][NB_MODEL_MAX_ITEM];
#endif

} __attribute__((aligned(4))) NB_Fe_PPBuf_s;

typedef enum NB_Detect_Ret_Enum
{
	NB_DETECT_FAIL = 0,
	NB_DETECT_SUCCESS = 1,
} NB_Detect_Ret;

typedef enum NB_LENS_s_t
{

	NB_LENS_8P5_8P5,
	NB_LENS_8P499,

} NB_LENS_s;

typedef enum NB_Model_Type_s_t
{

	NB_MODEL_TYPE_START = 0,

	// 脸
	NB_MODEL_TYPE_FACE = 10,

	// 头
	NB_MODEL_TYPE_HEAD = 20,

	// 头肩
	NB_MODEL_TYPE_HEADADD = 30,

	// 半身
	NB_MODEL_TYPE_TORSO = 40,

	// 手势-》手掌
	NB_MODEL_TYPE_GESTURE_GIVE_ME_FIVE = 50,

	// 手势-》点赞
	NB_MODEL_TYPE_GESTURE_GOOD,

	// 手势-》耶
	NB_MODEL_TYPE_GESTURE_YE,

	// 手势-》拳头
	NB_MODEL_TYPE_GESTURE_FIST,

	// 其他目标
	NB_MODEL_TYPE_OTHER,

	NB_MODEL_TYPE_END,

} NB_Model_Type_s;

typedef enum NB_Project_Type_s_t
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

} NB_Project_Type_s;

typedef enum NB_Found_Follow_s_t
{

	NB_FOUND_FOLLOW_START = 0,

	// 不使用
	NB_FOUND_FOLLOW_NOUSE = 10,

	// 使用
	NB_FOUND_FOLLOW_USE = 20,

	NB_FOUND_FOLLOW_END = 30,

} NB_Found_Follow_s;

extern u16 NB_search_1_w;

extern u8 NB_win_use_ofset;
extern u8 NB_motion_loop_times;
extern u8 NB_found_run_times;
extern u8 NB_found_follow_model;

// 识别模式画框循环状态
typedef enum NB_Motion_Win_loop_State_s_t
{

	NB_MOTION_WIN_LOOP_NULL,

	// 有识别当前
	NB_MOTION_WIN_LOOP_FOUND_START, // 1

	// 当前
	NB_MOTION_WIN_LOOP_START, // 2

	// 最优策略
	NB_MOTION_WIN_LOOP_MUST, // 3

	// 其他策略
	NB_MOTION_WIN_LOOP_OTHER, // 4

	NB_MOTION_WIN_LOOP_END,

} NB_Motion_Win_loop_State_s;

extern u8 NB_found_loop_times;
extern u8 NB_found_follow_state;

// 识别模式画框循环状态
typedef enum NB_Found_Win_loop_State_s_t
{

	NB_FOUND_WIN_LOOP_NULL,

	// 首次识别开始
	NB_FOUND_WIN_LOOP_START = 10, // 10

	// 执行偏移画框
	NB_FOUND_WIN_LOOP_OFFSET = 20, // 20

	// 基于当前识别最优策略
	NB_FOUND_WIN_LOOP_FOUND = 30, // 30

	// 基于猜测最优策略
	NB_FOUND_WIN_LOOP_GUESS = 40, // 40

	// 其他策略
	NB_FOUND_WIN_LOOP_OTHER = 50, // 50

	NB_FOUND_WIN_LOOP_END,

} NB_Found_Win_loop_State_s;

/*  Detect Config  识别的配置文件*/
typedef struct NB_Detect_Config_s_t
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
	// NB_Detect_Mode_s_t
	u8 mode;

	// 亮度滤波
	u8 b_filter;
	u8 b_filter_low_value;
	u8 b_filter_hight_value;

	// 特征值滤波
	// 1 归一化之后的特征值连续0
	// 2 中间得分小于四周得分
	u8 eigenvalue_filter;
	u8 eigenvalue_all_0;		// 占总数的百分比
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

	// 每个循环使用多少帧
	// u8 loop_use_id;

	// 解决误识别的滤波设置
	// 滤波等级
	// 0 不滤，直接使用  输出一帧里最靠近上次识别的得分或者最高得分
	// 1 X或Y满足
	// 2 X和Y同时满足
	// 3 满足X的项并且满足Y
	u8 loop_findlv;
	// 最少得分数量
	// u8 loop_aitem;
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

	// DEBUG等级
	// 0 不输出debug信息
	// 1 只输出错误信息
	// 2 输出全部的调试信息
	// 3 输出全部的调试信息 + 特征值信息
	u8 debug_lv;

	u8 debug_win;

	// W最大画框scaler
	u8 max_scaler_w[NB_DETECT_SYS_MODE_END];
	u8 max_scaler_h[NB_DETECT_SYS_MODE_END];

	u8 all_max_scaler_w;
	u8 all_max_scaler_h;

	u16 max_fe_buf_len;

	// 特征值比较是否跳过
	u8 jump;

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
	u8 winw_group_item[NB_WINW_MAX_GROUP];

	// 所有组大小的最大/最小
	u16 winw_max;
	u16 winw_min;
	u16 winw_each_w[NB_WINW_MAX_GROUP][NB_WINW_MAX_ITEM]; // 每个大小

	// 画框位置的模式
	// 0 始终全屏画框
	// 1 自动画框(全屏 + motion + 识别)
	// 2 固定位置画框
	u8 win_location_mode; // 使用全屏模式的画框控制

	// 固定位置画框的中心点
	u16 win_f_id_x0;
	u16 win_f_id_y0;

	u8 mode_found_default_wait_f;
	u8 mode_found_wait_f;

	u8 mode_motion_default_wait_f;
	u8 mode_motion_wait_f;

	// 每帧最多移动的像素点
	u8 each_fid_maxp;
	// 移动到画面外需要的帧数
	u8 min_m_fid;

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

	// 亮度控制的模式
	// 0 设置标准亮度，aec调整到标准亮度
	// 1 云台项目，按照各种亮度策略调整亮度
	u8 mb_control_mode;

	u8 pal_ntsc_mode;

	// 亮度循环周期及大小
	u8 mb_loop_global_f;
	u8 mb_loop_found_f;
	char mb_loop_b1;
	char mb_loop_b2;

	u8 gama_eable;

	// u8 mb_item;
	// u8 mb_table[10];

	// gama eable
	u8 mg_eable;

	u8 *mg_data;

	// gama range
	u8 mg_range;

	// 结果滤波   0-10
	u8 result_filter;

	// 按照一定频率输出结果
	u8 result_f;
	// 在没有结果的时候，通过motion来预测结果
	u8 result_motion;

	// 完全预测坐标
	u8 result_predict;

	u8 get_buf;

	// 预留

	u8 config_rev3;
	u8 config_rev4;
	u8 config_rev5;
	u8 config_rev6;
	u8 config_rev7;
	u8 config_rev8;
	u8 config_rev9;

} __attribute__((aligned(4))) NB_Detect_Config_s;

/*  Plan Win In Shape */
typedef struct NB_PlanWin_In_Shape_s_t
{
	// u16 motion_x;
	// u16 motion_y;

	// 需要使用者考虑宽高比的问题，此处的设置就是用作Scaler的宽高，不再做任何处理
	// u16 motion_w;
	// u16 motion_h;

	u16 x;
	u16 y;

	// 需要使用者考虑宽高比的问题，此处的设置就是用作Scaler的宽高，不再做任何处理
	u16 w;
	u16 h;
	// signed char size;

} __attribute__((aligned(4))) NB_PlanWin_In_Shape_s;

// 画框只会使用[0][0]来画框
typedef struct NB_User_Model_s_t
{
	// 支持模型组
	u8 group_item;

	// 每组配置

	// 模型种类
	u8 group_type[NB_MODEL_MAX_GROUP];

	// 大的模型在前面，先配置。画面会基于第一组模型
	u16 group_w[NB_MODEL_MAX_GROUP];
	u16 group_h[NB_MODEL_MAX_GROUP];
	u16 group_size[NB_MODEL_MAX_GROUP];

	// m_g使用顺序
	u8 group_sort_use[NB_MODEL_MAX_GROUP];

	// 使用顺序排序后，是否已经比较过
	// 0 没有比较过
	// 1比较过
	u8 group_compare_use[NB_MODEL_MAX_GROUP];

	// 所有模型最大特征值数量
	u16 group_max_datasize;

	// 所有组最大小框数量；
	u16 group_max_1winsize;

	u16 group_winw_min[NB_MODEL_MAX_GROUP];
	u16 group_winw_max[NB_MODEL_MAX_GROUP];

	// 一次偏移改变的占原始大小的比值
	u8 group_1offset_w[NB_MODEL_MAX_GROUP];
	u8 group_1offset_h[NB_MODEL_MAX_GROUP];

	// 每组层级及每级配置
	u8 group_level[NB_MODEL_MAX_GROUP];
	int *lv_buf[NB_MODEL_MAX_GROUP][NB_MODEL_MAX_LEVEL];

	// 识别的分数
	// 跟随的时候的分数
	// 也许有识别的分数
	int lv_foundscore[NB_MODEL_MAX_GROUP][NB_MODEL_MAX_LEVEL];
	int lv_followscore[NB_MODEL_MAX_GROUP][NB_MODEL_MAX_LEVEL];
	int lv_maybescore[NB_MODEL_MAX_GROUP][NB_MODEL_MAX_LEVEL];

	// 使用模型的模式
	// 0 识别到不再匹配其他模型
	// 1 无论识别情况，匹配完全部模型
	u8 use_model_mode;

} __attribute__((aligned(4))) NB_User_Model_s;

/*  Plan Win In Scaler */
typedef struct NB_PlanWin_Scaler_s_t
{
	// 画框的时候的Scaler大小
	/*
	和设置的画框的宽高对应
	硬件提供5个框，每个框w不能超过32，如果超过32，每32个大小会消耗一个硬件框，被占用的框就不能再使用
	h不受限制
	*/
	u16 set_w;
	u16 set_h;

} __attribute__((aligned(4))) NB_PlanWin_Scaler_s;

typedef struct NB_Found_Message_s_t
{

	// 状态  0 没有识别
	u8 state;

	// 真正识别的ID
	// 得到数据时的ID,组和层
	u32 get_id;

	u8 get_group;
	u8 get_level;

	u8 win_to_fe_sys_state;

	u16 x;
	u16 y;

	u16 w;
	u16 h;

	u16 x0;
	u16 y0;

	// 识别得分   follow分数
	int score[NB_MODEL_MAX_GROUP + 1][NB_MODEL_MAX_LEVEL + 1];

	// 归一化之后的buf
	u8 *after_buf;

} __attribute__((aligned(4))) NB_Found_Message_s;

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
u8 NB_check_value_error(u16 data1, u16 data2, u16 value);

void NB_detect_bottom_init(void);
void NB_detect_bottom_uninit(void);

NB_Detect_Ret NB_detect_bottom_win(u32 Frame_Id, u8 Item, NB_PlanWin_In_Shape_s Shape[],
								   NB_PlanWin_Scaler_s Scaler[]);
void NB_detect_bottom_febuf(void);
void NB_detect_bottom_result(u8 select);

void NB_detect_bottom_test(void);

void NB_data_copy(char *a, char *b, u16 len);

void NB_sensor_mem_reset(void);
u8 *NB_sensor_data_get(u16 x, u16 y, u16 w, u16 h);

extern u16 *NB_buf_before_t;
extern char *NB_buf_after_t;

extern NB_Fe_PPBuf_s NB_febuf;
extern u8 NB_set_scalerw_t;
extern u8 NB_set_scalerh_t;

extern NB_MB_MOTION_t_s NB_filter_motion;
extern NB_MB_MOTION_t_s NB_motor_motion;
extern NB_MB_MOTION_t_s NB_motion_head;

typedef enum NB_Find_State_Enum
{

	// 	 未找到
	NB_Find_State_No,

	//   找到
	NB_Find_State_Find,

	NB_Find_State_Find_Follow,

	NB_Find_State_Track,

} NB_Find_State;

typedef enum NB_Track_State_Enum
{

	NB_Track_State_No,

	NB_Track_State_Wait,

	NB_Track_State_Doing,

} NB_Track_State;

// win传参到fe
typedef enum NB_WIN_TO_FE_DATA_Enum
{

	// 全局画框
	NB_WIN_TO_FE_GLOBAL_START = 10,
	NB_WIN_TO_FE_GLOBAL = 20,

	// motion定位画框
	NB_WIN_TO_FE_MOTION_START = 30,
	NB_WIN_TO_FE_MOTION = 40,

	// found成功画框
	NB_WIN_TO_FE_FOUND_START = 50,
	NB_WIN_TO_FE_FOUND = 60,

} NB_WIN_TO_FE_DATA;

typedef enum NB_Motion_State_Enum
{

	// 	 未找到
	NB_Motion_State_No,

	NB_Motion_State_Found,

	NB_Motion_State_Soon_Wait,

	// edge
	NB_Motion_State_Letf,
	NB_Motion_State_Right, // edge

	// direction
	NB_Motion_Direction_Letf,  // 5
	NB_Motion_Direction_Right, // 6

} NB_Motion_State;

typedef struct NB_save_buf_s_t
{

	// u8 buffer_item;

	// 每个CH得分索引+1
	u16 buffer_index;

	// 归一话之前的数据
	short *buf_bef; //[NB_MODEL_SAVE_BUF_SIZE];

	// 归一化之后的数据
	char *buf_aft; //[NB_MODEL_SAVE_BUF_SIZE];

} __attribute__((aligned(4))) NB_save_buf_s;

typedef struct NB_nobuf_location_rec_s_t
{

	u8 state;
	// u16 size;

	u16 x;
	u16 y;
	u16 w;
	u16 h;

	// 中心点
	u16 x0;
	u16 y0;

	int score;

} __attribute__((aligned(4))) NB_nobuf_location_rec_s;

typedef struct NB_result_filter_s_t
{
	u32 f_id;

	u16 x;
	u16 y;
	u16 w;
	u16 h;

	// u16 x0;
	// u16 y0;

} __attribute__((aligned(4))) NB_result_filter_s;

int sensor_mem_init(int endian_mode);
void sensor_mem_save_frame(void);
void *sensor_mem_get_ch_buf(int ch);
int save_pgm_to_host(char *name, uint8_t *buf, int width, int height);
void sensor_mem_save_sacler(struct scaler_wins_t *pwins);
void scaler_change_wins(struct scaler_wins_t *pwins);
int sensor_mem_wait_for_interrupt(unsigned int timeout);

// extern int *NB_found_follow_score_table[][];

extern NB_PlanWin_In_Shape_s NB_shape[];
extern NB_PlanWin_Scaler_s NB_scaler[];

extern NB_Detect_Config_s NB_config;
extern NB_User_Model_s NB_model;

extern NB_Found_Message_s *NB_Found_M;

extern u8 NB_size_loop_times;
extern u8 NB_size_group;
extern u8 NB_size_group_w_index;

extern u8 NB_area_index;

extern u8 NB_motion_w_item;
extern u8 NB_motion_loop_w_index;

extern u8 NB_motion_x0y0item;
extern u8 NB_motion_loop_x0y0_index;

extern u8 NB_found_w_item;
extern u8 NB_found_loop_w_index;

extern u8 NB_found_x0y0_item;
extern u8 NB_found_loop_x0y0_index;

extern u8 NB_win_to_fe_save_index;

void NB_detect_mid_init(void);
void NB_detect_mid_uninit(void);

void NB_detect_mid_config(NB_Detect_Config_s configin,
						  NB_User_Model_s modelin, NB_AREA_s *area, NB_AREA_MID_s winmid);

void NB_detect_mid_febuf(void);

void NB_detect_mid_win(u32 Frame_Id);

void NB_detect_mid_result(u8 select);

extern NB_Found_Message_s *NB_Found;

extern u8 NB_buf_state;

extern int NB_PlanWin_T;
extern int NB_FeW_T;
extern int NB_DetectW_T;
extern int NB_FoundW_T;

extern u32 NB_ATrack_T;
extern u32 NB_ADetectFollow_T;

extern u8 NB_run_win_f;
extern u8 NB_found_f;

void NB_detect_top_init(void);
void NB_detect_top_config(NB_Detect_Config_s configin,
						  NB_User_Model_s modelin, NB_AREA_s *area, NB_AREA_MID_s user_winmid);
void NB_detect_top_febuf(void);
void NB_detect_top(u8 select, u32 *detected_cnt, u32 *win_flow, u32 Frame_Id);
void NB_detect_top_win(u8 Enable, u32 *detected_cnt, u32 *win_flow, u32 Frame_Id);

uint16_t NB_cal_crc16(uint16_t crc, const uint8_t *buf, uint32_t len);

void NB_detect_buf_init(void);
void NB_detect_buf_deinit(void);

typedef struct NB_WinToFeData_s_t
{
	// 0 不可用
	// 1 可用
	u8 state;

	u32 f_id;

	// 亮度相关信息
	u8 b; // 全局亮度
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

} __attribute__((aligned(4))) NB_WinToFeData_s;

typedef struct NB_FeData_s_t
{

	// 特征值比较信息
	u16 fe_sx;
	u16 fe_sy;
	u16 fe_ex;
	u16 fe_ey;

	u8 fe_hsize;
	u8 fe_vsize;

	// 设置每个模型	NB_MODEL_MAX_GROUP

	// 小框行列数量
	u8 win_1_offset_w_t[NB_MODEL_MAX_GROUP];
	u8 win_1_offset_h_t[NB_MODEL_MAX_GROUP];

	// 每个小框行列偏移1次对应原始像素点

	// 目标大小
	u8 win_1_w[NB_MODEL_MAX_GROUP];
	u8 win_1_h[NB_MODEL_MAX_GROUP];

	// 每个小框每个模型得分情况
	//  根据NB_found_follow_score_table获取

	// 识别成功信息
	// START//

	// 识别时触发一次
	u8 trigger;

	// 当前数据的帧ID
	unsigned int id;

	u8 group;
	u8 level;

	// 临近模型
	u8 near_group[20];
	u8 near_group_item;

	u16 win_x;
	u16 win_y;
	u16 win_w;
	u16 win_h;

	u16 win_x0;
	u16 win_y0;
	// END//

} __attribute__((aligned(4))) NB_FeData_s;

extern NB_WinToFeData_s NB_win_to_fedata[];
extern NB_FeData_s NB_fedata;

void NB_Set_Win_To_Fedata(void);
void NB_Set_Fedata_f(u8 select);
void NB_Set_Fedata_mg(u8 m_g);
NB_WinToFeData_s *NB_Get_Win_To_Fedata(void);

u8 NB_detect_top_check_result(void);

#endif
