#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"     // Device header


/******************************************************************************************/
/* ���� ���� */

#define LED0_GPIO_PORT                  GPIOA
#define LED0_GPIO_PIN                   GPIO_Pin_8
#define LED0_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)             /* PA��ʱ��ʹ�� */

#define LED1_GPIO_PORT                  GPIOD
#define LED1_GPIO_PIN                   GPIO_Pin_2
#define LED1_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); }while(0)             /* PD��ʱ��ʹ�� */

/******************************************************************************************/
/* LED�˿ڶ��� */
#define LED0(x)   do{ x ? \
                      GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, Bit_RESET) : \
                      GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, Bit_SET); \
                  }while(0)      /* LED0��ת */

#define LED1(x)   do{ x ? \
                      GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, Bit_RESET) : \
                      GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, Bit_SET); \
                  }while(0)      /* LED1��ת */


/* LEDȡ������ */
#define LED0_TOGGLE()   do{ GPIO_ReadOutputDataBit(LED0_GPIO_PORT, LED0_GPIO_PIN) ? \
                            GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, Bit_RESET): \
                            GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, Bit_SET);    \
                        }while(0)        /* ��תLED0 */
#define LED1_TOGGLE()   do{ GPIO_ReadOutputDataBit(LED1_GPIO_PORT, LED1_GPIO_PIN) ? \
                            GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, Bit_RESET): \
                            GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, Bit_SET);    \
                        }while(0)        /* ��תLED1 */
/******************************************************************************************/
/* �ⲿ�ӿں���*/
void led_init(void);/* ��ʼ�� */
                                                                       
#endif
