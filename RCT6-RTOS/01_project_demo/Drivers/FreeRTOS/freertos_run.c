#include "./FreeRTOS/freertos_run.h"

/* start_task */
#define START_TASK_PRIO 1            /* �������ȼ� */
#define START_TASK_STACK_SIZE 128    /* �����ջ��С */
TaskHandle_t start_task_handler;     /* ������ */
void start_task(void *pvParameters); /* ������ */

/* task1���� */
#define TASK1_PRIO 2            /* �������ȼ� */
#define TASK1_STACK_SIZE 128    /* �����ջ��С */
TaskHandle_t task1_handler;     /* ������ */
void task1(void *pvParameters); /* ������ */

/* task2���� */
#define TASK2_PRIO 2            /* �������ȼ� */
#define TASK2_STACK_SIZE 128    /* �����ջ��С */
TaskHandle_t task2_handler;     /* ������ */
void task2(void *pvParameters); /* ������ */

/* task3���� */
#define TASK3_PRIO 3            /* �������ȼ� */
#define TASK3_STACK_SIZE 128    /* �����ջ��С */
TaskHandle_t task3_handler;     /* ������ */
void task3(void *pvParameters); /* ������ */

void os_run(void)
{
    // ������ʼ����
    xTaskCreate((TaskFunction_t)start_task,           // ������
                (const char *)"start_task",           // ��������
                (uint16_t)START_TASK_STACK_SIZE,      // �����ջ��С
                (void *)NULL,                         // ���ݸ��������Ĳ���
                (UBaseType_t)START_TASK_PRIO,         // �������ȼ�
                (TaskHandle_t *)&start_task_handler); // ������
    vTaskStartScheduler();                            // �����������
}

// ��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL(); // �����ٽ���

    // ����TASK1����
    xTaskCreate((TaskFunction_t)task1,
                (const char *)"task1",
                (uint16_t)TASK1_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_PRIO,
                (TaskHandle_t *)&task1_handler);
    // ����TASK2����
    xTaskCreate((TaskFunction_t)task2,
                (const char *)"task2",
                (uint16_t)TASK2_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_PRIO,
                (TaskHandle_t *)&task2_handler);
    // ����TASK3����
    xTaskCreate((TaskFunction_t)task3,
                (const char *)"task3",
                (uint16_t)TASK2_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK3_PRIO,
                (TaskHandle_t *)&task3_handler);

    vTaskDelete(start_task_handler); // ɾ����ʼ����
    taskEXIT_CRITICAL();             // �˳��ٽ���
}

/*********************************************/
/*  task1������
 *  ʵ��LED0ÿ500ms��תһ��
 */
/*********************************************/
void task1(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(500);
        taskENTER_CRITICAL();
        printf("running--task1\r\n");
        LED0_TOGGLE();
        taskEXIT_CRITICAL();
    }
}

/*********************************************/
/*  task2������
 *  ʵ��LED1ÿ500ms��תһ��
 */
/*********************************************/
void task2(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(500);
        taskENTER_CRITICAL();
        printf("running--task2\r\n");
        LED1_TOGGLE();
        taskEXIT_CRITICAL();
    }
}

/*********************************************/
/*  task3������
 *  ��ȡ����״̬,����KEY0����task1������KEY1�ָ�task1
 */
/*********************************************/
void task3(void *pvParameters)
{
    uint8_t key_num = 0;
    while (1)
    {
        taskENTER_CRITICAL();
        key_num = key_scan(0);
        switch (key_num)
        {
        case KEY0_PRES: /* ��������1 */
        {
            printf("Suspend--task1\r\n");
            vTaskSuspend(task1_handler);
            break;
        }
        case KEY1_PRES: /* �ָ�����1 */
        {
            printf("Resume--task1\r\n");
            vTaskResume(task1_handler);
            break;
        }
        default:
        {
            break;
        }
        }
        taskEXIT_CRITICAL();
        vTaskDelay(10);
    }
}
