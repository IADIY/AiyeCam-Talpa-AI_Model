/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2023 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "nbsdk.h"
#include "bsp.h"
#include "nb_cmd_api.h"
#include "nbsdk_api.h"

/**************************************************************************
 *	Usage
 **************************************************************************/
/*
 1. Enable custom_rtc_register() in cmdAppInit()
 2. nb>rtc 1
 	rtc period = 1
 
 	nb>rtc int status:1,t=1000
 	cnt:0 
 	rtc int status:1,t=1000
 	cnt:1 
 	rtc int status:1,t=1000
 	cnt:2 
 	rtc int status:1,t=1000
 	cnt:3 
 	rtc int status:1,t=1000
 	cnt:4 
 	rtc int status:1,t=1000
 	cnt:5 

 */
/**************************************************************************
 *	Constants
 **************************************************************************/
#define RTC_CLK 32768
#define RTC_OFFSET 0//0xFFFF

/**************************************************************************
 *	External Function            
 **************************************************************************/

/**************************************************************************
 *	Function            
 **************************************************************************/
void rtc_int_handler(void);
static void rtcCfg(char *cmd[],int arg);
void custom_rtc_register(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/
static uint32_t rtc_count = 0;
static uint32_t rtc_irq_done = 0;
static uint32_t rtc_match_count = 0;
void rtc_int_handler(void)
{
	rtc_count = rtc_read_count();
	int status = rtc_get_status();
	
	printf("rtc int status:%x,t=%d\ncnt:%ld \n", status, 1000*(rtc_count-RTC_OFFSET)/RTC_CLK, rtc_irq_done);
#if 0
	sys_reset2(SYS_RSTN_RTC);
	rtc_set_syn(1);
	rtc_set_match_count(rtc_match_count);
#endif

	if(status)
	{
		rtc_int_mask(1);
		rtc_int_enable (0);
		rtc_clear_interrupt();
	}
	rtc_set_count(RTC_OFFSET);
	while(rtc_read_count() != RTC_OFFSET) { 
		rtc_set_count(RTC_OFFSET);
	}
	rtc_clear_interrupt();
	irq_ext_clear( IRQ_RTC );
	rtc_irq_done++;
	rtc_int_enable(1);
	rtc_int_mask(0);
	
#if 0	
	sys_delay(50);
	memdump(0x401a0000, 0x30);
	sys_delay(50);
	memdump(0x401a0000, 0x30);
#endif
}


static void
rtcCfg(
	char *cmd[],
	int arg
)
{
	int32_t period = 1;
	if( arg < 1 ){
		printf("input error => nb>rtc period\n");
		return;
	}
	else{
		period = strtoul(cmd[0], NULL, 0);
		if(period <= 0){
			period = 1;
		}
		rtc_set_syn(1);
		rtc_int_mask(1);
		rtc_clear_interrupt();
		irq_ext_clear(IRQ_RTC);
		irq_install_handler(( IRQ_ID_T )(IRQ_RTC), Handler_Wrapper_Entry(rtc_int_handler));
		rtc_match_count = period*RTC_CLK+RTC_OFFSET;
		rtc_set_match_count(rtc_match_count);
		rtc_clear_interrupt();		
		rtc_set_count(0);
		rtc_int_enable(1);
		rtc_int_mask(0);
		irq_ext_enable(IRQ_RTC);
		/* set highest driving */
		rtc_clock_driving(0xF); /* Need NBSDK_01.01.04 */
		printf("rtc period = %ld\n",period);
	}
}

/**
 * @brief custom_gpio_register
 * 
*/
void custom_rtc_register(void)
{
	customCmdRegister("rtc",rtcCfg,"trigger rtc");
}


