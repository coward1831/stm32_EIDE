#ifndef __FREERTOSRUN_H__
#define __FREERTOSRUN_H__
/* Ӳ�����������ͷ�ļ�***************************************************/
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/OLED_IIC/oled.h"
#include "./SYSTEM/usart/uart.h"
/* FreeRTOS***************************************************************/
#include "FreeRTOS.h" 
#include "task.h" 


void os_run(void);

#endif
