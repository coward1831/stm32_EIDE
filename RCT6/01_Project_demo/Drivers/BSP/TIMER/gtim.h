#ifndef __GTIM_H
#define __GTIM_H
#include "stm32f10x.h"     // Device header
#include "./BSP/TIMER/tim_config.h"


/******************************************************************************************/
/* 高级定时器 定义 TIM1，TIM8. */

#define TIM_TIM1_INT                       TIM1
#define TIM_TIM1_INT_IRQn                  TIM1_UP_IRQn         // 配置NVIC的TIM线
#define TIM_TIM1_INT_IRQHandler            TIM1_UP_IRQHandler  // 中断处理函数
#define TIM_TIM1_INT_CLK_ENABLE()          do{RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);; }while(0)  /* TIM 时钟使能 */

#define TIM_TIM8_INT                       TIM8
#define TIM_TIM8_INT_IRQn                  TIM8_UP_IRQn         // 配置NVIC的TIM线
#define TIM_TIM8_INT_IRQHandler            TIM8_UP_IRQHandler  // 中断处理函数
#define TIM_TIM8_INT_CLK_ENABLE()          do{RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);; }while(0)  /* TIM 时钟使能 */


/******************************************************************************************/
/* 通用定时器 定义 TIM2~TIM5. */

#define TIM_TIM2_INT                       TIM2
#define TIM_TIM2_INT_IRQn                  TIM2_IRQn         // 配置NVIC的TIM线
#define TIM_TIM2_INT_IRQHandler            TIM2_IRQHandler  // 中断处理函数
#define TIM_TIM2_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);; }while(0)  /* TIM 时钟使能 */

 
#define TIM_TIM3_INT                       TIM3
#define TIM_TIM3_INT_IRQn                  TIM3_IRQn         // 配置NVIC的TIM线
#define TIM_TIM3_INT_IRQHandler            TIM3_IRQHandler  // 中断处理函数
#define TIM_TIM3_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);; }while(0)  /* TIM 时钟使能 */

#define TIM_TIM4_INT                       TIM4
#define TIM_TIM4_INT_IRQn                  TIM4_IRQn         // 配置NVIC的TIM线
#define TIM_TIM4_INT_IRQHandler            TIM4_IRQHandler  // 中断处理函数
#define TIM_TIM4_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);; }while(0)  /* TIM 时钟使能 */

#define TIM_TIM5_INT                       TIM5
#define TIM_TIM5_INT_IRQn                  TIM5_IRQn         // 配置NVIC的TIM线
#define TIM_TIM5_INT_IRQHandler            TIM5_IRQHandler  // 中断处理函数
#define TIM_TIM5_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);; }while(0)  /* TIM 时钟使能 */


/******************************************************************************************/
/* 基本定时器 定义 TIM6~TIM7. */

#define TIM_TIM6_INT                       TIM6
#define TIM_TIM6_INT_IRQn                  TIM6_IRQn         // 配置NVIC的TIM线
#define TIM_TIM6_INT_IRQHandler            TIM6_IRQHandler  // 中断处理函数
#define TIM_TIM6_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);; }while(0)  /* TIM 时钟使能 */

#define TIM_TIM7_INT                       TIM7
#define TIM_TIM7_INT_IRQn                  TIM7_IRQn         // 配置NVIC的TIM线
#define TIM_TIM7_INT_IRQHandler            TIM7_IRQHandler  // 中断处理函数
#define TIM_TIM7_INT_CLK_ENABLE()          do{RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);; }while(0)  /* TIM 时钟使能 */

/******************************************************************************************/

void timx_init(void);      /* 配置定时中断初始化函数 */
void timx_run(void);       /* 开启定时器 */

#endif
