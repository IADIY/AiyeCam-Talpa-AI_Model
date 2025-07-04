/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2020 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/


#ifndef __NB__BASE__
#define __NB__BASE__

#if 1

#include "nbsdk.h"
#include "string.h"

#include "include/Basic.h"
#include "include/sensor_aeg.h"


typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;


#else

//#include "nbsdk_api.h" // PRE-COMPILING ONLY

#include "isp_fe.h" // PRE-COMPILING ONLY
// #include "isp_md.h"		 // PRE-COMPILING ONLY
#include "cv_norm.h"		// PRE-COMPILING ONLY
#include "riscv_sqrt_f32.h" // PRE-COMPILING ONLY
#include "cv_classify.h"	// PRE-COMPILING ONLY
#include "utils.h"			// PRE-COMPILING ONLY
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "nb_motion_aec_api.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define nb_malloc malloc
#define nb_free free
#define nb_realloc realloc
#define nb_calloc calloc
#define nb_strdup strdup

#define __raw_writel(v, a) (*(volatile unsigned int *)(a) = ((unsigned int)v))
#define __raw_readl(a) (*(volatile unsigned int *)(a))
#define __raw_writew(v, a) (*(volatile u16 *)(a) = ((u16)v))
#define __raw_readw(a) (*(volatile u16 *)(a))

#define BIT(nr) (1UL << (nr))

#define SYS_RSTN_SENSOR_MEM (BIT(18))

void sys_reset(unsigned int modules);
unsigned long long perf_get_ticks(void);

struct nb_exp_table_t
{
    unsigned char aecVal;  // ae ??板?
    unsigned short aecReg; // ?存ヨ 剧疆??aec 瀵瀛?ㄤ腑??板?
    unsigned char agcVal;  // agc ??板硷?x100
    unsigned char agcReg;  // ?存ヨ 剧疆??agc 瀵瀛?ㄤ腑??板?
    unsigned short dgVal;  // dg ??板硷?x100
    unsigned char dgReg;   // ?存ヨ 剧疆??dg 瀵瀛?ㄤ腑??板?
    int areaVal;           // ?荤?板硷?x10000
};


struct sensor_conf_t
{
    int sensorID;
    int i2c_slave_addr;

    int input_width;
    int input_height;
    int output_width;
    int output_height;

    int reso_mode; //1 vga mode  0 qvga
    int data_mode; //0 yuv 1 raw 2 rgb565
    int ac_freq;   //50/60
    int fps;       //0:25/30  1:50/60
    int dynamic_load;

    // ? ???? ? ?ㄤ寒搴????
    int auto_exposure;
    // ??涓娆¤峰??aec table ?缂??
    int lastTableNum;
    // 涓涓娆＄骞冲浜 搴?
    int lastAreaVal;

    // ?ㄥ???? 涓 锛dg??缃 ?搴? aec/agc蹇?甯э??浠ラ瑕??甯т互???dg???浼?虹伴 ???
    unsigned char lastDgReg;
    unsigned char dgReg;

    // ? ???? 灞?ㄤ寒搴???达?? ?ㄤ汉?歌 ? 娴渚涓 瀹?般?朵?妯″?涓?瑕?
    int local_adjustment;
    // ?哄骞冲浜 搴?
    int aveArea;
    // ?哄??
    int aveAreaSx;
    int aveAreaEx;
    int aveAreaSy;
    int aveAreaEy;

    // ?ㄤ??峰 memory bits, ?逛究璁＄ ?哄骞冲浜 搴?
    //int memoryBits[32*8] = {0};
    //int *memoryBits;
    //char charBins[32*32] = { 0 };
    char *charBins;

    // ? ?浜 搴???卤10%
    int expAve;

    int (*sensor_init)(int reso_mode, int data_mode, int ac_freq, int fps, ...);

    void (*sensor_set_mode)(int reso_mode, int data_mode);
    void (*sensor_set_ac_freq)(int ac_freq);

    int (*sensor_i2c_config)(void);

    void (*sensor_get_agc)(unsigned char *agcReg);
    void (*sensor_set_agc)(unsigned char agcReg);
    void (*sensor_get_agc_valx100)(int *agcVal);
    void (*sensor_set_agcVal)(int val, int step);
    void (*sensor_get_closest_agcVal)(int agcValOld, int *agcVal);

    void (*sensor_get_aec)(int *aecVal);
    void (*sensor_set_aec)(int val);

    void (*sensor_set_auto_aec_agc)(int enable);

    int (*sensor_get_table_closest_areaVal)(int aimsAreaVal);
    int (*sensor_set_exp)(struct nb_exp_table_t *exp, int detect_area, int aimsArea);
    int (*sensor_set_auto_exposure)(int flag);

    void (*sensor_aec_agc_init)(void);

    void (*sensor_uninit)(void);
};

int md_wait_for_motion(unsigned int timeout);
void perf_timer_init(void);

/*  system */
/* Machine mode IRQ handler wrapper
for support task switch in external irq handler:(by explicit call portYIELD_FROM_ISR())
it must do like systick_handler() according follow flow:
	portSAVE_CONTEXT
	portSAVE_EPC
	jal	f
	portRESTORE_CONTEXT
*/
#define Handler_Wrapper(f)                                    \
__attribute__((section(".text")))                                   \
void __handler_wrapper_##f (void) {           \
    asm volatile( ".extern in_interrupt_flag \n\t" \
        "addi sp, sp, (-31*4) \n\t"   \
        "sw ra, 0*4(sp)	    \n\t"	  \
        "sw gp, 1*4(sp)     \n\t"     \
        "sw tp, 2*4(sp)     \n\t"     \
        "sw a0, 3*4(sp)     \n\t"     \
        "sw a1, 4*4(sp)     \n\t"     \
        "sw a2, 5*4(sp)     \n\t"     \
        "sw a3, 6*4(sp)     \n\t"     \
        "sw a4, 7*4(sp)     \n\t"     \
        "sw a5, 8*4(sp)     \n\t"     \
        "sw a6, 9*4(sp)     \n\t"     \
        "sw a7, 10*4(sp)    \n\t"     \
        "sw t0, 11*4(sp)    \n\t"     \
        "sw t1, 12*4(sp)    \n\t"     \
        "sw t2, 13*4(sp)    \n\t"     \
        "sw t3, 14*4(sp)    \n\t"     \
        "sw t4, 15*4(sp)    \n\t"     \
        "sw t5, 16*4(sp)    \n\t"     \
        "sw t6, 17*4(sp)    \n\t"     \
        "sw s0, 18*4(sp)    \n\t"     \
        "sw s1, 19*4(sp)    \n\t"     \
        "sw s2, 20*4(sp)    \n\t"     \
        "sw s3, 21*4(sp)    \n\t"     \
        "sw s4, 22*4(sp)    \n\t"     \
        "sw s5, 23*4(sp)    \n\t"     \
        "sw s6, 24*4(sp)    \n\t"     \
        "sw s7, 25*4(sp)    \n\t"     \
        "sw s8, 26*4(sp)    \n\t"     \
        "sw s9, 27*4(sp)    \n\t"     \
        "sw s10, 28*4(sp)   \n\t"     \
        "sw s11, 29*4(sp)   \n\t"     \
        "li t0,1            \n\t"     \
        "la t1,in_interrupt_flag \n\t" \
        "sw t0, 0(t1)       \n\t"     \
        "lw t0, pxCurrentTCB\n\t"     \
	    "sw sp, 0*0(t0)		\n\t");   \
    asm volatile( "csrr t0, mepc\n\t" \
        "sw t0, 30*4(sp)\n\t");       \
    asm volatile("jalr  %0" :: "r" (f));    \
    asm volatile("lw t0, pxCurrentTCB \n\t"    \
        "lw sp, 0*0(t0)      \n\t"    \
        "lw t0, 30*4(sp)     \n\t"    \
        "csrw mepc, t0       \n\t"    \
        "li t0, 0x1880       \n\t"    \
        "csrw mstatus, t0    \n\t"    \
        "li t0,0            \n\t"     \
        "la t1,in_interrupt_flag \n\t" \
        "sw t0, 0(t1)        \n\t"     \
        "lw ra, 0*4(sp)      \n\t"    \
        "lw gp, 1*4(sp)      \n\t"    \
        "lw tp, 2*4(sp)      \n\t"    \
        "lw a0, 3*4(sp)      \n\t"    \
        "lw a1, 4*4(sp)      \n\t"    \
        "lw a2, 5*4(sp)      \n\t"    \
        "lw a3, 6*4(sp)      \n\t"    \
        "lw a4, 7*4(sp)      \n\t"    \
        "lw a5, 8*4(sp)      \n\t"    \
        "lw a6, 9*4(sp)      \n\t"    \
        "lw a7, 10*4(sp)     \n\t"    \
        "lw t0, 11*4(sp)     \n\t"    \
        "lw t1, 12*4(sp)     \n\t"    \
        "lw t2, 13*4(sp)     \n\t"    \
        "lw t3, 14*4(sp)     \n\t"    \
        "lw t4, 15*4(sp)     \n\t"    \
        "lw t5, 16*4(sp)     \n\t"    \
        "lw t6, 17*4(sp)     \n\t"    \
        "lw s0, 18*4(sp)     \n\t"    \
        "lw s1, 19*4(sp)     \n\t"    \
        "lw s2, 20*4(sp)     \n\t"    \
        "lw s3, 21*4(sp)     \n\t"    \
        "lw s4, 22*4(sp)     \n\t"    \
        "lw s5, 23*4(sp)     \n\t"    \
        "lw s6, 24*4(sp)     \n\t"    \
        "lw s7, 25*4(sp)     \n\t"    \
        "lw s8, 26*4(sp)     \n\t"    \
        "lw s9, 27*4(sp)     \n\t"    \
        "lw s10, 28*4(sp)    \n\t"    \
        "lw s11, 29*4(sp)    \n\t"    \
        "addi sp, sp, (+31*4)\n\t"    \
	    "mret   \n\t");               \
}


#define Handler_Wrapper_Entry(f) __handler_wrapper_##f
#define Handlder_Wrapper_Declare(f) void __handler_wrapper_##f(void)
void irq_init(void);

int irq_cpu_disable(void);
void irq_cpu_enable(void);

void irq_ext_enable(int irq);
void irq_ext_disable(int irq);
void irq_ext_clear(int irq);
int irq_install_handler(int irq,void* handler);


typedef enum
{
    IRQ_UART = 0x00,
    IRQ_I2S,
    IRQ_I2C,
    IRQ_KPD,
    IRQ_PWM0,
    IRQ_PWM1,
    IRQ_PWM2,
    IRQ_PWM3,
    IRQ_PWM4,
    IRQ_PWM5,
    IRQ_PWM6, //10
    IRQ_PWM7,
    IRQ_GPIO,
    IRQ_TIM0,
    IRQ_TIM1,
    IRQ_TIM2,
    IRQ_TIM3,
    IRQ_RTC,
    IRQ_WDT,
    IRQ_SPI,
    IRQ_DMAC, //20
    IRQ_SENSOR_DBG,
    IRQ_MMC,
    IRQ_SENSOR_MEM,
    IRQ_MD,
    IRQ_AES_ERR,
    IRQ_AES_DONE,
    IRQ_SSP,
    IRQ_SCALER_FINISH, //IRQ_RESV2,
    IRQ_FE,
    IRQ_NUM,
    IRQ_CORE1_EVENT,
} IRQ_ID_T;

extern struct sensor_conf_t *sensor_conf;

extern int md_get_stat_global_ave(void);
extern int md_get_motion_area(uint16_t *sx, uint16_t *sy, uint16_t *width, uint16_t *height);
extern int get_global_area(void);

#endif


#define GPIO_BASE                   																	(0x40050000)
#define GPIO_PORTA_DR               																	(GPIO_BASE+0x00)
#define GPIO_PORTA_GET_DR               															(GPIO_BASE+0x50)


#define GPIO_PORTA_GROUP         	      0			
#define GPIO_PORTB_GROUP         	      1			
#define GPIO_PORTC_GROUP         	      2			

#define GPIO_PORT_PIN_0									0       
#define GPIO_PORT_PIN_1									1       
#define GPIO_PORT_PIN_2									2       
#define GPIO_PORT_PIN_3									3       
#define GPIO_PORT_PIN_4									4       
#define GPIO_PORT_PIN_5									5       
#define GPIO_PORT_PIN_6									6       
#define GPIO_PORT_PIN_7									7       




// 设置保存每帧需要记录的数据的上限
#define NB__SAVE_WINTOFEDATA_ITEM																	5

#define NB__SAVE_WINTOFEDATA_START																50
#define NB__SAVE_WINTOFEDATA_OFFSET																25
#define NB__SAVE_WINTOFEDATA_START1																38  // 50 - 25/2



#define NB__DEBUG_DRAWWIN_BOX_ID																	1
#define NB__DEBUG_MOTION_BOX_ID																		2
//#define NB__DEBUG_TRACK_BOX_ID																	  3
#define NB__DEBUG_FOUND_GESTURE_BOX_ID														3
#define NB__DEBUG_FOUND_BOX_ID																		4

#define NB__MOTION_TABLE_ITEM					15
extern u8 NB__maybe_gesture_goto_sys_motions_state;

extern u8 NB_maybe_gesture_w_item;
extern u16 NB_maybe_gesture_w_table[];

extern u8 NB_maybe_gesture_x0y0_item;
extern u16 NB_maybe_gesture_x0_table[];
extern u16 NB_maybe_gesture_y0_table[];
extern u16 NB_maybe_gesture_y_table[];


enum
{
	NTSC_PAL_MODE_PAL,
	NTSC_PAL_MODE_NTSC,
};

void NB__set_ntsc_pal_mode(void);


enum
{
	// 全局识别
	NB__DETECT_SYS_MODE_START = 0,

	NB__DETECT_SYS_MODE_GLOBAL_START, // 1
	NB__DETECT_SYS_MODE_GLOBAL,
	
	NB__DETECT_SYS_MODE_MOTION_START, // 3
	NB__DETECT_SYS_MODE_MOTION,
	
	NB__DETECT_SYS_MODE_FOUND_START, // 5
	NB__DETECT_SYS_MODE_FOUND,       // 6

	NB__DETECT_SYS_MODE_END,     

	
};


typedef struct NB__Rec_s_t
{

	u16 x;
	u16 y;
	
	u16 w;
	u16 h;
	
	
}__attribute__((aligned(4))) NB__Rec_s;

// 根据距离选择使用模型
typedef enum NB__select_model_g_s_t
{


	NB__Select_Model_G_No,			   

	NB__Select_Model_G_Nearly, 		
	
	NB__Select_Model_G_Mid, 		

	NB__Select_Model_G_Far, 		 
	
	
	NB__Select_Model_G_End,

	
	
}NB__select_model_g_s;


extern TaskHandle_t xHandle_Win;
extern TaskHandle_t xHandle_User;
extern TaskHandle_t xHandle_Feature;
//extern TaskHandle_t xHandle_Result;



extern u32 NB__f_id;
extern u8 NB__fps;
extern u8 NB__global_b;
extern u8 NB__global_e;
extern u8 NB__global_ag;


//extern u8 NB__charBins[];


extern u8 NB__Savedata_index;

extern u8 NB__gesture_found_item;

extern u8 NB__control_gesture_enable;

// 0 云台停止状态，只能手势启动（不会比较其他模型）
// 1 云台启动状态，可以手势停止
extern u8 NB__gesture_control_motor_state;
extern u8 NB__found_gesture_control;
extern u16 NB__motor_stop_times;

extern u8 NB__motor_run;
extern u8 NB__detect_sys_mode;
extern u8 NB__found_to_motion;

extern u8 NB__filter_mode;
extern u8 NB__filter_m_g;
extern u8 NB__filter_m_l;

extern u16 NB__motor_lost_number;


extern u32 NB__show_motion_head_id;
extern u32 NB__show_found_id;

extern u8 NB__load_model_because;

extern u8 NB__load_model_ok_times;

extern u8 NB__load_model_last_state;
extern u8 NB__load_model_last_id;



extern u8 NB__load_model_state;
extern u8 NB__load_model_id;



u8 NB__load_model_update(u8 because,u8 set_model,u8 set_id,u8 *hold_times);

int NB__gpio_pin_2_group(int pin_no, int *group, int *pin);
void NB__gpio_set_value_app(int group,int pin, int val);
u8 NB__gpio_get_value_app(int group,int pin);


void NB__Boot_Init(void);
void NB__Base_Init(void);
void NB__Base_Action_start(u32 frame_id,u8 motor_state);
void NB__Base_Action_end(u32 frame_id);

void NB__updata_group_use_index(u8 group,u8 *table,u8 len);

void NB__WatchDogInit(void);


void NB__Binarization(unsigned char threshold);


#endif



