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
 1. Enable custom_timer_register() in cmdAppInit()
 2.	nb>timer 1 10 => timer 1 10hz
	timerid(1) timer_hz(10)-4800000
	timeSem[0]=0x2001af90

	nb>
	    5988 diff=  99(ms) taskTimer1 timer_hz=  10-0001-04798898
	    6088 diff= 100(ms) taskTimer1 timer_hz=  10-0002-04798898
	    6188 diff= 100(ms) taskTimer1 timer_hz=  10-0003-04798898
	    6288 diff= 100(ms) taskTimer1 timer_hz=  10-0004-04798898
	    6388 diff= 100(ms) taskTimer1 timer_hz=  10-0005-04798898
	    6488 diff= 100(ms) taskTimer1 timer_hz=  10-0006-04798898
	    6587 diff=  99(ms) taskTimer1 timer_hz=  10-0007-04798898
	    6687 diff= 100(ms) taskTimer1 timer_hz=  10-0008-04798898
	    6787 diff= 100(ms) taskTimer1 timer_hz=  10-0009-04798898
	    6887 diff= 100(ms) taskTimer1 timer_hz=  10-0010-04798898

 3.	nb>timer 2 1 => timer 2 1hz
	timerid(2) timer_hz(1)-48000000
	timeSem[1]=0x0

	nb>
	    4553 diff= 998(ms) taskTimer2 timer_hz=   1-0001-47998897
	    5552 diff= 999(ms) taskTimer2 timer_hz=   1-0002-47998897
	    6551 diff= 999(ms) taskTimer2 timer_hz=   1-0003-47998897
	    7550 diff= 999(ms) taskTimer2 timer_hz=   1-0004-47998897
	    8549 diff= 999(ms) taskTimer2 timer_hz=   1-0005-47998897
	    9548 diff= 999(ms) taskTimer2 timer_hz=   1-0006-47998897
	   10547 diff= 999(ms) taskTimer2 timer_hz=   1-0007-47998897
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
void timer1_int_handler(void);
void timer2_int_handler(void);
static void timerCfg(char *cmd[],int arg);
void custom_timer_register(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/
static BaseType_t xTask1 = 0;
static TaskHandle_t xHandle1 = NULL;
static BaseType_t xTask2 = 0;
static TaskHandle_t xHandle2 = NULL;
static SemaphoreHandle_t timeSem[2];
static uint32_t time_count[2];

void timer1_int_handler(void)
{
	int int_status = 0;
	BaseType_t xHigherPriorityTaskWoken=pdFALSE;

	int_status = timer_get_int_status( ( TIMER_ID_T )TIM1 );
	//printf("timer1 int_status:%x\n", int_status);
	if ( int_status )
	{
	    //printf("timer1 isr t=%8ld-%08ld-%04ld\n", xTaskGetTickCount(), timer_get_count(TIM1),time_count[0]);
		timer_clear_int( ( TIMER_ID_T )TIM1 );
		time_count[0]++;	
		if(timeSem[0]){
			xSemaphoreGiveFromISR((QueueHandle_t)timeSem[0], &xHigherPriorityTaskWoken);
		}
	}
	/*clear external pending irq*/
	irq_ext_clear( TIM1 );
	/*switch task if need*/
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void timer2_int_handler(void)
{
    int int_status = 0;
	BaseType_t xHigherPriorityTaskWoken=pdFALSE;

	int_status = timer_get_int_status( ( TIMER_ID_T )TIM2 );
	//printf("timer2 int_status:%x\n", int_status);
    if ( int_status )
    {
		//printf("timer2 isr t=%8ld-%08ld-%04ld\n", xTaskGetTickCount(), timer_get_count(TIM2),time_count[1]);
		timer_clear_int( ( TIMER_ID_T )TIM2 );
		time_count[1]++;	
		if(timeSem[1]){
			xSemaphoreGiveFromISR((QueueHandle_t)timeSem[1], &xHigherPriorityTaskWoken);
		}
    }
    /*clear external pending irq*/
    irq_ext_clear( TIM2 );
	/*switch task if need*/
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

static void taskTimer1(void *parameters)
{
	uint32_t timer_hz = (uint32_t)parameters;
	uint32_t loop = 100;
	uint32_t preT=0, currT=0;
	
	preT=currT=xTaskGetTickCount();
	printf("\n");
	while(loop > 0)
	{
		if(timeSem[0]==0){
			vTaskDelay(10);
			continue;
		}
		if(pdPASS == xSemaphoreTake((QueueHandle_t)timeSem[0], portMAX_DELAY)){
			loop --;
			currT = xTaskGetTickCount();
			printf("%8ld diff=%4ld(ms) %s timer_hz=%4ld-%04ld-%08ld\n", currT, currT-preT,__func__, timer_hz, time_count[0], timer_get_count(TIM1));
			preT = currT;
		}
	}

	printf("%s test done\n",__func__);
	xTask1 = 0;
	xHandle1 = NULL;
	vTaskDelete(NULL);
}

static void taskTimer2(void *parameters)
{
	uint32_t timer_hz = (uint32_t)parameters;
	uint32_t loop = 100;
	uint32_t preT=0, currT=0;

	preT=currT=xTaskGetTickCount();
	printf("\n");
	while(loop > 0)
	{
		if(timeSem[1]==0){
			vTaskDelay(10);
			continue;
		}
		if(pdPASS == xSemaphoreTake((QueueHandle_t)timeSem[1], portMAX_DELAY)){
			loop --;
			currT = xTaskGetTickCount();
			printf("%8ld diff=%4ld(ms) %s timer_hz=%4ld-%04ld-%08ld\n", currT, currT-preT,__func__, timer_hz, time_count[1], timer_get_count(TIM2));
			preT = currT;
		}
	}

	printf("%s test done\n",__func__);
	xTask2 = 0;
	xHandle2 = NULL;
	vTaskDelete(NULL);
}
static void
timerCfg(
	char *cmd[],
	int arg
)
{
	int32_t timerid;
	if( arg < 2 ){
		printf("input error => nb>timer timerid time\n");
		return;
	}
	else{
		timerid = strtoul(cmd[0], NULL, 0);
		if(!(timerid > 0 && timerid < 3)){
			printf("timerid is invalid %lx\n", timerid);
			return;
		}
		uint32_t timer_hz = strtoul(cmd[1], NULL, 0);
		printf("timerid(%ld) timer_hz(%ld)-%ld\n", timerid,timer_hz,system_clock()/2/timer_hz);
		if(timerid==1){
			time_count[0]=0;
			timer_init(timerid, TIM_MODE_USERDEF,0x2, system_clock()/2/timer_hz, Handler_Wrapper_Entry(timer1_int_handler));
			timeSem[0] = xSemaphoreCreateBinary();
			printf("timeSem[0]=0x%lx\n",(uint32_t)timeSem[0]);
		}
		if(timerid==2){
			time_count[1]=0;
			timer_init(timerid, TIM_MODE_USERDEF,0x2, system_clock()/2/timer_hz, Handler_Wrapper_Entry(timer2_int_handler));
			timeSem[1] = xSemaphoreCreateBinary();
			printf("timeSem[1]=0x%lx\n",(uint32_t)timeSem[0]);
		}
		timer_start(timerid);

		if((timerid==1) && (xTask1==0)){
			xTask1 = xTaskCreate(
			    taskTimer1,
			    "taskTimer1",
			    configMINIMAL_STACK_SIZE,
			    (void *const)timer_hz,
			    tskIDLE_PRIORITY + 1,
			    &xHandle1
			    );
			if( xTask1 != pdPASS )
			{
			    printf("taskTimer1 is NULL !\n");
			    exit(0);
			}
		}
		if((timerid==2) && (xTask2==0)){
			xTask2 = xTaskCreate(
			    taskTimer2,
			    "taskTimer2",
			    configMINIMAL_STACK_SIZE,
			    (void *const)timer_hz,
			    tskIDLE_PRIORITY + 1,
			    &xHandle2
			    );
			if( xTask2 != pdPASS )
			{
			    printf("taskTimer2 is NULL !\n");
			    exit(0);
			}
		}
	}
}

/**
 * @brief custom_gpio_register
 * 
*/
void custom_timer_register(void)
{
	customCmdRegister("timer",timerCfg,"trigger timer");
}



