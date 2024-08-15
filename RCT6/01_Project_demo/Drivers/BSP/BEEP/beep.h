#ifndef __BEEP_H
#define __BEEP_H
#include "stm32f10x.h"     // Device header

/******************************************************************************************/
/* 引脚 定义 */

#define BEEP_GPIO_PORT                  GPIOB
#define BEEP_GPIO_PIN                   GPIO_Pin_8
#define BEEP_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); }while(0)   /* PB口时钟使能 */

/******************************************************************************************/

/* 蜂鸣器控制 */
#define BEEP(x)   do{ x ? \
                      GPIO_WriteBit(BEEP_GPIO_PORT, BEEP_GPIO_PIN, Bit_SET) : \
                      GPIO_WriteBit(BEEP_GPIO_PORT, BEEP_GPIO_PIN, Bit_RESET); \
                  }while(0)

/* BEEP状态翻转 */
#define BEEP_TOGGLE()   do{ GPIO_ReadOutputDataBit(BEEP_GPIO_PORT, BEEP_GPIO_PIN) ? \
							GPIO_WriteBit(BEEP_GPIO_PORT, BEEP_GPIO_PIN, Bit_RESET): \
							GPIO_WriteBit(BEEP_GPIO_PORT, BEEP_GPIO_PIN, Bit_SET);    \
						}while(0)        /* 翻转LED1 */

void beep_init(void);   /* 初始化蜂鸣器 */

#endif

















