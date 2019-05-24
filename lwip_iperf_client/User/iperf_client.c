/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#include "iperf_client.h"

#include "lwip/opt.h"

#include "lwip/sys.h"
#include "lwip/api.h"

#define IPERF_BUFSZ         (4 * 1024)


static void iperf_client(void *thread_param)
{
  struct netconn *conn;
  
  int i;

  int ret;

  uint8_t *send_buf;
  
  uint64_t sentlen;
  
  u32_t tick1, tick2;
  ip4_addr_t ipaddr;

  printf("目地IP地址:%d.%d.%d.%d \t 端口号:%d\n\n",      \
          DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT);
  
  printf("请将电脑上位机设置为TCP Server.在User/arch/sys_arch.h文件中将目标IP地址修改为您电脑上的IP地址\n\n");
  
  printf("修改对应的宏定义:DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT\n\n");
  
  
  send_buf = (uint8_t *) pvPortMalloc(IPERF_BUFSZ);
  if (!send_buf) return ;

  for (i = 0; i < IPERF_BUFSZ; i ++)
      send_buf[i] = i & 0xff;
  
  while(1)
  {
    conn = netconn_new(NETCONN_TCP);
    if (conn == NULL)
    {
      printf("create conn failed!\n");
      vTaskDelay(10);
      continue;
    }
    
    IP4_ADDR(&ipaddr,DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3);
    
    ret = netconn_connect(conn,&ipaddr,DEST_PORT);
    if (ret == -1)
    {
        printf("Connect failed!\n");
        netconn_close(conn);
        vTaskDelay(10);
        continue;
    }
    
    printf("Connect to iperf server successful!\n");
    
    tick1 = sys_now();
    while (1)
    {
      tick2 = sys_now();
      
      if(tick2 - tick1 >= configTICK_RATE_HZ * 5)
      {     
        float f;
        f = (float)(sentlen*configTICK_RATE_HZ/125/(tick2 - tick1));
        f /= 1000.0f;
        printf("send speed = %.4f Mbps!\n", f);
        
        tick1 = tick2;
        sentlen = 0;
      }
      ret = netconn_write(conn,send_buf,IPERF_BUFSZ,1);
      if (ret == ERR_OK)
      {
          sentlen += IPERF_BUFSZ;
      }
      
    }
//    netconn_close(conn);
//    netconn_delete(conn);
  }
}

void
iperf_client_init(void)
{
  sys_thread_new("iperf_client", iperf_client, NULL, 1024, 4);
}
