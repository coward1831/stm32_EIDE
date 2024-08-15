/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
#include "stm32f10x.h"
/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
 
/***************************************************************************************************************/
/*                                        FreeRTOS������������ѡ��                                              */
/***************************************************************************************************************/

#define configUSE_PREEMPTION                        1                         //1ʹ����ռʽ�ںˣ�0ʹ��Э��
#define configUSE_TIME_SLICING                      1                         //1ʹ��ʱ��Ƭ����(Ĭ��ʽʹ�ܵ�)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION     1                         //1�������ⷽ����ѡ����һ��Ҫ���е�����
                                                                              //һ����Ӳ������ǰ����ָ������ʹ�õ�
                                                                              //MCUû����ЩӲ��ָ��Ļ��˺�Ӧ������Ϊ0��
                                                                        
#define configCPU_CLOCK_HZ                    ( ( unsigned long ) SystemCoreClock ) //CPUƵ��
#define configTICK_RATE_HZ                    ( ( TickType_t ) 1000 )          //ʱ�ӽ���Ƶ�ʣ���������Ϊ1000�����ھ���1ms,��1sִ��1000��
#define configMAX_PRIORITIES                  ( 32 )                           //��ʹ�õ�������ȼ�
#define configMINIMAL_STACK_SIZE              ( ( unsigned short ) 128 )       //��������ʹ�õĶ�ջ��С
#define configMAX_TASK_NAME_LEN               ( 16 )                           //���������ַ�������
#define configUSE_16_BIT_TICKS                 0                               //ϵͳ���ļ����������������ͣ�
                                                                               //1��ʾΪ16λ�޷������Σ�0��ʾΪ32λ�޷�������

#define configIDLE_SHOULD_YIELD                     1                          //Ϊ1ʱ�����������CPUʹ��Ȩ������ͬ���ȼ����û�����
#define configUSE_TASK_NOTIFICATIONS                1                          //Ϊ1ʱ��������֪ͨ���ܣ�Ĭ�Ͽ���
#define configUSE_TICKLESS_IDLE                     0                          //1���õ͹���ticklessģʽ

#define configUSE_QUEUE_SETS                        1                          //Ϊ1ʱ���ö���
#define configQUEUE_REGISTRY_SIZE                   8                          //��Ϊ0ʱ��ʾ���ö��м�¼�������ֵ�ǿ���
                                                                               //��¼�Ķ��к��ź��������Ŀ��
#define configCHECK_FOR_STACK_OVERFLOW              0                          //����0ʱ���ö�ջ�����⹦�ܣ����ʹ�ô˹���
                                                                               //�û������ṩһ��ջ������Ӻ��������ʹ�õĻ�
                                                                               //��ֵ����Ϊ1����2����Ϊ������ջ�����ⷽ����
//#define configUSE_RECURSIVE_MUTEXES               1                          //Ϊ1ʱʹ�õݹ黥���ź���
#define configUSE_COUNTING_SEMAPHORES               1                          //Ϊ1ʱʹ�ü����ź���

#define configUSE_MALLOC_FAILED_HOOK                0                          //1ʹ���ڴ�����ʧ�ܹ��Ӻ���
#define configUSE_APPLICATION_TASK_TAG              0                       
/***************************************************************************************************************/
/*                                FreeRTOS���ڴ������й�����ѡ��                                                */
/***************************************************************************************************************/
#define configSUPPORT_DYNAMIC_ALLOCATION            1                          //֧�ֶ�̬�ڴ�����
#define configTOTAL_HEAP_SIZE                ( ( size_t ) ( 10 * 1024 ) )      //ϵͳ�����ܵĶѴ�С

/***************************************************************************************************************/
/*                                FreeRTOS�빳�Ӻ����йص�����ѡ��                                              */
/***************************************************************************************************************/
#define configUSE_IDLE_HOOK                         0                          //1��ʹ�ÿ��й��ӣ�0����ʹ��
#define configUSE_TICK_HOOK                         0                          //1��ʹ��ʱ��Ƭ���ӣ�0����ʹ��

/***************************************************************************************************************/
/*                                FreeRTOS������ʱ�������״̬�ռ��йص�����ѡ��                                 */
/***************************************************************************************************************/

#define configUSE_TRACE_FACILITY                    0                          //Ϊ1���ÿ��ӻ����ٵ���
//#define configUSE_STATS_FORMATTING_FUNCTIONS      1                          //���configUSE_TRACE_FACILITYͬʱΪ1ʱ���������3������
//                                                                             //prvWriteNameToBuffer(),vTaskList(),
//                                                                             //vTaskGetRunTimeStats()
//#define configGENERATE_RUN_TIME_STATS             0                          //Ϊ1ʱ��������ʱ��ͳ�ƹ���                                                                       
 
/***************************************************************************************************************/
/*                                FreeRTOS��Э���йص�����ѡ��                                                  */
/***************************************************************************************************************/
//#define configUSE_CO_ROUTINES                     0                       //Ϊ1ʱ����Э�̣�����Э���Ժ���������ļ�croutine.c
//#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )                     //Э�̵���Ч���ȼ���Ŀ

/***************************************************************************************************************/
/*                                FreeRTOS��������ʱ���йص�����ѡ��                                            */
/***************************************************************************************************************/
//#define configUSE_TIMERS                          1                               //Ϊ1ʱ����������ʱ��
//#define configTIMER_TASK_PRIORITY                 (configMAX_PRIORITIES-1)        //������ʱ�����ȼ�
//#define configTIMER_QUEUE_LENGTH                  5                               //������ʱ�����г���
//#define configTIMER_TASK_STACK_DEPTH              (configMINIMAL_STACK_SIZE*2)    //������ʱ�������ջ��С


/***************************************************************************************************************/
/*                                FreeRTOS��ѡ��������ѡ��                                                      */
/***************************************************************************************************************/
#define INCLUDE_xTaskGetSchedulerState              1 
#define INCLUDE_vTaskPrioritySet                    1
#define INCLUDE_uxTaskPriorityGet                   1
#define INCLUDE_vTaskDelete                         1
#define INCLUDE_vTaskCleanUpResources               0
#define INCLUDE_vTaskSuspend                        1
#define INCLUDE_vTaskDelayUntil                     1
#define INCLUDE_vTaskDelay                          1
#define INCLUDE_eTaskGetState                       1
//#define INCLUDE_xTimerPendFunctionCall            1



/***************************************************************************************************************/
/*                                FreeRTOS���ж��йص�����ѡ��                                                  */
/***************************************************************************************************************/
/* This is the value being used as per the ST library which permits 16
priority values, 0 to 15.  This must correspond to the
configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
NVIC value of 255. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY     15      //�ж�������ȼ�
/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
(lowest) to 0 (1?) (highest). */
#define configKERNEL_INTERRUPT_PRIORITY             255
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY        191 /* equivalent to 0xb0, or priority 11. */


/***************************************************************************************************************/
/*                                FreeRTOS���жϷ������йص�����ѡ��                                          */
/***************************************************************************************************************/
#define xPortPendSVHandler      PendSV_Handler
#define vPortSVCHandler         SVC_Handler
#define xPortSysTickHandler     SysTick_Handler


#endif /* FREERTOS_CONFIG_H */
