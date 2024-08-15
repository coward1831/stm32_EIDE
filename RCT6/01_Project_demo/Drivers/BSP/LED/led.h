#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"     // Device header


/******************************************************************************************/
/* 引脚 定义 */

#define LED0_GPIO_PORT                  GPIOA
#define LED0_GPIO_PIN                   GPIO_Pin_8
#define LED0_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)             /* PA口时钟使能 */

#define LED1_GPIO_PORT                  GPIOD
#define LED1_GPIO_PIN                   GPIO_Pin_2
#define LED1_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); }while(0)             /* PD口时钟使能 */

/******************************************************************************************/
/* LED端口定义 */
#define LED0(x)   do{ x ? \
                      GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, Bit_RESET) : \
                      GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, Bit_SET); \
                  }while(0)      /* LED0翻转 */

#define LED1(x)   do{ x ? \
                      GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, Bit_RESET) : \
                      GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, Bit_SET); \
                  }while(0)      /* LED1翻转 */


/* LED取反定义 */
#define LED0_TOGGLE()   do{ GPIO_ReadOutputDataBit(LED0_GPIO_PORT, LED0_GPIO_PIN) ? \
                            GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, Bit_RESET): \
                            GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, Bit_SET);    \
                        }while(0)        /* 翻转LED0 */
#define LED1_TOGGLE()   do{ GPIO_ReadOutputDataBit(LED1_GPIO_PORT, LED1_GPIO_PIN) ? \
                            GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, Bit_RESET): \
                            GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, Bit_SET);    \
                        }while(0)        /* 翻转LED1 */
/******************************************************************************************/
/* 外部接口函数*/
void led_init(void);/* 初始化 */
                                                                       
#endif
