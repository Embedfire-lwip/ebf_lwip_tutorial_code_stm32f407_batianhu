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
  * ʵ��ƽ̨:Ұ��  STM32ȫϵ�п����� 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
#include "main.h"
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "mqttclient.h"
#include "cJSON_Process.h"
#include "./dwt_delay/core_delay.h"  
#include "bsp_dht11.h"

/**************************** ������ ********************************/
/* 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ��������������������������������Լ�����ô
 * ����������ΪNULL��
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* ���������� */
static TaskHandle_t Test1_Task_Handle = NULL;/* LED������ */
static TaskHandle_t Test2_Task_Handle = NULL;/* KEY������ */

/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬������ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */
 
QueueHandle_t MQTT_Data_Queue =NULL;

/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */
DHT11_Data_TypeDef DHT11_Data;

/******************************* �궨�� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩ�궨�塣
 */
#define  MQTT_QUEUE_LEN    4   /* ���еĳ��ȣ����ɰ������ٸ���Ϣ */
#define  MQTT_QUEUE_SIZE   4   /* ������ÿ����Ϣ��С���ֽڣ� */

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void AppTaskCreate(void);/* ���ڴ������� */

static void Test1_Task(void* pvParameters);/* Test1_Task����ʵ�� */
static void Test2_Task(void* pvParameters);/* Test2_Task����ʵ�� */

extern void TCPIP_Init(void);


/*****************************************************************
  * @brief  ������
  * @param  ��
  * @retval ��
  * @note   ��һ����������Ӳ����ʼ�� 
            �ڶ���������APPӦ������
            ������������FreeRTOS����ʼ���������
  ****************************************************************/
int main(void)
{	
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  
  /* ������Ӳ����ʼ�� */
  BSP_Init();

  /* ����AppTaskCreate���� */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* ������ں��� */
                        (const char*    )"AppTaskCreate",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* ������ƿ�ָ�� */ 
  /* ����������� */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* �������񣬿������� */
  else
    return -1;  
  
  while(1);   /* ��������ִ�е����� */    
}


/***********************************************************************
  * @ ������  �� AppTaskCreate
  * @ ����˵���� Ϊ�˷�����������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
 
  /* ����Test_Queue */
  MQTT_Data_Queue = xQueueCreate((UBaseType_t ) MQTT_QUEUE_LEN,/* ��Ϣ���еĳ��� */
                                 (UBaseType_t ) MQTT_QUEUE_SIZE);/* ��Ϣ�Ĵ�С */
  if(NULL != MQTT_Data_Queue)
    PRINT_DEBUG("����MQTT_Data_Queue��Ϣ���гɹ�!\r\n");
  
  TCPIP_Init();
  
  mqtt_thread_init();

  taskENTER_CRITICAL();           //�����ٽ���
 
  /* ����Test1_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )Test1_Task, /* ������ں��� */
                        (const char*    )"Test1_Task",/* �������� */
                        (uint16_t       )512,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )2,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&Test1_Task_Handle);/* ������ƿ�ָ�� */
  if(pdPASS == xReturn)
    PRINT_DEBUG("Create Test1_Task sucess...\r\n");
  
  /* ����Test2_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )Test2_Task,  /* ������ں��� */
                        (const char*    )"Test2_Task",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&Test2_Task_Handle);/* ������ƿ�ָ�� */ 
  if(pdPASS == xReturn)
    PRINT_DEBUG("Create Test2_Task sucess...\n\n");
  
  vTaskDelete(AppTaskCreate_Handle); //ɾ��AppTaskCreate����
  
  taskEXIT_CRITICAL();            //�˳��ٽ���
}



/**********************************************************************
  * @ ������  �� Test1_Task
  * @ ����˵���� Test1_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Test1_Task(void* parameter)
{	
  uint8_t res;
  BaseType_t xReturn = pdPASS;
  //ϵͳ��ʱ��ʼ��
  CPU_TS_TmrInit();
  //DHT11��ʼ��
  DHT11_Init();
  DHT11_Data_TypeDef* send_data;
  while (1)
  {
    taskENTER_CRITICAL();           //�����ٽ���
    res = DHT11_Read_TempAndHumidity(&DHT11_Data);
    taskEXIT_CRITICAL();            //�˳��ٽ���
    send_data = &DHT11_Data;
    if(SUCCESS == res)
    {
//      PRINT_DEBUG("humidity = %f , temperature = %f\n",
//             DHT11_Data.humidity,DHT11_Data.temperature);
//      PRINT_DEBUG("������Ϣsend_data1��\n");
      xReturn = xQueueSend( MQTT_Data_Queue, /* ��Ϣ���еľ�� */
                            &send_data,/* ���͵���Ϣ���� */
                            0 );        /* �ȴ�ʱ�� 0 */
//      if(xReturn == pdTRUE)
//        PRINT_DEBUG("������Ϣ���ݳɹ�\n");
    }

    LED1_TOGGLE;
//    PRINT_DEBUG("LED1_TOGGLE\n");
    vTaskDelay(1000);/* ��ʱ1000��tick */
  }
}

/**********************************************************************
  * @ ������  �� Test2_Task
  * @ ����˵���� Test2_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Test2_Task(void* parameter)
{	 
  while (1)
  {
    LED2_TOGGLE;
//    PRINT_DEBUG("LED2_TOGGLE\n");

    vTaskDelay(2000);/* ��ʱ2000��tick */
  }
}



/********************************END OF FILE****************************/