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
 1. Enable custom_i2cslv_register() in cmdAppInit()
 2. Prepare a master I2C ( CA341A I2C module OK )
 3. Connect master I2C pin to NB1001's IOA3/IOA4 
 4. type command "i2cslv"
 		nb>i2cslv
 		i2c slave test
 		I2C using IOA3/IOA4
 5. Send Slave Addr=0x32 subaddr=0x2002c000 data=0x11223344 I2C to NB1001
 6. Master trigger I2C write to NB1001
 	nb>I2C slave transfer completed successfully. 

	NB1001 i2c slave received data :
	0x11  0x22  0x33  0x44  

	NB1001 i2c slave send ack data :
	0x44  0x6f  0x6e  0x65
 */
/**************************************************************************
 *	Constants
 **************************************************************************/
#define NB1001_I2C_SLAVE_ADDR  (0x32)
#define I2C_DATA_LENGTH        (4)  /* MAX is 256 */

/**************************************************************************
 *	External Function            
 **************************************************************************/

/**************************************************************************
 *	Function            
 **************************************************************************/
static void custom_i2c_slv(char *cmd[],int arg);
void custom_i2cslv_register(void);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/
uint8_t g_slave_rx_buff[I2C_DATA_LENGTH];
uint8_t g_slave_tx_buff[I2C_DATA_LENGTH] = {'D', 'o', 'n', 'e'};


static void i2c_slave_callback(i2c_slave_transfer_t *xfer, void *userData)
{
    callback_message_t *cb_msg = (callback_message_t *)userData;
    BaseType_t reschedule;

    switch (xfer->event)
    {
        /*  Transmit request */
        case I2C_SLAVE_TRANSMIT_EVENT:
            /*  Update information for transmit process */
            xfer->data = g_slave_tx_buff;
            xfer->data_size = I2C_DATA_LENGTH;
            break;

        /*  Receive request */
        case I2C_SLAVE_RECEIVE_EVENT:
            /*  Update information for received process */
            xfer->data = g_slave_rx_buff;
            xfer->data_size = I2C_DATA_LENGTH;
            break;

        /*  Transfer done */
        case I2C_SLAVE_COMPLETION_EVENT:
            cb_msg->async_status = xfer->completion_status;
            xSemaphoreGiveFromISR(cb_msg->sem, &reschedule);
            portYIELD_FROM_ISR(reschedule);
            break;

        default:
            break;
    }
}

/*
 * Task responsible for slave I2C communication.
 */
static void i2c_slave_task(void *pvParameters)
{
    i2c_slave_config_t slaveConfig;
    i2c_slave_handle_t g_s_handle;

    callback_message_t cb_msg = {0};

	sys_set_padshare(IOA3, PAD_FUNC1, PAD_PULL_UP, PAD_STRENGTH_DIS);
	sys_set_padshare(IOA4, PAD_FUNC1, PAD_PULL_UP, PAD_STRENGTH_DIS);
	printf("I2C using IOA3/IOA4\n");
	
    cb_msg.sem = xSemaphoreCreateBinary();
    if (cb_msg.sem == NULL)
    {
        printf("I2C slave: Error creating semaphore\r\n");
        vTaskSuspend(NULL);
    }

    /* Set up I2C slave */
    slaveConfig.slave_address = NB1001_I2C_SLAVE_ADDR;
	i2c_slave_init(&slaveConfig);

    for (uint32_t i = 0; i < I2C_DATA_LENGTH; i++)
    {
        g_slave_rx_buff[i] = 0;
    }

    memset(&g_s_handle, 0, sizeof(g_s_handle));

    i2c_slave_transfer_create_handle(&g_s_handle, i2c_slave_callback, &cb_msg);
    i2c_slave_transfer_non_blocking(&g_s_handle, I2C_SLAVE_COMPLETION_EVENT);

	while(1){
	    /* Wait for transfer to finish */
	    xSemaphoreTake(cb_msg.sem, portMAX_DELAY);

	    if (cb_msg.async_status == 0)
	    {
	        printf("I2C slave transfer completed successfully. \r\n\r\n");
	    }
	    else
	    {
	        printf("I2C slave transfer completed with error. \r\n\r\n");
	    }

	    printf("NB1001 i2c slave received data :");
	    for (uint32_t i = 0; i < I2C_DATA_LENGTH; i++)
	    {
	        if (i % 8 == 0)
	        {
	            printf("\n");
	        }
	        printf("0x%2x  ", g_slave_rx_buff[i]);
	    }
	    printf("\n\n");

	    printf("NB1001 i2c slave send ack data :");
	    for (uint32_t i = 0; i < I2C_DATA_LENGTH; i++)
	    {
	        if (i % 8 == 0)
	        {
	            printf("\n");
	        }
	        printf("0x%2x  ", g_slave_tx_buff[i]);
	    }
	    printf("\n\n");
	}
    printf("\r\nEnd of FreeRTOS I2C example.\r\n");

    vTaskSuspend(NULL);
}

static void
custom_i2c_slv(
	char *cmd[],
	int arg
)
{
    printf("i2c slave test\n");
    if (xTaskCreate(i2c_slave_task, "i2c_slave_task", configMINIMAL_STACK_SIZE + 60, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
    {
        printf("Failed to create i2c slave task\n");
    }
}


/**
 * @brief custom_i2cslv_register
 * 
*/
void custom_i2cslv_register(void)
{
	customCmdRegister("i2cslv",custom_i2c_slv,"i2c slave test");
}



