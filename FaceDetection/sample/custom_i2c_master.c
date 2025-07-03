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
 1. Enable custom_i2cmst_register() in cmdAppInit()
 2. Prepare a slave I2C device
 3. Connect NB1001's IOA3/IOA4 to pin of slave I2C device  
 4. nb>i2cr 0x22 0x2002C000 4 4
		pbuf=2001a308
		i2c read slave(0x22)subAddr(0x2002c000)addrlen(4)datalen(4) 
		data:
		i2cr(4):
		00: 6f 00 40 17 
		OK
 4. nb>i2cw 0x22 0x2002C000 4 0x20000000 16
		I2C using IOA3/IOA4
		i2cw(16):
		00: 6f 00 40 17 6f 00 20 75 6f 00 00 40 6f 00 a0 74 
		i2c write slave(0x22)subAddr(0x2002c000)addrlen(4)buf(0x20000000)datalen(16) OK
		i2cw(16):
		00: 17 40 00 6f 75 20 00 6f 40 00 00 6f 74 a0 00 6f
 */
/**************************************************************************
 *	Constants
 **************************************************************************/
#define BUF_START  0x20000000

/**************************************************************************
 *	External Function            
 **************************************************************************/
extern void print_buffer( char* , unsigned char* , int );

/**************************************************************************
 *	Function            
 **************************************************************************/
static void i2cr(char *cmd[],int arg);
static void i2cw(char *cmd[],int arg);
void custom_i2cmst_register(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/
static uint32_t initialRun = 0;

static void
i2cr(
	char *cmd[],
	int arg
)
{
	uint32_t slave = 0, slavelen=1, subAddr, datalen=1;
	uint8_t *pbuf;
	if( arg < 3 ){
		printf("input error => nb>i2cr addr addr_len subaddr data_len\n");
		return;
	}
	else{
		if(initialRun==0){
			initialRun = 1;
			sys_set_padshare(IOC4, PAD_FUNC0, PAD_PULL_UP, PAD_STRENGTH_DIS);
			sys_set_padshare(IOC5, PAD_FUNC0, PAD_PULL_UP, PAD_STRENGTH_DIS);
			printf("I2C using IOA3/IOA4\n");
		}
		slave = strtoul(cmd[0], NULL, 0);
		subAddr = strtoul(cmd[1], NULL, 0);
		slavelen = strtoul(cmd[2], NULL, 0);
		datalen = strtoul(cmd[3], NULL, 0);
		pbuf = nb_malloc(ROUND_UP(datalen,16));
		printf("pbuf=%lx\n",(uint32_t)pbuf);
		printf("i2c read slave(0x%lx)subAddr(0x%lx)addrlen(%ld)datalen(%ld) ",slave,subAddr, slavelen, datalen);
		int ret = 0;
		if(datalen){
			ret = i2c_read(slave, subAddr, slavelen, pbuf, datalen);
		}
		if(ret<0){
			printf("FAIL=%d\n",ret);
		}
		else{
			printf("\ndata:\n");
			print_buffer("i2cr", pbuf, datalen);
			printf("OK\n");
		}
		nb_free(pbuf);
		pbuf=NULL;
	}
}

static void
i2cw(
	char *cmd[],
	int arg
)
{
	uint32_t slave = 0, slavelen=1, subAddr, buf=0, datalen=1;
	if( arg < 5 ){
		printf("input error => nb>i2cw addr subaddr addr_len data data_len\n");
		return;
	}
	else{
		if(initialRun==0){
			initialRun = 1;
			sys_set_padshare(IOC4, PAD_FUNC0, PAD_PULL_UP, PAD_STRENGTH_DIS);
			sys_set_padshare(IOC5, PAD_FUNC0, PAD_PULL_UP, PAD_STRENGTH_DIS);
			printf("I2C using IOA3/IOA4\n");
		}
		slave = strtoul(cmd[0], NULL, 0);
		subAddr = strtoul(cmd[1], NULL, 0);
		slavelen = strtoul(cmd[2], NULL, 0);
		buf = strtoul(cmd[3], NULL, 0);
		datalen = strtoul(cmd[4], NULL, 0);
		print_buffer("i2cw", (unsigned char* )buf, datalen);
		printf("i2c write slave(0x%lx)subAddr(0x%lx)addrlen(%ld)buf(0x%lx)datalen(%ld) ",slave,subAddr,slavelen,buf,datalen);
		int ret = 0;
		if(datalen){
			ret = i2c_write(slave, subAddr, slavelen, (uint8_t *)buf, datalen);
		}
		if(ret<0){
			printf("FAIL=%d\n",ret);
		}
		else{
			printf("OK\n");
			#if 1
			if(subAddr & BUF_START){
				print_buffer("i2cw", (unsigned char* )subAddr, datalen);
			}
			#endif
		}
	}
}
/**
 * @brief custom_i2cslv_register
 * 
*/
void custom_i2cmst_register(void)
{
	customCmdRegister("i2cr",i2cr,"i2c master read");
	customCmdRegister("i2cw",i2cw,"i2c master write");
}




