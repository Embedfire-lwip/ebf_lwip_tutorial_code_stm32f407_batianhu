#include "udpecho.h"
#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/init.h"
#include "netif/etharp.h"
#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include <stdio.h>	
#include <string.h>	

static void udp_demo_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
   struct pbuf *q = NULL;
   const char* reply = "This is reply!\n";

   if(arg)
   {
       printf("%s",(char *)arg);
   }

   pbuf_free(p);
   
   q = pbuf_alloc(PBUF_TRANSPORT, strlen(reply)+1, PBUF_RAM);
   if(!q)
   {
   	   printf("out of PBUF_RAM\n");
	   return;
   }

   memset(q->payload, 0 , q->len);
   memcpy(q->payload, reply, strlen(reply));
   udp_sendto(upcb, q, addr, port);
   pbuf_free(q);
}

static char * st_buffer= "We get a data\n";
void UDP_Echo_Init(void)
{
    struct udp_pcb *udpecho_pcb;
    /* 新建一个控制块*/      
    udpecho_pcb = udp_new();    

    /* 绑定端口号 */
    udp_bind(udpecho_pcb, IP_ADDR_ANY, UDP_ECHO_PORT);
    
    /* 注册接收数据回调函数 */
    udp_recv(udpecho_pcb, udp_demo_callback, (void *)st_buffer);
}





















