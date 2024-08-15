#include "./FreeRTOS/freertos_run.h"

/* start_task */
#define START_TASK_PRIO 1            /* 任务优先级 */
#define START_TASK_STACK_SIZE 128    /* 任务堆栈大小 */
TaskHandle_t start_task_handler;     /* 任务句柄 */
void start_task(void *pvParameters); /* 任务函数 */

/* task1任务 */
#define TASK1_PRIO 2            /* 任务优先级 */
#define TASK1_STACK_SIZE 128    /* 任务堆栈大小 */
TaskHandle_t task1_handler;     /* 任务句柄 */
void task1(void *pvParameters); /* 任务函数 */

/* task2任务 */
#define TASK2_PRIO 2            /* 任务优先级 */
#define TASK2_STACK_SIZE 128    /* 任务堆栈大小 */
TaskHandle_t task2_handler;     /* 任务句柄 */
void task2(void *pvParameters); /* 任务函数 */

/* task3任务 */
#define TASK3_PRIO 3            /* 任务优先级 */
#define TASK3_STACK_SIZE 128    /* 任务堆栈大小 */
TaskHandle_t task3_handler;     /* 任务句柄 */
void task3(void *pvParameters); /* 任务函数 */

void os_run(void)
{
    // 创建开始任务
    xTaskCreate((TaskFunction_t)start_task,           // 任务函数
                (const char *)"start_task",           // 任务名称
                (uint16_t)START_TASK_STACK_SIZE,      // 任务堆栈大小
                (void *)NULL,                         // 传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,         // 任务优先级
                (TaskHandle_t *)&start_task_handler); // 任务句柄
    vTaskStartScheduler();                            // 开启任务调度
}

// 开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL(); // 进入临界区

    // 创建TASK1任务
    xTaskCreate((TaskFunction_t)task1,
                (const char *)"task1",
                (uint16_t)TASK1_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_PRIO,
                (TaskHandle_t *)&task1_handler);
    // 创建TASK2任务
    xTaskCreate((TaskFunction_t)task2,
                (const char *)"task2",
                (uint16_t)TASK2_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_PRIO,
                (TaskHandle_t *)&task2_handler);
    // 创建TASK3任务
    xTaskCreate((TaskFunction_t)task3,
                (const char *)"task3",
                (uint16_t)TASK2_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK3_PRIO,
                (TaskHandle_t *)&task3_handler);

    vTaskDelete(start_task_handler); // 删除开始任务
    taskEXIT_CRITICAL();             // 退出临界区
}

/*********************************************/
/*  task1任务函数
 *  实现LED0每500ms翻转一次
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
/*  task2任务函数
 *  实现LED1每500ms翻转一次
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
/*  task3任务函数
 *  获取按键状态,按下KEY0挂起task1，按下KEY1恢复task1
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
        case KEY0_PRES: /* 挂起任务1 */
        {
            printf("Suspend--task1\r\n");
            vTaskSuspend(task1_handler);
            break;
        }
        case KEY1_PRES: /* 恢复任务1 */
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
