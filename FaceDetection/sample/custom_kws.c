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
 1. Enable custom_kws_register() in cmdAppInit()

 2. make sure the i2s dmic is on in EVB1.6(U4) or EVB1.7(U11) 
 
 3. make sure the MIC_CLK/MIC_LR/MIC_DO connect to IOC0/IOC1/IOC2
 
 4. type command "kws"
    nb>kws
	
 5. Speak to i2s dmic by "up","down","left","right","yes","no"
    We could get below's uart log。
    yes...99 %
    no...99 %
    down...99 %
    left...99 %
    right...99 %
    yes...99 %
    no...99 %
    down...99 %
    up...99 %
    down...99 %
    down...98 %
    right...99 %
    left...99 %
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
void custom_kws_register(void);
static void usage(void);
static void audio_dmic_gpio_init(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/
static void usage(void)
{
    printf("kws : enable kws speech detection flow\n");
}

static void audio_dmic_gpio_init(void)
{
	printf("audio_dmic_gpio_init\n");
	//EVB use IOC0/IOC1/IOC2 as I2S pin
	sys_set_padshare(IOC0, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //MIC_CLK
	sys_set_padshare(IOC1, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //MIC_LR
	sys_set_padshare(IOC2, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //MIC_DO
}

void kws_detect_result_handler(int ind, int pro)
{
    //printf("%s: ind - %d, pro - %d\n", __FUNCTION__, ind, pro);

    // 配置ds_cnn.dat时，其内部存在以下几组模型：
    // 0: _silence_
    // 1: _unknown_
    // 2: up
    // 3: down
    // 4: left
    // 5: right
    // 6: yes
    // 7: no
	if(pro < 98)
	{
		/* if < 98%, not confirm, but here is TBD */
		return;
	}
    switch (ind)
    {
    	case 2:
			printf("up...%d %%\n", pro);
			break;
    	case 3:
			printf("down...%d %%\n", pro);
			break;
    	case 4:
			printf("left...%d %%\n", pro);
			break;
    	case 5:
			printf("right...%d %%\n", pro);
			break;
    	case 6:
			printf("yes...%d %%\n", pro);
			break;
    	case 7:
			printf("no...%d %%\n", pro);
			break;
		default:
			return;
    }
}

static void
speech_recognition(
	char *cmd[],
	int arg
)
{
	audio_dmic_gpio_init();
	
	//kws init
	int r = kws_init(DEV_CIC, DB_KWS_DEFAULT,1);
	if (!r)
	{
		//print out support class name
		for (int i=0;i<kws_get_class_total();i++)
			printf("class %d: %s\n",i,kws_get_class_name(i));
		
		//start kws
		r = kws_start();
		printf("start kws task %s ret:%d\n",r?"FAIL":"OK",r);
	}
	else
	{
		printf("init kws task fail : 0x%x\n",r);
	}
	return;
}

/**
 * @brief custom_kws_register
 * 
*/
void custom_kws_register(void)
{
	customCmdRegister("kws",speech_recognition,"speech recognition demo code");
}


