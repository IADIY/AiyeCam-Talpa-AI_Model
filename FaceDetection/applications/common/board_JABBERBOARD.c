/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#include "nbsdk.h"
#include "bsp.h"

/*
 for JABBER board
*/

#ifdef NB_JABBERBOARD

//#define AUDIO_AMP_MODE_1
//#define AUDIO_AMP_MODE_1

//#define PLL_CLOCK   576
#define PLL_CLOCK   480

// NB_SENSOR_PAL, support 100 /50 / 25 / 12(12.5) FPS
// NB_SENSOR_NTSC, support 120 /60 / 30 / 15 FPS
#define NB_SENSOR_PAL_NTSC      ( NB_SENSOR_PAL )
#define INTERNAL_SENSOR_FPS     ( 50 )
#define SYSTEM_CLK              ( 80 ) // 80 / 60 / 48 /36 / 24
#define INTERNAL_SENSOR_CLK     ( 15 )  // 5 / 8 / 15 / 30

#ifndef BSP_NO_FEATURE_INIT
#define FEATURE_DISABLE_CONSOLE
#define FEATURE_ENABLE_SENSOR_DCBC
#define FEATURE_ENABLE_PM
#include "feature_init.h"
#endif

void board_init(void)
{
    //padshare
    sys_set_padshare(IOA0, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //gpio key
    sys_set_padshare(IOA1, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //gpio: Audio Amp
    sys_set_padshare(IOA2, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //gpio
    sys_set_padshare(IOA3, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //
    sys_set_padshare(IOA4, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //
    sys_set_padshare(IOA5, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //gpio
    sys_set_padshare(IOA6, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //gpio
    sys_set_padshare(IOA7, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //LED 0

    sys_set_padshare(IOB1, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //flash
    sys_set_padshare(IOB2, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    sys_set_padshare(IOB3, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    sys_set_padshare(IOB4, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    sys_set_padshare(IOB5, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    sys_set_padshare(IOB6, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    sys_set_padshare(IOB7, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //

    sys_set_padshare(IOC0, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);//dmic
    sys_set_padshare(IOC1, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);//dmic
    sys_set_padshare(IOC2, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);//dmic
    sys_set_padshare(IOC3, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);//LED 1
    sys_set_padshare(IOC4, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);//LED 2
    sys_set_padshare(IOC5, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);//LED 3
    sys_set_padshare(IOC6, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);//pwm0

    //core voltage adjust
    bsp_init_core();

    //480 PLL, 80M core clock
    bsp_init_clock(PLL_CLOCK, SYSTEM_CLK);

    __raw_writel(0x154,0x401d012c); //spll_vctl_test_en ==1, only for debug

    // enale all pclk
    bsp_enable_pclk();

    //set main task stack size
    system_config_stack(configMINIMAL_STACK_SIZE*16);
}

int board_sensor_init( void )
{
    int ret = 0;

    printf("internal sensor.\n");

    internal_sensor_init( PLL_CLOCK, INTERNAL_SENSOR_CLK );

    // mode : NB_SENSOR_PAL (50Hz), NB_SENSOR_NTSC(60Hz)
    // fps, NB_SENSOR_PAL : 12(12.5)/25/50/100,   NB_SENSOR_NTSC: 15/30/60/120
    internal_sensor_config(INTERNAL_SENSOR_CLK, NB_SENSOR_PAL_NTSC, INTERNAL_SENSOR_FPS);

    memset(sensor_conf,0,sizeof(struct sensor_conf_t));
    sensor_conf->input_width = 320;
    sensor_conf->input_height = 320;
    sensor_conf->output_width = 320;
    sensor_conf->output_height = 320;
	sensor_conf->charBins = nb_malloc(32*32);
	if (!sensor_conf->charBins)
		return 1;

    crop_init();
    crop_config_win(0,0,320,320);
    crop_enable(0,0);

    return ret;
}

int board_led_init(void)
{
    led_add_conf( LED0, LED_FLASHING, 500 );
    led_add_conf( LED1, LED_FIXED, 0 );
    led_add_conf( LED2, LED_FIXED, 0 );
    led_add_conf( LED3, LED_FIXED, 0 );
    return 0;
}

int bsp_init(void)
{
    int ret=0;

    printf("JABBER board init.\n");

    /*configure access speed:20M*/
    sf_config_speed(20000000);

    ret = board_sensor_init();
    if (ret)
        return ret;

    ret = board_led_init();

    /*set audio amp*/
#if defined(AUDIO_AMP_MODE_0)
    gpio_set_dir(IOA1,GPIO_OUTPUT_DIRECTION);
    gpio_set_value( IOA1, 1 ); // 拉高一次
#elif defined(AUDIO_AMP_MODE_1)
    gpio_set_dir(IOA1,GPIO_OUTPUT_DIRECTION);
    // 拉高两次， 其中脉冲宽度需要大于1us, 不能大于12us
    gpio_set_value( IOA1, 1 ); // 拉高一次
    udelay(5);
    gpio_set_value( IOA1, 0 );
    udelay(5);
    gpio_set_value( IOA1, 1 ); // 拉高第二次
#endif

    //add gpio key if exists
    #ifdef GPIO_KEY0
    #if (GPIO_KEY0 != -1)
    gpio_key_enable(0,0);
    gpio_key_add( GPIO_KEY0, GOPI_ACTIVE_LEVEL );
    #endif
    #endif
    
    return ret;
}

#endif
