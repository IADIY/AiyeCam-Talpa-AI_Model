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
 1. Enable custom_gspi_register() in cmdAppInit()
 2.	flash(W25Q80DV) Read Unique ID 4Bh dummy dummy dummy dummy (UID63-UIDO)
	nb>gspicmd 0x4B 12
		Read Data -[ff]-[ff]-[ff]-[ff]-[dc]-[67]-[1c]-[b2]-[07]-[b9]-[40]-[2a]
		
 3. nb>sfw 0x30000 0x2002d000 0x1000
	srcBuf(64):
	00: a4 bb 28 70 60 13 ff ad cf 54 12 41 10 61 ae 59 
	10: 23 a7 67 82 50 c0 67 fe 9d bb 95 14 a7 47 5d bf 
	20: 66 7f 61 55 05 c0 3e a5 eb 7f 18 22 29 19 f1 dd 
	30: b6 79 29 91 10 40 b4 8b ff e7 89 7a 08 38 e7 a7 
	Sector Data(64):
	00: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	10: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	20: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	30: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	ReadBack Data(64):
	00: a4 bb 28 70 60 13 ff ad cf 54 12 41 10 61 ae 59 
	10: 23 a7 67 82 50 c0 67 fe 9d bb 95 14 a7 47 5d bf 
	20: 66 7f 61 55 05 c0 3e a5 eb 7f 18 22 29 19 f1 dd 
	30: b6 79 29 91 10 40 b4 8b ff e7 89 7a 08 38 e7 a7 
	Write Data Compare to srcBuf OK
	
 4. nb>sfr 0x30000 0x100
	ReadBack Data(256):
	00: a4 bb 28 70 60 13 ff ad cf 54 12 41 10 61 ae 59 
	10: 23 a7 67 82 50 c0 67 fe 9d bb 95 14 a7 47 5d bf 
	20: 66 7f 61 55 05 c0 3e a5 eb 7f 18 22 29 19 f1 dd 
	30: b6 79 29 91 10 40 b4 8b ff e7 89 7a 08 38 e7 a7 
	40: 5b de 09 c0 80 12 5c 8e fd fc 18 c9 c6 01 6f 76 
	50: 5f fc 32 84 cb 41 8b b5 e9 6f 0c 04 1a 4a 3e d2 
	60: 73 8c 32 10 12 25 6e b3 ff e2 63 48 2b 43 2e 2c 
	70: c4 0f aa 31 40 c9 59 8a c9 f7 8c 08 63 62 dc a9 
	80: df ad 08 00 c1 82 ad 48 cd f2 00 2d 26 52 d7 43 

 */
/**************************************************************************
 *	Constants
 **************************************************************************/

/**************************************************************************
 *	External Function            
 **************************************************************************/
extern void print_buffer( char* name, unsigned char* buf, int len );

/**************************************************************************
 *	Function            
 **************************************************************************/
static void sfcmdxfer(char *cmd[],int arg);
static void sfwrite(char *cmd[],int arg);
static void sfread(char *cmd[],int arg);
void custom_gspi_register(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/


		
static void
sfcmdxfer(
	char *cmd[],
	int arg
)
{
	if( arg < 2 ){
		printf("input error => nb>gspicmd cmd data_len\n");
		return;
	}
	else{
		uint8_t command;
		uint32_t data_len;
		command = strtoul(cmd[0], NULL, 0);
		data_len = strtoul(cmd[1], NULL, 0);
		uint8_t id[data_len];
		int ret = sf_cmd_xfer(&command, 1, id, data_len);
		if(ret!=0){
			printf("GSPI cmd=(0x%X) error(0x%x)\n", command, ret);
		}
		else{
			printf("GSPI cmd=(0x%X)\n", command);
			uint32_t i;
			printf("Read Data ");
			for(i=0;i<data_len;i++){
				printf("-[%02x]", id[i]);
			}
			printf("\n");
		}
	}
}

static void
sfwrite(
	char *cmd[],
	int arg
)
{
	uint8_t *pbuf=NULL;
	if( arg < 3 ){
		printf("input error => nb>sfwrite sector srcBuf data_len\n");
		return;
	}
	else{
		uint32_t sector, srcBuf;
		uint32_t data_len;
		sector = strtoul(cmd[0], NULL, 0);
		srcBuf = strtoul(cmd[1], NULL, 0);
		data_len = strtoul(cmd[2], NULL, 0);
		print_buffer("srcBuf",(unsigned char* )srcBuf, 64);
		pbuf = nb_malloc(data_len);
		int ret = sf_erase(sector, data_len);
		if(ret!=0){
			printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
			goto gspiWrite_exit;
		}
		else{
			ret = sf_read(sector, data_len, (char *)pbuf);
			if(ret!=0){
				printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
				goto gspiWrite_exit;
			}
			print_buffer("Sector Data",pbuf, 64);
			ret = sf_write(sector, data_len, (char *)srcBuf);
			if(ret!=0){
				printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
				goto gspiWrite_exit;
			}
			ret = sf_read(sector, data_len, (char *)pbuf);
			if(ret!=0){
				printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
				goto gspiWrite_exit;
			}
			print_buffer("ReadBack Data",pbuf, 64);
			if (memcmp(pbuf,(char *)srcBuf,data_len)==0){
				printf("Write Data Compare to srcBuf OK\n");
			}
			else{
				printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
			}
		}
	}
gspiWrite_exit:
	if(pbuf){
		nb_free(pbuf);
	}
}

static void
sfread(
	char *cmd[],
	int arg
)
{
	uint8_t *pbuf=NULL;
	if( arg < 2 ){
		printf("input error => nb>sfRead sector data_len\n");
		return;
	}
	else{
		uint32_t sector;
		uint32_t data_len;
		sector = strtoul(cmd[0], NULL, 0);
		data_len = strtoul(cmd[1], NULL, 0);
		pbuf = nb_malloc(data_len);
		uint32_t ret = sf_read(sector, data_len, (char *)pbuf);
		if(ret!=0){
			printf("%s(%d) ret=%ld\n", __func__,__LINE__, ret);
			goto gspiWrite_exit;
		}
		print_buffer("ReadBack Data",pbuf, data_len);
	}
gspiWrite_exit:
	if(pbuf){
		nb_free(pbuf);
	}
}
/**
 * @brief custom_gspi_register
 * 
*/
void custom_gspi_register(void)
{
	sf_init();
	customCmdRegister("gspicmd",sfcmdxfer,"send command to spi flash");
	customCmdRegister("sfw",sfwrite,"write to spi flash");
	customCmdRegister("sfr",sfread,"write to spi flash");
}


