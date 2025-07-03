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
 1. Enable custom_spi_mst_register() in cmdAppInit()

 2. After system fw boot OK ( supposed spi flash default connect to QSPI ), 
    Connect SPI1 to QSPI pin as below ( SPI only 1 bit data bus )
    IOB7 <--> IOB1  //CS
    IOA0 <--> IOB2  //CLK
    IOA1 <--> IOB3  //MISO
    IOA2 <--> IOB4  //MOSI

 3. nb>spimstinit     //spi master initial                           
	ssp actual clock: 2500000                     
	RDID(8):                                     
	00: ef 40 14 00 00 84 00 20                  
	sr:0x0                                       
	name                     :WINBOND W25Q80DV   
	jedec_id                 :0x1440ef           
	nr_pages                 :4096               
	page_size                :256                
	erase_size               :4096               
	erase_cmd                :32                 
	write_quad_cmd           :50                 
	read_quad_cmd            :107                
	write_xstatus_cmd        :1                  
	read_xstatus_cmd         :53                 
	xstatus_write_enable_cmd :80                 
	quad_bit                 :1                  
	trans_type               :0                  
	dummy_cycles             :8                  
	flags                    :2                  
	flash_size               :1048576            
	flash_page_size          :256                
	flash_erase_size         :4096               
	pspi_flash_tbuf          :0x2001efd8-272     
	pspi_flash_rbuf          :0x2001f0f0-272 
	
4. nb>spisfw 0x40000 0x2002d000 4123    //spi write & readback to offset 0x40000 from 0x2002d000 with size=4123 bytes              
	srcBuf(64):                                         
	00: e4 fb 28 70 60 13 ff ad cf 54 12 41 10 61 ae 51 
	10: 27 a5 63 82 50 c0 67 fe 9d fb 94 56 a1 46 5d bd 
	20: 66 7f 61 d5 05 c0 3e a5 eb ff 18 22 29 19 f1 dd 
	30: 36 79 29 91 10 40 b4 8b ff e7 81 7a 08 38 e7 87 
	Erased Data(64):                                    
	00: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	10: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	20: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	30: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	srcBuf(128):                                        
	00: e4 fb 28 70 60 13 ff ad cf 54 12 41 10 61 ae 51 
	10: 27 a5 63 82 50 c0 67 fe 9d fb 94 56 a1 46 5d bd 
	20: 66 7f 61 d5 05 c0 3e a5 eb ff 18 22 29 19 f1 dd 
	30: 36 79 29 91 10 40 b4 8b ff e7 81 7a 08 38 e7 87 
	40: 5b d4 19 80 80 16 5c ce fd fc 08 c9 c6 01 6f 76 
	50: 5f fc 32 84 cb 40 83 b5 e9 6f 2c 04 1a 4a 3e d2 
	60: 77 8c 12 10 12 25 7e bb ff e2 6b c8 2b 43 2c 2c 
	70: c4 0f ab 31 40 89 5b 8a c9 ff 8d 08 63 66 dc a9 
	ReadBack Data(128):                                 
	00: e4 fb 28 70 60 13 ff ad cf 54 12 41 10 61 ae 51 
	10: 27 a5 63 82 50 c0 67 fe 9d fb 94 56 a1 46 5d bd 
	20: 66 7f 61 d5 05 c0 3e a5 eb ff 18 22 29 19 f1 dd 
	30: 36 79 29 91 10 40 b4 8b ff e7 81 7a 08 38 e7 87 
	40: 5b d4 19 80 80 16 5c ce fd fc 08 c9 c6 01 6f 76 
	50: 5f fc 32 84 cb 40 83 b5 e9 6f 2c 04 1a 4a 3e d2 
	60: 77 8c 12 10 12 25 7e bb ff e2 6b c8 2b 43 2c 2c 
	70: c4 0f ab 31 40 89 5b 8a c9 ff 8d 08 63 66 dc a9 
	ReadBack Data Compare to srcBuf => Same !           

 */
/**************************************************************************
 *	Constants
 **************************************************************************/
#define SPI_FREQ			   2500000    //25Mhz, Too fast will lost data
#define BUS_WIDTH			   8
#define SPI_MODE			   SPI_MODE_3
#define SPI_ISR			   1
#define SPI_POLL			   0

/* Erase commands */
#define CMD_ERASE_4K			0x20
#define CMD_ERASE_32K			0x52
#define CMD_ERASE_CHIP		0xc7
#define CMD_ERASE_64K			0xd8

/* Write commands */
#define CMD_WRITE_STATUS         0x01
#define CMD_WRITE_STATUS2        0x31
#define CMD_WRITE_ENABLE         0x06
#define CMD_QUAD_PAGE_PROGRAM	 0x32
#define CMD_WRITE_STATUS_ENABLE  0x50
#define CMD_PAGE_PROGRAM         0x02

/* Read commands */
#define CMD_READ_QUAD_OUTPUT_FAST	0x6b
#define CMD_READ_ID					0x9f
#define CMD_READ_ID_QUAD				0xaf
#define CMD_READ_STATUS				0x05
#define CMD_READ_STATUS2				0x35
#define CMD_FLAG_STATUS				0x70
#define CMD_READ_ARRAY_FAST			0x0b

#define SPI_FLASH_3B_ADDR_LEN		3
#define SPI_FLASH_CMD_LEN			(1 + SPI_FLASH_3B_ADDR_LEN)

/* Common status(SR) */
#define STATUS_WIP			(1<<0)
#define STATUS_QEB_WINSPAN	(1<<1)
#define STATUS_QEB_MXIC		(1<<6)
#define STATUS_PEC			(1<<7)
#define STATUS_QEB_MICRON	(1<<7)
#define SR_BP0					(1<<2)  /* Block protect 0 */
#define SR_BP1					(1<<3)  /* Block protect 1 */
#define SR_BP2					(1<<4)  /* Block protect 2 */

/* Flash timeout values */
#define SF_WRITE_ENABLE_TIMEOUT	(500)
#define SF_PROG_TIMEOUT			(3 * 1000)
#define SF_PAGE_ERASE_TIMEOUT	(3 * 1000)

//assume 1 byte cmd + 4 byte addr + 1 byte dummy(read)
#define FLASH_FIFO_MODE_MAX_SIZE_PER_BLOCK  (QSPI_FIFO_DEPTH-6)

#define FLASH_READ_BUF_SIZE 		(256)
#define SPI_BUF_SIZE            ROUND_UP(FLASH_READ_BUF_SIZE+8, 16)
#define min(a,b)            		(((a) < (b)) ? (a) : (b))

/**************************************************************************
 *	External Function            
 **************************************************************************/
extern void print_buffer( char* name, unsigned char* buf, int len );

/**************************************************************************
 *	Function            
 **************************************************************************/
void custom_spi_mst_register(void);
static void spi_mst_init(char *cmd[],int arg);
void custom_spi_mst_register(void);
static void spi_flash_sf_addr(uint32_t, uint8_t*);
static int spi_flash_read_id(uint8_t*);
static int spi_flash_read_sr(uint8_t*);
static int spi_flash_wait_ready(unsigned long);
static int spi_xfer_main(int,unsigned int,const void*, void*, unsigned long);
static int spi_flash_write_enable(void);
static int spi_flash_erase(uint32_t offset, uint32_t len);
static int spi_flash_read(uint32_t offset, uint32_t len, char* buf);
static int spi_flash_write(uint32_t offset, uint32_t len, char* buf);
static void spi_mst_sferase(char *cmd[],int arg);
static void spi_mst_sfw(char *cmd[],int arg);
static void spi_mst_sfr(char *cmd[],int arg);
static void spi_mst_sfer(char *cmd[],int arg);

/**************************************************************************
 *	Global Data                       
 **************************************************************************/
extern const struct flash_info dataflash_type[];
extern unsigned int dataflash_num;
static unsigned int flash_size = 0;
static unsigned int flash_page_size = 0;
static unsigned int flash_erase_size = 0;
static uint8_t *pspi_flash_tbuf = NULL;
static uint8_t *pspi_flash_rbuf = NULL;


static int spi_xfer_main(int mode,unsigned int bitlen,const void* dout, void* din, unsigned long flags)
{
    if (mode)
        return spi_xfer(bitlen,dout,din,flags);
    else
        return spi_polling_xfer(bitlen,dout,din,flags);
}

static void spi_flash_sf_addr(uint32_t addr, uint8_t* cmd)
{
	/* cmd[0] is actual command */
	cmd[1] = addr >> 16;
	cmd[2] = addr >> 8;
	cmd[3] = addr >> 0;
}

static int spi_flash_read_id(uint8_t* id)
{
	int ret;
	uint8_t cmd[8];
	uint8_t resp[8];
	cmd[0] = CMD_READ_ID;
	ret = spi_xfer_main(SPI_ISR, 6*8, cmd, resp, SPI_XFER_ONCE);
	memcpy(id,resp+1,5);
	return ret;
}

static int spi_flash_read_sr(uint8_t* rs)
{
	int ret;
	uint8_t cmd[8];
	uint8_t resp[8];
	cmd[0] = CMD_READ_STATUS;
	ret = spi_xfer_main(SPI_ISR,2*8,cmd, resp, SPI_XFER_ONCE);
	*rs = resp[1];
	return ret;
}

static int spi_flash_wait_ready(unsigned long timeout)
{
	int ret;
	uint8_t sr=0xff;

	do 
	{
		sr = 0xff;
		ret = spi_flash_read_sr(&sr);
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			return ret;
		}
		if ((!(sr & STATUS_WIP))){
			return 0;
		}
		if (timeout>0){
			timeout--;
		}
		if (timeout <=0){
			printf("%s(%d)err:%d\n",__func__,__LINE__,-pdFREERTOS_ERRNO_ETIMEDOUT);
			return -pdFREERTOS_ERRNO_ETIMEDOUT;
		}
		vTaskDelay( pdMS_TO_TICKS( 1 ) );
	} while (1);
	return -1;
}

static struct flash_info *rdid_probe(uint8_t *idcode)
{
	unsigned int tmp;
	struct flash_info *info;
	uint32_t jedec;

	jedec = idcode[0] | (idcode[1]<<8) | (idcode[2]<<16);
	for (tmp = 0, info = (struct flash_info *)dataflash_type;
			tmp < dataflash_num;
			tmp++, info++) 
	{
		if (info->jedec_id == jedec) 
		{
			return info;
		}
	}
	return NULL;
}

static int spi_flash_write_enable(void)
{
	int ret=0;
	uint8_t cmd[8];
	uint8_t rs = 0;
	int timeout = SF_WRITE_ENABLE_TIMEOUT;
	
	/*check if it's busy or not*/
	ret = spi_flash_wait_ready(500);
	if (ret){
		printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
		return ret;
	}

	/*issue write enable*/
	cmd[0] = CMD_WRITE_ENABLE;
	ret = spi_xfer_main(SPI_ISR,1*8,cmd, NULL,SPI_XFER_ONCE);
	if (ret){
		printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
		return ret;
	}
	
	/*wait wel*/
	timeout = SF_WRITE_ENABLE_TIMEOUT;
	do
	{
		ret = spi_flash_read_sr(&rs);
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}
		if (rs & 0x2)
			return 0;
		timeout--;
		if (timeout <= 0) 
		{
			printf("%s(%d)err:%d\n",__func__,__LINE__,-pdFREERTOS_ERRNO_ETIMEDOUT);
			return -pdFREERTOS_ERRNO_ETIMEDOUT;
		}
		vTaskDelay( pdMS_TO_TICKS( 1 ) );
	} while((~rs & 0x2));
	return ret;
}

static int spi_flash_erase(uint32_t offset, uint32_t len)
{
	uint8_t cmd[8];
	uint32_t erase_size,erase_addr;
	int ret = -1;
	unsigned long timeout = SF_PAGE_ERASE_TIMEOUT;
	uint8_t cmd_len;
	uint8_t rs;

	erase_size = flash_erase_size;
	
	if(len % erase_size) {/* Force to erase 1 erase size ~4096 */
		len = ROUND_UP(len, erase_size);
	}

	/* Consistency checking */
	if (offset + len > (uint32_t)flash_size) 
	{
		printf("ERROR: attempting erase past flash size (%#x)\n",flash_size);
		return 1;
	}
	if (offset % erase_size || len == 0) 
	{
		printf("SF: Erase offset/length not multiple of erase size offset/psf.erase_size/len = %ld/%ld/%ld\n", offset, erase_size, len);
		return -1;
	}

	cmd[0] = CMD_ERASE_4K;
	cmd_len = 1+3;
	
	while (len) 
	{
		erase_addr = offset;
		spi_flash_sf_addr(erase_addr, cmd);

		ret = spi_flash_write_enable();
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}

retry:		
		/*check if it's busy or not*/
		ret = spi_flash_wait_ready(500);
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}

		ret = spi_xfer_main(SPI_ISR,cmd_len*8, cmd,NULL,SPI_XFER_ONCE);
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}

		ret = spi_flash_wait_ready(timeout);
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}
		
		/*check erase cmd executed by flash or not
		if executed, wel should be clear
		*/
		rs =  0xff;
		ret = spi_flash_read_sr(&rs);
		if (!ret && (rs &2))
		{
			printf("retry erase\n\n\n");
			goto retry;
		}

		offset += erase_size;
		len -= erase_size;
	}
	return ret;
}

/**
 * @brief read spi flash
 *
 * read spi flash
 * 
 * @param[in] offset   start addr to read from 
 * @param[in] len      read size
 *  
 * @retval 0   success
 * @retval 1   fail
 * 
*/
static int spi_flash_read(uint32_t offset, uint32_t len, char* buf)
{
	uint8_t cmd[8];
	unsigned int addr;
	int ret=-1;
	size_t chunk_len=FLASH_READ_BUF_SIZE,actual;
	int cmd_len;

	/*check if it's busy or not*/
	ret = spi_flash_wait_ready(500);
	if (ret){
		printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
		return ret;
	}
	cmd[0] = CMD_READ_ARRAY_FAST;
	cmd_len = 1+3+1;/*one dummy*/

	for (actual = 0; actual < len; actual += chunk_len) 
	{
		addr = offset;
		chunk_len = min(len - actual, FLASH_READ_BUF_SIZE);
		if((chunk_len%2==0) &&( chunk_len>1)){
			chunk_len = chunk_len - 1; /* make it odd */
		}
		spi_flash_sf_addr(addr, cmd);
		memset((void *)pspi_flash_tbuf,0xff, SPI_BUF_SIZE);
		memcpy((void *)pspi_flash_tbuf, cmd, cmd_len);
		ret = spi_xfer_main(SPI_ISR,(cmd_len + chunk_len)*8, pspi_flash_tbuf, pspi_flash_rbuf, SPI_XFER_ONCE);
		memcpy((uint8_t*)buf + actual,pspi_flash_rbuf + cmd_len, chunk_len);
		if (ret)
		{
			printf("flash read read:%d\n",ret);
			print_buffer("tx",(unsigned char *)pspi_flash_tbuf,cmd_len+chunk_len);
			print_buffer("rx",(unsigned char *)pspi_flash_rbuf,cmd_len+chunk_len);
			break;
		}
		offset += chunk_len;
	}
	return ret;
}


/**
 * @brief write spi flash
 *
 * write spi flash
 * 
 * @param[in] offset  start addr to write
 * @param[in] len     write size
 *  
 * @retval 0   success
 * @retval 1   fail
 * 
 * @note   you should erase flash first before write
 * 
*/
static int spi_flash_write(uint32_t offset, uint32_t len, char* buf)
{
	uint8_t cmd[8];
	size_t chunk_len,actual;
	uint32_t write_addr;
	unsigned long byte_addr;
	int ret=-1;
	unsigned long timeout = SF_PAGE_ERASE_TIMEOUT;
	int cmd_len;
	
	cmd[0] = CMD_PAGE_PROGRAM;
	cmd_len = 1+3;

	for (actual = 0; actual < len; actual += chunk_len) 
	{
		write_addr = offset;
		byte_addr = offset % flash_page_size;
		chunk_len = min(len - actual,(size_t)(flash_page_size - byte_addr));

		spi_flash_sf_addr(write_addr, cmd);
		ret = spi_flash_write_enable();
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}
	
		/*check if it's busy or not*/
		ret = spi_flash_wait_ready(500);
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}

		memcpy(pspi_flash_tbuf,cmd,4);
		memcpy(pspi_flash_tbuf+4,(uint8_t*)buf + actual,chunk_len);
		ret = spi_xfer_main(SPI_ISR,(cmd_len+chunk_len)*8, pspi_flash_tbuf, pspi_flash_rbuf, SPI_XFER_ONCE);
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}

		ret = spi_flash_wait_ready(timeout);
		if (ret){
			printf("%s(%d)err:%d\n",__func__,__LINE__,ret);
			break;
		}
		offset += chunk_len;
	}
	return ret;
}

static void
spi_mst_sfer(
	char *cmd[],
	int arg
)
{
	if( arg < 2 ){
		printf("input error => nb>sfRead sector data_len\n");
		return;
	}
	else{
		uint32_t sector;
		uint32_t data_len;
		sector = strtoul(cmd[0], NULL, 0);
		data_len = strtoul(cmd[1], NULL, 0);
		uint32_t ret = spi_flash_erase(sector, data_len);
		if(ret!=0){
			printf("%s(%d) ret=%ld\n", __func__,__LINE__, ret);
		}
	}
}

static void
spi_mst_sfw(
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
		print_buffer((char *)"srcBuf",(unsigned char *)srcBuf, 64);
		pbuf = nb_malloc(data_len);
		int ret = spi_flash_erase(sector, data_len);
		if(ret!=0){
			printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
			goto spi_mst_sfw_exit;
		}
		else{
			ret = spi_flash_read(sector, data_len, (char *)pbuf);
			if(ret!=0){
				printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
				goto spi_mst_sfw_exit;
			}
			print_buffer("Erased Data",(unsigned char *)pbuf, 64);
			ret = spi_flash_write(sector, data_len, (char *)srcBuf);
			if(ret!=0){
				printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
				goto spi_mst_sfw_exit;
			}
			ret = spi_flash_read(sector, data_len, (char *)pbuf);
			if(ret!=0){
				printf("%s(%d) ret=%d\n", __func__,__LINE__, ret);
				goto spi_mst_sfw_exit;
			}
			print_buffer((char *)"srcBuf",(unsigned char *)srcBuf, 128);
			print_buffer("ReadBack Data",(unsigned char *)pbuf, 128);
			printf("ReadBack Data Compare to srcBuf =>");
			if (memcmp(pbuf,(char *)srcBuf,data_len)==0){
				printf(" Same !\n");
			}
			else{
				printf(" Not Same ! ret:%d\n", ret);
			}
		}
	}
spi_mst_sfw_exit:
	if(pbuf){
		nb_free(pbuf);
	}
}

static void
spi_mst_sfr(
	char *cmd[],
	int arg
)
{
	uint8_t *pbuf=NULL;
	if( arg < 2 ){
		printf("input error => nb>spisfr sector data_len\n");
		return;
	}
	else{
		uint32_t sector;
		uint32_t data_len;
		sector = strtoul(cmd[0], NULL, 0);
		data_len = strtoul(cmd[1], NULL, 0);
		pbuf = nb_malloc(data_len);
		uint32_t ret = spi_flash_read(sector, data_len, (char *)pbuf);
		if(ret!=0){
			printf("%s(%d) ret=%ld\n", __func__,__LINE__, ret);
			goto spi_mst_sfr_exit;
		}
		print_buffer("ReadBack Data", (unsigned char *)pbuf, data_len);

	}
spi_mst_sfr_exit:
	if(pbuf){
		nb_free(pbuf);
	}
}

static void
spi_mst_io(
	char *cmd[],
	int arg
)
{
	if( arg < 1 ){
		return;
	}
	else{
		uint32_t io;
		io = strtoul(cmd[0], NULL, 0);
		switch(io){
			case 0:
				/* Set QSPI pin to GPIO input & SPI pin to SPI */
				sys_set_padshare(IOB1, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOB2, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOB3, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOB4, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				gpio_set_dir(IOB1, GPIO_INPUT_DIRECTION);		
				gpio_set_dir(IOB2, GPIO_INPUT_DIRECTION);		
				gpio_set_dir(IOB3, GPIO_INPUT_DIRECTION);		
				gpio_set_dir(IOB4, GPIO_INPUT_DIRECTION);
				/* Set to SPI1 */
				sys_set_padshare(IOA0, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOA1, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOA2, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOB7, PAD_FUNC5, PAD_PULL_UP, PAD_STRENGTH_DIS);
				printf("Set QSPI pin to GPIO input & SPI pin to SPI\n");
				break;
			case 1:
				/* Set QSPI pin to GPIO input & SPI pin to SPI */
				sys_set_padshare(IOB7, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOA0, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOA1, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOA2, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				gpio_set_dir(IOB7, GPIO_INPUT_DIRECTION);		
				gpio_set_dir(IOA0, GPIO_INPUT_DIRECTION);		
				gpio_set_dir(IOA1, GPIO_INPUT_DIRECTION);		
				gpio_set_dir(IOA2, GPIO_INPUT_DIRECTION);
				/* Set to QSPI */
				sys_set_padshare(IOB1, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOB2, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOB3, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				sys_set_padshare(IOB4, PAD_FUNC0, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
				printf("Set QSPI pin to QSPI input & SPI pin to GPIO input\n");
				break;
			default:
				break;		
		}
	}
}

static void
spi_mst_init(
	char *cmd[],
	int arg
)
{
	if( arg < 0 ){
		return;
	}
	else{
		/* Set QSPI pin to GPIO input because we connect SPI & QSPI pin together */
		sys_set_padshare(IOB1, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
		sys_set_padshare(IOB2, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
		sys_set_padshare(IOB3, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
		sys_set_padshare(IOB4, PAD_FUNC5, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
		gpio_set_dir(IOB1, GPIO_INPUT_DIRECTION);		
		gpio_set_dir(IOB2, GPIO_INPUT_DIRECTION);		
		gpio_set_dir(IOB3, GPIO_INPUT_DIRECTION);		
		gpio_set_dir(IOB4, GPIO_INPUT_DIRECTION);		
		
		/* Set to SPI1 */
		sys_set_padshare(IOA0, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
		sys_set_padshare(IOA1, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
		sys_set_padshare(IOA2, PAD_FUNC1, PAD_PULL_NO_PULL, PAD_STRENGTH_DIS);
		sys_set_padshare(IOB7, PAD_FUNC5, PAD_PULL_UP, PAD_STRENGTH_DIS);
		
		int r = spi_init(SPI_MASTER, SPI_FREQ, SPI_FRAME_FORMAT_MOTORROLA, SPI_MODE, IOB7, BUS_WIDTH);
		if(r < 0){
			printf("%s(%d)ERROR:%d\n",__func__,__LINE__,r);
			return;
		}
		uint8_t idcode[8];
		spi_flash_read_id(idcode);
		print_buffer("RDID", (unsigned char *)idcode, 8 );
		
		uint8_t sr = 0xff;
		r = spi_flash_read_sr(&sr);
		if(r < 0){
			printf("%s(%d)ERROR:%d\n",__func__,__LINE__,r);
			return;
		}
		printf("sr:0x%x\n",sr);

		r = spi_flash_wait_ready(500);
		if(r < 0){
			printf("%s(%d)ERROR:%d\n",__func__,__LINE__,r);
			return;
		}
 		struct flash_info *pinfo = rdid_probe(idcode);
		if (pinfo==NULL)
		{
			printf("%s(%d)ERROR:%d\n",__func__,__LINE__,r);
			return;
		}
		
		printf("name                     :%s\n",pinfo->name);
		///JEDEC id has a high byte of zero plus three data bytes: the manufacturer id, then a two byte device id.
		printf("jedec_id                 :0x%lx\n",pinfo->jedec_id);
		/// total pages number
		printf("nr_pages                 :%ld\n",pinfo->nr_pages);
		/// each page size
		printf("page_size                :%d\n",pinfo->page_size);
		/// erase size: minmun size to erase when issue erase command
		printf("erase_size               :%d\n",pinfo->erase_size);
		/// erase command code
		printf("erase_cmd                :%d\n",pinfo->erase_cmd);
		/// quad mode program command code
		printf("write_quad_cmd           :%d\n",pinfo->write_quad_cmd);
		/// quad mode read command code
		printf("read_quad_cmd            :%d\n",pinfo->read_quad_cmd);
		/// write status command code
		printf("write_xstatus_cmd        :%d\n",pinfo->write_xstatus_cmd);
		/// read status command code
		printf("read_xstatus_cmd         :%d\n",pinfo->read_xstatus_cmd);
		/// status write enable command code
		printf("xstatus_write_enable_cmd :%d\n",pinfo->xstatus_write_enable_cmd);
		/// which bit in xstatus mean quad mode
		printf("quad_bit                 :%d\n",pinfo->quad_bit);
		/// trans mode when using QUAD mode
		printf("trans_type               :%d\n",pinfo->trans_type);
		/// quad read ,dummy cycle between write cmd/addr and read data
		printf("dummy_cycles             :%d\n",pinfo->dummy_cycles);
		/// flash configuration flags
		printf("flags                    :%ld\n",pinfo->flags);

		flash_size = pinfo->nr_pages * pinfo->page_size;
		printf("flash_size               :%d\n",flash_size);
		flash_page_size = pinfo->page_size;
		printf("flash_page_size          :%d\n",flash_page_size);
		flash_erase_size = pinfo->erase_size;
		printf("flash_erase_size         :%d\n",flash_erase_size);
			
		if(pspi_flash_tbuf != NULL){
			nb_free(pspi_flash_tbuf);
			pspi_flash_tbuf = NULL;
		}
		pspi_flash_tbuf = nb_malloc(SPI_BUF_SIZE);
		printf("pspi_flash_tbuf          :0x%lx-%ld\n",(uint32_t)pspi_flash_tbuf, SPI_BUF_SIZE);

		if(pspi_flash_rbuf != NULL){
			nb_free(pspi_flash_rbuf);
			pspi_flash_rbuf = NULL;
		}
		pspi_flash_rbuf = nb_malloc(SPI_BUF_SIZE);
		printf("pspi_flash_rbuf          :0x%lx-%ld\n",(uint32_t)pspi_flash_rbuf, SPI_BUF_SIZE);
	}
}
/**
 * @brief custom_gspi_register
 * 
*/
void custom_spi_mst_register(void)
{
	customCmdRegister("spimstinit",spi_mst_init,"initial spi master mode");
	customCmdRegister("spisfr",spi_mst_sfr,"spi mode to read spi flash");
	customCmdRegister("spisfw",spi_mst_sfw,"spi mode to write spi flash");
	customCmdRegister("spisfer",spi_mst_sfer,"spi mode to erase spi flash");
	customCmdRegister("spisfio",spi_mst_io,"Set spi flash pin to QSPI or SPI");
}



