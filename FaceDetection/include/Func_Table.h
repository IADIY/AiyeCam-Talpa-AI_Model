//******************************************************************************
// Copyright (C) 2022 NeuronBasic Co., Ltd. All rights reserved.
//
// File        : Func_Table.h
// Author      : SP, DK
// Creat Date  : 2022-04-21
// Last Update : 2022-05-26
// Version     : V1.2.0
// Description : Function Table list.
// Note        : Table for release        
//******************************************************************************
// #include <Basic.h>

#define __at(_addr) __attribute__ ((at(_addr)))

#ifndef __REGISTER_TABLE_H__
#define __REGISTER_TABLE_H__
#ifdef __cplusplus
extern "C" {
#endif
/****** DO NOT WRITE ABOVE THIS LINE *******/

/******************************************************************************/
/*                          MACOROS DECLARATIONS                              */
/******************************************************************************/
//Some BIT values definition for the sake of convenience

#define    BIT00	0x00000001
#define    BIT01	0x00000002
#define    BIT02	0x00000004
#define    BIT03	0x00000008
#define    BIT04	0x00000010
#define    BIT05	0x00000020
#define    BIT06	0x00000040
#define    BIT07	0x00000080
#define    BIT08	0x00000100
#define    BIT09	0x00000200
#define    BIT10	0x00000400
#define    BIT11	0x00000800
#define    BIT12	0x00001000
#define    BIT13	0x00002000
#define    BIT14	0x00004000
#define    BIT15	0x00008000
#define    BIT16	0x00010000
#define    BIT17	0x00020000
#define    BIT18	0x00040000
#define    BIT19	0x00080000
#define    BIT20	0x00100000
#define    BIT21	0x00200000
#define    BIT22	0x00400000
#define    BIT23	0x00800000
#define    BIT24	0x01000000
#define    BIT25	0x02000000
#define    BIT26	0x04000000
#define    BIT27	0x08000000
#define    BIT28	0x10000000
#define    BIT29	0x20000000
#define    BIT30	0x40000000
#define    BIT31	0x80000000
/******************************************************************************/
/*                                    I2S                                     */
/******************************************************************************/
#define    I2S_BASE_ADDR                      (0x40010000)              
#define    I2S_CIC_EN_ADDR                    (I2S_BASE_ADDR + 0x240)    
#define    I2S_DMA_LR_SEL_ADDR                (I2S_BASE_ADDR + 0x24C)   

// const u_int32_t I2S_REG[] __attribute__ ((at(0x20000100))) ={I2S_BASE_ADDR, I2S_CIC_EN_ADDR, I2S_DMA_LR_SEL_ADDR};
/******************************************************************************/
/*                                    PWM                                     */
/******************************************************************************/
#define    PWM_0_BASE_ADDR                    (0x40040000)
#define    PWM_0_STATUS_ADDR                  (PWM_0_BASE_ADDR + 0x4)    
#define    PWM_0_INT_ADDR                     (PWM_0_BASE_ADDR + 0x8)   
#define    PWM_0_SAMPLE_ADDR                  (PWM_0_BASE_ADDR + 0xC)    
#define    PWM_0_PERIOD_ADDR                  (PWM_0_BASE_ADDR + 0x10)   

#define    PWM_1_BASE_ADDR                    (0x40040100)
#define    PWM_1_STATUS_ADDR                  (PWM_1_BASE_ADDR + 0x4)
#define    PWM_1_INT_ADDR                     (PWM_1_BASE_ADDR + 0x8)
#define    PWM_1_SAMPLE_ADDR                  (PWM_1_BASE_ADDR + 0xC)
#define    PWM_1_PERIOD_ADDR                  (PWM_1_BASE_ADDR + 0x10)

#define    PWM_2_BASE_ADDR                    (0x40040200)
#define    PWM_2_STATUS_ADDR                  (PWM_2_BASE_ADDR + 0x4)
#define    PWM_2_INT_ADDR                     (PWM_2_BASE_ADDR + 0x8)
#define    PWM_2_SAMPLE_ADDR                  (PWM_2_BASE_ADDR + 0xC)
#define    PWM_2_PERIOD_ADDR                  (PWM_2_BASE_ADDR + 0x10)

#define    PWM_3_BASE_ADDR                    (0x40040300)
#define    PWM_3_STATUS_ADDR                  (PWM_3_BASE_ADDR + 0x4)
#define    PWM_3_INT_ADDR                     (PWM_3_BASE_ADDR + 0x8)
#define    PWM_3_SAMPLE_ADDR                  (PWM_3_BASE_ADDR + 0xC)
#define    PWM_3_PERIOD_ADDR                  (PWM_3_BASE_ADDR + 0x10)

#define    PWM_4_BASE_ADDR                    (0x40040400)
#define    PWM_4_STATUS_ADDR                  (PWM_4_BASE_ADDR + 0x4)
#define    PWM_4_INT_ADDR                     (PWM_4_BASE_ADDR + 0x8)
#define    PWM_4_SAMPLE_ADDR                  (PWM_4_BASE_ADDR + 0xC)
#define    PWM_4_PERIOD_ADDR                  (PWM_4_BASE_ADDR + 0x10)

#define    PWM_5_BASE_ADDR                    (0x40040500)
#define    PWM_5_STATUS_ADDR                  (PWM_5_BASE_ADDR + 0x4)
#define    PWM_5_INT_ADDR                     (PWM_5_BASE_ADDR + 0x8)
#define    PWM_5_SAMPLE_ADDR                  (PWM_5_BASE_ADDR + 0xC)
#define    PWM_5_PERIOD_ADDR                  (PWM_5_BASE_ADDR + 0x10)

#define    PWM_6_BASE_ADDR                    (0x40040600)
#define    PWM_6_STATUS_ADDR                  (PWM_6_BASE_ADDR + 0x4)
#define    PWM_6_INT_ADDR                     (PWM_6_BASE_ADDR + 0x8)
#define    PWM_6_SAMPLE_ADDR                  (PWM_6_BASE_ADDR + 0xC)
#define    PWM_6_PERIOD_ADDR                  (PWM_6_BASE_ADDR + 0x10)

#define    PWM_7_BASE_ADDR                    (0x40040700)
#define    PWM_7_STATUS_ADDR                  (PWM_7_BASE_ADDR + 0x4)
#define    PWM_7_INT_ADDR                     (PWM_7_BASE_ADDR + 0x8)
#define    PWM_7_SAMPLE_ADDR                  (PWM_7_BASE_ADDR + 0xC)
#define    PWM_7_PERIOD_ADDR                  (PWM_7_BASE_ADDR + 0x10)

/******************************************************************************/
/*                                    SPI                                     */
/******************************************************************************/
#define    SPI_BASE_ADDR                      (0x40070000)                      
#define    SPI_SYNC_ADDR                      (SPI_BASE_ADDR + 0x4)             
#define    SPI_FRAME_ADDR                     (SPI_BASE_ADDR + 0x8)             
#define    SPI_IMAGE_FORMAT_ADDR              (SPI_BASE_ADDR + 0xC)            
#define    SPI_DELAY_1_ADDR                   (SPI_BASE_ADDR + 0x10)           
#define    SPI_DELAY_2_ADDR                   (SPI_BASE_ADDR + 0x14)            

/******************************************************************************/
/*                                ISP-BinSkip                                 */
/******************************************************************************/
#define    ISP_BINSKIP_BASE_ADDR              (0x40090000)                      
#define    ISP_CROP_SIZE_ADDR                 (ISP_BINSKIP_BASE_ADDR + 0x4)     
#define    ISP_BINSKIP_SIZE_ADDR              (ISP_BINSKIP_BASE_ADDR + 0x8)    
#define    ISP_BINSKIP_MODE_ADDR              (ISP_BINSKIP_BASE_ADDR + 0xC)     
#define    ISP_CROP_EN_ADDR                   (ISP_BINSKIP_BASE_ADDR + 0x10)   
#define    ISP_BINSKIP_START_ADDR             (ISP_BINSKIP_BASE_ADDR + 0x14)  
#define    ISP_BINSKIP_END_ADDR               (ISP_BINSKIP_BASE_ADDR + 0x18)    
#define    ISP_BINSKIP_SKIP_H_ADDR            (ISP_BINSKIP_BASE_ADDR + 0x20)   
#define    ISP_BINSKIP_SKIP_V_ADDR            (ISP_BINSKIP_BASE_ADDR + 0x24) 

/******************************************************************************/
/*                                 ISP-Motion                                 */
/******************************************************************************/
#define    ISP_MOTION_BASE_ADDR               (0x40090800)                      
#define    ISP_MOTION_SIZE_ADDR               (ISP_MOTION_BASE_ADDR + 0x4)      
#define    ISP_MOTION_FIX_START_ADDR          (ISP_MOTION_BASE_ADDR + 0x8)      
#define    ISP_MOTION_FIX_END_ADDR            (ISP_MOTION_BASE_ADDR + 0xC)      
#define    ISP_MOTION_FREE_START_0_ADDR       (ISP_MOTION_BASE_ADDR + 0x10)     
#define    ISP_MOTION_FREE_END_0_ADDR         (ISP_MOTION_BASE_ADDR + 0x14)     
#define    ISP_MOTION_FREE_START_1_ADDR       (ISP_MOTION_BASE_ADDR + 0x18)     
#define    ISP_MOTION_FREE_END_1_ADDR         (ISP_MOTION_BASE_ADDR + 0x1C)
#define    ISP_MOTION_FREE_START_2_ADDR       (ISP_MOTION_BASE_ADDR + 0x20)     
#define    ISP_MOTION_FREE_END_2_ADDR         (ISP_MOTION_BASE_ADDR + 0x24)
#define    ISP_MOTION_FREE_START_3_ADDR       (ISP_MOTION_BASE_ADDR + 0x28)     
#define    ISP_MOTION_FREE_END_3_ADDR         (ISP_MOTION_BASE_ADDR + 0x2C)
#define    ISP_MOTION_FREE_START_4_ADDR       (ISP_MOTION_BASE_ADDR + 0x30)     
#define    ISP_MOTION_FREE_END_4_ADDR         (ISP_MOTION_BASE_ADDR + 0x34)
#define    ISP_MOTION_FREE_START_5_ADDR       (ISP_MOTION_BASE_ADDR + 0x38)     
#define    ISP_MOTION_FREE_END_5_ADDR         (ISP_MOTION_BASE_ADDR + 0x3C)
#define    ISP_MOTION_FREE_START_6_ADDR       (ISP_MOTION_BASE_ADDR + 0x40)     
#define    ISP_MOTION_FREE_END_6_ADDR         (ISP_MOTION_BASE_ADDR + 0x44)
#define    ISP_MOTION_FREE_START_7_ADDR       (ISP_MOTION_BASE_ADDR + 0x48)     
#define    ISP_MOTION_FREE_END_7_ADDR         (ISP_MOTION_BASE_ADDR + 0x4C)

#define    ISP_MOTION_FREE_CMP_ADDR           (ISP_MOTION_BASE_ADDR + 0x50)   
#define    ISP_MOTION_FREE_CMP_RATIO_ADDR     (ISP_MOTION_BASE_ADDR + 0x54)   
#define    ISP_MOTION_FIX_CMP_ADDR            (ISP_MOTION_BASE_ADDR + 0x58)   
#define    ISP_MOTION_FIX_CMP_RATIO_ADDR      (ISP_MOTION_BASE_ADDR + 0x5C)   
#define    ISP_MOTION_GLOBAL_CMP_ADDR         (ISP_MOTION_BASE_ADDR + 0x60)   
#define    ISP_MOTION_GLOBAL_CMP_RATIO_ADDR   (ISP_MOTION_BASE_ADDR + 0x64)   

#define    ISP_MOTION_AREA_MODE_ADDR          (ISP_MOTION_BASE_ADDR + 0x68)    
#define    ISP_MOTION_CPU_MODE_ADDR           (ISP_MOTION_BASE_ADDR + 0x6C)    
#define    ISP_MOTION_MODE_EN_ADDR            (ISP_MOTION_BASE_ADDR + 0x70)    
#define    ISP_MOTION_FIX_BIN_SIZE_ADDR       (ISP_MOTION_BASE_ADDR + 0x74)    
#define    ISP_MOTION_MODE_CMP_ADDR           (ISP_MOTION_BASE_ADDR + 0x78)    

#define    ISP_MOTION_FREE_MAX_FRAME_ADDR     (ISP_MOTION_BASE_ADDR + 0x7C)    

#define    ISP_MOTION_LOCAL_CMP_RANGLE       (ISP_MOTION_BASE_ADDR + 0x80)    
#define    ISP_MOTION_GLOBAL_CMP_RANGLE      (ISP_MOTION_BASE_ADDR + 0x84)    

#define    ISP_MOTION_FIX_BIN_BELOW_RANGEL    (ISP_MOTION_BASE_ADDR + 0x8C)   
#define    ISP_MOTION_FIX_BIN_ABOVE_RANGEL    (ISP_MOTION_BASE_ADDR + 0x90)   
#define    ISP_MOTION_FIX_BIN_BELOW_TOTAL     (ISP_MOTION_BASE_ADDR + 0x94)   

#define    ISP_MOTION_FIX_DETECT_WIDTH        (ISP_MOTION_BASE_ADDR + 0x98)   
#define    ISP_MOTION_FIX_DETECT_HEIGHT       (ISP_MOTION_BASE_ADDR + 0x9C)   

#define    ISP_MOTION_DETECT_FLAG_INT_EN      (ISP_MOTION_BASE_ADDR + 0xA0)   
#define    ISP_MOTION_DETECT_FLAG_INT_CL      (ISP_MOTION_BASE_ADDR + 0xA4)   
#define    ISP_MOTION_UNDETECT_FLAG_INT_CL    (ISP_MOTION_BASE_ADDR + 0xA8)   
#define    ISP_MOTION_MEM_W_INT_CL            (ISP_MOTION_BASE_ADDR + 0xAC)   
#define    ISP_MOTION_FINISH_INT_CL           (ISP_MOTION_BASE_ADDR + 0xB0)   

#define    ISP_MOTION_MAX_FRMAE_LIMIT         (ISP_MOTION_BASE_ADDR + 0xC0)   
#define    ISP_MOTION_UNDETECT_INT_MAX        (ISP_MOTION_BASE_ADDR + 0xC4)   
#define    ISP_MOTION_DETECT_INT_MAX          (ISP_MOTION_BASE_ADDR + 0xC8)   

#define    ISP_MOTION_AUTO_BIN                (ISP_MOTION_BASE_ADDR + 0xCC)   

#define    ISP_FIX_SUBBLOCK_WIDTH             (ISP_MOTION_BASE_ADDR + 0xD0)   
#define    ISP_FIX_SUBBLOCK_HEIGHT            (ISP_MOTION_BASE_ADDR + 0xD4)   
#define    ISP_FIX_SUBBLOCK_DELTA_WIDTH_LR    (ISP_MOTION_BASE_ADDR + 0xD8)   
#define    ISP_FIX_SUBBLOCK_DELTA_WIDTH_OTHER (ISP_MOTION_BASE_ADDR + 0xDC)   

#define    ISP_FIX_DETECT_DELTA_RANGE         (ISP_MOTION_BASE_ADDR + 0xF0)   

#define    ISP_MOTION_FIX_BIN_STATS_CF        (ISP_MOTION_BASE_ADDR + 0xF4)   
#define    ISP_MOTION_FIX_BIN_STATS_HL        (ISP_MOTION_BASE_ADDR + 0xF8)   

#define    ISP_MOTION_FIX_BIN_SELECT_OUTPUT   (ISP_MOTION_BASE_ADDR + 0xFC)   


/******************************************************************************/
/*                                 ISP-Scaler                                 */
/******************************************************************************/
#define    ISP_SCALER_BASE_ADDR               (0x40091000)                     
#define    ISP_SCALER_SIZE_ADDR               (ISP_SCALER_BASE_ADDR + 0x4)     
#define    ISP_SCALER_FACTOR_0                (ISP_SCALER_BASE_ADDR + 0x8)     
#define    ISP_SCALER_H_CROP_INDEX_0          (ISP_SCALER_BASE_ADDR + 0xC)     
#define    ISP_SCALER_V_CROP_INDEX_0          (ISP_SCALER_BASE_ADDR + 0x10)    
#define    ISP_SCALER_FACTOR_1                (ISP_SCALER_BASE_ADDR + 0x14)    
#define    ISP_SCALER_H_CROP_INDEX_1          (ISP_SCALER_BASE_ADDR + 0x18)    
#define    ISP_SCALER_V_CROP_INDEX_1          (ISP_SCALER_BASE_ADDR + 0x1C)    
#define    ISP_SCALER_FACTOR_2                (ISP_SCALER_BASE_ADDR + 0x20)    
#define    ISP_SCALER_H_CROP_INDEX_2          (ISP_SCALER_BASE_ADDR + 0x24)    
#define    ISP_SCALER_V_CROP_INDEX_2          (ISP_SCALER_BASE_ADDR + 0x28)    
#define    ISP_SCALER_FACTOR_3                (ISP_SCALER_BASE_ADDR + 0x2C)    
#define    ISP_SCALER_H_CROP_INDEX_3          (ISP_SCALER_BASE_ADDR + 0x30)    
#define    ISP_SCALER_V_CROP_INDEX_3          (ISP_SCALER_BASE_ADDR + 0x34)    
#define    ISP_SCALER_FACTOR_4                (ISP_SCALER_BASE_ADDR + 0x38)    
#define    ISP_SCALER_H_CROP_INDEX_4          (ISP_SCALER_BASE_ADDR + 0x3C)    
#define    ISP_SCALER_V_CROP_INDEX_4          (ISP_SCALER_BASE_ADDR + 0x40)    

#define    ISP_SCALER_SP_DISABLE_ADDR         (ISP_SCALER_BASE_ADDR + 0x44)    
#define    ISP_SCALER_STORE_POSITION_ADDR     (ISP_SCALER_BASE_ADDR + 0x48)    

#define    ISP_SCALER_FINISH_INT_EN_ADDR      (ISP_SCALER_BASE_ADDR + 0x4C)    
#define    ISP_SCALER_FINISH_INT_CL_ADDR      (ISP_SCALER_BASE_ADDR + 0x50)    

#define    ISP_SCALER_FINISH_INT_STATUS_ADDR  (ISP_SCALER_BASE_ADDR + 0x80)    

/******************************************************************************/
/*                                   ISP-FE                                   */
/******************************************************************************/
#define    ISP_FE_BASE_ADDR                   (0x40091800)
#define    ISP_FE_MODE_ADDR                   (ISP_FE_BASE_ADDR + 0x4)         
#define    ISP_FE_SIZE_ADDR                   (ISP_FE_BASE_ADDR + 0x8)         
#define    ISP_FE_WIDTH_ADDR                  (ISP_FE_BASE_ADDR + 0xC)         
#define    ISP_FE_HOG_MAG_ADDR                (ISP_FE_BASE_ADDR + 0x10)        
#define    ISP_FE_HOG_DBZ_ADDR                (ISP_FE_BASE_ADDR + 0x14)        
#define    ISP_FE_HOG_BG_EN_ADDR              (ISP_FE_BASE_ADDR + 0x18)        
#define    ISP_FE_BG_VAL_ADDR                 (ISP_FE_BASE_ADDR + 0x1C)        
#define    ISP_FE_QUARTER_0_ADDR              (ISP_FE_BASE_ADDR + 0x50)        
#define    ISP_FE_QUARTER_1_ADDR              (ISP_FE_BASE_ADDR + 0x54)        
#define    ISP_FE_QUARTER_2_ADDR              (ISP_FE_BASE_ADDR + 0x58)        
#define    ISP_FE_QUARTER_3_ADDR              (ISP_FE_BASE_ADDR + 0x5C)        
#define    ISP_FE_QUARTER_4_ADDR              (ISP_FE_BASE_ADDR + 0x60)        
#define    ISP_FE_IN_MANUAL_0_ADDR            (ISP_FE_BASE_ADDR + 0x6C)        
#define    ISP_FE_IN_MANUAL_1_ADDR            (ISP_FE_BASE_ADDR + 0x70)        
#define    ISP_FE_IN_MANUAL_2_ADDR            (ISP_FE_BASE_ADDR + 0x74)        
#define    ISP_FE_IN_MANUAL_3_ADDR            (ISP_FE_BASE_ADDR + 0x78)        
#define    ISP_FE_IN_MANUAL_4_ADDR            (ISP_FE_BASE_ADDR + 0x7C)        
#define    ISP_FE_IN_REMOVE_ADDR              (ISP_FE_BASE_ADDR + 0xa0)        
#define    ISP_FE_ELL_YX_0_ADDR               (ISP_FE_BASE_ADDR + 0xa4)        
#define    ISP_FE_ELL_YX_1_ADDR               (ISP_FE_BASE_ADDR + 0xa8)        
#define    ISP_FE_ELL_YX_2_ADDR               (ISP_FE_BASE_ADDR + 0xac)        
#define    ISP_FE_ELL_YX_3_ADDR               (ISP_FE_BASE_ADDR + 0xb0)        
#define    ISP_FE_ELL_YX_4_ADDR               (ISP_FE_BASE_ADDR + 0xb4)        
#define    ISP_FE_ROUND_VAL_0_ADDR            (ISP_FE_BASE_ADDR + 0xb8)        
#define    ISP_FE_ROUND_VAL_1_ADDR            (ISP_FE_BASE_ADDR + 0xbc)        
#define    ISP_FE_ROUND_VAL_2_ADDR            (ISP_FE_BASE_ADDR + 0xc0)        
#define    ISP_FE_ROUND_VAL_3_ADDR            (ISP_FE_BASE_ADDR + 0xc4)        
#define    ISP_FE_ROUND_VAL_4_ADDR            (ISP_FE_BASE_ADDR + 0xc8)        
#define    ISP_FE_EDGE_ADDR                   (ISP_FE_BASE_ADDR + 0xcc)        
#define    ISP_FE_MANUAL_ADDR                 (ISP_FE_BASE_ADDR + 0xd0)        
#define    ISP_FE_STORE_ADDR                  (ISP_FE_BASE_ADDR + 0xd4)        

#define    ISP_FE_BUFFER_GOT_ADDR             (ISP_FE_BASE_ADDR + 0x80)        
#define    ISP_FE_BUFFER_MISS_ADDR            (ISP_FE_BASE_ADDR + 0x84)        
#define    ISP_FE_AHB_ADDR                    (ISP_FE_BASE_ADDR + 0x88)        
#define    ISP_FE_BUFFER_STA_ADDR             (ISP_FE_BASE_ADDR + 0x90)        
#define    ISP_FE_IN_ACTUAL_0_ADDR            (ISP_FE_BASE_ADDR + 0x200)       
#define    ISP_FE_IN_ACTUAL_1_ADDR            (ISP_FE_BASE_ADDR + 0x204)       
#define    ISP_FE_IN_ACTUAL_2_ADDR            (ISP_FE_BASE_ADDR + 0x208)       
#define    ISP_FE_IN_ACTUAL_3_ADDR            (ISP_FE_BASE_ADDR + 0x20C)       
#define    ISP_FE_IN_ACTUAL_4_ADDR            (ISP_FE_BASE_ADDR + 0x210)       
#define    ISP_FE_IN_TOTAL_0_ADDR             (ISP_FE_BASE_ADDR + 0x220)       
#define    ISP_FE_IN_TOTAL_1_ADDR             (ISP_FE_BASE_ADDR + 0x224)       
#define    ISP_FE_IN_TOTAL_2_ADDR             (ISP_FE_BASE_ADDR + 0x228)       
#define    ISP_FE_IN_TOTAL_3_ADDR             (ISP_FE_BASE_ADDR + 0x22C)       
#define    ISP_FE_IN_TOTAL_4_ADDR             (ISP_FE_BASE_ADDR + 0x230)       
#define    ISP_FE_OUT_LEVEL_0_NO_CH0_ADDR     (ISP_FE_BASE_ADDR + 0x240)       
#define    ISP_FE_OUT_LEVEL_1_NO_CH_0_ADDR    (ISP_FE_BASE_ADDR + 0x244)       
#define    ISP_FE_OUT_LEVEL_0_NO_CH_1_ADDR    (ISP_FE_BASE_ADDR + 0x248)       
#define    ISP_FE_OUT_LEVEL_1_NO_CH_1_ADDR    (ISP_FE_BASE_ADDR + 0x24C)       
#define    ISP_FE_OUT_LEVEL_0_NO_CH_2_ADDR    (ISP_FE_BASE_ADDR + 0x250)       
#define    ISP_FE_OUT_LEVEL_1_NO_CH_2_ADDR    (ISP_FE_BASE_ADDR + 0x254)       
#define    ISP_FE_OUT_LEVEL_0_NO_CH_3_ADDR    (ISP_FE_BASE_ADDR + 0x258)       
#define    ISP_FE_OUT_LEVEL_1_NO_CH_3_ADDR    (ISP_FE_BASE_ADDR + 0x25C)       
#define    ISP_FE_OUT_LEVEL_0_NO_CH_4_ADDR    (ISP_FE_BASE_ADDR + 0x260)       
#define    ISP_FE_OUT_LEVEL_1_NO_CH_4_ADDR    (ISP_FE_BASE_ADDR + 0x264)       

/******************************************************************************/
/*                                  ISP-Debug                                 */
/******************************************************************************/
#define    ISP_DEBUG_BASE_ADDR                (0x40092000)
#define    ISP_DEBUG_WIDTH_ADDR               (ISP_DEBUG_BASE_ADDR + 0x4)       
#define    ISP_DEBUG_LOGO_STA_ADDR            (ISP_DEBUG_BASE_ADDR + 0x8)       
#define    ISP_DEBUG_FRAME_BCD_ADDR           (ISP_DEBUG_BASE_ADDR + 0xC)       
#define    ISP_DEBUG_FRAME_HEX_ADDR           (ISP_DEBUG_BASE_ADDR + 0x10)      
#define    ISP_DEBUG_FRAME_EN_ADDR            (ISP_DEBUG_BASE_ADDR + 0x14)      
#define    ISP_DEBUG_MARK_COLOR_ADDR          (ISP_DEBUG_BASE_ADDR + 0x18)      
#define    ISP_DEBUG_MARK_MAX_ADDR            (ISP_DEBUG_BASE_ADDR + 0x20)      
#define    ISP_DEBUG_MARK_START_ADDR          (ISP_DEBUG_BASE_ADDR + 0x24)      
#define    ISP_DEBUG_SRST_ADDR                (ISP_DEBUG_BASE_ADDR + 0x28)      
#define    ISP_DEBUG_MARK_START_BIN_ADDR      (ISP_DEBUG_BASE_ADDR + 0x2C)      
#define    ISP_DEBUG_BOX_STA_0_ADDR           (ISP_DEBUG_BASE_ADDR + 0x30)      
#define    ISP_DEBUG_BOX_END_0_ADDR           (ISP_DEBUG_BASE_ADDR + 0x34)      
#define    ISP_DEBUG_BOX_STA_1_ADDR           (ISP_DEBUG_BASE_ADDR + 0x38)      
#define    ISP_DEBUG_BOX_END_1_ADDR           (ISP_DEBUG_BASE_ADDR + 0x40)      
#define    ISP_DEBUG_BOX_STA_2_ADDR           (ISP_DEBUG_BASE_ADDR + 0x44)      
#define    ISP_DEBUG_BOX_END_2_ADDR           (ISP_DEBUG_BASE_ADDR + 0x48)      
#define    ISP_DEBUG_BOX_STA_3_ADDR           (ISP_DEBUG_BASE_ADDR + 0x4C)      
#define    ISP_DEBUG_BOX_END_3_ADDR           (ISP_DEBUG_BASE_ADDR + 0x50)      
#define    ISP_DEBUG_BOX_STA_4_ADDR           (ISP_DEBUG_BASE_ADDR + 0x54)      
#define    ISP_DEBUG_BOX_END_4_ADDR           (ISP_DEBUG_BASE_ADDR + 0x58)      
#define    ISP_DEBUG_BOX_DIS_4_ADDR           (ISP_DEBUG_BASE_ADDR + 0x5C)      
#define    ISP_DEBUG_LOGO_ADDR                (ISP_DEBUG_BASE_ADDR + 0x70)      
#define    ISP_DEBUG_LABEL_VAL_0_ADDR         (ISP_DEBUG_BASE_ADDR + 0x80)      
#define    ISP_DEBUG_LABEL_STA_0_ADDR         (ISP_DEBUG_BASE_ADDR + 0x84)      
#define    ISP_DEBUG_LABEL_VAL_1_ADDR         (ISP_DEBUG_BASE_ADDR + 0x88)      
#define    ISP_DEBUG_LABEL_STA_1_ADDR         (ISP_DEBUG_BASE_ADDR + 0x8C)      
#define    ISP_DEBUG_LABEL_VAL_2_ADDR         (ISP_DEBUG_BASE_ADDR + 0x90)      
#define    ISP_DEBUG_LABEL_STA_2_ADDR         (ISP_DEBUG_BASE_ADDR + 0x94)      
#define    ISP_DEBUG_LABEL_VAL_3_ADDR         (ISP_DEBUG_BASE_ADDR + 0x98)     
#define    ISP_DEBUG_LABEL_STA_3_ADDR         (ISP_DEBUG_BASE_ADDR + 0x9C)     
#define    ISP_DEBUG_LABEL_VAL_4_ADDR         (ISP_DEBUG_BASE_ADDR + 0xA0)     
#define    ISP_DEBUG_LABEL_STA_4_ADDR         (ISP_DEBUG_BASE_ADDR + 0xA4)     
#define    ISP_DEBUG_LABEL_VAL_5_ADDR         (ISP_DEBUG_BASE_ADDR + 0xA8)     
#define    ISP_DEBUG_LABEL_STA_5_ADDR         (ISP_DEBUG_BASE_ADDR + 0xAC)     
#define    ISP_DEBUG_LABEL_VAL_6_ADDR         (ISP_DEBUG_BASE_ADDR + 0xB0)     
#define    ISP_DEBUG_LABEL_STA_6_ADDR         (ISP_DEBUG_BASE_ADDR + 0xB4)     
#define    ISP_DEBUG_LABEL_VAL_7_ADDR         (ISP_DEBUG_BASE_ADDR + 0xB8)     
#define    ISP_DEBUG_LABEL_STA_7_ADDR         (ISP_DEBUG_BASE_ADDR + 0xBC)     
#define    ISP_DEBUG_DEBUG_LABEL_EN_ADDR      (ISP_DEBUG_BASE_ADDR + 0xC0)     
#define    ISP_DEBUG_O_VSYNC_ADDR             (ISP_DEBUG_BASE_ADDR + 0xD0)     

#define    ISP_DEBUG_CURRENT_BCD_ADDR         (ISP_DEBUG_BASE_ADDR + 0x100)     
#define    ISP_DEBUG_CURRENT_BIN_ADDR         (ISP_DEBUG_BASE_ADDR + 0x104)     
/******************************************************************************/
/*                                  ISP-Gamma                                 */
/******************************************************************************/
#define    ISP_GAMMA_BASE_ADDR                (0x40092800)
#define    ISP_GAMMA_WIDTH_ADDR               (ISP_GAMMA_BASE_ADDR + 0x4)       
#define    ISP_GAMMA_FIX_0_ADDR               (ISP_GAMMA_BASE_ADDR + 0x40)      
#define    ISP_GAMMA_FIX_1_ADDR               (ISP_GAMMA_BASE_ADDR + 0x44)      
#define    ISP_GAMMA_FIX_2_ADDR               (ISP_GAMMA_BASE_ADDR + 0x48)      
#define    ISP_GAMMA_FIX_3_ADDR               (ISP_GAMMA_BASE_ADDR + 0x4c)      
#define    ISP_GAMMA_FIX_4_ADDR               (ISP_GAMMA_BASE_ADDR + 0x50)      
#define    ISP_GAMMA_FIX_5_ADDR               (ISP_GAMMA_BASE_ADDR + 0x54)      
#define    ISP_GAMMA_FIX_6_ADDR               (ISP_GAMMA_BASE_ADDR + 0x58)      
#define    ISP_GAMMA_FIX_7_ADDR               (ISP_GAMMA_BASE_ADDR + 0x5C)      
#define    ISP_GAMMA_FIX_8_ADDR               (ISP_GAMMA_BASE_ADDR + 0x60)      
#define    ISP_GAMMA_FIX_9_ADDR               (ISP_GAMMA_BASE_ADDR + 0x64)      
#define    ISP_GAMMA_FIX_10_ADDR              (ISP_GAMMA_BASE_ADDR + 0x68)      
#define    ISP_GAMMA_FIX_11_ADDR              (ISP_GAMMA_BASE_ADDR + 0x6C)      
#define    ISP_GAMMA_FIX_12_ADDR              (ISP_GAMMA_BASE_ADDR + 0x70)      
#define    ISP_GAMMA_OFFSET_ADDR              (ISP_GAMMA_BASE_ADDR + 0x80)      
#define    ISP_GAMMA_GAIN_ADDR                (ISP_GAMMA_BASE_ADDR + 0x84)      
#define    ISP_GAMMA_IN_VAL_ADDR              (ISP_GAMMA_BASE_ADDR + 0xA0)      
#define    ISP_GAMMA_IN_TOTAL_VAL_ADDR        (ISP_GAMMA_BASE_ADDR + 0xA4)      
#define    ISP_GAMMA_OUT_VAL_ADDR             (ISP_GAMMA_BASE_ADDR + 0xA8)      
#define    ISP_GAMMA_OUT_TOTAL_VAL_ADDR       (ISP_GAMMA_BASE_ADDR + 0xAC)      
/******************************************************************************/
/*                                 ISP-Pseudo                                 */
/******************************************************************************/
#define    ISP_PSEUDO_BASE_ADDR               (0x40093000)                      
#define    ISP_PSEUDO_SIZE_ADDR               (ISP_PSEUDO_BASE_ADDR + 0x4)      
#define    ISP_PSEUDO_H_PORCH_ADDR            (ISP_PSEUDO_BASE_ADDR + 0x8)      
#define    ISP_PSEUDO_V_PORCH_ADDR            (ISP_PSEUDO_BASE_ADDR + 0xC)      
#define    ISP_PSEUDO_IMAGE_TYPE_ADDR         (ISP_PSEUDO_BASE_ADDR + 0x20)     
#define    ISP_PSEUDO_IMAGE_PARAM_0_ADDR      (ISP_PSEUDO_BASE_ADDR + 0x24)     
#define    ISP_PSEUDO_IMAGE_PARAM_1_ADDR      (ISP_PSEUDO_BASE_ADDR + 0x28)     
#define    ISP_PSEUDO_IMAGE_PARAM_2_ADDR      (ISP_PSEUDO_BASE_ADDR + 0x2C)     
#define    ISP_PSEUDO_ANIMATION_EN_ADDR       (ISP_PSEUDO_BASE_ADDR + 0x40)     
#define    ISP_PSEUDO_ANIMATION_STATUS_ADDR   (ISP_PSEUDO_BASE_ADDR + 0x40)     

/******************************************************************************/
/*                                  ISP-FIFO                                  */
/******************************************************************************/
#define    ISP_FIFO_BASE_ADDR                 (0x40094000)                      
#define    ISP_FIFO_INT_EN_ADDR               (ISP_FIFO_BASE_ADDR + 0x4)        
#define    ISP_FIFO_BUF_OVERFLOW_INT_CL_ADDR  (ISP_FIFO_BASE_ADDR + 0x8)        
#define    ISP_FIFO_BUF_FINISH_INT_CL_ADDR    (ISP_FIFO_BASE_ADDR + 0xC)        
#define    ISP_FIFO_BUF_UNDETECT_INT_CL_ADDR  (ISP_FIFO_BASE_ADDR + 0x10)       
#define    ISP_FIFO_FE_DATA_LESS_INT_CL_ADDR  (ISP_FIFO_BASE_ADDR + 0x14)       
#define    ISP_FIFO_FE_DATA_MORE_INT_CL_ADDR  (ISP_FIFO_BASE_ADDR + 0x18)       

#define    ISP_FIFO_BUF_BLOCK_REMAIN_ADDR     (ISP_FIFO_BASE_ADDR + 0x80)       
#define    ISP_FIFO_BUF_BLOCK_MISS_ADDR       (ISP_FIFO_BASE_ADDR + 0x80)       
#define    ISP_FIFO_BUF_INT_STATUS_ADDR       (ISP_FIFO_BASE_ADDR + 0x80)       

/******************************************************************************/
/*                                  CIS-DIGI                                  */
/******************************************************************************/
//BLC
#define    CIS_DIGI_BLC_BASE_ADDR             (0x40093800)                       
#define    CIS_DIGI_BLC_CTRL_1_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0x4)     
#define    CIS_DIGI_BLC_CTRL_2_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0x8)     
#define    CIS_DIGI_BLC_CTRL_3_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0xC)     
#define    CIS_DIGI_BLC_CTRL_4_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0x10)    
#define    CIS_DIGI_BLC_CTRL_5_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0x14)    
#define    CIS_DIGI_BLC_CTRL_6_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0x18)    
#define    CIS_DIGI_BLC_CTRL_7_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0x1C)    
#define    CIS_DIGI_BLC_CTRL_8_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0x20)    
#define    CIS_DIGI_BLC_CTRL_9_ADDR           (CIS_DIGI_BLC_BASE_ADDR + 0x24)    

//DGC
#define    CIS_DIGI_DGC_BASE_ADDR             (0x40093828)                       
#define    CIS_DIGI_DGC_CTRL_1_ADDR           (CIS_DIGI_DGC_BASE_ADDR + 0x4)     
#define    CIS_DIGI_DGC_CTRL_2_ADDR           (CIS_DIGI_DGC_BASE_ADDR + 0x8)     
#define    CIS_DIGI_DGC_CTRL_3_ADDR           (CIS_DIGI_DGC_BASE_ADDR + 0xC)     
#define    CIS_DIGI_DGC_CTRL_4_ADDR           (CIS_DIGI_DGC_BASE_ADDR + 0x10)    

//EGA
#define    CIS_DIGI_EGA_BASE_ADDR             (0x4009383C)                       
#define    CIS_DIGI_EXP_LINE_ADDR             (CIS_DIGI_EGA_BASE_ADDR + 0x4)     
#define    CIS_DIGI_GAIN_ADDR                 (CIS_DIGI_EGA_BASE_ADDR + 0x8)     
#define    CIS_DIGI_EGA_CTRL_3_ADDR           (CIS_DIGI_EGA_BASE_ADDR + 0xC)     
#define    CIS_DIGI_EGA_CTRL_4_ADDR           (CIS_DIGI_EGA_BASE_ADDR + 0x10)    
#define    CIS_DIGI_EGA_CTRL_5_ADDR           (CIS_DIGI_EGA_BASE_ADDR + 0x14)    
#define    CIS_DIGI_EGA_CTRL_6_ADDR           (CIS_DIGI_EGA_BASE_ADDR + 0x18)    
#define    CIS_DIGI_EGA_CTRL_7_ADDR           (CIS_DIGI_EGA_BASE_ADDR + 0x1C)    
#define    CIS_DIGI_EGA_CTRL_8_ADDR           (CIS_DIGI_EGA_BASE_ADDR + 0x20)    
#define    CIS_DIGI_EGA_CTRL_9_ADDR           (CIS_DIGI_EGA_BASE_ADDR + 0x24)    
#define    CIS_DIGI_EGA_CTRL_10_ADDR          (CIS_DIGI_EGA_BASE_ADDR + 0x28)    
#define    CIS_DIGI_EGA_CTRL_11_ADDR          (CIS_DIGI_EGA_BASE_ADDR + 0x2C)    

//WINC
#define    CIS_DIGI_WINC_BASE_ADDR            (0x4009386C)                       

//Timing cotrol
#define    CIS_DIGI_TIME_BASE_ADDR            (0x40093870)                       
#define    CIS_DIGI_TIME_CTRL_1_ADDR          (CIS_DIGI_TIME_BASE_ADDR + 0x4)    
#define    CIS_DIGI_TIME_CTRL_2_ADDR          (CIS_DIGI_TIME_BASE_ADDR + 0x8)    
#define    CIS_DIGI_TIME_CTRL_3_ADDR          (CIS_DIGI_TIME_BASE_ADDR + 0xC)    
#define    CIS_DIGI_TIME_CTRL_4_ADDR          (CIS_DIGI_TIME_BASE_ADDR + 0x10)   
#define    CIS_DIGI_TIME_CTRL_5_ADDR          (CIS_DIGI_TIME_BASE_ADDR + 0x14)   
#define    CIS_DIGI_TIME_CTRL_6_ADDR          (CIS_DIGI_TIME_BASE_ADDR + 0x18)   
#define    CIS_DIGI_TIME_CTRL_7_ADDR          (CIS_DIGI_TIME_BASE_ADDR + 0x1C)   
#define    CIS_DIGI_TIME_CTRL_8_ADDR          (CIS_DIGI_TIME_BASE_ADDR + 0x20)   

//Array control
#define    CIS_DIGI_ARR_BASE_ADDR             (0x40093894)                       
#define    CIS_DIGI_ARR_CTRL_1_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0x4)     
#define    CIS_DIGI_ARR_CTRL_2_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0x8)     
#define    CIS_DIGI_ARR_CTRL_3_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0xC)     
#define    CIS_DIGI_ARR_CTRL_4_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0x10)    
#define    CIS_DIGI_ARR_CTRL_5_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0x14)    
#define    CIS_DIGI_ARR_CTRL_6_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0x18)    
#define    CIS_DIGI_ARR_CTRL_7_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0x1C)    
#define    CIS_DIGI_ARR_CTRL_8_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0x20)    
#define    CIS_DIGI_ARR_CTRL_9_ADDR           (CIS_DIGI_ARR_BASE_ADDR + 0x24)    
#define    CIS_DIGI_ARR_CTRL_10_ADDR          (CIS_DIGI_ARR_BASE_ADDR + 0x28)    
#define    CIS_DIGI_ARR_CTRL_11_ADDR          (CIS_DIGI_ARR_BASE_ADDR + 0x2C)    
#define    CIS_DIGI_ARR_CTRL_12_ADDR          (CIS_DIGI_ARR_BASE_ADDR + 0x30)    
#define    CIS_DIGI_ARR_CTRL_13_ADDR          (CIS_DIGI_ARR_BASE_ADDR + 0x34)    
#define    CIS_DIGI_ARR_CTRL_14_ADDR          (CIS_DIGI_ARR_BASE_ADDR + 0x38)    
#define    CIS_DIGI_ARR_CTRL_15_ADDR          (CIS_DIGI_ARR_BASE_ADDR + 0x3C)    
#define    CIS_DIGI_ARR_CTRL_16_ADDR          (CIS_DIGI_ARR_BASE_ADDR + 0x40)    
#define    CIS_DIGI_ARR_CTRL_17_ADDR          (CIS_DIGI_ARR_BASE_ADDR + 0x44)    

//System control
#define    CIS_DIGI_SYS_BASE_ADDR             (0x400938DC)                       

//DPD
#define    CIS_DIGI_DPD_BASE_ADDR             (0X400938E0)                       
#define    CIS_DIGI_DPD_CTRL_ADDR             (CIS_DIGI_DPD_BASE_ADDR + 0X4)     

//EG
#define    CIS_DIGI_EG_BASE_ADDR              (0x400938EC)                       
#define    CIS_DIGI_EG_CTRL_1_ADDR            (CIS_DIGI_EG_BASE_ADDR + 0x4)      
#define    CIS_DIGI_EG_CTRL_2_ADDR            (CIS_DIGI_EG_BASE_ADDR + 0x8)      


/******************************************************************************/
/*                                   CIS-TOP                                  */
/******************************************************************************/
#define    CIS_TOP_BASE_ADDR                  (0x401D00D0)                       
#define    CIS_TOP_DIVIDER_ADDR               (CIS_TOP_BASE_ADDR + 0x4)          
#define    CIS_TOP_PWC_ADDR                   (CIS_TOP_BASE_ADDR + 0x8)          
#define    CIS_TOP_RAMP_0_ADDR                (CIS_TOP_BASE_ADDR + 0xC)          
#define    CIS_TOP_RAMP_1_ADDR                (CIS_TOP_BASE_ADDR + 0x10)         

/******************************************************************************/
/*                                  PAD_CTRL                                  */
/******************************************************************************/
// I2C
#define    PAD_CTRL_I2C_0_SCK_ADDR            (0x401D0054)
#define    PAD_CTRL_I2C_0_SDA_ADDR            (0x401D0058)

#define    PAD_CTRL_I2C_1_SCK_ADDR            (0x401D0030)
#define    PAD_CTRL_I2C_1_SDA_ADDR            (0x401D0034)

// QSPI
#define    PAD_CTRL_QSPI_EN_ADDR              (0x40300108)
#define    PAD_CTRL_QSPI_CLK_ADDR             (0x4030010C)
#define    PAD_CTRL_QSPI_D0_ADDR              (0x40300110)
#define    PAD_CTRL_QSPI_D1_ADDR              (0x40300114)
#define    PAD_CTRL_QSPI_D2_ADDR              (0x40300118)
#define    PAD_CTRL_QSPI_D3_ADDR              (0x4030011C)

// SPI
#define    PAD_CTRL_SPI_EN_ADDR               (0x40300120)
#define    PAD_CTRL_SPI_CLK_ADDR              (0x40300124)
#define    PAD_CTRL_SPI_DI_ADDR               (0x40300128)
#define    PAD_CTRL_SPI_DO_ADDR               (0x4030012C)

// UART
#define    PAD_CTRL_UART_SIN_ADDR             (0x40300138)
#define    PAD_CTRL_UART_SOUT_ADDR            (0x4030013C)

// I2S
#define    PAD_CTRL_I2S_MCLK_ADDR             (0x40300140)
#define    PAD_CTRL_I2S_BCLK_ADDR             (0x40300144)
#define    PAD_CTRL_I2S_WS_ADDR               (0x40300148)
#define    PAD_CTRL_I2S_DI_ADDR               (0x4030014C)
#define    PAD_CTRL_I2S_DO_ADDR               (0x40300150)

// Strobe
#define    PAD_CTRL_STROBE_BASE_ADDR          (0x4030015C)

/******************************************************************************/
/*                                  SYS_CTRL                                  */
/******************************************************************************/
#define    SYS_CPU_0_BOOT_ADDR                (0x40300034)
#define    SYS_CPU_1_BOOT_ADDR                (0x40300038)
#define    SYS_CPU_1_EN_ADDR                  (0x4030003C)
#define    SYS_CIS_SOURCE_ADDR                (0x40300040)    
#define    SYS_THRESH_LOW_ADDR                (0x40300044)
#define    SYS_THRESH_HIGH_ADDR               (0x40300048)
#define    SYS_RINGCK_TEST_ADDR               (0x4030004C)    
#define    SYS_CLK_CNT_RINGCK_ADDR            (0x40300050)    
#define    SYS_RINGCK_TEST_END_ADDR           (0x40300054)    


/******************************************************************************/
/*                                   Reset                                    */
/******************************************************************************/

#define    RESET_RTC_I2C_ADDR                 (0x401D007C)   
#define    RESET_ZERO_RISK_ADDR               (0x401D009C)   
#define    RESET_SW_FUNC_0_ADDR               (0x401D00B0)   

#define    RESET_SW_FUNC_1_ADDR               (0x40300000)   
#define    RESET_SW_CPU_0_ADDR                (0x40300058)
#define    RESET_SW_CPU_1_ADDR                (0x4030005C)

// note: 4009_38DC[1] : CIS-Digital reset.

/******************************************************************************/
/*                                   Clock                                    */
/******************************************************************************/
#define    SYS_CLK_ADDR                       (0x401D0080)
#define    CMOS_XCLK_ADDR                     (0x401D0084)
#define    CLK_DIV_ADDR                       (0x401D008C)   
#define    PCLK_EN_ADDR                       (0x401D00BC)   
#define    SYS_CLK_EN_ADDR                    (0x401D00C0)   
#define    CIS_PAD_CLK_ADDR                   (0x401D00C4)   

#define    CLK_UART_DIV_ADDR                  (0x40300004)
#define    CLK_I2S_DIV_ADDR                   (0x40300008)   
#define    CLK_SSP_DIV_ADDR                   (0x4030000C)
#define    CLK_KPD_DIV_ADDR                   (0x40300010)   
#define    CLK_TIMER_1_DIV_ADDR               (0x40300014)   
#define    CLK_TIMER_2_DIV_ADDR               (0x40300018)   
#define    CLK_TIMER_3_DIV_ADDR               (0x4030001C)   
#define    CLK_TIMER_4_DIV_ADDR               (0x40300020)   
#define    CLK_WDT_DIV_ADDR                   (0x40300024)   
#define    CLK_SPI_DIV_ADDR                   (0x40300028)   
#define    CLK_GPIO_DIV_ADDR                  (0x4030002C)

#define    CLK_SW_FUNC_1_EN_ADDR              (0x40300060)   

/******************************************************************************/
/*                                    PMU                                     */
/******************************************************************************/
#define    PMU_PK_BG_ADDR                     (0x401D0100)
#define    PMU_PK_LDO_VO_ADDR                 (PMU_PK_BG_ADDR + 0x4)
#define    PMU_XTL_32K_ADDR                   (PMU_PK_BG_ADDR + 0x8)
#define    PMU_RC_OSC480K_ADDR                (PMU_PK_BG_ADDR + 0xC)
#define    PMU_HV_BG_ADDR                     (PMU_PK_BG_ADDR + 0x10)
#define    PMU_LDO_LS_ADDR                    (PMU_PK_BG_ADDR + 0x14)
#define    PMU_LDO_SPLL_ADDR                  (PMU_PK_BG_ADDR + 0x18)
#define    PMU_LDO_CIS_ADDR                   (PMU_PK_BG_ADDR + 0x1C)
#define    PMU_BUCK_DCDC_ADDR                 (PMU_PK_BG_ADDR + 0x20)
#define    PMU_XTL_24M_ADDR                   (PMU_PK_BG_ADDR + 0x24)
#define    PMU_SPLL_0_ADDR                    (PMU_PK_BG_ADDR + 0x28)
#define    PMU_SPLL_1_ADDR                    (PMU_PK_BG_ADDR + 0x2C)

/******************************************************************************/
/*                                 ZeroRiscV                                  */
/******************************************************************************/
#define    ZR_BOOT_ADDR                       (0x401D0094)
#define    ZR_FETCH_EN_ADDR                   (0x401D0098)

#define    ZR_EXT_STAT_ADDR                   (0x401D00A0)
#define    ZR_EXT_POL_ADDR                    (0x401D00A4)
#define    ZR_EXT_LVL_ADDR                    (0x401D00A8)

#define    ZR_DPL_OFF_ADDR                    (0x401D00AC)

#define    ZR_PD_PK_MAILBOX_ADDR              (0x401D00B4)
#define    ZR_PK_PD_MAILBOX_ADDR              (0x401D00B8)

#define    ZR_INT_PIR_STAT_ADDR               (0x401D00C8)
#define    ZR_INT_PIR_POL_LVL_ADDR            (0x401D00CC)

/******************************************************************************/
/*                              SensorToMemery                                */
/******************************************************************************/
#define    SENSOR_MEM_BASE_ADDR               (0x400A0000)
#define    SENSOR_MEM_ENDIAN_MODE_ADDR        (SENSOR_MEM_BASE_ADDR + 0x04)
#define    SENSOR_MEM_WATER_MARK_ADDR         (SENSOR_MEM_BASE_ADDR + 0x08)
#define    SENSOR_MEM_INT_EN_ADDR             (SENSOR_MEM_BASE_ADDR + 0x0C)
#define    SENSOR_MEM_INT_STAT_ADDR           (SENSOR_MEM_BASE_ADDR + 0x10)
#define    SENSOR_MEM_SCALER_CH_0_ADDR        (SENSOR_MEM_BASE_ADDR + 0x14)
#define    SENSOR_MEM_SCALER_CH_1_ADDR        (SENSOR_MEM_BASE_ADDR + 0x18)
#define    SENSOR_MEM_SCALER_CH_2_ADDR        (SENSOR_MEM_BASE_ADDR + 0x1C)
#define    SENSOR_MEM_SCALER_CH_3_ADDR        (SENSOR_MEM_BASE_ADDR + 0x20)
#define    SENSOR_MEM_SCALER_CH_4_ADDR        (SENSOR_MEM_BASE_ADDR + 0x24)

//SRAM
// Memory address range : 0x20044000 - 0x20047FFF
#define    SENSOR_MEM_IMAGE_0_START_ADDR      (SENSOR_MEM_BASE_ADDR + 0x18000)
#define    SENSOR_MEM_IMAGE_0_END_ADDR        (SENSOR_MEM_BASE_ADDR + 0x1BFFF)  

// Memory address range : 0x20040000 - 0x20043FFF
#define    SENSOR_MEM_IMAGE_1_START_ADDR      (SENSOR_MEM_BASE_ADDR + 0x14000)
#define    SENSOR_MEM_IMAGE_1_END_ADDR        (SENSOR_MEM_BASE_ADDR + 0x17FFF)

// Memory address range : 0x2003C000 - 0x2003FFFF
#define    SENSOR_MEM_IMAGE_2_START_ADDR      (SENSOR_MEM_BASE_ADDR + 0x10000)
#define    SENSOR_MEM_IMAGE_2_END_ADDR        (SENSOR_MEM_BASE_ADDR + 0x13FFF)

// Memory address range : 0x20038000 - 0x2003BFFF
#define    SENSOR_MEM_IMAGE_3_START_ADDR      (SENSOR_MEM_BASE_ADDR + 0xC000)
#define    SENSOR_MEM_IMAGE_3_END_ADDR        (SENSOR_MEM_BASE_ADDR + 0xFFFF)

// Memory address range : 0x20034000 - 0x20037FFF
#define    SENSOR_MEM_IMAGE_4_START_ADDR      (SENSOR_MEM_BASE_ADDR + 0x8000)
#define    SENSOR_MEM_IMAGE_4_END_ADDR        (SENSOR_MEM_BASE_ADDR + 0xBFFF)

// Memory address range : 0x20030000 - 0x20033FFF
#define    SENSOR_MEM_IMAGE_5_START_ADDR      (SENSOR_MEM_BASE_ADDR + 0x4000)
#define    SENSOR_MEM_IMAGE_5_END_ADDR        (SENSOR_MEM_BASE_ADDR + 0x7FFF)

// Memory address range : 0x2002C000 - 0x2002FFFF
#define    SENSOR_MEM_IMAGE_6_START_ADDR      (SENSOR_MEM_BASE_ADDR + 0x0000)
#define    SENSOR_MEM_IMAGE_6_END_ADDR        (SENSOR_MEM_BASE_ADDR + 0x3FFF)
//note : RD not confirm yet.

/******************************************************************************/
/*                                   AES                                      */
/******************************************************************************/
#define    AES_BASE_ADDR                      (0x400E0000)
#define    AES_RW_ADDR                        (AES_BASE_ADDR + 0x4)
#define    AES_DATA_IN_ADDR                    (AES_BASE_ADDR + 0x8)
#define    AES_DATA_OUT_ADDR                  (AES_BASE_ADDR + 0xC)
#define    AES_KEY_0_ADDR                     (AES_BASE_ADDR + 0x10)
#define    AES_KEY_1_ADDR                     (AES_BASE_ADDR + 0x14)
#define    AES_KEY_2_ADDR                     (AES_BASE_ADDR + 0x18)
#define    AES_KEY_3_ADDR                     (AES_BASE_ADDR + 0x1C)
#define    AES_IV_0_ADDR                      (AES_BASE_ADDR + 0x20)
#define    AES_IV_1_ADDR                      (AES_BASE_ADDR + 0x24)
#define    AES_IV_2_ADDR                      (AES_BASE_ADDR + 0x28)
#define    AES_IV_3_ADDR                      (AES_BASE_ADDR + 0x2C)

//note : RD not confirm yet.


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif