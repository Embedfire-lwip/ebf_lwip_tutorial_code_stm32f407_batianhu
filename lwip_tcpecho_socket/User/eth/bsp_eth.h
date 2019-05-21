#ifndef __BSP_ETH_H__
#define __BSP_ETH_H__

#include "stm32f4xx_hal.h"

/* FreeRTOSÍ·ÎÄ¼þ */
#include "FreeRTOS.h"
#include "task.h"

/**ETH GPIO Configuration    
PC1     ------> ETH_MDC
PA1     ------> ETH_REF_CLK
PA2     ------> ETH_MDIO
PA7     ------> ETH_CRS_DV
PC4     ------> ETH_RXD0
PC5     ------> ETH_RXD1
PG11     ------> ETH_TX_EN
PG13     ------> ETH_TXD0
PG14     ------> ETH_TXD1 
*/

/* Private defines --------------------------------------*/
#define ETH_MDC_Pin                 GPIO_PIN_1        //C1
#define ETH_MDC_GPIO_Port           GPIOC
#define ETH_REF_CLK_Pin             GPIO_PIN_1        //A1
#define ETH_REF_CLK_GPIO_Port       GPIOA
#define ETH_MDIO_Pin                GPIO_PIN_2        //A2
#define ETH_MDIO_GPIO_Port          GPIOA
#define ETH_CRS_DV_Pin              GPIO_PIN_7        //A7
#define ETH_CRS_DV_GPIO_Port        GPIOA
#define ETH_RXD0_Pin                GPIO_PIN_4        //C4
#define ETH_RXD0_GPIO_Port          GPIOC
#define ETH_RXD1_Pin                GPIO_PIN_5        //C5
#define ETH_RXD1_GPIO_Port          GPIOC
#define ETH_TX_EN_Pin               GPIO_PIN_11       //G11
#define ETH_TX_EN_GPIO_Port         GPIOG
#define ETH_TXD0_Pin                GPIO_PIN_13       //G13
#define ETH_TXD0_GPIO_Port          GPIOG
#define ETH_TXD1_Pin                GPIO_PIN_14       //G14
#define ETH_TXD1_GPIO_Port          GPIOG 




HAL_StatusTypeDef Bsp_Eth_Init(void);


#endif
