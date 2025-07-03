/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#include "nbsdk.h"
#include "bsp.h"

/*
 for eval board
*/

#ifdef NB_EVALBOARD

//#define PLL_CLOCK   576
#define PLL_CLOCK 480

// NB_SENSOR_PAL, support 100 /50 / 25 / 12(12.5) FPS
// NB_SENSOR_NTSC, support 120 /60 / 30 / 15 FPS
#define NB_SENSOR_PAL_NTSC (NB_SENSOR_PAL)
#define INTERNAL_SENSOR_FPS (50)
#define SYSTEM_CLK (80)          // 80 / 60 / 48 /36 / 24
#define INTERNAL_SENSOR_CLK (15) // 5 / 8 / 15 / 30

#define FEATURE_ENABLE_SENSOR_DCBC
#ifndef BSP_NO_FEATURE_INIT
#define FEATURE_ENABLE_PM
#include "feature_init.h"
#endif

/*if uloader is not used, set offset to 0, ULOADER_ALIGN_SIZE is defined in creatNBF.sh */
#ifndef ULOADER_ALIGN_SIZE
#define ULOADER_ALIGN_SIZE 0
#endif

void board_init(void)
{
    /*EVALBOARD-V:
      padshare: not vid & not spi vid mode
      when vid switch on:
        IOA0/IOA2/IOA5/IOA6/IOA7/IOC0/IOC1/IOC2/IOC3/IOC4/IOC5 is used by; uart/i2c0/dmic function can't be used
      when spi vid switch on:
        IOA0/IOA1/IOA2/IOB7 is used by; led/gpio key can't be used
    */

    // set all IO to GPIO Input Mode to prevent floating
    sys_set_padshare(IOA0, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA0, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOA1, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA1, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOA2, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA2, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOA3, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA3, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOA4, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA4, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOA5, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA5, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOA6, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA6, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOA7, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOA7, GPIO_INPUT_DIRECTION);

    sys_set_padshare(IOB1, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOB1, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOB2, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOB2, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOB3, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOB3, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOB4, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOB4, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOB5, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOB5, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOB6, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOB6, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOB7, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOB7, GPIO_INPUT_DIRECTION);

    sys_set_padshare(IOC0, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC0, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOC1, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC1, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOC2, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC2, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOC3, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC3, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOC4, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC4, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOC5, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC5, GPIO_INPUT_DIRECTION);
    sys_set_padshare(IOC6, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
    gpio_set_dir(IOC6, GPIO_INPUT_DIRECTION);

    // core voltage adjust
    bsp_init_core();

    // 480 PLL, 80M core clock
    bsp_init_clock(PLL_CLOCK, SYSTEM_CLK);

    // enale all pclk
    bsp_enable_pclk();

    // set main task stack size
    system_config_stack(configMINIMAL_STACK_SIZE * 5);

    //to use printf in board_init()
    console_io_init();
	
    //uncomment if need spi flash running on standard mode(1 line)
    //sf_config_mode(QSPI_MODE_STD);

    //if uloader is used, should offset the nbf header to ULOADER_ALIGN_SIZE=16KB 
    pack_set_base(ULOADER_ALIGN_SIZE);
}

int board_sensor_init(void)
{
    int ret = 0;

    printf("internal sensor.\n");

    internal_sensor_init(PLL_CLOCK, INTERNAL_SENSOR_CLK);

    // mode : NB_SENSOR_PAL (50Hz), NB_SENSOR_NTSC(60Hz)
    // fps, NB_SENSOR_PAL : 12(12.5)/25/50/100,   NB_SENSOR_NTSC: 15/30/60/120
    internal_sensor_config(INTERNAL_SENSOR_CLK, NB_SENSOR_PAL_NTSC, INTERNAL_SENSOR_FPS);

    memset(sensor_conf, 0, sizeof(struct sensor_conf_t));
    sensor_conf->input_width = 320;
    sensor_conf->input_height = 320;
    sensor_conf->output_width = 320;
    sensor_conf->output_height = 320;
    sensor_conf->charBins = nb_malloc(32 * 32);
    if (!sensor_conf->charBins)
        return 1;

    crop_init();
    crop_config_win(0, 0, 320, 320);
    crop_enable(0, 0);

    return ret;
}

int board_led_init(void)
{
#if (LED0 != -1)
    led_add_conf(LED0, LED_FLASHING, 500);
#endif

#if (LED1 != -1)
    led_add_conf(LED1, LED_FIXED, 0);
#endif

#if (LED2 != -1)
    led_add_conf(LED2, LED_FIXED, 0);
#endif

#if (LED3 != -1)
    led_add_conf(LED3, LED_FIXED, 0);
#endif
    return 0;
}

int bsp_init(void)
{
    int ret = 0;

    printf("EVAL board init.\n");

    /*configure access speed:20M*/
    sf_config_speed(20000000);

    ret = board_sensor_init();
    if (ret)
        return ret;

    ret = board_led_init();

// add gpio key if exists
#if (GPIO_KEY0 != -1)
    gpio_key_enable(0, 0);
    gpio_key_add(GPIO_KEY0, GOPI_ACTIVE_LEVEL);
#endif

    return ret;
}

#endif
