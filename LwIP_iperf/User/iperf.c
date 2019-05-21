///*
// * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
// * All rights reserved. 
// * 
// * Redistribution and use in source and binary forms, with or without modification, 
// * are permitted provided that the following conditions are met:
// *
// * 1. Redistributions of source code must retain the above copyright notice,
// *    this list of conditions and the following disclaimer.
// * 2. Redistributions in binary form must reproduce the above copyright notice,
// *    this list of conditions and the following disclaimer in the documentation
// *    and/or other materials provided with the distribution.
// * 3. The name of the author may not be used to endorse or promote products
// *    derived from this software without specific prior written permission. 
// *
// * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
// * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
// * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
// * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
// * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
// * OF SUCH DAMAGE.
// *
// * This file is part of the lwIP TCP/IP stack.
// * 
// * Author: Adam Dunkels <adam@sics.se>
// *
// */
//#include "tcpecho.h"

//#include "lwip/opt.h"

//#if LWIP_NETCONN

//#include "lwip/sys.h"
//#include "lwip/api.h"
///*-----------------------------------------------------------------------------------*/
//static void 
//tcpecho_thread(void *arg)
//{
//  struct netconn *conn, *newconn;
//  err_t err;
//  LWIP_UNUSED_ARG(arg);

//  /* Create a new connection identifier. */
//  /* Bind connection to well known port number 7. */
//#if LWIP_IPV6
//  conn = netconn_new(NETCONN_TCP_IPV6);
//  netconn_bind(conn, IP6_ADDR_ANY, 7);
//#else /* LWIP_IPV6 */
//  conn = netconn_new(NETCONN_TCP);
//  netconn_bind(conn, IP_ADDR_ANY, 7);
//#endif /* LWIP_IPV6 */
//  LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

//  /* Tell connection to go into listening mode. */
//  netconn_listen(conn);

//  while (1) {

//    /* Grab new connection. */
//    err = netconn_accept(conn, &newconn);
//    /*printf("accepted new connection %p\n", newconn);*/
//    /* Process the new connection. */
//    if (err == ERR_OK) {
//      struct netbuf *buf;
//      void *data;
//      u16_t len;
//      
//      while ((err = netconn_recv(newconn, &buf)) == ERR_OK) {
//        /*printf("Recved\n");*/
//        do {
////             netbuf_data(buf, &data, &len);
////             err = netconn_write(newconn, data, len, 1);
//#if 0
//            if (err != ERR_OK) {
//              printf("tcpecho: netconn_write: error \"%s\"\n", lwip_strerr(err));
//            }
//#endif
//        } while (netbuf_next(buf) >= 0);
//        netbuf_delete(buf);
//      }
//      /*printf("Got EOF, looping\n");*/ 
//      /* Close connection and discard connection identifier. */
////      netconn_close(newconn);
////      netconn_delete(newconn);
//    }
////    printf("tcpecho_thread run\n");
//  }
//}




///*-----------------------------------------------------------------------------------*/
//void
//tcpecho_init(void)
//{
//  sys_thread_new(TCP_SERVER_THREAD_NAME, tcpecho_thread, NULL, TCP_SERVER_THREAD_STACKSIZE, TCP_SERVER_THREAD_PRIO);
//}
///*-----------------------------------------------------------------------------------*/

//#endif /* LWIP_NETCONN */
/**
* iperf-liked network performance tool
*
*/

 /* FreeRTOSÍ·ÎÄ¼þ */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include <stdint.h>
#include <stdio.h>

//#include <lwip/time.h>
#include <lwip/sockets.h>
//#include <lwip/select.h>
//#include "netdb.h"
#include "iperf.h"

#include "lwip/opt.h"

#include "lwip/sys.h"
#include "lwip/api.h"

#define IPERF_PORT          5001
#define IPERF_BUFSZ         (4 * 1024)

#define IPERF_MODE_STOP     0
#define IPERF_MODE_SERVER   1
#define IPERF_MODE_CLIENT   2

typedef struct
{
    int mode;

    char *host;
    int port;
} IPERF_PARAM;
static IPERF_PARAM param = {IPERF_MODE_SERVER, NULL, IPERF_PORT};

static void iperf_client(void *thread_param)
{
    int i;
    int sock;
    int ret;

    uint8_t *send_buf;
    uint64_t sentlen;
    uint32_t tick1, tick2;
    struct sockaddr_in addr;

    char speed[32] = { 0 };

    send_buf = (uint8_t *) malloc(IPERF_BUFSZ);
    if (!send_buf) return ;

    for (i = 0; i < IPERF_BUFSZ; i ++)
        send_buf[i] = i & 0xff;

    while (param.mode != IPERF_MODE_STOP)
    {
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock < 0)
        {
            printf("create socket failed!\n");
            vTaskDelay(configTICK_RATE_HZ);
            continue;
        }

        addr.sin_family = PF_INET;
        addr.sin_port = htons(param.port);
        addr.sin_addr.s_addr = inet_addr((char *)param.host);

        ret = connect(sock, (const struct sockaddr *)&addr, sizeof(addr));
        if (ret == -1)
        {
            printf("Connect failed!\n");
            closesocket(sock);

            vTaskDelay(configTICK_RATE_HZ);
            continue;
        }

        printf("Connect to iperf server successful!\n");

        {
            int flag = 1;

            setsockopt(sock,
                       IPPROTO_TCP,     /* set option at TCP level */
                       TCP_NODELAY,     /* name of option */
                       (void *) &flag,  /* the cast is historical cruft */
                       sizeof(int));    /* length of option value */
        }

        sentlen = 0;

        tick1 = xTaskGetTickCount();
        while (param.mode != IPERF_MODE_STOP)
        {
            tick2 = xTaskGetTickCount();
            if (tick2 - tick1 >= configTICK_RATE_HZ * 5)
            {
                float f;

                f = (float)(sentlen * configTICK_RATE_HZ / 125 / (tick2 - tick1));
                f /= 1000.0f;
                snprintf(speed, sizeof(speed), "%.4f Mbps!\n", f);
                printf("%s", speed);
                tick1 = tick2;
                sentlen = 0;
            }

            ret = send(sock, send_buf, IPERF_BUFSZ, 0);
            if (ret > 0)
            {
                sentlen += ret;
            }

            if (ret < 0) break;
        }

        closesocket(sock);

        vTaskDelay(configTICK_RATE_HZ * 2);
        printf("disconnected!\n");
    }
}

void iperf_server(void *thread_param)
{
    uint8_t *recv_data;
    socklen_t sin_size;
    uint32_t tick1, tick2;
    int sock = -1, connected, bytes_received;
    uint64_t recvlen;
    struct sockaddr_in server_addr, client_addr;
    char speed[32] = { 0 };
    fd_set readset;
    struct timeval timeout;

    recv_data = (uint8_t *)pvPortMalloc(IPERF_BUFSZ);
    if (recv_data == NULL)
    {
        printf("No memory\n");
        goto __exit;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("Socket error\n");
        goto __exit;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(param.port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), 0x0, sizeof(server_addr.sin_zero));

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        printf("Unable to bind\n");
        goto __exit;
    }

    if (listen(sock, 5) == -1)
    {
        printf("Listen error\n");
        goto __exit;
    }

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    printf("iperf_server\n");
    while (param.mode != IPERF_MODE_STOP)
    {
        FD_ZERO(&readset);
        FD_SET(sock, &readset);

        if (select(sock + 1, &readset, NULL, NULL, &timeout) == 0)
            continue;

        sin_size = sizeof(struct sockaddr_in);

        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);

        printf("new client connected from (%s, %d)\n",
                   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        {
            int flag = 1;

            setsockopt(connected,
                       IPPROTO_TCP,     /* set option at TCP level */
                       TCP_NODELAY,     /* name of option */
                       (void *) &flag,  /* the cast is historical cruft */
                       sizeof(int));    /* length of option value */
        }

        recvlen = 0;
        tick1 = xTaskGetTickCount();
        while (param.mode != IPERF_MODE_STOP)
        {
            bytes_received = recv(connected, recv_data, IPERF_BUFSZ, 0);
            if (bytes_received <= 0) break;

            recvlen += bytes_received;

            tick2 = xTaskGetTickCount();
            if (tick2 - tick1 >= configTICK_RATE_HZ * 5)
            {
                float f;

                f = (float)(recvlen * configTICK_RATE_HZ / 125 / (tick2 - tick1));
                f /= 1000.0f;
                snprintf(speed, sizeof(speed), "%.4f Mbps!\n", f);
                printf("%s", speed);
                tick1 = tick2;
                recvlen = 0;
            }
        }

        if (connected >= 0) closesocket(connected);
        connected = -1;
    }

__exit:
    if (sock >= 0) closesocket(sock);
    if (recv_data) free(recv_data);
}

void iperf_usage(void)
{
    printf("Usage: iperf [-s|-c host] [options]\n");
    printf("       iperf [-h|--stop]\n");
    printf("\n");
    printf("Client/Server:\n");
    printf("  -p #         server port to listen on/connect to\n");
    printf("\n");
    printf("Server specific:\n");
    printf("  -s           run in server mode\n");
    printf("\n");
    printf("Client specific:\n");
    printf("  -c <host>    run in client mode, connecting to <host>\n");
    printf("\n");
    printf("Miscellaneous:\n");
    printf("  -h           print this message and quit\n");
    printf("  --stop       stop iperf program\n");

    return ;
}

int iperf(int argc, char **argv)
{
    int mode = 0; /* server mode */
    char *host = NULL;
    int port = IPERF_PORT;

    if (argc == 1) goto __usage;
    else
    {
        if (strcmp(argv[1], "-h") == 0) goto __usage;
        else if (strcmp(argv[1], "--stop") == 0)
        {
            /* stop iperf */
            param.mode = IPERF_MODE_STOP;
            return 0;
        }
        else if (strcmp(argv[1], "-s") == 0)
        {
            mode = IPERF_MODE_SERVER; /* server mode */

            /* iperf -s -p 5000 */
            if (argc == 4)
            {
                if (strcmp(argv[2], "-p") == 0)
                {
                    port = atoi(argv[3]);
                }
                else goto __usage;
            }
        }
        else if (strcmp(argv[1], "-c") == 0)
        {
            mode = IPERF_MODE_CLIENT; /* client mode */
            if (argc < 3) goto __usage;

            host = argv[2];
            if (argc == 5)
            {
                /* iperf -c host -p port */
                if (strcmp(argv[3], "-p") == 0)
                {
                    port = atoi(argv[4]);
                }
                else goto __usage;
            }
        }
        else if (strcmp(argv[1], "-h") == 0)
        {
            goto __usage;
        }
        else goto __usage;
    }

    /* start iperf */
    if (param.mode == IPERF_MODE_STOP)
    {
//        thread_t tid = NULL;

        param.mode = mode;
        param.port = port;
        if (param.host)
        {
            free(param.host);
            param.host = NULL;
        }
        if (host) param.host = "192.168.1.122";
        mode = IPERF_MODE_SERVER;
        if (mode == IPERF_MODE_CLIENT)
        {
          sys_thread_new(TCP_SERVER_THREAD_NAME, iperf_client, NULL, 2048, 4);

            
        }                        
        else if (mode == IPERF_MODE_SERVER)
            sys_thread_new(TCP_SERVER_THREAD_NAME, iperf_server, NULL, 2048, 4);

//        if (tid) thread_startup(tid);
    }
    else
    {
        printf("Please stop iperf firstly, by:\n");
        printf("iperf --stop\n");
    }

    return 0;

__usage:
    iperf_usage();
    return 0;
}

#ifdef USING_FINSH
    #include <finsh.h>
    MSH_CMD_EXPORT(iperf, the network bandwidth measurement tool);
#endif
