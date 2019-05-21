#ifndef __SDRAM_H
#define	__SDRAM_H

//#include "stm32f4xx.h"
//#include <stdio.h>



//#define IS42S16400J_SIZE 0x800000  //400000*16bits = 0x800000  ，8M字节


///*SDRAM 的bank选择*/  
//#define FMC_BANK_SDRAM            FMC_Bank2_SDRAM  
//#define FMC_COMMAND_TARGET_BANK   FMC_SDRAM_CMD_TARGET_BANK2

///**
//  * @brief  FMC SDRAM 数据基地址
//  */   
//#define SDRAM_BANK_ADDR     ((uint32_t)0xD0000000)
//  
///**
//  * @brief  FMC SDRAM 数据宽度
//  */  
///* #define SDRAM_MEMORY_WIDTH   FMC_SDMemory_Width_8b  */
//#define SDRAM_MEMORY_WIDTH    FMC_SDRAM_MEM_BUS_WIDTH_16 

///**
//  * @brief  FMC SDRAM CAS Latency
//  */  
///* #define SDRAM_CAS_LATENCY   FMC_CAS_Latency_2  */
//#define SDRAM_CAS_LATENCY    FMC_SDRAM_CAS_LATENCY_3

///**
//  * @brief  FMC SDRAM SDCLK时钟分频因子
//  */  
//#define SDCLOCK_PERIOD    FMC_SDRAM_CLOCK_PERIOD_2        /* Default configuration used with LCD */
///* #define SDCLOCK_PERIOD    FMC_SDClock_Period_3 */

///**
//  * @brief  FMC SDRAM 突发读取特性
//  */  
//#define SDRAM_READBURST    FMC_SDRAM_RBURST_DISABLE    /* Default configuration used with LCD */
///* #define SDRAM_READBURST    FMC_Read_Burst_Enable  */

///**
//  * @brief  FMC SDRAM Bank Remap
//  */    
///* #define SDRAM_BANK_REMAP */   

//#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)



///**
//  * @brief  FMC SDRAM 模式配置的寄存器相关定义
//  */
//#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
//#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
//#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
//#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
//#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
//#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
//#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
//#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
//#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
//#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
//#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)      


///*信息输出*/
//#define SDRAM_DEBUG_ON         1

//#define SDRAM_INFO(fmt,arg...)           printf("<<-SDRAM-INFO->> "fmt"\n",##arg)
//#define SDRAM_ERROR(fmt,arg...)          printf("<<-SDRAM-ERROR->> "fmt"\n",##arg)
//#define SDRAM_DEBUG(fmt,arg...)          do{\
//                                          if(SDRAM_DEBUG_ON)\
//                                          printf("<<-SDRAM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
//                                          }while(0)
///**
//  * @}
//  */  
// 
///*地址信号线*/  
//#define FMC_A0_GPIO_PORT        GPIOF
//#define FMC_A0_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A0_GPIO_PIN         GPIO_PIN_0
//#define FMC_A0_PINSOURCE        GPIO_PinSource0
//#define FMC_A0_AF               GPIO_AF_FMC

//#define FMC_A1_GPIO_PORT        GPIOF
//#define FMC_A1_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A1_GPIO_PIN         GPIO_PIN_1
//#define FMC_A1_PINSOURCE        GPIO_PinSource1
//#define FMC_A1_AF               GPIO_AF_FMC

//#define FMC_A2_GPIO_PORT        GPIOF
//#define FMC_A2_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A2_GPIO_PIN         GPIO_PIN_2
//#define FMC_A2_PINSOURCE        GPIO_PinSource2
//#define FMC_A2_AF               GPIO_AF_FMC

//#define FMC_A3_GPIO_PORT        GPIOF
//#define FMC_A3_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A3_GPIO_PIN         GPIO_PIN_3
//#define FMC_A3_PINSOURCE        GPIO_PinSource3
//#define FMC_A3_AF               GPIO_AF_FMC

//#define FMC_A4_GPIO_PORT        GPIOF
//#define FMC_A4_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A4_GPIO_PIN         GPIO_PIN_4
//#define FMC_A4_PINSOURCE        GPIO_PinSource4
//#define FMC_A4_AF               GPIO_AF_FMC

//#define FMC_A5_GPIO_PORT        GPIOF
//#define FMC_A5_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A5_GPIO_PIN         GPIO_PIN_5
//#define FMC_A5_PINSOURCE        GPIO_PinSource5
//#define FMC_A5_AF               GPIO_AF_FMC

//#define FMC_A6_GPIO_PORT        GPIOF
//#define FMC_A6_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A6_GPIO_PIN         GPIO_PIN_12
//#define FMC_A6_PINSOURCE        GPIO_PinSource12
//#define FMC_A6_AF               GPIO_AF_FMC

//#define FMC_A7_GPIO_PORT        GPIOF
//#define FMC_A7_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A7_GPIO_PIN         GPIO_PIN_13
//#define FMC_A7_PINSOURCE        GPIO_PinSource13
//#define FMC_A7_AF               GPIO_AF_FMC

//#define FMC_A8_GPIO_PORT        GPIOF
//#define FMC_A8_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A8_GPIO_PIN         GPIO_PIN_14
//#define FMC_A8_PINSOURCE        GPIO_PinSource14
//#define FMC_A8_AF               GPIO_AF_FMC

//#define FMC_A9_GPIO_PORT        GPIOF
//#define FMC_A9_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_A9_GPIO_PIN         GPIO_PIN_15
//#define FMC_A9_PINSOURCE        GPIO_PinSource15
//#define FMC_A9_AF               GPIO_AF_FMC


//#define FMC_A10_GPIO_PORT        GPIOG
//#define FMC_A10_GPIO_CLK         __HAL_RCC_GPIOG_CLK_ENABLE()
//#define FMC_A10_GPIO_PIN         GPIO_PIN_0
//#define FMC_A10_PINSOURCE        GPIO_PinSource0
//#define FMC_A10_AF               GPIO_AF_FMC


//#define FMC_A11_GPIO_PORT        GPIOG
//#define FMC_A11_GPIO_CLK         __HAL_RCC_GPIOG_CLK_ENABLE()
//#define FMC_A11_GPIO_PIN         GPIO_PIN_1
//#define FMC_A11_PINSOURCE        GPIO_PinSource1
//#define FMC_A11_AF               GPIO_AF_FMC

///*数据信号线*/
//#define FMC_D0_GPIO_PORT        GPIOD
//#define FMC_D0_GPIO_CLK         __HAL_RCC_GPIOD_CLK_ENABLE()
//#define FMC_D0_GPIO_PIN         GPIO_PIN_14
//#define FMC_D0_PINSOURCE        GPIO_PinSource14
//#define FMC_D0_AF               GPIO_AF_FMC

//#define FMC_D1_GPIO_PORT        GPIOD
//#define FMC_D1_GPIO_CLK         __HAL_RCC_GPIOD_CLK_ENABLE()
//#define FMC_D1_GPIO_PIN         GPIO_PIN_15
//#define FMC_D1_PINSOURCE        GPIO_PinSource15
//#define FMC_D1_AF               GPIO_AF_FMC

//#define FMC_D2_GPIO_PORT        GPIOD
//#define FMC_D2_GPIO_CLK         __HAL_RCC_GPIOD_CLK_ENABLE()
//#define FMC_D2_GPIO_PIN         GPIO_PIN_0
//#define FMC_D2_PINSOURCE        GPIO_PinSource0
//#define FMC_D2_AF               GPIO_AF_FMC

//#define FMC_D3_GPIO_PORT        GPIOD
//#define FMC_D3_GPIO_CLK         __HAL_RCC_GPIOD_CLK_ENABLE()
//#define FMC_D3_GPIO_PIN         GPIO_PIN_1
//#define FMC_D3_PINSOURCE        GPIO_PinSource1
//#define FMC_D3_AF               GPIO_AF_FMC

//#define FMC_D4_GPIO_PORT        GPIOE
//#define FMC_D4_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D4_GPIO_PIN         GPIO_PIN_7
//#define FMC_D4_PINSOURCE        GPIO_PinSource7
//#define FMC_D4_AF               GPIO_AF_FMC

//#define FMC_D5_GPIO_PORT        GPIOE
//#define FMC_D5_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D5_GPIO_PIN         GPIO_PIN_8
//#define FMC_D5_PINSOURCE        GPIO_PinSource8
//#define FMC_D5_AF               GPIO_AF_FMC

//#define FMC_D6_GPIO_PORT        GPIOE
//#define FMC_D6_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D6_GPIO_PIN         GPIO_PIN_9
//#define FMC_D6_PINSOURCE        GPIO_PinSource9
//#define FMC_D6_AF               GPIO_AF_FMC

//#define FMC_D7_GPIO_PORT        GPIOE
//#define FMC_D7_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D7_GPIO_PIN         GPIO_PIN_10
//#define FMC_D7_PINSOURCE        GPIO_PinSource10
//#define FMC_D7_AF               GPIO_AF_FMC

//#define FMC_D8_GPIO_PORT        GPIOE
//#define FMC_D8_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D8_GPIO_PIN         GPIO_PIN_11
//#define FMC_D8_PINSOURCE        GPIO_PinSource11
//#define FMC_D8_AF               GPIO_AF_FMC

//#define FMC_D9_GPIO_PORT        GPIOE
//#define FMC_D9_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D9_GPIO_PIN         GPIO_PIN_12
//#define FMC_D9_PINSOURCE        GPIO_PinSource12
//#define FMC_D9_AF               GPIO_AF_FMC

//#define FMC_D10_GPIO_PORT        GPIOE
//#define FMC_D10_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D10_GPIO_PIN         GPIO_PIN_13
//#define FMC_D10_PINSOURCE        GPIO_PinSource13
//#define FMC_D10_AF               GPIO_AF_FMC

//#define FMC_D11_GPIO_PORT        GPIOE
//#define FMC_D11_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D11_GPIO_PIN         GPIO_PIN_14
//#define FMC_D11_PINSOURCE        GPIO_PinSource14
//#define FMC_D11_AF               GPIO_AF_FMC

//#define FMC_D12_GPIO_PORT        GPIOE
//#define FMC_D12_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_D12_GPIO_PIN         GPIO_PIN_15
//#define FMC_D12_PINSOURCE        GPIO_PinSource15
//#define FMC_D12_AF               GPIO_AF_FMC

//#define FMC_D13_GPIO_PORT        GPIOD
//#define FMC_D13_GPIO_CLK         __HAL_RCC_GPIOD_CLK_ENABLE()
//#define FMC_D13_GPIO_PIN         GPIO_PIN_8
//#define FMC_D13_PINSOURCE        GPIO_PinSource8
//#define FMC_D13_AF               GPIO_AF_FMC

//#define FMC_D14_GPIO_PORT        GPIOD
//#define FMC_D14_GPIO_CLK         __HAL_RCC_GPIOD_CLK_ENABLE()
//#define FMC_D14_GPIO_PIN         GPIO_PIN_9
//#define FMC_D14_PINSOURCE        GPIO_PinSource9
//#define FMC_D14_AF               GPIO_AF_FMC

//#define FMC_D15_GPIO_PORT        GPIOD
//#define FMC_D15_GPIO_CLK         __HAL_RCC_GPIOD_CLK_ENABLE()
//#define FMC_D15_GPIO_PIN         GPIO_PIN_10
//#define FMC_D15_PINSOURCE        GPIO_PinSource10
//#define FMC_D15_AF               GPIO_AF_FMC


///*控制信号线*/  
//#define FMC_CS_GPIO_PORT        GPIOH
//#define FMC_CS_GPIO_CLK         __HAL_RCC_GPIOH_CLK_ENABLE()
//#define FMC_CS_GPIO_PIN         GPIO_PIN_6
//#define FMC_CS_PINSOURCE        GPIO_PinSource6
//#define FMC_CS_AF               GPIO_AF_FMC

//#define FMC_BA0_GPIO_PORT        GPIOG
//#define FMC_BA0_GPIO_CLK         __HAL_RCC_GPIOG_CLK_ENABLE()
//#define FMC_BA0_GPIO_PIN         GPIO_PIN_4
//#define FMC_BA0_PINSOURCE        GPIO_PinSource4
//#define FMC_BA0_AF               GPIO_AF_FMC

//#define FMC_BA1_GPIO_PORT        GPIOG
//#define FMC_BA1_GPIO_CLK         __HAL_RCC_GPIOG_CLK_ENABLE()
//#define FMC_BA1_GPIO_PIN         GPIO_PIN_5
//#define FMC_BA1_PINSOURCE        GPIO_PinSource5
//#define FMC_BA1_AF               GPIO_AF_FMC

//#define FMC_WE_GPIO_PORT        GPIOC
//#define FMC_WE_GPIO_CLK         __HAL_RCC_GPIOC_CLK_ENABLE()
//#define FMC_WE_GPIO_PIN         GPIO_PIN_0
//#define FMC_WE_PINSOURCE        GPIO_PinSource0
//#define FMC_WE_AF               GPIO_AF_FMC

//#define FMC_RAS_GPIO_PORT        GPIOF
//#define FMC_RAS_GPIO_CLK         __HAL_RCC_GPIOF_CLK_ENABLE()
//#define FMC_RAS_GPIO_PIN         GPIO_PIN_11
//#define FMC_RAS_PINSOURCE        GPIO_PinSource11
//#define FMC_RAS_AF               GPIO_AF_FMC

//#define FMC_CAS_GPIO_PORT        GPIOG
//#define FMC_CAS_GPIO_CLK         __HAL_RCC_GPIOG_CLK_ENABLE()
//#define FMC_CAS_GPIO_PIN         GPIO_PIN_15
//#define FMC_CAS_PINSOURCE        GPIO_PinSource15
//#define FMC_CAS_AF               GPIO_AF_FMC

//#define FMC_CLK_GPIO_PORT        GPIOG
//#define FMC_CLK_GPIO_CLK         __HAL_RCC_GPIOG_CLK_ENABLE()
//#define FMC_CLK_GPIO_PIN         GPIO_PIN_8
//#define FMC_CLK_PINSOURCE        GPIO_PinSource8
//#define FMC_CLK_AF               GPIO_AF_FMC

//#define FMC_CKE_GPIO_PORT        GPIOH
//#define FMC_CKE_GPIO_CLK         __HAL_RCC_GPIOH_CLK_ENABLE()
//#define FMC_CKE_GPIO_PIN         GPIO_PIN_7
//#define FMC_CKE_PINSOURCE        GPIO_PinSource7
//#define FMC_CKE_AF               GPIO_AF_FMC

///*UDQM LDQM*/
//#define FMC_UDQM_GPIO_PORT        GPIOE
//#define FMC_UDQM_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_UDQM_GPIO_PIN         GPIO_PIN_1
//#define FMC_UDQM_PINSOURCE        GPIO_PinSource1
//#define FMC_UDQM_AF               GPIO_AF_FMC

//#define FMC_LDQM_GPIO_PORT        GPIOE
//#define FMC_LDQM_GPIO_CLK         __HAL_RCC_GPIOE_CLK_ENABLE()
//#define FMC_LDQM_GPIO_PIN         GPIO_PIN_0
//#define FMC_LDQM_PINSOURCE        GPIO_PinSource0
//#define FMC_LDQM_AF               GPIO_AF_FMC


///** @defgroup STM32429 SDRAM函数
//  * @{
//  */ 
//void  SDRAM_Init(void);
//void  SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize);
//void  SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize);
//uint8_t SDRAM_Test(void);




#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"

//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=10 
//对IS61LV25616/IS62WV25616,地址线范围为A0~A17 
//对IS61LV51216/IS62WV51216,地址线范围为A0~A18
#define Bank1_SRAM4_ADDR    ((uint32_t)(0x6C000000))		

#define IS62WV51216_SIZE 0x100000  //512*16/2bits = 0x100000  ，1M字节


//#define FSMC_GPIO_AF             GPIO_AF_FSMC

///*A地址信号线*/    
//#define FSMC_A0_GPIO_PORT        GPIOF
//#define FSMC_A0_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A0_GPIO_PIN         GPIO_Pin_0
//#define FSMC_A0_GPIO_PinSource   GPIO_PinSource0

//#define FSMC_A1_GPIO_PORT        GPIOF
//#define FSMC_A1_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A1_GPIO_PIN         GPIO_Pin_1
//#define FSMC_A1_GPIO_PinSource   GPIO_PinSource1

//#define FSMC_A2_GPIO_PORT        GPIOF
//#define FSMC_A2_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A2_GPIO_PIN         GPIO_Pin_2
//#define FSMC_A2_GPIO_PinSource   GPIO_PinSource2

//#define FSMC_A3_GPIO_PORT        GPIOF
//#define FSMC_A3_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A3_GPIO_PIN         GPIO_Pin_3
//#define FSMC_A3_GPIO_PinSource   GPIO_PinSource3

//#define FSMC_A4_GPIO_PORT        GPIOF
//#define FSMC_A4_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A4_GPIO_PIN         GPIO_Pin_4
//#define FSMC_A4_GPIO_PinSource   GPIO_PinSource4

//#define FSMC_A5_GPIO_PORT        GPIOF
//#define FSMC_A5_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A5_GPIO_PIN         GPIO_Pin_5
//#define FSMC_A5_GPIO_PinSource   GPIO_PinSource5

//#define FSMC_A6_GPIO_PORT        GPIOF
//#define FSMC_A6_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A6_GPIO_PIN         GPIO_Pin_12
//#define FSMC_A6_GPIO_PinSource   GPIO_PinSource12

//#define FSMC_A7_GPIO_PORT        GPIOF
//#define FSMC_A7_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A7_GPIO_PIN         GPIO_Pin_13
//#define FSMC_A7_GPIO_PinSource   GPIO_PinSource13

//#define FSMC_A8_GPIO_PORT        GPIOF
//#define FSMC_A8_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A8_GPIO_PIN         GPIO_Pin_14
//#define FSMC_A8_GPIO_PinSource   GPIO_PinSource14

//#define FSMC_A9_GPIO_PORT        GPIOF
//#define FSMC_A9_GPIO_CLK         RCC_AHB1Periph_GPIOF
//#define FSMC_A9_GPIO_PIN         GPIO_Pin_15
//#define FSMC_A9_GPIO_PinSource   GPIO_PinSource15

//#define FSMC_A10_GPIO_PORT        GPIOG
//#define FSMC_A10_GPIO_CLK         RCC_AHB1Periph_GPIOG
//#define FSMC_A10_GPIO_PIN         GPIO_Pin_0
//#define FSMC_A10_GPIO_PinSource   GPIO_PinSource0

//#define FSMC_A11_GPIO_PORT        GPIOG
//#define FSMC_A11_GPIO_CLK         RCC_AHB1Periph_GPIOG
//#define FSMC_A11_GPIO_PIN         GPIO_Pin_1
//#define FSMC_A11_GPIO_PinSource   GPIO_PinSource1

//#define FSMC_A12_GPIO_PORT        GPIOG
//#define FSMC_A12_GPIO_CLK         RCC_AHB1Periph_GPIOG
//#define FSMC_A12_GPIO_PIN         GPIO_Pin_2
//#define FSMC_A12_GPIO_PinSource   GPIO_PinSource2

//#define FSMC_A13_GPIO_PORT        GPIOG
//#define FSMC_A13_GPIO_CLK         RCC_AHB1Periph_GPIOG
//#define FSMC_A13_GPIO_PIN         GPIO_Pin_3
//#define FSMC_A13_GPIO_PinSource   GPIO_PinSource3

//#define FSMC_A14_GPIO_PORT        GPIOG
//#define FSMC_A14_GPIO_CLK         RCC_AHB1Periph_GPIOG
//#define FSMC_A14_GPIO_PIN         GPIO_Pin_4
//#define FSMC_A14_GPIO_PinSource   GPIO_PinSource4

//#define FSMC_A15_GPIO_PORT        GPIOG
//#define FSMC_A15_GPIO_CLK         RCC_AHB1Periph_GPIOG
//#define FSMC_A15_GPIO_PIN         GPIO_Pin_5
//#define FSMC_A15_GPIO_PinSource   GPIO_PinSource5

//#define FSMC_A16_GPIO_PORT        GPIOD
//#define FSMC_A16_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_A16_GPIO_PIN         GPIO_Pin_11
//#define FSMC_A16_GPIO_PinSource   GPIO_PinSource11

//#define FSMC_A17_GPIO_PORT        GPIOD
//#define FSMC_A17_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_A17_GPIO_PIN         GPIO_Pin_12
//#define FSMC_A17_GPIO_PinSource   GPIO_PinSource12

//#define FSMC_A18_GPIO_PORT        GPIOD
//#define FSMC_A18_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_A18_GPIO_PIN         GPIO_Pin_13
//#define FSMC_A18_GPIO_PinSource   GPIO_PinSource13

///*D 数据信号线*/
//#define FSMC_D0_GPIO_PORT        GPIOD
//#define FSMC_D0_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_D0_GPIO_PIN         GPIO_Pin_14
//#define FSMC_D0_GPIO_PinSource   GPIO_PinSource14

//#define FSMC_D1_GPIO_PORT        GPIOD
//#define FSMC_D1_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_D1_GPIO_PIN         GPIO_Pin_15
//#define FSMC_D1_GPIO_PinSource   GPIO_PinSource15

//#define FSMC_D2_GPIO_PORT        GPIOD
//#define FSMC_D2_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_D2_GPIO_PIN         GPIO_Pin_0
//#define FSMC_D2_GPIO_PinSource   GPIO_PinSource0

//#define FSMC_D3_GPIO_PORT        GPIOD
//#define FSMC_D3_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_D3_GPIO_PIN         GPIO_Pin_1
//#define FSMC_D3_GPIO_PinSource   GPIO_PinSource1

//#define FSMC_D4_GPIO_PORT        GPIOE
//#define FSMC_D4_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D4_GPIO_PIN         GPIO_Pin_7
//#define FSMC_D4_GPIO_PinSource   GPIO_PinSource7

//#define FSMC_D5_GPIO_PORT        GPIOE
//#define FSMC_D5_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D5_GPIO_PIN         GPIO_Pin_8
//#define FSMC_D5_GPIO_PinSource   GPIO_PinSource8

//#define FSMC_D6_GPIO_PORT        GPIOE
//#define FSMC_D6_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D6_GPIO_PIN         GPIO_Pin_9
//#define FSMC_D6_GPIO_PinSource   GPIO_PinSource9

//#define FSMC_D7_GPIO_PORT        GPIOE
//#define FSMC_D7_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D7_GPIO_PIN         GPIO_Pin_10
//#define FSMC_D7_GPIO_PinSource   GPIO_PinSource10

//#define FSMC_D8_GPIO_PORT        GPIOE
//#define FSMC_D8_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D8_GPIO_PIN         GPIO_Pin_11
//#define FSMC_D8_GPIO_PinSource   GPIO_PinSource11

//#define FSMC_D9_GPIO_PORT        GPIOE
//#define FSMC_D9_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D9_GPIO_PIN         GPIO_Pin_12
//#define FSMC_D9_GPIO_PinSource   GPIO_PinSource12

//#define FSMC_D10_GPIO_PORT        GPIOE
//#define FSMC_D10_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D10_GPIO_PIN         GPIO_Pin_13
//#define FSMC_D10_GPIO_PinSource   GPIO_PinSource13

//#define FSMC_D11_GPIO_PORT        GPIOE
//#define FSMC_D11_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D11_GPIO_PIN         GPIO_Pin_14
//#define FSMC_D11_GPIO_PinSource   GPIO_PinSource14

//#define FSMC_D12_GPIO_PORT        GPIOE
//#define FSMC_D12_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_D12_GPIO_PIN         GPIO_Pin_15
//#define FSMC_D12_GPIO_PinSource   GPIO_PinSource15

//#define FSMC_D13_GPIO_PORT        GPIOD
//#define FSMC_D13_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_D13_GPIO_PIN         GPIO_Pin_8
//#define FSMC_D13_GPIO_PinSource   GPIO_PinSource8

//#define FSMC_D14_GPIO_PORT        GPIOD
//#define FSMC_D14_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_D14_GPIO_PIN         GPIO_Pin_9
//#define FSMC_D14_GPIO_PinSource   GPIO_PinSource9

//#define FSMC_D15_GPIO_PORT        GPIOD
//#define FSMC_D15_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_D15_GPIO_PIN         GPIO_Pin_10
//#define FSMC_D15_GPIO_PinSource   GPIO_PinSource10

///*控制信号线*/  
///*CS片选*/
///*NE4 ,对应的基地址0x6C000000*/
//#define FSMC_CS_GPIO_PORT        GPIOG
//#define FSMC_CS_GPIO_CLK         RCC_AHB1Periph_GPIOG
//#define FSMC_CS_GPIO_PIN         GPIO_Pin_12
//#define FSMC_CS_GPIO_PinSource   GPIO_PinSource12

///*WE写使能*/
//#define FSMC_WE_GPIO_PORT        GPIOD
//#define FSMC_WE_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_WE_GPIO_PIN         GPIO_Pin_5
//#define FSMC_WE_GPIO_PinSource   GPIO_PinSource5

///*OE读使能*/
//#define FSMC_OE_GPIO_PORT        GPIOD
//#define FSMC_OE_GPIO_CLK         RCC_AHB1Periph_GPIOD
//#define FSMC_OE_GPIO_PIN         GPIO_Pin_4
//#define FSMC_OE_GPIO_PinSource   GPIO_PinSource4


///*UB数据掩码*/
//#define FSMC_UDQM_GPIO_PORT        GPIOE
//#define FSMC_UDQM_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_UDQM_GPIO_PIN         GPIO_Pin_1
//#define FSMC_UDQM_GPIO_PinSource   GPIO_PinSource1

///*LB数据掩码*/
//#define FSMC_LDQM_GPIO_PORT        GPIOE
//#define FSMC_LDQM_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define FSMC_LDQM_GPIO_PIN         GPIO_Pin_0
//#define FSMC_LDQM_GPIO_PinSource   GPIO_PinSource0


/*信息输出*/
#define SRAM_DEBUG_ON         1

#define SRAM_INFO(fmt,arg...)           printf("<<-SRAM-INFO->> "fmt"\n",##arg)
#define SRAM_ERROR(fmt,arg...)          printf("<<-SRAM-ERROR->> "fmt"\n",##arg)
#define SRAM_DEBUG(fmt,arg...)          do{\
                                          if(SRAM_DEBUG_ON)\
                                          printf("<<-SRAM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)




											  
void FSMC_SRAM_Init(void);
void FSMC_SRAM_MspInit(void);                                          
void FSMC_SRAM_WriteBuffer(uint8_t* pBuffer,uint32_t WriteAddr,uint32_t NumHalfwordToWrite);
void FSMC_SRAM_ReadBuffer(uint8_t* pBuffer,uint32_t ReadAddr,uint32_t NumHalfwordToRead);

uint8_t SRAM_Test(void);


#endif /* __SDRAM_H */
