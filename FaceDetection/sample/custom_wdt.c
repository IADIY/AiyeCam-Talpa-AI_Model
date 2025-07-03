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
 1. Enable custom_wdt_register() in cmdAppInit()
 2. counter is equal to 2^(16 + time_out), time_out=0 is 64*1024
 3. nb>wdt 0 6
		WDT_MODE_SYSRESET : reset system
		1: counter:3594176 eclapse 500 ms
		2: counter:3091674 eclapse 502 ms
		3: counter:2589172 eclapse 502 ms
		4: counter:2086670 eclapse 502 ms
		5: counter:1584167 eclapse 502 ms
		6: counter:1081665 eclapse 502 ms
		7: counter:579163 eclapse 502 ms
		8: counter:76661 eclapse 502 ms
		C
		NBSDK_VERSION:NBSDK_01.00.00-Apr  8 2022-13:32:14
		Build @HOST-Apr  8 2022-13:55:15

 4.	nb>nb>wdt 1 4
		WDT_MODE_INTFIRST : issues interrupt
		1: counter:448259 eclapse 500 ms
		wdt int occur, wdt_event = 1
		wdt feed
		3: counter:494137 eclapse 500 ms
		wdt int occur, wdt_event = 1
		wdt feed
		5: counter:541016 eclapse 500 ms
		6: counter:38514 eclapse 502 ms
		wdt int occur, wdt_event = 1
		wdt feed
		8: counter:85392 eclapse 500 ms
		wdt int occur, wdt_event = 1
		wdt feed
 */
/**************************************************************************
 *	Constants
 **************************************************************************/

/**************************************************************************
 *	External Function            
 **************************************************************************/

/**************************************************************************
 *	Function            
 **************************************************************************/
void wdt_int_handler(void);
static void wdtCfg(char *cmd[],int arg);
void custom_wdt_register(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/
static int feed_in_irq = 1;
static int prev_count = 0;

void wdt_int_handler(void)
{
	int status;

	status = wdt_get_status();
	if (status)
	{
		printf("wdt int occur, wdt_event = %d\n", status);
		if (feed_in_irq){
			wdt_clear_int();
			printf("wdt feed\n");
			wdt_restart();
			prev_count = 0;
		}
		else{
			irq_ext_disable(IRQ_WDT);
		}
	}
	irq_ext_clear((IRQ_ID_T)(IRQ_WDT));
}

static void
wdtCfg(
	char *cmd[],
	int arg
)
{
	int32_t wdt_mode;
	if( arg < 2 ){
		printf("input error => nb>timer mode time_out\n");
		return;
	}
	else{
		wdt_mode = strtoul(cmd[0], NULL, 0);
		if(wdt_mode == WDT_MODE_SYSRESET){
			printf("WDT_MODE_SYSRESET : reset system\n");
		}
		else if(wdt_mode == WDT_MODE_INTFIRST){
			printf("WDT_MODE_INTFIRST : issues interrupt\n");
		}
		else{
			printf("wdt_mode is invalid %lx\n", wdt_mode);
			return;
		}
		uint32_t wdt_time_out = strtoul(cmd[1], NULL, 0);
		if(wdt_time_out > (uint32_t)WDT_TOP_2G){
			printf("wdt_time_out is invalid %lx\n", wdt_time_out);
			return;
		}
		int i;
		int cur_count;
		
		wdt_init_clk(0);
		wdt_enable(0);
		wdt_set_timeout(wdt_time_out);
		wdt_set_rpl(WDT_RPL_32PCLK);
		wdt_set_mode(wdt_mode);
		wdt_restart();
		
		feed_in_irq = 1;
		
		irq_ext_disable((IRQ_ID_T)(IRQ_WDT));
		irq_install_handler((IRQ_ID_T)(IRQ_WDT), Handler_Wrapper_Entry(wdt_int_handler));
		irq_ext_enable((IRQ_ID_T)(IRQ_WDT));
		wdt_enable(1);
		
		vTaskDelay(100);
		for (i=0;i<15;i++)
		{
			cur_count = wdt_get_count();
			if (!prev_count){
				prev_count = cur_count;
			}
			else{
				printf("%d: counter:%d eclapse %d ms\n",i,cur_count,1000*(prev_count-cur_count)/1000000);
			}
			prev_count = cur_count;
			vTaskDelay(500);
		}
	}
}

/**
 * @brief custom_gpio_register
 * 
*/
void custom_wdt_register(void)
{
	customCmdRegister("wdt",wdtCfg,"trigger wdt");
}

