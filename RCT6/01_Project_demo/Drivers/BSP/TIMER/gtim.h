#ifndef __GTIM_H
#define __GTIM_H
#include "stm32f10x.h"     // Device header
#include "./BSP/TIMER/tim_config.h"


/******************************************************************************************/
/* �߼���ʱ�� ���� TIM1��TIM8. */

#define TIM_TIM1_INT                       TIM1
#define TIM_TIM1_INT_IRQn                  TIM1_UP_IRQn         // ����NVIC��TIM��
#define TIM_TIM1_INT_IRQHandler            TIM1_UP_IRQHandler  // �жϴ�����
#define TIM_TIM1_INT_CLK_ENABLE()          do{RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);; }while(0)  /* TIM ʱ��ʹ�� */

#define TIM_TIM8_INT                       TIM8
#define TIM_TIM8_INT_IRQn                  TIM8_UP_IRQn         // ����NVIC��TIM��
#define TIM_TIM8_INT_IRQHandler            TIM8_UP_IRQHandler  // �жϴ�����
#define TIM_TIM8_INT_CLK_ENABLE()          do{RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);; }while(0)  /* TIM ʱ��ʹ�� */


/******************************************************************************************/
/* ͨ�ö�ʱ�� ���� TIM2~TIM5. */

#define TIM_TIM2_INT                       TIM2
#define TIM_TIM2_INT_IRQn                  TIM2_IRQn         // ����NVIC��TIM��
#define TIM_TIM2_INT_IRQHandler            TIM2_IRQHandler  // �жϴ�����
#define TIM_TIM2_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);; }while(0)  /* TIM ʱ��ʹ�� */

 
#define TIM_TIM3_INT                       TIM3
#define TIM_TIM3_INT_IRQn                  TIM3_IRQn         // ����NVIC��TIM��
#define TIM_TIM3_INT_IRQHandler            TIM3_IRQHandler  // �жϴ�����
#define TIM_TIM3_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);; }while(0)  /* TIM ʱ��ʹ�� */

#define TIM_TIM4_INT                       TIM4
#define TIM_TIM4_INT_IRQn                  TIM4_IRQn         // ����NVIC��TIM��
#define TIM_TIM4_INT_IRQHandler            TIM4_IRQHandler  // �жϴ�����
#define TIM_TIM4_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);; }while(0)  /* TIM ʱ��ʹ�� */

#define TIM_TIM5_INT                       TIM5
#define TIM_TIM5_INT_IRQn                  TIM5_IRQn         // ����NVIC��TIM��
#define TIM_TIM5_INT_IRQHandler            TIM5_IRQHandler  // �жϴ�����
#define TIM_TIM5_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);; }while(0)  /* TIM ʱ��ʹ�� */


/******************************************************************************************/
/* ������ʱ�� ���� TIM6~TIM7. */

#define TIM_TIM6_INT                       TIM6
#define TIM_TIM6_INT_IRQn                  TIM6_IRQn         // ����NVIC��TIM��
#define TIM_TIM6_INT_IRQHandler            TIM6_IRQHandler  // �жϴ�����
#define TIM_TIM6_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);; }while(0)  /* TIM ʱ��ʹ�� */

#define TIM_TIM7_INT                       TIM7
#define TIM_TIM7_INT_IRQn                  TIM7_IRQn         // ����NVIC��TIM��
#define TIM_TIM7_INT_IRQHandler            TIM7_IRQHandler  // �жϴ�����
#define TIM_TIM7_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);; }while(0)  /* TIM ʱ��ʹ�� */

/******************************************************************************************/

void timx_init(void);      /* ���ö�ʱ�жϳ�ʼ������ */
void timx_run(void);       /* ������ʱ�� */

#endif
