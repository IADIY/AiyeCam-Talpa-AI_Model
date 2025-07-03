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
 1. Enable custom_audio_detect_rec_play_register() in cmdAppInit()
 2. Make sure the dmic is ready on baord, EVB1.6 is U7, EVB1.7 is U11(SPH0641LM4H-1)
    If memory is not enough, please mark off winTaskInit(5000) and userTaskInit()

 3. nb>audio rec tf               	//record 5 second to spi flash
	custom_audio_dmic_gpio_init
	custom_audio_detect_init
	sample rate:8000 real:7812
	record_flash_off=0xffffffff
	record_len=5 Seconds
	audio_lib_sample_rate=8000
	SPI totalSize=1048576,erase=4096
	len=80000,aligned_len=81920
	erase 5 second cost:544 ms
	start record to flash

	nb>off:966656 size:16000
	write flash 1 second cost:627 ms
	off:982656 size:16000
	write flash 1 second cost:627 ms
	off:998656 size:16000
	write flash 1 second cost:627 ms
	off:1014656 size:16000
	write flash 1 second cost:627 ms
	off:1030656 size:16000
	write flash 1 second cost:627 ms
	record complete
	write flash 1 second cost:1 ms 
 
 4. nb>audio rec tm					//record 5 second to memory(sram)
	custom_audio_dmic_gpio_init
	custom_audio_detect_init
	sample rate:8000 real:7812
	record_len=5
	audio_lib_sample_rate=8000
	start record to mem

	nb>off:0 size:16000
	off:16000 size:16000
	off:32000 size:16000
	off:48000 size:16000
	off:64000 size:16000
	record complete
 
 5. nb>audio play ff				//playback the pre-saved audio in flash
	custom_audio_play_init
	record_flash_off=0xffffffff
	record_len=5 Seconds
	audio_lib_sample_rate=8000
	SPI totalSize=1048576,erase=4096
	len=80000,aligned_len=81920
	
 6. nb>audio play fm          		//playback the pre-saved audio in memory(sram), must "audio rec tm" first
 
 */
/**************************************************************************
 *	Constants
 **************************************************************************/
#define DEFAULT_SAMPLE_RATE       8000
#define DEFAULT_REC_LENGTH_BY_SEC 5     // 5 second
#define DEFAULT_VOLUME            3

#define ROUND_DOWN(val,div) ((uint32_t)(val) & -(uint32_t)(div))
#define ROUND_UP(val,div)   ROUND_DOWN( (uint32_t)(val) + (div) - 1, div)

/**************************************************************************
 *	External Function            
 **************************************************************************/

/**************************************************************************
 *	Function            
 **************************************************************************/
static void custom_audio_detect_exit(void);
void custom_audio_detect_rec_play_register(void);
static void usage(void);
static void custom_audio_play_init(void);
static void custom_audio_detect_init(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/
int audio_lib_sample_rate = DEFAULT_SAMPLE_RATE;
int record_len = DEFAULT_REC_LENGTH_BY_SEC;

/* record to flash */
int record_flash_flag = 0;
int record_flash_off = -1;  //must be aligned of flash erase size: generall 4k bytes
int record_aligned_len=0;
int record_flash_off_cur;

/* record to sram */
int record_mem_flag = 0;
int16_t *audio_buffer=NULL;
int audio_buffer_off = 0;

/* pwm hw initail */
static uint8_t play_pwn_initial = 0;
/* audio detection initail */
static uint8_t audio_detect_initial = 0;

static void usage(void)
{
    printf("audio rec tf    : record 5 second to flash\n");
    printf("audio rec tm    : record 5 second to sram\n");
    printf("audio play ff   : playback saved audio in flash\n");
    printf("audio play fm   : playback saved audio in memory\n");
}

static int custom_audio_detect_record(int16_t* buf,int samples)
{
    int r;
    //printf("detect\n");
    unsigned long long start,end;

    if (record_flash_flag)
    {
        start = perf_get_ticks();
        int flash_size = samples*2;
        if (flash_size + record_flash_off_cur > record_flash_off+record_len*audio_lib_sample_rate*2)
        {
            flash_size = record_flash_off+record_len*audio_lib_sample_rate*2 - record_flash_off_cur;
        }
        if (flash_size>0)
        {
            printf("off:%d size:%d\n",record_flash_off_cur,samples*2);
            r = sf_write(record_flash_off_cur,samples*2,(char*)buf);
            if (r)
            {
                printf("write flash fail\n");
                return 1;
            }
            record_flash_off_cur += samples*2;
        }
		else
        {
            record_flash_flag = 0;
			audio_detect_pause();
            printf("record complete\n");
        }
        end = perf_get_ticks();
        printf("write flash %d second cost:%d ms\n",1,(unsigned int)(end-start)/PERF_TIMER_MS_CNT);
    }

    if (record_mem_flag)
    {
        if (!audio_buffer)
        {
            audio_buffer = malloc(audio_lib_sample_rate*2*record_len);
            if (!audio_buffer)
            {
                printf("audio buffer alloc fail\n");
                return 1;
            }
            audio_buffer_off = 0;
        }
        int size = samples*2;
        if (audio_buffer_off + size > record_len*audio_lib_sample_rate*2)
        {
            size = record_len*audio_lib_sample_rate*2 - audio_buffer_off;
        }
        if (size>0)
        {
            printf("off:%d size:%d\n",audio_buffer_off,size);
            memcpy((char*)audio_buffer+audio_buffer_off,buf,size);
            audio_buffer_off += size;
        }
		else
        {
            record_mem_flag = 0;
			audio_detect_pause();
            printf("record complete\n");
        }
    }
    return 0;
}

static void custom_audio_dmic_gpio_init(void)
{
	printf("custom_audio_dmic_gpio_init\n");
	//EVB use IOC0/IOC1/IOC2 as I2S pin
	sys_set_padshare(IOC0, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //MIC_CLK
	sys_set_padshare(IOC1, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //MIC_LR
	sys_set_padshare(IOC2, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //MIC_DO
}

static void custom_audio_play_init(void)
{
	if(!play_pwn_initial)
	{
		printf("custom_audio_play_init\n");
		//EVB 1.7 need IOA4 set low to amplifier SD pin
		sys_set_padshare(IOA4, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //gpio
		gpio_set_value(IOA4,0);
		gpio_set_dir(IOA4, GPIO_OUTPUT_DIRECTION);
		//EVB 1.6/ EVB 1.7 use IOC6 as pwm output	
		sys_set_padshare(IOC6, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS); //pwm0
		//audio playback init
		int r = audio_play_init(DEV_PWM, IOC6); //IOC6
		if (r)
		{
			printf("audio_play_init fail\n");
			return;
		}
		audio_volume(DEFAULT_VOLUME);
		play_pwn_initial=1;
	}
}

static void custom_audio_play_exit(void)
{
	audio_play_exit();
	play_pwn_initial = 0;
}

static void custom_audio_detect_init(void)
{
	if(!audio_detect_initial)
	{		
		printf("custom_audio_detect_init\n");

		//audio detect/record init
		int r = audio_detect_init(DEV_CIC,audio_lib_sample_rate,audio_lib_sample_rate*2);
		if (r)
		{
			printf("audio detect init fail\n");
			return;
		}

		//set larger gain for dmic record
		if (audio_lib_sample_rate == 8000)
		{
			audio_detect_set_feature(AUDIO_DETECT_GAIN,4);
		}
		else
		{
			audio_detect_set_feature(AUDIO_DETECT_GAIN,3);
		}

		//set and enable detect
		audio_detect_set_feature(AUDIO_DETECT_FN, (int)custom_audio_detect_record);
		audio_detect_set_feature(AUDIO_DETECT_ENABLE, 1);
		
		//start detect
		r = audio_detect_start();
		if (r)
		{
			printf("audio detect start fail\n");
			return;
		}
		audio_detect_initial=1;
	}
}

static uint32_t custom_audio_record_to_flash_offset(void)
{
	printf("record_flash_off=0x%x\n",record_flash_off);
	printf("record_len=%d Seconds\n",record_len);
	printf("audio_lib_sample_rate=%d\n",audio_lib_sample_rate);

	struct flash_info *pspiinfo = flash_info_get();
	uint32_t totalSize = pspiinfo->nr_pages * pspiinfo->page_size;
	uint32_t erase_unit = pspiinfo->erase_size;
	printf("SPI totalSize=%ld,erase=%ld\n", totalSize, erase_unit);

	uint32_t len = record_len*audio_lib_sample_rate*2;
	uint32_t aligned_len = ROUND_UP(len, erase_unit);
	if( len > (totalSize/2))
	{
		printf("Warning !!! request size %ld > %ld/2\n", len, totalSize);
	}
	record_flash_off = ROUND_DOWN(totalSize - aligned_len, erase_unit); 		
	printf("len=%ld,aligned_len=%ld\n", len, aligned_len);
	return aligned_len;
}

static void custom_audio_detect_exit(void)
{
	audio_detect_exit();
	audio_detect_initial=0;
}

static void
audio_record(
	char *cmd[],
	int arg
)
{
	if( arg < 1 ){
	    printf("record error!\n");
		usage();
		return;
	}
	else{
		int r=0;	
		if(strcmp(cmd[0], "tf")==0) /* to flash */
		{
			custom_audio_dmic_gpio_init();
			custom_audio_detect_init();
			
			if(arg>=2)
			{
				record_len = strtoul(cmd[1], NULL, 0);
			}
			unsigned long long start,end;
			start = perf_get_ticks();
			if(record_flash_off == -1)
			{
			 	record_aligned_len = custom_audio_record_to_flash_offset();
			}
			printf("record_flash_off=%d record_aligned_len:%d\n",record_flash_off,record_aligned_len);
			r = sf_erase(record_flash_off,record_aligned_len);
			if (r)
			{
				printf("erase flash fail:%d\n",r);
				return;
			}
			record_flash_off_cur = record_flash_off;
			end = perf_get_ticks();
			printf("erase %d second cost:%d ms\n",record_len,(unsigned int)(end-start)/PERF_TIMER_MS_CNT);
			
			audio_detect_refresh_buffer();
			audio_detect_resume();
			record_flash_flag = 1;
			printf("start record to flash\n");
			return;
		}
		else if(strcmp(cmd[0], "tm")==0) /* to sram */
		{
			custom_audio_dmic_gpio_init();
			custom_audio_detect_init();
			
			if(arg>=2)
			{
				record_len = strtoul(cmd[1], NULL, 0);
			}
			printf("record_len=%d\n",record_len);
			printf("audio_lib_sample_rate=%d\n",audio_lib_sample_rate);
			
			audio_detect_refresh_buffer();
			audio_detect_resume();
			audio_buffer_off = 0;
			record_mem_flag = 1;
			printf("start record to mem\n");
			return;
		}
		else
		{
			usage();
		}
	}
}

static void
audio_playback(
	char *cmd[],
	int arg
)
{
	if( arg < 1 ){
	    printf("playback error!\n");
		usage();
		return;
	}
	else{
		int r=0;	
		if(strcmp(cmd[0], "ff")==0)  /* from flash */
		{
			custom_audio_play_init();

			if(record_flash_off == -1)
			{
				record_aligned_len = custom_audio_record_to_flash_offset();
			}

			printf("record_flash_off=%d audio_lib_sample_rate:%d\n",record_flash_off,audio_lib_sample_rate);
			r = audio_play_flash_pending(record_flash_off,record_len*audio_lib_sample_rate*2,AUDIO_FMT_PCM16,1,audio_lib_sample_rate);
			if (r)
			{
				printf("playback fail\n");
				return;
			}
			custom_audio_play_exit();			
			return;
		}
		else if(strcmp(cmd[0], "fm")==0) /* from sram */
		{
			if(audio_buffer == NULL)
			{
				printf("play from sram must rec first\n");
				return;
			}
			
			custom_audio_play_init();
			r = audio_play_buffer_pending((int8_t*)audio_buffer,record_len*audio_lib_sample_rate*2,AUDIO_FMT_PCM16,1,audio_lib_sample_rate);
			if (r)
			{
				printf("playback fail\n");
				return;
			}
			custom_audio_play_exit();			
			return;
		}
		else
		{
			usage();
		}
	}
}

static void
audio_operation(
	char *cmd[],
	int arg
)
{
	if( arg < 1 ){
	    printf("operation audio error!\n");
		usage();
		return;
	}
	if(strcmp(cmd[0], "rec")==0)
	{
		audio_record(&cmd[1], arg-1);
	}
	else if(strcmp(cmd[0], "play")==0)
	{
		audio_playback(&cmd[1], arg-1);
	}
	else
	{
		usage();
	}
}


/**
 * @brief custom_audio_detect_rec_play_register
 * 
*/
void custom_audio_detect_rec_play_register(void)
{
	customCmdRegister("audio",audio_operation,"audio detection record and playback flow");
}

