#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

/******************************************************************************************/
/* ���� ���� */

#define KEY0_GPIO_PORT                  GPIOC
#define KEY0_GPIO_PIN                   GPIO_Pin_5
#define KEY0_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); }while(0)   /* PC��ʱ��ʹ�� */

#define KEY1_GPIO_PORT                  GPIOA
#define KEY1_GPIO_PIN                   GPIO_Pin_15
#define KEY1_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)   /* PA��ʱ��ʹ�� */

#define WKUP_GPIO_PORT                  GPIOA
#define WKUP_GPIO_PIN                   GPIO_Pin_0
#define WKUP_GPIO_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)   /* PA��ʱ��ʹ�� */

/******************************************************************************************/

#define KEY0        GPIO_ReadInputDataBit(KEY0_GPIO_PORT, KEY0_GPIO_PIN)     /* ��ȡKEY0���� */
#define KEY1        GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* ��ȡKEY1���� */
#define WK_UP       GPIO_ReadInputDataBit(WKUP_GPIO_PORT, WKUP_GPIO_PIN)     /* ��ȡWKUP���� */


#define KEY0_PRES    1              /* KEY0���� */
#define KEY1_PRES    2              /* KEY1���� */
#define WKUP_PRES    3              /* KEY_UP����(��WK_UP) */

void key_init(void);                /* ������ʼ������ */
uint8_t key_scan(uint8_t mode);     /* ����ɨ�躯�� */

#endif


















