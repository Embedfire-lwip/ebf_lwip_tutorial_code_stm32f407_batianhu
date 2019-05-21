/**
  ******************************************************************************
  * @file    bsp_sdram.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   sdram应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板  
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./sdram/bsp_sdram.h"  

static SRAM_HandleTypeDef  SRAM_Handler;
static FMC_NORSRAM_TimingTypeDef Timing;

/**
  * @brief  Initializes SRAM MSP.
  */
 void FSMC_SRAM_MspInit(void)
{
//  static DMA_HandleTypeDef dmaHandle;
  GPIO_InitTypeDef GPIO_Init_Structure;
//  SRAM_HandleTypeDef *hsram = & SRAM_Handler;
    
  /* Enable FMC clock */
  __HAL_RCC_FSMC_CLK_ENABLE();
  
//  /* Enable chosen DMAx clock */
//  __SRAM_DMAx_CLK_ENABLE();

  /* Enable GPIOs clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  
  /* Common GPIO configuration */
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_PULLUP;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_HIGH;
  GPIO_Init_Structure.Alternate = GPIO_AF12_FSMC;
  
  /* GPIOD configuration */
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8     |\
                              GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |\
                              GPIO_PIN_14 | GPIO_PIN_15;
   
  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

  /* GPIOE configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7     |\
                              GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |\
                              GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);
  
  /* GPIOF configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOF, &GPIO_Init_Structure);
  
  /* GPIOG configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5 | GPIO_PIN_12;
  
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);  
  

//  /* Configure common DMA parameters */
//  dmaHandle.Init.Channel             = SRAM_DMAx_CHANNEL;
//  dmaHandle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
//  dmaHandle.Init.PeriphInc           = DMA_PINC_ENABLE;
//  dmaHandle.Init.MemInc              = DMA_MINC_ENABLE;
//  dmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
//  dmaHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
//  dmaHandle.Init.Mode                = DMA_NORMAL;
//  dmaHandle.Init.Priority            = DMA_PRIORITY_HIGH;
//  dmaHandle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
//  dmaHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
//  dmaHandle.Init.MemBurst            = DMA_MBURST_INC8;
//  dmaHandle.Init.PeriphBurst         = DMA_PBURST_INC8; 
//  
//  dmaHandle.Instance = SRAM_DMAx_STREAM;
//  
//   /* Associate the DMA handle */
//  __HAL_LINKDMA(hsram, hdma, dmaHandle);
//  
//  /* Deinitialize the stream for new transfer */
//  HAL_DMA_DeInit(&dmaHandle);
//  
//  /* Configure the DMA stream */
//  HAL_DMA_Init(&dmaHandle);
//    
//  /* NVIC configuration for DMA transfer complete interrupt */
//  HAL_NVIC_SetPriority(SRAM_DMAx_IRQn, 0x0F, 0);
//  HAL_NVIC_EnableIRQ(SRAM_DMAx_IRQn);   
}


/**
  * @brief  Initializes the SRAM device.
  * @retval SRAM status
  */
void FSMC_SRAM_Init(void)
{ 
   SRAM_Handler.Instance = FMC_NORSRAM_DEVICE;
   SRAM_Handler.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  
  /* SRAM device configuration */  
  Timing.AddressSetupTime      = 0x00;
  Timing.AddressHoldTime       = 0x00;
  Timing.DataSetupTime         = 0x08;
  Timing.BusTurnAroundDuration = 0x00;
  Timing.CLKDivision           = 0x00;
  Timing.DataLatency           = 0x00;
  Timing.AccessMode            = FSMC_ACCESS_MODE_A;
 
  SRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK4;     					        //使用NE4
	SRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 	//地址/数据线不复用
	SRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   				    //SRAM
	SRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; 	//16位数据宽度
	SRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE; //是否使能突发访问,仅对同步突发存储器有效,此处未用到
	SRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;//等待信号的极性,仅在突发模式访问下有用
	SRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   	//存储器是在等待周期之前的一个时钟周期还是等待周期期间使能NWAIT
	SRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    	//存储器写使能
	SRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;           	//等待使能位,此处未用到
	SRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_DISABLE;        	//读写使用相同的时序
	SRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;	//是否使能同步传输模式下的等待信号,此处未用到
	SRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           	  //禁止突发写
	SRAM_Handler.Init.ContinuousClock=FSMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
  
//  sramHandle.Init.NSBank             = FSMC_NORSRAM_BANK2;
//  sramHandle.Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE;
//  sramHandle.Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM;
//  sramHandle.Init.MemoryDataWidth    = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
//  sramHandle.Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE;
//  sramHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
//  sramHandle.Init.WrapMode           = FSMC_WRAP_MODE_DISABLE;
//  sramHandle.Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS;
//  sramHandle.Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE;
//  sramHandle.Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE;
//  sramHandle.Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE;
//  sramHandle.Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
//  sramHandle.Init.WriteBurst         = SRAM_WRITEBURST;
    
  /* SRAM controller initialization */
  FSMC_SRAM_MspInit();
  HAL_SRAM_Init(& SRAM_Handler, &Timing, &Timing);
//  if(HAL_SRAM_Init(&sramHandle, &Timing, &Timing) != HAL_OK)
//  {
//    return SRAM_ERROR;
//  }
//  else
//  {
//    return SRAM_OK;
//  }
}


















//static FMC_SDRAM_CommandTypeDef Command;
//SDRAM_HandleTypeDef hsdram1;
//#define sdramHandle hsdram1
///**
//  * @brief  延迟一段时间
//  * @param  延迟的时间长度
//  * @retval None
//  */
//static void SDRAM_delay(__IO uint32_t nCount)
//{
//  __IO uint32_t index = 0; 
//  for(index = (100000 * nCount); index != 0; index--)
//  {
//  }
//}

///**
//  * @brief  初始化控制SDRAM的IO
//  * @param  无
//  * @retval 无
//  */
//static void SDRAM_GPIO_Config(void)
//{		
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//  /* 使能SDRAM相关的GPIO时钟 */

//  /*地址信号线*/
//  FMC_A0_GPIO_CLK;  FMC_A1_GPIO_CLK;  FMC_A2_GPIO_CLK;
//  FMC_A3_GPIO_CLK;FMC_A4_GPIO_CLK;FMC_A5_GPIO_CLK;
//  FMC_A6_GPIO_CLK; FMC_A7_GPIO_CLK; FMC_A8_GPIO_CLK;
//  FMC_A9_GPIO_CLK; FMC_A10_GPIO_CLK;FMC_A11_GPIO_CLK; 
//  /*数据信号线*/
//  FMC_D0_GPIO_CLK; FMC_D1_GPIO_CLK ; FMC_D2_GPIO_CLK ; 
//  FMC_D3_GPIO_CLK ; FMC_D4_GPIO_CLK ; FMC_D5_GPIO_CLK ;
//  FMC_D6_GPIO_CLK; FMC_D7_GPIO_CLK ; FMC_D8_GPIO_CLK ;
//  FMC_D9_GPIO_CLK ;FMC_D10_GPIO_CLK; FMC_D11_GPIO_CLK;
//  FMC_D12_GPIO_CLK; FMC_D13_GPIO_CLK; FMC_D14_GPIO_CLK;
//  FMC_D15_GPIO_CLK;  
//  /*控制信号线*/
//  FMC_CS_GPIO_CLK ; FMC_BA0_GPIO_CLK; FMC_BA1_GPIO_CLK ;
//  FMC_WE_GPIO_CLK ; FMC_RAS_GPIO_CLK ; FMC_CAS_GPIO_CLK;
//  FMC_CLK_GPIO_CLK ; FMC_CKE_GPIO_CLK; FMC_UDQM_GPIO_CLK;
//  FMC_LDQM_GPIO_CLK;


//  
//  /*-- GPIO 配置 -----------------------------------------------------*/

//  /* 通用 GPIO 配置 */       
//  GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;//配置为复用功能
//  GPIO_InitStructure.Pull      = GPIO_PULLUP;
//  GPIO_InitStructure.Speed     = GPIO_SPEED_FAST;
//  GPIO_InitStructure.Alternate = GPIO_AF12_FMC;
//  
//  
//  /*地址信号线 针对引脚配置*/
//  GPIO_InitStructure.Pin = FMC_A0_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A0_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A1_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A1_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A2_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A2_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A3_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A3_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A4_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A4_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A5_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A5_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A6_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A6_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A7_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A7_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A8_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A8_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A9_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A9_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A10_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A10_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A11_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A11_GPIO_PORT, &GPIO_InitStructure);

//  
//  
//  /*数据信号线 针对引脚配置*/
//  GPIO_InitStructure.Pin = FMC_D0_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D0_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D1_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D1_GPIO_PORT, &GPIO_InitStructure);

//    
//  GPIO_InitStructure.Pin = FMC_D2_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D2_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D3_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D3_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D4_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D4_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D5_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D5_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D6_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D6_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D7_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D7_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D8_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D8_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D9_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D9_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D10_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D10_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D11_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D11_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D12_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D12_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D13_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D13_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D14_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D14_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D15_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D15_GPIO_PORT, &GPIO_InitStructure);

//  
//  /*控制信号线*/
//  GPIO_InitStructure.Pin = FMC_CS_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_CS_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_BA0_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_BA0_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_BA1_GPIO_PIN;
//  HAL_GPIO_Init(FMC_BA1_GPIO_PORT, &GPIO_InitStructure);

//    
//  GPIO_InitStructure.Pin = FMC_WE_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_WE_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_RAS_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_RAS_GPIO_PORT, &GPIO_InitStructure);

//    
//  GPIO_InitStructure.Pin = FMC_CAS_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_CAS_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_CLK_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_CLK_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_CKE_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_CKE_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_UDQM_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_UDQM_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_LDQM_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_LDQM_GPIO_PORT, &GPIO_InitStructure);

//		
//}

///**
//  * @brief  对SDRAM芯片进行初始化配置
//  * @param  None. 
//  * @retval None.
//  */
//static void SDRAM_InitSequence(void)
//{
//  uint32_t tmpr = 0;
//  
///* Step 3 --------------------------------------------------------------------*/
//  /* 配置命令：开启提供给SDRAM的时钟 */
//  Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
//  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//  Command.AutoRefreshNumber = 1;
//  Command.ModeRegisterDefinition = 0;
///* Send the command */
//  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

//  /* Step 2: Insert 100 us minimum delay */ 
//  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
//  SDRAM_delay(1);
//    
///* Step 5 --------------------------------------------------------------------*/
//  /* 配置命令：对所有的bank预充电 */ 
//  Command.CommandMode = FMC_SDRAM_CMD_PALL;
//  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//  Command.AutoRefreshNumber = 1;
//  Command.ModeRegisterDefinition = 0;
///* Send the command */
//  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);   
//  
///* Step 6 --------------------------------------------------------------------*/
//  /* 配置命令：自动刷新 */   
//  Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
//  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//  Command.AutoRefreshNumber = 4;
//  Command.ModeRegisterDefinition = 0;
// /* Send the command */
//  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
//  
///* Step 7 --------------------------------------------------------------------*/
//  /* 设置sdram寄存器配置 */
//  tmpr = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
//                   SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
//                   SDRAM_MODEREG_CAS_LATENCY_3           |
//                   SDRAM_MODEREG_OPERATING_MODE_STANDARD |
//                   SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
//  
//  /* 配置命令：设置SDRAM寄存器 */
//  Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
//  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//  Command.AutoRefreshNumber = 1;
//  Command.ModeRegisterDefinition = tmpr;
//  /* Send the command */
//  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
//  
///* Step 8 --------------------------------------------------------------------*/

//  /* 设置刷新计数器 */
//  /* (15.62 us x Freq) - 20 */
//	  /* Step 6: Set the refresh rate counter */
//  /* Set the device refresh rate */
//  HAL_SDRAM_ProgramRefreshRate(&sdramHandle, 1386); 
////  FMC_SetRefreshCount(1386);
////  /* 发送上述命令*/
////  while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET)
////  {
////  }
//}


///**
//  * @brief  初始化配置使用SDRAM的FMC及GPIO接口，
//  *         本函数在SDRAM读写操作前需要被调用
//  * @param  None
//  * @retval None
//  */
//void SDRAM_Init(void)
//{
//  //FMC_SDRAMInitTypeDef  FMC_SDRAMInitStructure;
////  FMC_SDRAMTimingInitTypeDef  FMC_SDRAMTimingInitStructure; 
//  
//  /* 配置FMC接口相关的 GPIO*/
//  SDRAM_GPIO_Config();
//  
//  /* 使能 FMC 时钟 */
//	__HAL_RCC_FMC_CLK_ENABLE();
////  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);
// 
////  /* 配置 FMC 相关参数 ---------------------------------------------------------*/
////  /* SDCLK： 90 Mhz (HCLK/2 :180Mhz/2) */
////  /* TMRD: 2 Clock cycles */
////  FMC_SDRAMTimingInitStructure.FMC_LoadToActiveDelay    = 2;      
////  /* TXSR: min=70ns (7x11.11ns) */
////  FMC_SDRAMTimingInitStructure.FMC_ExitSelfRefreshDelay = 7;
////  /* TRAS: min=42ns (4x11.11ns) max=120k (ns) */
////  FMC_SDRAMTimingInitStructure.FMC_SelfRefreshTime      = 4;
////  /* TRC:  min=70 (7x11.11ns) */        
////  FMC_SDRAMTimingInitStructure.FMC_RowCycleDelay        = 7;         
////  /* TWR:  min=1+ 7ns (1+1x11.11ns) */
////  FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime    = 2;      
////  /* TRP:  20ns => 2x11.11ns */
////  FMC_SDRAMTimingInitStructure.FMC_RPDelay              = 2;                
////  /* TRCD: 20ns => 2x11.11ns */
////  FMC_SDRAMTimingInitStructure.FMC_RCDDelay             = 2;

/////* FMC SDRAM 控制配置 */
////  FMC_SDRAMInitStructure.FMC_Bank = FMC_BANK_SDRAM;
////  /* 行地址线宽度: [7:0] */
////  FMC_SDRAMInitStructure.FMC_ColumnBitsNumber = FMC_ColumnBits_Number_8b;
////  /* 列地址线宽度: [11:0] */
////  FMC_SDRAMInitStructure.FMC_RowBitsNumber = FMC_RowBits_Number_12b;
////  /* 数据线宽度 */
////  FMC_SDRAMInitStructure.FMC_SDMemoryDataWidth = SDRAM_MEMORY_WIDTH;
////  /* SDRAM内部bank数量*/
////  FMC_SDRAMInitStructure.FMC_InternalBankNumber = FMC_InternalBank_Number_4;
////  /* CAS潜伏期 */
////  FMC_SDRAMInitStructure.FMC_CASLatency = SDRAM_CAS_LATENCY; 
////  /* 禁止写保护*/
////  FMC_SDRAMInitStructure.FMC_WriteProtection = FMC_Write_Protection_Disable;
////  /* SDCLK时钟分频因子，SDCLK = HCLK/SDCLOCK_PERIOD*/
////  FMC_SDRAMInitStructure.FMC_SDClockPeriod = SDCLOCK_PERIOD; 
////  /* 突发读模式设置*/  
////  FMC_SDRAMInitStructure.FMC_ReadBurst = SDRAM_READBURST;
////  /* 读延迟配置 */
////  FMC_SDRAMInitStructure.FMC_ReadPipeDelay = FMC_ReadPipe_Delay_1;
////  /* SDRAM时序参数 */
////  FMC_SDRAMInitStructure.FMC_SDRAMTimingStruct = &FMC_SDRAMTimingInitStructure;
////  
////  /* FMC SDRAM bank initialization */
////  FMC_SDRAMInit(&FMC_SDRAMInitStructure); 
//  FMC_SDRAM_TimingTypeDef SdramTiming;

//  /** Perform the SDRAM1 memory initialization sequence
//  */
//  hsdram1.Instance = FMC_SDRAM_DEVICE;
//  /* hsdram1.Init */
//  hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
//  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
//  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
//  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
//  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
//  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
//  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
//  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
//  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
//  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
//  /* SdramTiming */
//  SdramTiming.LoadToActiveDelay = 2;
//  SdramTiming.ExitSelfRefreshDelay = 7;
//  SdramTiming.SelfRefreshTime = 4;
//  SdramTiming.RowCycleDelay = 7;
//  SdramTiming.WriteRecoveryTime = 2;
//  SdramTiming.RPDelay = 2;
//  SdramTiming.RCDDelay = 2;

//  HAL_SDRAM_Init(&hsdram1, &SdramTiming);  
//  /* FMC SDRAM device initialization sequence */
//  SDRAM_InitSequence(); 
//  
//}



///**
//  * @brief  以“字”为单位向sdram写入数据 
//  * @param  pBuffer: 指向数据的指针 
//  * @param  uwWriteAddress: 要写入的SDRAM内部地址
//  * @param  uwBufferSize: 要写入数据大小
//  * @retval None.
//  */
//void SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
//{
//  __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;

//  /* 禁止写保护 */
//  HAL_SDRAM_WriteProtection_Disable(&hsdram1);
//  /* 检查SDRAM标志，等待至SDRAM空闲 */ 
//  while(HAL_SDRAM_GetState(&hsdram1) != RESET)
//  {
//  }

//  /* 循环写入数据 */
//  for (; uwBufferSize != 0; uwBufferSize--) 
//  {
//    /* 发送数据到SDRAM */
//    *(uint32_t *) (SDRAM_BANK_ADDR + write_pointer) = *pBuffer++;

//    /* 地址自增*/
//    write_pointer += 4;
//  }
//    
//}

///**
//  * @brief  从SDRAM中读取数据 
//  * @param  pBuffer: 指向存储数据的buffer
//  * @param  ReadAddress: 要读取数据的地十
//  * @param  uwBufferSize: 要读取的数据大小
//  * @retval None.
//  */
//void SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
//{
//  __IO uint32_t write_pointer = (uint32_t)uwReadAddress;
//  
//   
//  /* 检查SDRAM标志，等待至SDRAM空闲 */  
//  while ( HAL_SDRAM_GetState(&hsdram1) != RESET)
//  {
//  }
//  
//  /*读取数据 */
//  for(; uwBufferSize != 0x00; uwBufferSize--)
//  {
//   *pBuffer++ = *(__IO uint32_t *)(SDRAM_BANK_ADDR + write_pointer );
//    
//   /* 地址自增*/
//    write_pointer += 4;
//  } 
//}


///**
//  * @brief  测试SDRAM是否正常 
//  * @param  None
//  * @retval 正常返回1，异常返回0
//  */
//uint8_t SDRAM_Test(void)
//{
//  /*写入数据计数器*/
//  uint32_t counter=0;
//  
//  /* 8位的数据 */
//  uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;  
//  
//  /* 16位的数据 */
//  uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0; 
//  
//  SDRAM_INFO("正在检测SDRAM，以8位、16位的方式读写sdram...");


//  /*按8位格式读写数据，并校验*/
//  
//  /* 把SDRAM数据全部重置为0 ，IS42S16400J_SIZE是以8位为单位的 */
//  for (counter = 0x00; counter < IS42S16400J_SIZE; counter++)
//  {
//    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
//  }
//  
//  /* 向整个SDRAM写入数据  8位 */
//  for (counter = 0; counter < IS42S16400J_SIZE; counter++)
//  {
//    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
//  }
//  
//  /* 读取 SDRAM 数据并检测*/
//  for(counter = 0; counter<IS42S16400J_SIZE;counter++ )
//  {
//    ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);  //从该地址读出数据
//    
//    if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))      //检测数据，若不相等，跳出函数,返回检测失败结果。
//    {
//      SDRAM_ERROR("8位数据读写错误！");
//      return 0;
//    }
//  }
//	
//  
//  /*按16位格式读写数据，并检测*/
//  
//  /* 把SDRAM数据全部重置为0 */
//  for (counter = 0x00; counter < IS42S16400J_SIZE/2; counter++)
//  {
//    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)0x00;
//  }
//  
//  /* 向整个SDRAM写入数据  16位 */
//  for (counter = 0; counter < IS42S16400J_SIZE/2; counter++)
//  {
//    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
//  }
//  
//    /* 读取 SDRAM 数据并检测*/
//  for(counter = 0; counter<IS42S16400J_SIZE/2;counter++ )
//  {
//    uhReaddata_16b = *(__IO uint16_t*)(SDRAM_BANK_ADDR + 2*counter);  //从该地址读出数据
//    
//    if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))      //检测数据，若不相等，跳出函数,返回检测失败结果。
//    {
//      SDRAM_ERROR("16位数据读写错误！");

//      return 0;
//    }
//  }

//  
//  SDRAM_INFO("SDRAM读写测试正常！"); 
//  /*检测正常，return 1 */
//  return 1;
//  

//}




//#include "./sram/bsp_sram.h"	  



///**
//  * @brief  初始化控制SRAM的IO
//  * @param  无
//  * @retval 无
//  */
//static void SRAM_GPIO_Config(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;
// 
//  /* 使能SRAM相关的GPIO时钟 */

//                         /*地址信号线*/
//  RCC_AHB1PeriphClockCmd(FSMC_A0_GPIO_CLK | FSMC_A1_GPIO_CLK | FSMC_A2_GPIO_CLK | 
//                         FSMC_A3_GPIO_CLK | FSMC_A4_GPIO_CLK | FSMC_A5_GPIO_CLK |
//                         FSMC_A6_GPIO_CLK | FSMC_A7_GPIO_CLK | FSMC_A8_GPIO_CLK |
//                         FSMC_A9_GPIO_CLK | FSMC_A10_GPIO_CLK| FSMC_A11_GPIO_CLK| 
//												 FSMC_A12_GPIO_CLK| FSMC_A13_GPIO_CLK|FSMC_A14_GPIO_CLK|
//												 FSMC_A15_GPIO_CLK|FSMC_A16_GPIO_CLK|FSMC_A17_GPIO_CLK|FSMC_A18_GPIO_CLK|
//                         /*数据信号线*/
//                         FSMC_D0_GPIO_CLK | FSMC_D1_GPIO_CLK | FSMC_D2_GPIO_CLK | 
//                         FSMC_D3_GPIO_CLK | FSMC_D4_GPIO_CLK | FSMC_D5_GPIO_CLK |
//                         FSMC_D6_GPIO_CLK | FSMC_D7_GPIO_CLK | FSMC_D8_GPIO_CLK |
//                         FSMC_D9_GPIO_CLK | FSMC_D10_GPIO_CLK| FSMC_D11_GPIO_CLK|
//                         FSMC_D12_GPIO_CLK| FSMC_D13_GPIO_CLK| FSMC_D14_GPIO_CLK|
//                         FSMC_D15_GPIO_CLK|  
//                         /*控制信号线*/
//                         FSMC_CS_GPIO_CLK  | FSMC_WE_GPIO_CLK | FSMC_OE_GPIO_CLK |
//                         FSMC_UDQM_GPIO_CLK|FSMC_LDQM_GPIO_CLK, ENABLE);
//												 


//	 /*-- GPIO 配置 -----------------------------------------------------*/

//  /* 通用 GPIO 配置 */
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  
//  /*A地址信号线 针对引脚配置*/
//  GPIO_InitStructure.GPIO_Pin = FSMC_A0_GPIO_PIN; 
//  GPIO_Init(FSMC_A0_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A0_GPIO_PORT,FSMC_A0_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A1_GPIO_PIN; 
//  GPIO_Init(FSMC_A1_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A1_GPIO_PORT,FSMC_A1_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A2_GPIO_PIN; 
//  GPIO_Init(FSMC_A2_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A2_GPIO_PORT,FSMC_A2_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A3_GPIO_PIN; 
//  GPIO_Init(FSMC_A3_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A3_GPIO_PORT,FSMC_A3_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A4_GPIO_PIN; 
//  GPIO_Init(FSMC_A4_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A4_GPIO_PORT,FSMC_A4_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A5_GPIO_PIN; 
//  GPIO_Init(FSMC_A5_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A5_GPIO_PORT,FSMC_A5_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A6_GPIO_PIN; 
//  GPIO_Init(FSMC_A6_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A6_GPIO_PORT,FSMC_A6_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A7_GPIO_PIN; 
//  GPIO_Init(FSMC_A7_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A7_GPIO_PORT,FSMC_A7_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A8_GPIO_PIN; 
//  GPIO_Init(FSMC_A8_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A8_GPIO_PORT,FSMC_A8_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A9_GPIO_PIN; 
//  GPIO_Init(FSMC_A9_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A9_GPIO_PORT,FSMC_A9_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A10_GPIO_PIN; 
//  GPIO_Init(FSMC_A10_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A10_GPIO_PORT,FSMC_A10_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A11_GPIO_PIN; 
//  GPIO_Init(FSMC_A11_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A11_GPIO_PORT,FSMC_A11_GPIO_PinSource,FSMC_GPIO_AF);
//	
//  GPIO_InitStructure.GPIO_Pin = FSMC_A12_GPIO_PIN; 
//  GPIO_Init(FSMC_A12_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A12_GPIO_PORT,FSMC_A12_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A13_GPIO_PIN; 
//  GPIO_Init(FSMC_A13_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A13_GPIO_PORT,FSMC_A13_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A14_GPIO_PIN; 
//  GPIO_Init(FSMC_A14_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A14_GPIO_PORT,FSMC_A14_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A15_GPIO_PIN; 
//  GPIO_Init(FSMC_A15_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A15_GPIO_PORT,FSMC_A15_GPIO_PinSource,FSMC_GPIO_AF);  
//	
//  GPIO_InitStructure.GPIO_Pin = FSMC_A16_GPIO_PIN; 
//  GPIO_Init(FSMC_A16_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A16_GPIO_PORT,FSMC_A16_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A17_GPIO_PIN; 
//  GPIO_Init(FSMC_A17_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A17_GPIO_PORT,FSMC_A17_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A18_GPIO_PIN; 
//  GPIO_Init(FSMC_A18_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A18_GPIO_PORT,FSMC_A18_GPIO_PinSource,FSMC_GPIO_AF);
//    
//  /*DQ数据信号线 针对引脚配置*/
//  GPIO_InitStructure.GPIO_Pin = FSMC_D0_GPIO_PIN; 
//  GPIO_Init(FSMC_D0_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D0_GPIO_PORT,FSMC_D0_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D1_GPIO_PIN; 
//  GPIO_Init(FSMC_D1_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D1_GPIO_PORT,FSMC_D1_GPIO_PinSource,FSMC_GPIO_AF);
//    
//  GPIO_InitStructure.GPIO_Pin = FSMC_D2_GPIO_PIN; 
//  GPIO_Init(FSMC_D2_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D2_GPIO_PORT,FSMC_D2_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D3_GPIO_PIN; 
//  GPIO_Init(FSMC_D3_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D3_GPIO_PORT,FSMC_D3_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D4_GPIO_PIN; 
//  GPIO_Init(FSMC_D4_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D4_GPIO_PORT,FSMC_D4_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D5_GPIO_PIN; 
//  GPIO_Init(FSMC_D5_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D5_GPIO_PORT,FSMC_D5_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D6_GPIO_PIN; 
//  GPIO_Init(FSMC_D6_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D6_GPIO_PORT,FSMC_D6_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D7_GPIO_PIN; 
//  GPIO_Init(FSMC_D7_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D7_GPIO_PORT,FSMC_D7_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D8_GPIO_PIN; 
//  GPIO_Init(FSMC_D8_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D8_GPIO_PORT,FSMC_D8_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D9_GPIO_PIN; 
//  GPIO_Init(FSMC_D9_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D9_GPIO_PORT,FSMC_D9_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D10_GPIO_PIN; 
//  GPIO_Init(FSMC_D10_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D10_GPIO_PORT,FSMC_D10_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D11_GPIO_PIN; 
//  GPIO_Init(FSMC_D11_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D11_GPIO_PORT,FSMC_D11_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D12_GPIO_PIN; 
//  GPIO_Init(FSMC_D12_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D12_GPIO_PORT,FSMC_D12_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D13_GPIO_PIN; 
//  GPIO_Init(FSMC_D13_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D13_GPIO_PORT,FSMC_D13_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D14_GPIO_PIN; 
//  GPIO_Init(FSMC_D14_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D14_GPIO_PORT,FSMC_D14_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D15_GPIO_PIN; 
//  GPIO_Init(FSMC_D15_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D15_GPIO_PORT,FSMC_D15_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  /*控制信号线*/
//  GPIO_InitStructure.GPIO_Pin = FSMC_CS_GPIO_PIN; 
//  GPIO_Init(FSMC_CS_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_CS_GPIO_PORT,FSMC_CS_GPIO_PinSource,FSMC_GPIO_AF);
//    
//  GPIO_InitStructure.GPIO_Pin = FSMC_WE_GPIO_PIN; 
//  GPIO_Init(FSMC_WE_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_WE_GPIO_PORT,FSMC_WE_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_OE_GPIO_PIN; 
//  GPIO_Init(FSMC_OE_GPIO_PORT, &GPIO_InitStructure);   
//  GPIO_PinAFConfig(FSMC_OE_GPIO_PORT,FSMC_OE_GPIO_PinSource,FSMC_GPIO_AF);  
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_UDQM_GPIO_PIN; 
//  GPIO_Init(FSMC_UDQM_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_UDQM_GPIO_PORT,FSMC_UDQM_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_LDQM_GPIO_PIN; 
//  GPIO_Init(FSMC_LDQM_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_LDQM_GPIO_PORT,FSMC_LDQM_GPIO_PinSource,FSMC_GPIO_AF); 
//}				  			


///**
//  * @brief  初始化FSMC外设
//  * @param  None. 
//  * @retval None.
//  */
//void FSMC_SRAM_Init(void)
//{	
//	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
//	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;

//	/*初始化SRAM相关的GPIO*/
//	SRAM_GPIO_Config();
//		
//	/*使能FSMC外设时钟*/
//	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);

//	//地址建立时间（ADDSET）为1个HCLK,1/168M = 6ns
//	readWriteTiming.FSMC_AddressSetupTime = 0x00;	

//	//地址保持时间（ADDHLD）模式A未用到
//	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 

//	//数据保持时间（DATAST）+ 1个HCLK = 9/168M=54ns(对EM的SRAM芯片)	
//	readWriteTiming.FSMC_DataSetupTime = 0x08;		  
//	
//	//设置总线转换周期，仅用于复用模式的NOR操作
//	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//	
//	//设置时钟分频，仅用于同步类型的存储器
//	readWriteTiming.FSMC_CLKDivision = 0x00;	

//	//数据保持时间，仅用于同步型的NOR
//	readWriteTiming.FSMC_DataLatency = 0x00;		
//	
//	//选择匹配SRAM的模式
//	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 
//    

//	// 选择FSMC映射的存储区域： Bank1 sram4
//	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
//	
//	//设置地址总线与数据总线是否复用，仅用于NOR
//	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
//	
//	//设置要控制的存储器类型：SRAM类型
//	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;   
//	
//	//存储器数据宽度：16位
//	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; 
//	
//	//设置是否使用突发访问模式，仅用于同步类型的存储器
//	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
//	
//	//设置是否使能等待信号，仅用于同步类型的存储器
//	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
//	
//	//设置等待信号的有效极性，仅用于同步类型的存储器
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
//	
//	//设置是否支持把非对齐的突发操作，仅用于同步类型的存储器
//	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable; 
//	
//	//设置等待信号插入的时间，仅用于同步类型的存储器
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
//	
//	//存储器写使能 
//	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
//	
//	//不使用等待信号
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  		
//	
//	// 不使用扩展模式，读写使用相同的时序
//	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; 
//	
//	//突发写操作
//	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
//	
//	//读写时序配置
//	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
//	
//	//读写同样时序，使用扩展模式时这个配置才有效
//	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; 

//	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

//	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK										  
//											
//}
//	  		



/**
  * @brief  以“字”为单位向sdram写入数据 
  * @param  pBuffer: 指向数据的指针 
  * @param  uwWriteAddress: 要写入的SRAM内部地址
  * @param  uwBufferSize: 要写入数据大小
  * @retval None.
  */
void SRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;
 

  /* 循环写入数据 */
  for (; uwBufferSize != 0; uwBufferSize--) 
  {
    /* 发送数据到SRAM */
    *(uint32_t *) (Bank1_SRAM4_ADDR + write_pointer) = *pBuffer++;

    /* 地址自增*/
    write_pointer += 4;
  }
    
}

/**
  * @brief  从SRAM中读取数据 
  * @param  pBuffer: 指向存储数据的buffer
  * @param  ReadAddress: 要读取数据的地十
  * @param  uwBufferSize: 要读取的数据大小
  * @retval None.
  */
void SRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwReadAddress;
  
  
  /*读取数据 */
  for(; uwBufferSize != 0x00; uwBufferSize--)
  {
   *pBuffer++ = *(__IO uint32_t *)(Bank1_SRAM4_ADDR + write_pointer );
    
   /* 地址自增*/
    write_pointer += 4;
  } 
}


/**
  * @brief  测试SRAM是否正常 
  * @param  None
  * @retval 正常返回1，异常返回0
  */
uint8_t SRAM_Test(void)
{
  /*写入数据计数器*/
  uint32_t counter=0;
  
  /* 8位的数据 */
  uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;  
  
  /* 16位的数据 */
  uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0; 
  
  SRAM_INFO("正在检测SRAM，以8位、16位的方式读写sram...");


  /*按8位格式读写数据，并校验*/
  
  /* 把SRAM数据全部重置为0 ，IS62WV51216_SIZE是以8位为单位的 */
  for (counter = 0x00; counter < IS62WV51216_SIZE; counter++)
  {
    *(__IO uint8_t*) (Bank1_SRAM4_ADDR + counter) = (uint8_t)0x0;
  }
  
  /* 向整个SRAM写入数据  8位 */
  for (counter = 0; counter < IS62WV51216_SIZE; counter++)
  {
    *(__IO uint8_t*) (Bank1_SRAM4_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
  }
  
  /* 读取 SRAM 数据并检测*/
  for(counter = 0; counter<IS62WV51216_SIZE;counter++ )
  {
    ubReaddata_8b = *(__IO uint8_t*)(Bank1_SRAM4_ADDR + counter);  //从该地址读出数据
    
    if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))      //检测数据，若不相等，跳出函数,返回检测失败结果。
    {
      SRAM_ERROR("8位数据读写错误！");
      return 0;
    }
  }
	
  
  /*按16位格式读写数据，并检测*/
  
  /* 把SRAM数据全部重置为0 */
  for (counter = 0x00; counter < IS62WV51216_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (Bank1_SRAM4_ADDR + 2*counter) = (uint16_t)0x00;
  }
  
  /* 向整个SRAM写入数据  16位 */
  for (counter = 0; counter < IS62WV51216_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (Bank1_SRAM4_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
  }
  
    /* 读取 SRAM 数据并检测*/
  for(counter = 0; counter<IS62WV51216_SIZE/2;counter++ )
  {
    uhReaddata_16b = *(__IO uint16_t*)(Bank1_SRAM4_ADDR + 2*counter);  //从该地址读出数据
    
    if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))      //检测数据，若不相等，跳出函数,返回检测失败结果。
    {
      SRAM_ERROR("16位数据读写错误！");

      return 0;
    }
  }
  
  SRAM_INFO("SRAM读写测试正常！"); 
  /*检测正常，return 1 */
  return 1;

}


/*********************************************END OF FILE**********************/

