//******************************************************************************
// Copyright (C) 2021 NeuronBasic Co., Ltd. All rights reserved.
//
// File        : sensor_aeg.h
// Description : Sensor Auto Exposure/Gain Control.
// Author      : AE
// Creat Date  : 2021-06-04
// Last Update : 2023-04-13
// Version     : V3.4
//
//******************************************************************************

#ifndef __SENSOR_AEG_H__
#define __SENSOR_AEG_H__

// AEG应用工程
#define MACR_AEG_APPLICATION_PROJECT_GENERAL                1 // 常规应用，无特定要求
#define MACR_AEG_APPLICATION_PROJECT_PARTIAL                2 // 特定应用，仅局部调整
#define MACR_AEG_APPLICATION_PROJECT_CUSTOM                 3 // 自定义应用

// 供电频率配置
#define MACR_AEG_AC_FREQ_CFG_50HZ                           1 // 供电频率为50Hz
#define MACR_AEG_AC_FREQ_CFG_60HZ                           2 // 供电频率为60Hz

// AEG策略定义
#define MACR_AEG_STRATEGY_METERING_MIX                      0 // 混合型测光调整策略
#define MACR_AEG_STRATEGY_METERING_SPOT                     1 // 单点型测光调整策略

// 应用识别模式定义
#define MACR_AEG_APP_DETE_MODE_NONE                         0 // 无识别模式
#define MACR_AEG_APP_DETE_MODE_FACE                         1 // 人脸识别模式
#define MACR_AEG_APP_DETE_MODE_HEAD                         2 // 人头识别模式
#define MACR_AEG_APP_DETE_MODE_HEADADD                      3 // 头肩识别模式
#define MACR_AEG_APP_DETE_MODE_TORSO                        4 // 半身识别模式
#define MACR_AEG_APP_DETE_MODE_GESTURE                      5 // 手势识别模式
#define MACR_AEG_APP_DETE_MODE_UND_NREF                     6 // 未定义识别模式，无可参考区域
#define MACR_AEG_APP_DETE_MODE_UND_CREF                     7 // 未定义识别模式，中央区域可参考

// 帧率定义
#define MACR_AEG_FRM_RATE_NONE                              0 // 无效帧率
#define MACR_AEG_FRM_RATE_12_5FPS                           1 // 12.5FPS, 50Hz
#define MACR_AEG_FRM_RATE_15FPS                             2 // 15FPS, 60Hz
#define MACR_AEG_FRM_RATE_25FPS                             3 // 25FPS, 50Hz
#define MACR_AEG_FRM_RATE_30FPS                             4 // 30FPS, 60Hz
#define MACR_AEG_FRM_RATE_50FPS                             5 // 50FPS, 50Hz
#define MACR_AEG_FRM_RATE_60FPS                             6 // 60FPS, 60Hz
#define MACR_AEG_FRM_RATE_100FPS                            7 // 100FPS, 50Hz
#define MACR_AEG_FRM_RATE_120FPS                            8 // 120FPS, 60Hz
#define MACR_AEG_FRM_RATE_LAST                              MACR_AEG_FRM_RATE_120FPS
// 可选帧率数量
#define MACR_AEG_FRM_RATE_NUM                               MACR_AEG_FRM_RATE_LAST

// 工作模式定义
// 注意：以常规工作模式起始，在常规模式下收集到合适的轮询参数后，其它工作模式才可生效
#define MACR_AEG_WORK_MODE_NONE                             0 // 无效的工作模式
#define MACR_AEG_WORK_MODE_REGULAR                          1 // 常规工作模式（默认）
#define MACR_AEG_WORK_MODE_FAST_PARA_POLL                   2 // 快速参数轮询模式
#define MACR_AEG_WORK_MODE_GENERAL_PARA_POLL                3 // 普通参数轮询模式

// 快速轮询模式的参数
#define MACR_AEG_FAST_POLL_PARA_AUTO                        0 // 自动选择合适的参数进行轮询
#define MACR_AEG_FAST_POLL_PARA_AUTO_NO_FINE_TUNING         1 // 自动选择合适的参数进行轮询（无微调）
#define MACR_AEG_FAST_POLL_PARA_AUTO_NO_COARSE_REDUCE       2 // 自动选择合适的参数进行轮询（无粗调-降低）
#define MACR_AEG_FAST_POLL_PARA_FORCE_FINE_TUNING           3 // 强制上下微调成像参数进行轮询
#define MACR_AEG_FAST_POLL_PARA_FORCE_COARSE_REDUCE         4 // 强制粗调（降低）成像参数进行轮询
#define MACR_AEG_FAST_POLL_PARA_FORCE_WITH_EXTERNAL         5 // 通过外部设置参的数进行轮询

// 低功耗模式选项定义，其耗能情况：无>低>中>高
#define MACR_AEG_LPM_OPT_NONE								0 // 低功耗模式选项：无
#define MACR_AEG_LPM_OPT_LOW								1 // 低功耗模式选项：低
#define MACR_AEG_LPM_OPT_MID								2 // 低功耗模式选项：中
#define MACR_AEG_LPM_OPT_HIGH								3 // 低功耗模式选项：高

// Gamma控制选项定义
#define MACR_AEG_GAMMA_OPT_OFF                              0 // 关闭Gamma
#define MACR_AEG_GAMMA_OPT_ON_GENERAL                       1 // 启用Gamma，配置为常规Gamma曲线
#define MACR_AEG_GAMMA_OPT_ON_AUTO_FULL                     2 // 启用Gamma，通过环境判断自动切换Gamma曲线（全场景切换检测）
#define MACR_AEG_GAMMA_OPT_ON_AUTO_BL                       3 // 启用Gamma，通过环境判断自动切换Gamma曲线（仅背光场景切换检测）

// 外部参数控制
#define MACR_AEG_EPC_ELPM_DLY_TIME_s                        1 // 延迟进入低功耗模式的时间（单位：秒）
#define MACR_AEG_EPC_MD_CALC_FRM_NUM                        2 // Motion用于计算时的帧数
#define MACR_AEG_EPC_LPF_ON_FRM_NUM                         3 // 低功耗过程中灯光闪烁-开启帧数（检测Motion）
#define MACR_AEG_EPC_LPF_OFF_TIME_ms                        4 // 低功耗过程中灯光闪烁-关闭时间（降低功耗，单位：ms）

typedef struct _sensor_aeg_custom_app_info_structure
{
	volatile unsigned char valid_flag;					      // 信息有效标记，0 or 1
	volatile unsigned char adjust_strategy;                   // 调整策略，MACR_AEG_STRATEGY_METERING_MIX or MACR_AEG_STRATEGY_METERING_SPOT
	volatile unsigned char frm_rate_max;					  // 最高工作帧率（起始帧率为最高帧率），MACR_AEG_FRM_RATE_12_5FPS ~ MACR_AEG_FRM_RATE_60FPS
	volatile unsigned char frm_rate_min;					  // 最低工作帧率，MACR_AEG_FRM_RATE_12_5FPS ~ MACR_AEG_FRM_RATE_60FPS
	volatile unsigned char lpm_opt;							  // 低功耗模式选项
	volatile unsigned char light_level_max;					  // 可支持的最大灯光等级
	volatile unsigned char light_level_min;					  // 可支持的最小灯光等级
	volatile unsigned char ana_gain_max;		    		  // 最大增益，2 ~ 16
	volatile unsigned char dete_info_filter;                  // 识别信息过滤，0 or 1
	volatile unsigned char md_info_filter;                    // Motion信息过滤，0 or 1
	volatile unsigned char test_mode_valid_flag;			  // 测试模式生效标记
}sensor_aeg_custom_app_info_structure;

/**
 * @brief      自动AEG亮度控制模块初始化。
 * @param[in]  app_sel    AEG所服务的应用；
 *             - MACR_AEG_APPLICATION_PROJECT_GENERAL    常规应用，无特定要求
 *             - MACR_AEG_APPLICATION_PROJECT_POSTURE    Posture-姿势校正
 *             - MACR_AEG_APPLICATION_PROJECT_CUSTOM     自定义应用
 * @param[in]  ac_freq    本次所设定的供电频率；
 *             - MACR_AEG_AC_FREQ_CFG_50HZ    供电频率为50Hz
 *             - MACR_AEG_AC_FREQ_CFG_60HZ    供电频率为60Hz
 * @param[in] gamma_flag   Gamma功能控制；
 *             - 0  关闭Gamma；
 *             - 1  开启Gamma（固定Gamma）；
 *             - 2  开启Gamma且根据环境自动切换Gamma。（仅混合型调整策略下有效）
 * @note       选择自定义应用时，必须先通过API sensor_aeg_update_custom_application_info()配置应用信息。
 */
void sensor_aeg_init(char app_sel, char ac_freq, char gamma_flag);

/**
 * @brief      AEG控制主流程。
 * @param[in]  target_brightness    目标图像亮度。
 * @note       亮度设置为120（256级）时，有较好的图像效果。
 */
void sensor_aeg_brightness(unsigned char target_brightness);

/**
 * @brief      获取当前的成像参数稳定状态。
 * @return
 *   - 0       当前参数处于未稳定状态
 *   - 1       当前参数处于稳定状态
 */
int sensor_aeg_is_imging_para_stable(void);

/**
 * @brief      应用更新Detect信息。
 * @param[in]  mode        识别的模式；
 * @param[in]  frm_id      Frame ID；
 * @param[in]  center_x    中心点x坐标；
 * @param[in]  center_y    中心点y坐标；
 * @param[in]  w           宽度；
 * @param[in]  h           高度；
 * @param[in]  score       识别分数。
 */
void sensor_aeg_update_dete_info(char mode, unsigned int frm_id, unsigned int center_x, unsigned int center_y, unsigned int w, unsigned int h, int score);

/**
 * @brief      应用更新Motion信息。
 * @param[in]  frm_id      Frame ID；
 * @param[in]  sx          起始点x坐标；
 * @param[in]  sy          起始点y坐标；
 * @param[in]  w           宽度；
 * @param[in]  h           高度。
 */
void sensor_aeg_update_md_info(unsigned int frm_id, unsigned short sx, unsigned short sy, unsigned short w, unsigned short h);

/**
 * @brief      应用更新自定义区域的信息。
 * @param[in]  frm_id      Frame ID；
 * @param[in]  sx          起始点x坐标；
 * @param[in]  xy          起始点y坐标；
 * @param[in]  w           宽度；
 * @param[in]  h           高度。
 * @note       此区域的优先级将低于Motion区域。
 */
void sensor_aeg_update_custom_area_info(unsigned int frm_id, unsigned short sx, unsigned short sy, unsigned short w, unsigned short h);

/**
 * @brief      获取当前的帧率。
 * @return
 *             - MACR_AEG_FRM_RATE_NONE
 *             - MACR_AEG_FRM_RATE_12_5FPS
 *             - MACR_AEG_FRM_RATE_15FPS
 *             - MACR_AEG_FRM_RATE_25FPS
 *             - MACR_AEG_FRM_RATE_30FPS
 *             - MACR_AEG_FRM_RATE_50FPS
 *             - MACR_AEG_FRM_RATE_60FPS
 *             - MACR_AEG_FRM_RATE_100FPS
 *             - MACR_AEG_FRM_RATE_120FPS
 */
unsigned char sensor_aeg_get_curr_frm_rate(void);

/**
 * @brief      获取当前的供电频率。
 * @return    
 *             - MACR_AEG_AC_FREQ_CFG_50HZ
 *             - MACR_AEG_AC_FREQ_CFG_60HZ
 */
char sensor_aeg_get_ac_freq(void);

/**
 * @brief      更新工作模式。
 * @param      work_mode               工作模式；
 * @param      recover_regular_para    是否需要恢复常规参数；0 - 不需要恢复，1 - 需要恢复
 * @param      para_keep_frm_num       模式切换成功后的参数保持数量。（仅切换至Regular模式生效）
 */
void sensor_aeg_update_work_mode(char work_mode, char recover_regular_para, unsigned int para_keep_frm_num);

/**
 * @brief      获取当前的工作模式。
 * @return 
 *  - MACR_AEG_WORK_MODE_NONE
 *  - MACR_AEG_WORK_MODE_REGULAR
 *  - MACR_AEG_WORK_MODE_FAST_PARA_POLL
 *  - MACR_AEG_WORK_MODE_GENERAL_PARA_POLL
 */
char sensor_aeg_get_curr_work_mode(void);

/**
 * @brief      当前是否允许切换工作模式。
 * @retval
 *  - 0        禁止切换
 *  - 1        允许切换
 */
char sensor_aeg_is_switch_work_mode_enable(void);

/**
 * @brief      设置参数轮询时的最大轮数。
 * @param      poll_cnt    参数轮询的轮数。
 */
void sensor_aeg_set_poll_para_max_num(unsigned int poll_cnt);

/**
 * @brief      获取最新的参考图像亮度。
 * @return     最新的参考图像亮度。
 */
unsigned char sensor_aeg_get_latest_ref_mean(void);

/**
 * @brief      快速轮询参数过程中的识别参数记录使能选项。
 * @param      flag    使能选项。0 - 不使能识别参数记录，1 - 使能识别参数记录
 */
void sensor_aeg_fast_poll_rec_dete_enable(char flag);

/**
 * @brief      当前是否可能是强背光场景。
 * @return     强背光场景判断值:
 *  - 0        当前不为强背光场景
 *  - 1        当前可能为强背光场景
 */
char sensor_aeg_is_might_strong_bk_light_scenes(void);

/**
 * @brief      应用更新计划识别信息。
 * @param[in]  frm_id      Frame ID；
 * @param[in]  sx          起始点x坐标；
 * @param[in]  sy          起始点y坐标；
 * @param[in]  w           宽度；
 * @param[in]  h           高度。
 * @return     计划识别区域的过亮比例，0 ~ 100-->%0 ~ %100。
 */
unsigned char sensor_aeg_update_plan_dete_info(unsigned int frm_id, unsigned short sx, unsigned short sy, unsigned short w, unsigned short h);

/**
 * @brief      设置快速轮询的参数选项。
 * @param[in]  para_opt       快速轮询的参数选项；
 *             - MACR_AEG_FAST_POLL_PARA_AUTO
 *             - MACR_AEG_FAST_POLL_PARA_AUTO_NO_FINE_TUNING
 *             - MACR_AEG_FAST_POLL_PARA_AUTO_NO_COARSE_REDUCE
 *             - MACR_AEG_FAST_POLL_PARA_FORCE_FINE_TUNING
 *             - MACR_AEG_FAST_POLL_PARA_FORCE_COARSE_REDUCE
 * @param[in]  frm_interval    轮询参数的间隔帧数，默认为6帧。
 * @note       每次启动快速轮询前应主动设置，否则将按照上次配置的方式使用。
 */
void sensor_aeg_set_fast_poll_para_opt(char para_opt, unsigned char frm_interval);

/**
 * @brief      设置快速轮询模式的参数调整信息。
 * @param      para_adjust_rate_1st    第1组参数的调整比例（基于当前成像参数），取值范围：-99 ~ 99；
 * @param      para_adjust_rate_2st    第2组参数的调整比例（基于当前成像参数），取值范围：-99 ~ 99。
 */
void sensor_aeg_set_fast_poll_external_para_adjust_rate(int para_adjust_rate_1st, int para_adjust_rate_2st);

/**
 * @brief      设置常规轮询的参数选项。
 * @param[in]  mean_min        轮询的最小亮度，30 ~ 200；
 * @param[in]  mean_max        轮询的最大亮度；50 ~ 240；
 * @param[in]  rate            轮询参数的计算比例，5 ~ 100；
 * @param[in]  is_ref_dete     是否需要识别参数，0 or 1；
 * @param[in]  frm_interval    轮询参数的间隔帧数，默认为6帧。   
 */
void sensor_aeg_set_general_poll_para_opt(unsigned char mean_min, unsigned char mean_max, unsigned char rate, unsigned char is_ref_dete, unsigned char frm_interval);

/**
 * @brief      设置曝光时间的上限。
 * @param[in]  expo_row    曝光时间行数的上限。
 */
void sensor_aeg_set_expo_row_upper_limit(unsigned int expo_row);

/**
 * @brief      判断特定帧是否为成像参数生效帧（曝光时间 or 模拟增益参数配置生效的帧）。
 * @param[in]  frm_id    待判断的帧ID。
 * @return
 *  - 0        非参数生效帧
 *  - 1        参数生效帧
 */
int sensor_aeg_is_para_active_frame(unsigned int frm_id);

/**
 * @brief      灯光等级控制。
 * @param[in]  level    灯光等级。
 * @note       此API为弱定义，应用需重写此API，以完成对灯光等级的控制。
 */
void sensor_aeg_light_level_ctrl(unsigned int level);

/**
 * @brief      深度休眠控制。
 * @param[in]  frm_id_curr      当前的Frame ID；
 * @param[in]  sleep_frm_num    需要休眠的帧数。
 * @return     休眠控制成功标志，0 or 1
 * @note       此API为弱定义，应用需重写此API，以完成深度休眠的控制。
 */
int sensor_aeg_deep_sleep_ctrl(unsigned int frm_id_curr, unsigned int sleep_frm_num, unsigned int sleep_time_ms);

/**
 * @brief      设置参考Motion进行参数调整时的最小间隔帧数。
 * @param[in]  frm_interval_min    最小帧间隔（0表示不做最小值限制）；
 */
void sensor_aeg_set_min_interval_frm_ref_md_adjust(unsigned char frm_interval_min);

/**
 * @brief      设置调整参考的亮度值。
 * @param[in]  brightness    参考亮度值。
 * @note       此处参考的亮度值应与AEG目标亮度值搭配使用，且不应大于AEG目标亮度值。
 */
void sensor_aeg_set_adjust_ref_brightness(unsigned char brightness);

/**
 * @brief      复位成像参数稳定标志。
 */
void sensor_aeg_reset_imging_para_stable_flag(void);

/**
 * @brief      粗调增益等级的自动调整。
 * @note       此API需要在Vertical Blanking过程中运行且没有AEG模块初始化需求，
 *			   另外，内部需要获取全图亮度。
 */
void sensor_aeg_adjust_coarse_gain_level(void);

/**
 * @brief      获取AEG版本信息。
 * @param[out] data_buff_pt    信息存储区；
 * @param[in]  data_len_max    信息存储区的最大长度。
 * @return     获取的信息长度
 *   - -1      输入信息无效
 *   - others  获取到的信息长度
 * @note       此API可在模块初始化之前使用。
 */
int sensor_aeg_get_version(unsigned char* data_buff_pt, unsigned int data_len_max);

/**
 * @brief      更新自定义应用的信息。
 * @param[in]  cfg_info_str    配置信息结构体。
 * @return
 *  - 0        信息更新成功
 *  - -1       信息更新失败
 * @note       若需要使用自定义应用，则必须在初始化之前调用此API更新信息。
 */
int sensor_aeg_update_custom_application_info(sensor_aeg_custom_app_info_structure cfg_info_str);

/**
 * @brief      图像调试标签功能使能控制。
 * @param[in]  is_enable    使能控制。0 - 禁能；1 - 使能。
 */
void sensor_aeg_video_debug_label_enable(char is_enable);

/**
 * @brief     更新默认的Gamma配置值。
 * @param[in] gamma_value_pt    待更新的Gamma值的指针（大小为49的unsigned char类型数组）。
 * @note      此API必须在初始化前调用，其配置值才可生效。
 */
void sensor_aeg_update_def_gamma_value(unsigned char *gamma_value_pt);

/**
 * @brief      更新外部参数信息。
 * @param[in]  epc_type    外部参数类型；
 *                         - MACR_AEG_EPC_ELPM_DLY_TIME_s
 *                         - MACR_AEG_EPC_MD_CALC_FRM_NUM
 *                         - MACR_AEG_EPC_LPF_ON_FRM_NUM
 *                         - MACR_AEG_EPC_LPF_OFF_TIME_ms
 * @param[in]  epc_value   外部参数值。
 * @note       目前支持的外部参数类型如下
 */
void sensor_aeg_update_epc_info(unsigned char epc_type, int epc_value);

/*****************************************************************************
 *
 * 注意：当前位置之后API为Sensor操作相关，与AEG模块本身无直接相关性。
 *
 ****************************************************************************/

/**
 * @brief      获取帧宽。
 * @return     Sensor当前设置的帧宽。
 */
unsigned int sensor_get_frame_width(void);

/**
 * @brief      获取帧长。
 * @return     Sensor当前设置的帧长。
 */
unsigned int sensor_get_frame_height(void);

/**
 * @brief      设置帧长。
 * @param[in]  设置的帧长。
 * @return     Sensor当前设置的帧长
 */
void sensor_set_frame_height(unsigned int frm_h);

/**
 * @brief      设置Sensor曝光时间。
 * @param[in]  expo_row    设置的曝光时间，单位：行数。
 * @return     实际设置的曝光时间行数。
 */
unsigned int sensor_set_exposure_row(unsigned int expo_row);

/**
 * @brief      获取Sensor当前的曝光时间。
 * @return     Sensor当前的曝光时间，单位：行。
 */
unsigned int sensor_get_exposure_row(void);

/**
 * @brief      设置Sensor模拟增益。
 * @param[in]  ana_gain    模拟增益，1x、2x、...16x。
 * @return     实际设置生效的模拟增益等级
 */
unsigned int sensor_set_analog_gain(unsigned int ana_gain);

/**
 * @brief      获取Sensor当前的模拟增益。
 * @return     当前的模拟增益等级，1x、2x、...16x。
 */
unsigned int sensor_get_analog_gain(void);

/**
 * @brief      配置真实的模拟增益。
 * @param[in]  cfg_gain    模拟增益的实际配置值（0x10 ~ 0xFF）
 */
void sensor_set_real_analog_gain(unsigned char cfg_gain);

/**
 * @brief      获取当前真实的模拟增益。
 * @return     实际的模拟增益配置值（0x10 ~ 0xFF）
 */
unsigned char sensor_get_real_analog_gain(void);

#endif /*  end of __SENSOR_AEG_H__ */
