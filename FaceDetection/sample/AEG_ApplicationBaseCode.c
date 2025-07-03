
// 1. 初始化过程

// 1.1 获取AEG版本信息
unsigned char aeg_ver_array[64 + 1] = { 0 };
unsigned int aeg_ver_len = 0;

// 获取AEG版本信息
aeg_ver_len = sensor_aeg_get_version(aeg_ver_array, 64);

if (aeg_ver_len > 0)
{
	aeg_ver_array[aeg_ver_len] = '\0';
	printf("\r\nAEG Version: %s\r\n\r\n", aeg_ver_array);
}
else
{
	printf("\r\nAEG Version is Error!!!\r\n");
}

// 1.2 应用初始化

/*************************************（可选）如有自定义Gama需求则处理*************************************/
// 自定义Gama值 - Gamma值数量默认为49
unsigned char custom_gamma_value_array[] = { 0x00, 0x1A, 0x2D, 0x3D, 0x4C, 0x5B, 0x6A, 0x78, 0x85, 0x91, 0x9C, 0xA3,
											0xA7, 0xAC, 0xB0, 0xB5, 0xB9, 0xBB, 0xBF, 0xC1, 0xC4, 0xC4, 0xC7, 0xCB,
											0xCB, 0xCF, 0xD0, 0xD3, 0xD4, 0xD8, 0xD8, 0xDC, 0xDC, 0xE0, 0xE1, 0xE4,
											0xE5, 0xE9, 0xE9, 0xED, 0xEE, 0xF1, 0xF2, 0xF6, 0xF6, 0xFA, 0xFA, 0xFE,
											0xFF};
// 写入自定义Gamma值
// 注：此部分必须再初始化前完成，否则将不生效
sensor_aeg_update_def_gamma_value(&custom_gamma_value_array[0]);	
/*************************************（可选）如有自定义Gama需求则处理*************************************/

// 注意：IR镜头下，为了更好的使用效果，请务必使用此Gamma曲线替换默认Gamma曲线
unsigned char gamma_custom_array[] = {0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40, 0x46, 0x4B, 0x50,
									  0x55, 0x59, 0x5C, 0x60, 0x64, 0x69, 0x6D, 0x71, 0x75, 0x79, 0x7D, 0x81,
									  0x85, 0x87, 0x8A, 0x8D, 0x90, 0x93, 0x96, 0x99, 0x9E, 0xA3, 0xA6, 0xAA,
									  0xAF, 0xB4, 0xB9, 0xBE, 0xC3, 0xCB, 0xD0, 0xD5, 0xDB, 0xE3, 0xEC, 0xF5, 
									  0xFF};

// 定义供电频率
char ac_freq = (NB_ntsc_pal_mode == NTSC_PAL_MODE_NTSC) ? MACR_AEG_AC_FREQ_CFG_60HZ : MACR_AEG_AC_FREQ_CFG_50HZ;
// 定义Gamma标志
char gamma_flag = MACR_AEG_GAMMA_OPT_OFF;
// Gamma标志目前仅支持以下4种，请选择其中一种
/**********************************************************************************************
MACR_AEG_GAMMA_OPT_OFF          // 关闭Gamma
MACR_AEG_GAMMA_OPT_ON_GENERAL   // 启用Gamma，配置为常规Gamma曲线
MACR_AEG_GAMMA_OPT_ON_AUTO_FULL // 启用Gamma，通过环境判断自动切换Gamma曲线（全场景切换检测）
MACR_AEG_GAMMA_OPT_ON_AUTO_BL   // 启用Gamma，通过环境判断自动切换Gamma曲线（仅背光场景切换检测）
**********************************************************************************************/
/*************************************Partial应用 - Start*************************************/
sensor_aeg_init(MACR_AEG_APPLICATION_PROJECT_PARTIAL, ac_freq, gamma_flag);
/*************************************Partial应用 - End***************************************/

/*************************************General应用 - Start*************************************/
sensor_aeg_init(MACR_AEG_APPLICATION_PROJECT_GENERAL, ac_freq, gamma_flag);
/*************************************General应用 - End***************************************/

/*************************************自定义应用 - Start*************************************/
unsigned char frm_rate_max = 0;
unsigned char frm_rate_min = 0;
sensor_aeg_custom_app_info_structure app_info_str = { 0 };

if (ac_freq == MACR_AEG_AC_FREQ_CFG_60HZ)
{
	frm_rate_max = MACR_AEG_FRM_RATE_60FPS;
	frm_rate_min = MACR_AEG_FRM_RATE_30FPS;
}
else
{
	frm_rate_max = MACR_AEG_FRM_RATE_50FPS;
	frm_rate_min = MACR_AEG_FRM_RATE_25FPS;
}

// 设定AEG算法策略类型
app_info_str.adjust_strategy = MACR_AEG_STRATEGY_METERING_MIX;
// 设定工作帧率-->起始帧率为最高帧率，若最小帧率小于<最大帧率，则根据环境进行帧率切换，否则保持初始帧率
// 注：最小灯光等级配置大于0时，帧率切换功能失效，工作帧率为配置的最大帧率
app_info_str.frm_rate_max = frm_rate_max;
app_info_str.frm_rate_min = frm_rate_min;
// 设定低功耗模式的选项：None(0ms)、Low(160ms)、Mid(320ms)、High(480ms)（灯光生效时配置才生效）
// 注：若要实现深度休眠，则应重写对应AP实体I，否则深度休眠无效：
// API：int sensor_aeg_deep_sleep_ctrl(unsigned int frm_id_curr, unsigned int sleep_frm_num, unsigned int sleep_time_ms)
app_info_str.lpm_opt = MACR_AEG_LPM_OPT_NONE;
// 设置可支持的最大灯光等级
// 注：灯光等级设置范围为0 ~ 100，若大于0，则应重写对应API实体，否则灯光控制无效：
// API：void sensor_aeg_light_level_ctrl(unsigned int level)
// 注：最大、最小灯光等级一致时，则表示开灯时灯光为固定等级，否则在最小~最大灯光等级中控制；
// 注：IR镜头时，最小灯光等级应配置为大于0；常规镜头时，最小灯光等级应配置为0；
app_info_str.light_level_max = 0;
app_info_str.light_level_min = 0;
// 设定最大的模拟增益，可设置值：2 ~ 16
app_info_str.ana_gain_max = 15;
// 设定识别信息过滤
app_info_str.dete_info_filter = 1;
// 设定Motion信息过滤
app_info_str.md_info_filter = 1;
// 设定测试模式选项：仅以全图亮度进行AEG控制
app_info_str.test_mode_valid_flag = 0;
// 设定参数有效标志
app_info_str.valid_flag = 1;

// 自定义信息更新成功，启动自定义应用
if (sensor_aeg_update_custom_application_info(app_info_str) == 0)
{
	sensor_aeg_init(MACR_AEG_APPLICATION_PROJECT_CUSTOM, ac_freq, gamma_flag);
}
// 自定义信息更新失败，启动General应用
else
{
	sensor_aeg_init(MACR_AEG_APPLICATION_PROJECT_GENERAL, ac_freq, gamma_flag);
}
/*************************************自定义应用 - End***************************************/

// 1.3 Video Label控制（默认开启，）
sensor_aeg_video_debug_label_enable(0);

// 1.4 设定AEG内部运行参数

// 设置延迟进入低功耗模式的时间，单位：秒
sensor_aeg_update_epc_info(MACR_AEG_EPC_ELPM_DLY_TIME_s, 5);   // 延迟5秒进入低功耗模式
// 设置Motion用于计算时的帧数
sensor_aeg_update_epc_info(MACR_AEG_EPC_MD_CALC_FRM_NUM, 200); // Motion计算时的最大帧数为200帧
// 设置低功耗过程中灯光闪烁-开启帧数（检测Motion）
sensor_aeg_update_epc_info(MACR_AEG_EPC_LPF_ON_FRM_NUM, 6);    // 低功耗过程中灯光闪烁-开启的帧数为6帧
// 设置低功耗过程中灯光闪烁-关闭时间，单位：毫秒
sensor_aeg_update_epc_info(MACR_AEG_EPC_LPF_OFF_TIME_ms, 500); // 低功耗过程中灯光闪烁-关闭时间为500ms

// 2. 运行过程

// 2.1 AEG主流程
sensor_aeg_brightness(120);

// 2.2 更新识别信息至AEG模块内部
// 注意：实际应用时，CH0304需根据应用的Project版本进行相应替换，如替换为CH0608 or NB……
if (CH0304__Found->state != CH0304__Find_State_No)
{
	unsigned int dete_center_x = CH0304__Found->x0;
	unsigned int dete_center_y = CH0304__Found->y0;
	unsigned int dete_w = CH0304__Found->w;
	unsigned int dete_h = CH0304__Found->h;
	CH0304__Model_Type_s dete_type = NB_MODEL_TYPE_OTHER;
	int dete_score = CH0304__Found->score[CH0304__Found->get_group][CH0304__Found->get_level];
	char aeg_dete_mode = MACR_AEG_APP_DETE_MODE_NONE;

	// 通过模型直接识别到的则取Group中的数据、否则提取Level中的数据（如Follow）
	dete_type = (CH0304__Found->state == CH0304__Find_State_Find) ? detect_model.group_type[CH0304__Found->get_group] : detect_model.group_type[CH0304__Found->get_level];

	// 将当前识别的类型转换为AEG模块定义的识别模式
	switch (dete_type)
	{
	case NB_MODEL_TYPE_FACE:
		aeg_dete_mode = MACR_AEG_APP_DETE_MODE_FACE;
		break;
	case NB_MODEL_TYPE_HEAD:
		aeg_dete_mode = MACR_AEG_APP_DETE_MODE_HEAD;
		break;
	case NB_MODEL_TYPE_HEADADD:
		aeg_dete_mode = MACR_AEG_APP_DETE_MODE_HEADADD;
		break;
	case NB_MODEL_TYPE_TORSO:
		aeg_dete_mode = MACR_AEG_APP_DETE_MODE_TORSO;
		break;
	case NB_MODEL_TYPE_GESTURE_GIVE_ME_FIVE:
	case NB_MODEL_TYPE_GESTURE_GOOD:
	case NB_MODEL_TYPE_GESTURE_YE:
		aeg_dete_mode = MACR_AEG_APP_DETE_MODE_GESTURE;
		break;
	default:
		aeg_dete_mode = MACR_AEG_APP_DETE_MODE_UND_NREF;
		break;
	}

	// 更新识别信息至AEG模块内部
	sensor_aeg_update_dete_info(aeg_dete_mode, CH0304__Found->get_id, dete_center_x, dete_center_y, dete_w, dete_h, dete_score);
}

// 2.3 更新Motion信息至AEG模块内部
unsigned short sx = 0;
unsigned short sy = 0;
unsigned short w = 0;
unsigned short h = 0;

// 获取到有效的Motion信息，则做一次信息更新
// 注：电机转动的过程中不应更新此信息
if (md_get_motion_area(&sx, &sy, &w, &h) == 1)
{
	// 判断当前帧是否为参数生效帧，若为参数生效帧，则有可能是由于参数变化而误判的Motion
	if (sensor_aeg_is_para_active_frame(curr_frm_id) == 0)
	{
		sensor_aeg_update_md_info(debug_get_frame_id_hex(), sx, sy, w, h);	
	}
}

// 2.4 轮询模式

// 2.4.1 进入轮询模式

// 记录轮询模式下的Frame ID
if (sensor_aeg_get_curr_work_mode() != MACR_AEG_WORK_MODE_REGULAR)
{
	s_last_poll_mode_frm_id = debug_get_frame_id_hex();
}

if ((sensor_aeg_get_curr_work_mode() == MACR_AEG_WORK_MODE_REGULAR) && 		\
	(sensor_aeg_is_switch_work_mode_enable() == 1) &&			\
	(debug_get_frame_id_hex() - s_last_poll_mode_frm_id > 100)/* 此项可选，用于限制过于频繁的进入轮询模式，仅做参考 */)
{
	// 实际应用时，可根据实际需求从以下轮询方式种选择任意一种参数轮询方式
#if (0)
	// 1. 常规参数轮询
	// 注：持续轮询（需主动退出），轮询图像亮度100~180，轮询参数变化幅度±30%，轮询间隔帧数10帧，且参考过往的识别参数进行轮询
	sensor_aeg_update_work_mode(MACR_AEG_WORK_MODE_GENERAL_PARA_POLL, 0, 0);
	sensor_aeg_set_poll_para_max_num(0xFFFFFFFF);
	unsigned char limit_mean_l = 100;
	unsigned char limit_mean_h = 180;
	unsigned char adjust_rate = 30;
	unsigned char is_need_dete_para = 1;
	unsigned char frm_intreval = 10;
	sensor_aeg_set_general_poll_para_opt(limit_mean_l, limit_mean_h, adjust_rate, is_need_dete_para, frm_intreval);
#endif

#if (0)
	// 2. 快速轮询 - MACR_AEG_FAST_POLL_PARA_FORCE_WITH_EXTERNAL
	// 注：持续轮询（需主动退出），根据外部输入的参数变化幅度进行参数计算轮询，轮询间隔帧数为6帧
	int poll_para_rate1 = 40;
	int poll_para_rate2 = -20;
	sensor_aeg_set_fast_poll_external_para_adjust_rate(poll_para_rate1, poll_para_rate2);
	// 使用外部参数进行轮询
	unsigned char poll_frm_interval = 6; 
	sensor_aeg_set_fast_poll_para_opt(MACR_AEG_FAST_POLL_PARA_FORCE_WITH_EXTERNAL, poll_frm_interval);
	// 切换至快速参数轮询模式
	sensor_aeg_update_work_mode(MACR_AEG_WORK_MODE_FAST_PARA_POLL,0,0);
	// 设置最多可轮询的轮数（1轮对应N组参数）
	// 若在设置的轮数过程中未主动退出快速参数轮询模式，则在设置轮数完成后自动切换至常规工作模式
	unsigned int poll_cnt = 0xFFFFFFFF;
	sensor_aeg_set_poll_para_max_num(poll_cnt);
#endif

#if (0)
	// 3. 快速轮询 - MACR_AEG_FAST_POLL_PARA_FORCE_COARSE_REDUCE
	// 注：轮询3轮自动退出（可主动退出），基于当前成像参数，强制下调较大幅度的参数进行轮询，轮询间隔帧数为6帧
	unsigned char poll_frm_interval = 6; 
	sensor_aeg_set_fast_poll_para_opt(MACR_AEG_FAST_POLL_PARA_FORCE_COARSE_REDUCE, poll_frm_interval);
	// 切换至快速参数轮询模式
	sensor_aeg_update_work_mode(MACR_AEG_WORK_MODE_FAST_PARA_POLL,0,0);
	// 设置最多可轮询的轮数（1轮对应N组参数）
	// 若在设置的轮数过程中未主动退出快速参数轮询模式，则在设置轮数完成后自动切换至常规工作模式
	unsigned int poll_cnt = 3;
	sensor_aeg_set_poll_para_max_num(poll_cnt);	
#endif

#if (0)
	// 4. 快速轮询 - MACR_AEG_FAST_POLL_PARA_FORCE_FINE_TUNING
	// 注：轮询1轮自动退出（可主动退出），基于当前成像参数，强制上下调整较小幅度的参数进行轮询，轮询间隔帧数为6帧
	unsigned char poll_frm_interval = 6; 
	sensor_aeg_set_fast_poll_para_opt(MACR_AEG_FAST_POLL_PARA_FORCE_FINE_TUNING, poll_frm_interval);
	// 切换至快速参数轮询模式
	sensor_aeg_update_work_mode(MACR_AEG_WORK_MODE_FAST_PARA_POLL,0,0);
	// 设置最多可轮询的轮数（1轮对应N组参数）
	// 若在设置的轮数过程中未主动退出快速参数轮询模式，则在设置轮数完成后自动切换至常规工作模式
	unsigned int poll_cnt = 1;
	sensor_aeg_set_poll_para_max_num(poll_cnt);
#endif

#if (0)
	// 5. 快速轮询 - MACR_AEG_FAST_POLL_PARA_AUTO
	// 注：轮询2轮自动退出（可主动退出），基于当前成像参数，根据环境自动确认轮询参数，轮询间隔帧数为6帧
	unsigned char poll_frm_interval = 6; 
	sensor_aeg_set_fast_poll_para_opt(MACR_AEG_FAST_POLL_PARA_AUTO, poll_frm_interval);
	// 切换至快速参数轮询模式
	sensor_aeg_update_work_mode(MACR_AEG_WORK_MODE_FAST_PARA_POLL,0,0);
	// 设置最多可轮询的轮数（1轮对应N组参数）
	// 若在设置的轮数过程中未主动退出快速参数轮询模式，则在设置轮数完成后自动切换至常规工作模式
	unsigned int poll_cnt = 2;
	sensor_aeg_set_poll_para_max_num(poll_cnt);
#endif

#if (0)
	// 6. 快速轮询 - MACR_AEG_FAST_POLL_PARA_AUTO_NO_FINE_TUNING
	// 注：轮询2轮自动退出（可主动退出），基于当前成像参数，根据环境自动确认轮询参数，轮询间隔帧数为6帧
	// 注：与MACR_AEG_FAST_POLL_PARA_AUTO差异在于，检测到当前轮询方式的参数微调，则本次轮询不生效
	unsigned char poll_frm_interval = 6; 
	sensor_aeg_set_fast_poll_para_opt(MACR_AEG_FAST_POLL_PARA_AUTO_NO_FINE_TUNING, poll_frm_interval);
	// 切换至快速参数轮询模式
	sensor_aeg_update_work_mode(MACR_AEG_WORK_MODE_FAST_PARA_POLL,0,0);
	// 设置最多可轮询的轮数（1轮对应N组参数）
	// 若在设置的轮数过程中未主动退出快速参数轮询模式，则在设置轮数完成后自动切换至常规工作模式
	unsigned int poll_cnt = 2;
	sensor_aeg_set_poll_para_max_num(poll_cnt);
#endif

#if (0)
	// 7. 快速轮询 - MACR_AEG_FAST_POLL_PARA_AUTO_NO_COARSE_REDUCE
	// 注：轮询2轮自动退出（可主动退出），基于当前成像参数，根据环境自动确认轮询参数，轮询间隔帧数为6帧
	// 注：与MACR_AEG_FAST_POLL_PARA_AUTO差异在于，检测到当前轮询方式的参数粗调，则本次轮询不生效
	unsigned char poll_frm_interval = 6; 
	sensor_aeg_set_fast_poll_para_opt(MACR_AEG_FAST_POLL_PARA_AUTO_NO_COARSE_REDUCE, poll_frm_interval);
	// 切换至快速参数轮询模式
	sensor_aeg_update_work_mode(MACR_AEG_WORK_MODE_FAST_PARA_POLL,0,0);
	// 设置最多可轮询的轮数（1轮对应N组参数）
	// 若在设置的轮数过程中未主动退出快速参数轮询模式，则在设置轮数完成后自动切换至常规工作模式
	unsigned int poll_cnt = 2;
	sensor_aeg_set_poll_para_max_num(poll_cnt);
#endif
}

// 2.4.2 退出快速轮询
// 触发轮询操作，并且在轮询过程中识别成功，则主动切换模式-->同时可以保持次参数一段时间
if ((识别成功) && (sensor_aeg_get_curr_work_mode() != MACR_AEG_WORK_MODE_REGULAR) && (sensor_aeg_is_switch_work_mode_enable() == 1))
{
	// 切换完成后，保持0帧-->之后连续0帧无识别，启动调整
	sensor_aeg_update_work_mode(MACR_AEG_WORK_MODE_REGULAR, 0, detect_config.mb_loop_f);
}

// 2.5 设定最大可支持的曝光时间行数
// 注：需在AEG初始化完成后再进行设置，否则，将不生效

// 最高曝光时间设置为300行（50/60FPS下，最大曝光时间为396行）
sensor_aeg_set_expo_row_upper_limit(300);

// 3. 灯光、深度休眠内容实现（注意：此部分AEG内部是定义弱函数、无有效内容，若需要对应功能生效，则应重写此API）

// 3.1 API重写 - 完成对灯光等级控制
// 注：请根据实际硬件情况，在此接口中实现灯光等级控制

void sensor_aeg_light_level_ctrl(unsigned int level)
{
	HardPWM(IOB7, 2, level, 0);
}

// 3.2 重写API，完成对深度休眠的控制（需注意搭配不同的SDK CodeBase用法差异）
// 注：请根据实际硬件情况，在此接口中深度休眠控制

#if (0) // 搭配SDK CodeBase版本：V1.0.17及以上

#define MACR_LPM_DECREASE_FRM_RATE  0
// 重写API，完成对深度休眠的控制
int sensor_aeg_deep_sleep_ctrl(unsigned int frm_id_curr, unsigned int sleep_frm_num, unsigned int sleep_time_ms)
{
	int is_sleep_succ = 0;
	unsigned int lp_time_ms = 0;
	unsigned long long tick_base = 0;
	unsigned long long goal_ticks = 0;

	if ((sleep_frm_num <= 0) || (sleep_time_ms <= 0))
	{
		return is_sleep_succ;
	}

#if (MACR_LPM_DECREASE_FRM_RATE == 1)
	unsigned int frm_rate_des = 0;
	unsigned int org_frm_h = 0;
	unsigned int new_frm_h = 0;
	unsigned char curr_frm_rate = MACR_AEG_FRM_RATE_NONE;
	unsigned int frm_id_base = 0;

	org_frm_h = sensor_get_frame_height();
	curr_frm_rate = sensor_aeg_get_curr_frm_rate();
	frm_rate_des = (sleep_frm_num > 2) ? (sleep_frm_num - 2) : 1;
	new_frm_h = org_frm_h * frm_rate_des;
	// 强制降低帧率
	if (org_frm_h < new_frm_h)
	{
		sensor_set_frame_height(new_frm_h);
		frm_id_base = debug_get_frame_id_hex();
	}
#endif

	// 计算Low Power实际时间，预留一帧退出
	lp_time_ms = sleep_time_ms - sleep_time_ms / sleep_frm_num;
	// 计算Low Power实际时间，预留延时时间
	lp_time_ms = (lp_time_ms > 6) ? (lp_time_ms - 6) : 1;
	// 计算Low Power过程中的Tick数
	goal_ticks = lp_time_ms * 215;

	// 进入低功耗模式
	pm_switch_power_mode(PM_STATE_LOW_POWER);
	// 获取进入Low Power时的Tick数，用于计数
	tick_base = perf_get_ticks();
	
	// 等待完成预定的休眠时间
	while (1)
	{
#if (MACR_LPM_DECREASE_FRM_RATE == 1)
		if ((org_frm_h != new_frm_h) && (debug_get_frame_id_hex() > frm_id_base))
		{
			// 恢复帧率
			sensor_set_frame_height(org_frm_h);
			new_frm_h = org_frm_h;
		}
#endif

		if ((perf_get_ticks() - tick_base) >= goal_ticks)
		{
			break;
		}
	}

	// 退出低功耗模式
	pm_switch_power_mode(PM_STATE_NORMAL);
	// 延时1ms等待系统稳定
	mdelay(1);
	// 等待休眠状态的最后一帧图像处理完成
	while (md_wait_for_frame_finish(0) != 0);
	// 清除Motion信号
	md_wait_for_motion(0);
	// 控制完成，设置标志
	is_sleep_succ = 1;

	//motion_first = 0;
	return is_sleep_succ;
}

#else  // 搭配SDK CodeBase版本：V1.0.16及以下

/* Critical section management. */
extern void vTaskEnterCritical( void );
extern void vTaskExitCritical( void );

#define MACR_LPM_DECREASE_FRM_RATE  1

// 重写API，完成对深度休眠的控制
int sensor_aeg_deep_sleep_ctrl(unsigned int frm_id_curr, unsigned int sleep_frm_num, unsigned int sleep_time_ms)
{
	int is_sleep_succ = 0;
	unsigned int lp_time_ms = 0;
	unsigned long long tick_base = 0;
	unsigned long long goal_ticks = 0;

	if ((sleep_frm_num <= 0) || (sleep_time_ms <= 0))
	{
		return is_sleep_succ;
	}

	// 延时一段时间，等待系统稳定
	mdelay(5);
	// 进入临界区，系统进入Low Power模式
	vTaskEnterCritical();

#if (MACR_LPM_DECREASE_FRM_RATE == 1)
	unsigned int frm_rate_des = 0;
	unsigned int org_frm_h = 0;
	unsigned int new_frm_h = 0;
	unsigned char curr_frm_rate = MACR_AEG_FRM_RATE_NONE;
	unsigned int frm_id_base = 0;

	org_frm_h = sensor_get_frame_height();
	curr_frm_rate = sensor_aeg_get_curr_frm_rate();
	frm_rate_des = (sleep_frm_num > 2) ? (sleep_frm_num - 2) : 1;
	new_frm_h = org_frm_h * frm_rate_des;
	// 强制降低帧率
	if (org_frm_h < new_frm_h)
	{
		sensor_set_frame_height(new_frm_h);
		frm_id_base = debug_get_frame_id_hex();
	}
#endif

	// 计算Low Power实际时间，预留一帧退出
	lp_time_ms = sleep_time_ms - sleep_time_ms / sleep_frm_num;
	// 计算Low Power实际时间，预留延时时间
	lp_time_ms = (lp_time_ms > 6) ? (lp_time_ms - 6) : 1;
	// 计算Low Power过程中的Tick数
	goal_ticks = lp_time_ms * 215;
	// 获取进入Low Power时的Tick数，用于计数
	tick_base = perf_get_ticks();

	// 进入低功耗模式
	pm_switch_power_mode(PM_STATE_LOW_POWER);
	
	// 等待完成预定的休眠时间
	while (1)
	{
#if (MACR_LPM_DECREASE_FRM_RATE == 1)
		if ((org_frm_h != new_frm_h) && (debug_get_frame_id_hex() > frm_id_base))
		{
			// 恢复帧率
			sensor_set_frame_height(org_frm_h);
			new_frm_h = org_frm_h;
		}
#endif

		if ((perf_get_ticks() - tick_base) >= goal_ticks)
		{
			break;
		}
	}

	// 退出低功耗模式
	pm_switch_power_mode(PM_STATE_NORMAL);

	// 退出临界区，系统恢复正常工作
	vTaskExitCritical();
	
	// 延时1ms等待系统稳定
	mdelay(1);

	// 等待休眠状态的最后一帧图像处理完成
	while (md_wait_for_frame_finish(0) != 0);
	// 清除Motion信号
	md_wait_for_motion(0);

	// 控制完成，设置标志
	is_sleep_succ = 1;

	//motion_first = 0;
	return is_sleep_succ;
}

#endif