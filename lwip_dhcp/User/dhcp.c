#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/dhcp.h"
#include "lwip/inet.h"

#include "dhcp.h"

#if LWIP_NETCONN

#define MAX_BUFFER_LEN 256

char sendbuf[MAX_BUFFER_LEN];

extern struct netif gnetif;

static void dhcp_thread(void *arg)
{
	struct netconn *conn;
	ip4_addr_t ipaddr;
  int ret;
	int strlen = 0;
  
  while(ip_addr_cmp(&(gnetif.ip_addr),&ipaddr))   //等待dhcp分配的ip有效
  {
    vTaskDelay(1);
  }
  
  strlen = sprintf(sendbuf,"A LwIP client Using DHCP Address: %s\n", \
  ipaddr_ntoa((ip_addr_t *)&(gnetif.ip_addr)));

  printf("%s",sendbuf);
    
	while(1)
	{
reconnect:
    conn = netconn_new(NETCONN_TCP);
    if (conn == NULL)
    {
      printf("create conn failed!\n");
      vTaskDelay(10);
      continue;
    }

    printf("create conn success...\n");
    
    IP4_ADDR(&ipaddr,192,168,0,181); 			//构造服务器IP地址
    
    ret = netconn_connect(conn,&ipaddr,5001);	//连接服务器，端口号5001
    
    if (ret == -1)
    {
      printf("Connect failed!\n");
      netconn_close(conn);
      vTaskDelay(10);
      continue;
    }
    
    printf("Connect to server successful!\n");
    
    strlen = sprintf(sendbuf,"A LwIP client Using DHCP Address: %s\n", \
    ipaddr_ntoa((ip_addr_t *)&(gnetif.ip_addr)));
    
    while(1)
    {
      printf("%s",sendbuf);
      ret=netconn_write(conn,sendbuf, strlen, NETCONN_NOCOPY);
      if (ret == ERR_OK)
      {
         printf("write success...\n");
      }
      else
      {
        printf("write fail,try to reconnect...\n");
        netconn_close(conn);
        goto reconnect;
      }
      vTaskDelay(1000); 
    }
    
//    printf("Connection failed \n");
//    netconn_close(conn); 						//关闭连接
//    netconn_delete(conn);						//删除连接结构
  }
}


void dhcp_netconn_init()
{
  sys_thread_new("dhcp_thread", dhcp_thread, NULL, 1024, 4);
}

#endif /* LWIP_NETCONN*/
