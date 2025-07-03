/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#include "nbsdk.h"

/**
 * @addtogroup flash
 * @{
*/

/*data flash type supported
*/
const struct flash_info dataflash_type[] = 
{
	{ "Micron N25Q256A",0x19ba20, 131072, 256, 4096,0x0,0x0,0x0,0x61,0x65,0x6,7,QSPI_TT_QUAD,10,QUAD_ENABLE_LOW_ACTIVE|CMD_USE_TRANS_MODE|WRITE_STATUS_WAIT_READY},  /* 32M */
	{ "GigaDevice GD25Q80C",0x1440c8, 4096, 256, 4096,0x0,0x0,0x0,0x01,0x35,0x50,1,QSPI_TT_STD,8,WRITE_STATUS_COMBINE},  /* 1M */
	{ "GigaDevice GD25Q16C",0x1540c8, 8192, 256, 4096,0x0,0x0,0x0,0x01,0x35,0x50,1,QSPI_TT_STD,8,WRITE_STATUS_COMBINE},  /* 2M */
	{ "GigaDevice GD25Q32C",0x1640c8, 16384, 256, 4096,0x0,0x0,0x0,0x31,0x35,0x50,1,QSPI_TT_STD,8,0},  /* 4M */
	{ "GigaDevice GD25Q64C",0x1740c8, 32768, 256, 4096,0x0,0x0,0x0,0x31,0x35,0x50,1,QSPI_TT_STD,8,0},  /* 8M */
	{ "WINBOND W25Q80DV",0x1440ef, 4096, 256, 4096,0x0,0x0,0x0,0x01,0x35,0x50,1,QSPI_TT_STD,8,WRITE_STATUS_COMBINE},  /* 1M */
	{ "WINBOND W25Q16JV",0x1540ef, 8192, 256, 4096,0x0,0x0,0x0,0x31,0x35,0x50,1,QSPI_TT_STD,8,0},  /* 2M */
	{ "WINBOND W25Q32JV",0x1640ef, 16384, 256, 4096,0x0,0x0,0x0,0x31,0x35,0x50,1,QSPI_TT_STD,8,0},  /* 4M */
	{ "WINBOND W25Q80DW",0x1460ef, 4096, 256, 4096,0x0,0x0,0x0,0x01,0x35,0x50,1,QSPI_TT_STD,8,WRITE_STATUS_COMBINE},  /* 1M */
	{ "WINBOND W25Q16DW",0x1560ef, 8192, 256, 4096,0x0,0x0,0x0,0x01,0x35,0x50,1,QSPI_TT_STD,8,WRITE_STATUS_COMBINE},  /* 2M */
	{ "WINBOND W25Q32JW",0x1660ef, 16384, 256, 4096,0x0,0x0,0x0,0x31,0x35,0x50,1,QSPI_TT_STD,8,0},  /* 4M */
	{ "ZB ZB25VQ16",0x15605e, 8192, 256, 4096,0x0,0x0,0x0,0x31,0x35,0x50,1,QSPI_TT_STD,8,0},  /*2M*/
	{ "ZB ZB25VQ64",0x17405e, 32768, 256, 4096,0x0,0x0,0x0,0x31,0x35,0x50,1,QSPI_TT_STD,8,0},  /*8M*/
	{ "XTX XT25F16B",0x15400b, 8192, 256, 4096,0x0,0x0,0x0,0x01,0x35,0x50,1,QSPI_TT_STD,8,WRITE_STATUS_COMBINE},  /*2M*/
};
unsigned int dataflash_num = sizeof(dataflash_type)/sizeof(struct flash_info);

/** @} */

