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
 1. Enable custom_aes_register() in cmdAppInit()
 2.	nb>aes
	 test_len : 9328
	key(16):
	00: 4d d9 f5 04 78 3d 0d 82 a6 a9 92 20 13 ac 7f cc 
	vector(16):
	00: 2b d2 b9 3b 12 a5 70 2a d3 d3 1a d9 89 3e db 32 
	text_buf(64):
	00: 1a db 4e f7 46 fd 15 71 31 7c 73 48 0c f7 ba 4d 
	10: ed be 1a 59 dd fd f9 74 78 97 8b 26 0b 33 2c b8 
	20: 41 91 3e 40 8c 43 6c eb 9f 24 03 92 cc 0d 88 07 
	30: 3e 05 35 5e 0a 7e 99 d1 2c 7a 05 09 e7 ea 10 b0 
	encrypt buffer(64):
	00: 8b 3f 10 cc 0d d2 75 9d 22 a9 06 73 38 52 44 93 
	10: 13 d9 69 2e 72 3b d3 ce cc 8e a7 91 ac 6b 88 a1 
	20: 90 09 28 be 12 b7 b5 40 38 40 20 0d 1f b8 b0 db 
	30: 33 27 d0 4b d9 5f 26 c7 7e 20 c3 76 26 88 0f 47 
	decrypt buffer(64):
	00: 1a db 4e f7 46 fd 15 71 31 7c 73 48 0c f7 ba 4d 
	10: ed be 1a 59 dd fd f9 74 78 97 8b 26 0b 33 2c b8 
	20: 41 91 3e 40 8c 43 6c eb 9f 24 03 92 cc 0d 88 07 
	30: 3e 05 35 5e 0a 7e 99 d1 2c 7a 05 09 e7 ea 10 b0 

	 encrypt/decrypt data compare PASS
*/
/**************************************************************************
 *	Constants
 **************************************************************************/

/**************************************************************************
 *	External Function            
 **************************************************************************/
extern int compare_buffer(unsigned char*,unsigned char*,int);
extern void aes_enc_init_cbc(uint32_t* key,uint32_t* iv);
extern void aes_dec_init_cbc(uint32_t* key,uint32_t* iv);
extern int aes_encode_cbc(unsigned char*text_buf,unsigned char* enc_buf,int len);
extern int aes_decode_cbc(unsigned char*enc_buf,unsigned char* dec_buf,int len);
extern void aes_process_done(void);
extern void print_buffer( char* name, unsigned char* buf, int len );
extern void memdump(void *p, uint32_t size);

/**************************************************************************
 *	Function            
 **************************************************************************/
static void create_random_buffer(unsigned char* buf,int size);
void custom_aes_register(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/


/**
 * @brief generate random data array for test
 *
 * generate random data and store in buffer
 * 
 * @param[in] buf data buffer
 * @param[in] size length of data: bytes
 * 
*/
static void create_random_buffer(unsigned char* buf,int size)
{
    int i;
    for (i=0;i<size;i++)
        *(buf+i) = rand();
}

/**
 * @brief enc_dec_test
 *
 * do enc_dec_test
 * 
*/
static int aes_enc_dec_test(char *cmd[],int arg)
{
	uint8_t *text_buf;
	uint8_t *enc_buf;
	uint8_t *dec_buf;
	int ret=0;
	int test_len;
	uint32_t key[4];
	uint32_t iv[4];

	test_len = (unsigned int)rand() % 20000;

	if (test_len<16)
		test_len = 16;
	if (test_len % 16)
		test_len += 16-(test_len%16);

	printf("aes test_len : %d\n", test_len);
	text_buf = (uint8_t*)nb_malloc(test_len);
	enc_buf = (uint8_t*)nb_malloc(test_len);
	dec_buf = (uint8_t*)nb_malloc(test_len);

	/*generate random key and iv*/
	create_random_buffer((unsigned char*)&key[0],16);
	print_buffer("key", (unsigned char *)&key[0],16);
	create_random_buffer((unsigned char*)&iv[0],16);
	print_buffer("vector", (unsigned char *)&iv[0],16);

	if (text_buf && enc_buf && dec_buf)
	{
		memset(enc_buf,0,test_len);
		memset(dec_buf,0,test_len);
		create_random_buffer(text_buf,test_len);

		/*encode*/
		aes_enc_init_cbc(key,iv);
		ret = aes_encode_cbc(text_buf,enc_buf,test_len);
		if (ret){
			printf("aes encrypt fail:%d\n", ret);
		}
		else
		{
			aes_process_done();
			print_buffer("text_buf", text_buf,64);
			print_buffer("encrypt buffer", enc_buf,64);

			/*decode*/
			aes_dec_init_cbc(key,iv);
			ret = aes_decode_cbc(enc_buf,dec_buf,test_len);
			if (ret){
			    printf("aes decrypt fail:%d\n",ret);
			}
			else
			{
				print_buffer("decrypt buffer", dec_buf,64);
			    ret = compare_buffer(text_buf,dec_buf,test_len);
			    if (ret)
			    {
					printf("\naes encrypt/decrypt compare fail,ret=%d\n", ret);
					print_buffer("text_buf",text_buf,16);
					print_buffer("decrypt buffer",dec_buf,16);
			    }
				else{
					printf("\naes encrypt/decrypt data compare PASS\n");
				}
			}
		}
		aes_process_done();

		nb_free(text_buf);
		nb_free(enc_buf);
		nb_free(dec_buf);
	}
	else{
		ret = 1;
		printf("allocate test buffer fail\n");
		if (text_buf)
		    nb_free(text_buf);
		if (enc_buf)
		    nb_free(enc_buf);
		if (dec_buf)
		    nb_free(dec_buf);
	}
	return ret;
}

/**
 * @brief custom_aes_register
 *
 * Register enc_dec_test fncion to console command
 * 
*/
void custom_aes_register(void)
{
	customCmdRegister("aes",aes_enc_dec_test,"aes encrypt & decrypt");
}

