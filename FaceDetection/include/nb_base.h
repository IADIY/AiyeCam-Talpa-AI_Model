/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2020 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/

#ifndef __NB__BASE__
#define __NB__BASE__

#include "nbsdk.h"
#include "string.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define GPIO_BASE (0x40050000)
#define GPIO_PORTA_DR (GPIO_BASE + 0x00)

// 设置保存每帧需要记录的数据的上限
#define NB_SAVE_WINTOFEDATA_ITEM 10

#define NB_DEBUG_DRAWWIN_BOX_ID 1
#define NB_DEBUG_MOTION_BOX_ID 2
#define NB_DEBUG_TRACK_BOX_ID 3
#define NB_DEBUG_FOUND_BOX_ID 4

enum
{
    NTSC_PAL_MODE_PAL,
    NTSC_PAL_MODE_NTSC,
};

void NB_set_ntsc_pal_mode(void);

enum
{
    // 全局识别
    NB_DETECT_SYS_MODE_START = 0,

    NB_DETECT_SYS_MODE_GLOBAL_START, // 1
    NB_DETECT_SYS_MODE_GLOBAL,

    NB_DETECT_SYS_MODE_MOTION_START, // 3
    NB_DETECT_SYS_MODE_MOTION,

    NB_DETECT_SYS_MODE_FOUND_START, // 5
    NB_DETECT_SYS_MODE_FOUND,       // 6

    NB_DETECT_SYS_MODE_END,

};

typedef struct NB_Rec_s_t
{

    u16 x;
    u16 y;

    u16 w;
    u16 h;

} __attribute__((aligned(4))) NB_Rec_s;

extern u8 NB_Version[];
extern u32 NB_f_id;
extern u8 NB_fps;
extern u8 NB_global_b;
extern u8 NB_global_e;
extern u8 NB_global_ag;

extern u8 NB_Savedata_index;

extern u8 NB_motor_run;
extern u8 NB_detect_sys_mode;
extern u8 NB_filter_mode;
extern u8 NB_filter_m_g;
extern u8 NB_filter_m_l;

extern u8 NB_motion_found;

extern u16 NB_motor_lost_number;

extern u16 NB_fedata_old_w;

extern u32 NB_show_motion_head_id;
extern u32 NB_show_found_id;

/*WATCHDOG*/
/*APIs*/
void wdt_init_clk(int div);
void wdt_enable(unsigned int en);
void wdt_set_mode(WDT_MODE_T mode);
void wdt_set_rpl(WDT_RPL_T rpl);
void wdt_set_timeout(WDT_TOP_T top);
void wdt_restart(void);
unsigned int wdt_get_count(void);
unsigned int wdt_get_status(void);
void wdt_clear_int(void);
void NB_WatchDogInit(void);

int NB_gpio_pin_2_group(int pin_no, int *group, int *pin);
void NB_gpio_set_value_app(int pin_no, int val);

void NB_Boot_Init(void);
void NB_Base_Init(void);
void NB_Base_Action_start(u32 frame_id, u8 disable_motion, u8 found_mode_exit);
void NB_Base_Action_end(u32 frame_id);

void NB_Binarization(unsigned char threshold);

#endif
