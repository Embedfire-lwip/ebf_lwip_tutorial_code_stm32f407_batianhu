/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   FreeRTOS V9.0.0 + STM32 LwIP
  *********************************************************************
  * @attention
  *
  * 实验平台:野火  STM32全系列开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/ 
#include "main.h"

#include <lwip/opt.h>
#include <lwip/arch.h>
#include "tcpip.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "ethernetif.h"
#include "netif/ethernet.h"
#include "lwip/def.h"
#include "lwip/stats.h"
#include "lwip/etharp.h"
#include "lwip/ip.h"
#include "lwip/snmp.h"
#include "lwip/timeouts.h"

#include "udpecho.h"

struct netif gnetif;
ip4_addr_t ipaddr;
ip4_addr_t netmask;
ip4_addr_t gw;
uint8_t IP_ADDRESS[4];
uint8_t NETMASK_ADDRESS[4];
uint8_t GATEWAY_ADDRESS[4];

void LwIP_Init(void)
{
  /* IP addresses initialization */
  /* USER CODE BEGIN 0 */
  IP4_ADDR(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
  IP4_ADDR(&netmask,NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
  IP4_ADDR(&gw,GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
  
  /* USER CODE END 0 */
    
  /* Initilialize the LwIP stack without RTOS */
  lwip_init();
  
  /* add the network interface (IPv4/IPv6) without RTOS */
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

  /* Registers the default network interface */
  netif_set_default(&gnetif);

  if (netif_is_link_up(&gnetif))
  {
    /* When the netif is fully configured this function must be called */
    netif_set_up(&gnetif);
  }
  else
  {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
  }

/* USER CODE BEGIN 3 */
  printf("本地IP地址是:%ld.%ld.%ld.%ld\n\n",  \
        ((gnetif.ip_addr.addr)&0x000000ff),       \
        (((gnetif.ip_addr.addr)&0x0000ff00)>>8),  \
        (((gnetif.ip_addr.addr)&0x00ff0000)>>16), \
        ((gnetif.ip_addr.addr)&0xff000000)>>24);
/* USER CODE END 3 */
}


int flag = 0;
int main(void)
{
  //板级外设初始化
  BSP_Init();
  
  printf("本例程演示UDP回显实验,电脑发送数据到开发板,开发板将数据返回到电脑上\n\n");
  
  printf("网络连接模型如下：\n\t 电脑<--网线-->路由<--网线-->开发板\n\n");
  
  printf("实验中使用UDP协议传输数据,UDP协议是无连接协议\n\n");
  
  printf("本例程的IP地址均在User/arch/sys_arch.h文件中修改\n\n");
    
  printf("本例程参考<<LwIP应用实战开发指南>> 使用 RAW API 接口编程\n\n");
  
  printf("请将电脑上位机设置为UDP协议.输入开发板的IP地址(如192.168.0.122)\n\n");  
  
  printf("如需修改IP地址与端口号，则修改对应的宏定义:IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3,LOCAL_PORT\n\n");  
  
  //LwIP协议栈初始化
  LwIP_Init();  
  UDP_Echo_Init();
  while (1)
  {
    if(flag)
    {
      flag = 0;
      //调用网卡接收函数
      ethernetif_input(&gnetif);
    }
    //处理LwIP中定时事件
    sys_check_timeouts();
  }
}



/********************************END OF FILE****************************/
