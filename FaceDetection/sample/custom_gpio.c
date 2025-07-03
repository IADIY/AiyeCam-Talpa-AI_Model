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
 2.	IOA4 set to output and write value
	nb>gpiow 4 1
		GPIO set pin(IOA4) out val=1
	nb>gpiow 4 0
		GPIO set pin(IOA4) out val=0 

 3.	IOA4 set to input and read value
	nb>gpior 4GPIO get pin(IOA4) in val=1 

 4.	IOA4 pin toggle high/low to trigger ISR
	nb>gpioisr 4 1 4
		GPIO set pin(IOA4) int debounce=1, int_type=4
		gpio 4 callback:val(0) type(0x4)
		gpio_isr_callback(171)
		gpio 4 callback:val(1) type(0x4)
		gpio_isr_callback(171)
 */
/**************************************************************************
 *	Constants
 **************************************************************************/

/**************************************************************************
 *	External Function            
 **************************************************************************/
extern int gpio_pin_valid_check(int pin_no);
extern int gpio_get_int_type(int pin_no);
extern int gpio_get_int_type(int pin_no);
extern void gpio_set_int_type(int pin_no, GPIO_INT_TYPE_T inttype);

/**************************************************************************
 *	Function            
 **************************************************************************/
static void gpioCfg(char *cmd[], int arg);
static void gpioR(char *cmd[], int arg);
static void gpioW(char *cmd[], int arg);
static void gpioIsr(char *cmd[], int arg);
static int32_t getPinFromStr(char *pstr);
void custom_gpio_register(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/


static const char *io_string[] = {"IOA0","IOA1","IOA2","IOA3","IOA4","IOA5","IOA6","IOA7", \
		 "IOB0","IOB1","IOB2","IOB3","IOB4","IOB5","IOB6","IOB7", \
		 "IOC0","IOC1","IOC2","IOC3","IOC4","IOC5","IOC6", "XXXX"};

static int32_t getPinFromStr(char *pstr)
{
	uint32_t i=0;
	while(1){
		if (strcmp(pstr, io_string[i])==0) {
			return i;
		}
		else if (strcmp(io_string[i], "XXXX")==0) {
			return -1;
		}
		i++;
	}
}
		
static void
gpioCfg(
	char *cmd[],
	int arg
)
{
	int32_t pin = 0;
	int func, pull_on, strength;
	if( arg < 4 ){
		printf("input error => nb>gpiocfg pin_no func pull_on strength\n");
		return;
	}
	else{
		unsigned int val;
		pin = getPinFromStr(cmd[0]);
		if( -1 == pin ){
			pin = strtoul(cmd[0], NULL, 0);
		}
		if(0 != gpio_pin_valid_check(pin)){
			printf("pin_no = %ld error\n",pin);
			return;
		}
		val = sys_padshare_value_get(pin);
		func = strtoul(cmd[1], NULL, 0);
		if(func != -1){
			func = func & 0x07;
		}
		else{
			func = val & 0x07;
		}
		pull_on = strtoul(cmd[2], NULL, 0);
		if(pull_on != -1){
			pull_on &= 0x1;
		}
		else{
			pull_on = (val >> 3) & 0x1;
		}
		strength = strtoul(cmd[3], NULL, 0);
		if(strength != -1){
			strength &= 0x1;
		}
		else{
			strength = (val >> 4) & 0x1;
		}
		sys_set_padshare(pin, func, pull_on, strength);
		val = sys_padshare_value_get(pin);
		func = val & 0x07;
		pull_on = (val >> 3) & 0x1;
		strength = (val >> 4) & 0x1;
		printf("GPIO cfg pin(%s-%ld)func(%d)pull_on(%s)strength(%s)\n",io_string[pin], pin, func, pull_on ? "UP":"OFF", strength ? "ON" : "OFF");
	}
}

static void
gpioR(
	char *cmd[],
	int arg
)
{
	int32_t pin = 0;
	if( arg < 1 ){
		printf("input error => nb>gpior pin_no\n");
		return;
	}
	else{
		int func, pull_on, strength;
		unsigned int val;
		pin = getPinFromStr(cmd[0]);
		if( -1 == pin ){
			pin = strtoul(cmd[0], NULL, 0);
		}
		if(0 != gpio_pin_valid_check(pin)){
			printf("pin_no = %ld error\n",pin);
			return;
		}
		val = sys_padshare_value_get(pin);
		gpio_set_dir(pin, GPIO_INPUT_DIRECTION);
		if((val & 0x07) != PAD_FUNC5 ){
			func = PAD_FUNC5 & 0x07;       /* set to GPIO */
			pull_on = (val >> 3) & 0x1;
			strength = (val >> 4) & 0x1;
			sys_set_padshare(pin, func, pull_on, strength);	
		}
		printf("GPIO get pin(%s-%ld) in val=%d\n",io_string[pin],pin,gpio_get_value(pin));
	}
}

static void
gpioW(
	char *cmd[],
	int arg
)
{
	int32_t pin = 0;
	if( arg < 2 ){
		printf("input error => nb>gpiow pin_no value\n");
		return;
	}
	else{
		int func, pull_on, strength;
		unsigned int val, out;
		pin = getPinFromStr(cmd[0]);
		if( -1 == pin ){
			pin = strtoul(cmd[0], NULL, 0);
		}
		if(0 != gpio_pin_valid_check(pin)){
			printf("pin_no = %ld error\n",pin);
			return;
		}
		out = strtoul(cmd[1], NULL, 0);
		val = sys_padshare_value_get(pin);
		if((val & 0x07) != PAD_FUNC5 ){
			func = PAD_FUNC5 & 0x07;       /* set to GPIO */
			pull_on = (val >> 3) & 0x1;
			strength = (val >> 4) & 0x1;
			sys_set_padshare(pin, func, pull_on, strength);	
		}
		gpio_set_dir(pin, GPIO_OUTPUT_DIRECTION);
		gpio_set_value(pin, out);
		printf("GPIO set pin(%s-%ld) out val=%d\n",io_string[pin],pin,out);
	}
}

static void gpio_isr_callback(int gpio_no)
{
	int type;
	uint32_t value;
	type = gpio_get_int_type(gpio_no);
	value = gpio_get_value(gpio_no);
	printf("gpio %d callback:val(%lx) type(0x%x)\n",gpio_no,value,type);
	if ((type== GPIO_INT_HIGH_LEVEL) && (value!=0xffffffff) && value)
	{
		gpio_set_int_type(gpio_no,GPIO_INT_LOW_LEVEL);
		gpio_enable_int(gpio_no,0);
	}
	else if ((type== GPIO_INT_LOW_LEVEL) && (value==0))
	{
		gpio_set_int_type(gpio_no,GPIO_INT_HIGH_LEVEL);
		gpio_enable_int(gpio_no,0);
	}
	else{
		printf("%s(%d)\n",__func__,__LINE__);
	}
}

static void
gpioIsr(
	char *cmd[],
	int arg
)
{
	if( arg < 3 ){
		printf("input error => nb>gpioisr pin debounce int_type\n");
		return;
	}
	else{
		int func, pull_on, strength;
		int32_t pin = 0;
		uint32_t debounce = 0, int_type = 0;  
		/* IOA3/IOA4 confirmed */
		pin = getPinFromStr(cmd[0]);
		if( -1 == pin ){
			pin = strtoul(cmd[0], NULL, 0);
		}
		if (((int32_t)pin < (int32_t)IOA0) || (int32_t)pin > (int32_t)IOA7){
			printf("pin_no = %ld error, not support GPIO INT feature\n", pin);
			return;
		}
		uint32_t val = sys_padshare_value_get(pin);
		if((val & 0x07) != PAD_FUNC5 ){
			func = PAD_FUNC5 & 0x07;       /* set to GPIO */
			pull_on = (val >> 3) & 0x1;
			strength = (val >> 4) & 0x1;
			sys_set_padshare(pin, func, pull_on, strength);	
		}
		debounce = strtoul(cmd[1], NULL, 0);
		int_type = strtoul(cmd[2], NULL, 0);
		printf("GPIO set pin(%s-%ld) int debounce=%ld, int_type=%ld\n", \
			io_string[pin],pin,debounce,int_type);
		
		gpio_set_debounce_time(debounce);
		if(debounce>0){
			gpio_set_int_source(pin,int_type,1,gpio_isr_callback);
		}
		else{
			gpio_set_int_source(pin,int_type,0,gpio_isr_callback);
		}
		gpio_enable_int(pin,1);
	}
}

/**
 * @brief custom_gpio_register
 * 
*/
void custom_gpio_register(void)
{
	gpio_init();
	customCmdRegister("gpiocfg",gpioCfg,"gpio configure");
	customCmdRegister("gpior",gpioR,"gpio set to input & read input");
	customCmdRegister("gpiow",gpioW,"gpio set to output & write output value");
	customCmdRegister("gpioisr",gpioIsr,"gpio set to interrupt mode");
}


