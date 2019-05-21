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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(IPERF_PORT);
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
    while (1)
    {
        FD_ZERO(&readset);
        FD_SET(sock, &readset);
      
        if (select(sock + 1, &readset, NULL, NULL, &timeout) == 0)
            continue;
        
        printf("iperf_server\n");
        
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
        while (1)
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
//                snprintf(speed, sizeof(speed), "%.4f Mbps!\n", f);
//                printf("%s", speed);
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

void
iperf_server_init(void)
{
  sys_thread_new("iperf_server", iperf_server, NULL, 1024, 4);
}

