#ifndef __TIM_CONFIG_H
#define __TIM_CONFIG_H
#include "stm32f10x.h"     // Device header

/************************-----  定时器中断开关配置 -----************************/
/*
 *
 *     使用说明：开启对应的定时器就能在主函数中调用相对应的中断    
              可以通过修改下面的配置项来改变进入中断的频率
              还可以修改是否开启中断
              还可以修改对应的抢占优先级和响应优先级
              由于该驱动使用于RTOS中，即5-15的中断优先级才会被RTOS管理
              由于RTOS,该代码默认配置中断分组为 NVIC_PriorityGroup_4,即只存在抢占优先级
 *
 *
 *
 */
#define TIM1_SWITCH   0                        /* 定时器1的开关 */
#define TIM1_NVIC_SWITCH  0                    /* 定时器1中断的开关 */
#define TIM2_SWITCH   0                    
#define TIM2_NVIC_SWITCH  0                    /* TIM2 */
#define TIM3_SWITCH   0
#define TIM3_NVIC_SWITCH  0                    /* TIM3 */
#define TIM4_SWITCH   0
#define TIM4_NVIC_SWITCH  0                    /* TIM4 */
#define TIM5_SWITCH   0
#define TIM5_NVIC_SWITCH  0                    /* TIM5 */
#define TIM6_SWITCH   1
#define TIM6_NVIC_SWITCH  1                    /* TIM6 */
#define TIM7_SWITCH   0
#define TIM7_NVIC_SWITCH  0                    /* TIM7 */
#define TIM8_SWITCH   0
#define TIM8_NVIC_SWITCH  0                    /* TIM8 */

/* TIM1 的配置项 */
#if TIM1_SWITCH == 1  
    #define TIM1_ARR (1000-1)                   /* 计数周期，即ARR的值 */
    #define TIM1_PSC (72-1)                     /* 预分频器，即PSC的值 */
    #define TIM1_NVIC_PRE  2                    /* 抢占优先级 */
    #define TIM1_NVIC_SUB  0                    /* 响应优先级 */
#endif

/* TIM2 的配置项 */
#if TIM2_SWITCH == 1  
    #define TIM2_ARR (1000-1)                   /* 计数周期，即ARR的值 */
    #define TIM2_PSC (72-1)                     /* 预分频器，即PSC的值 */
    #define TIM2_NVIC_PRE  2                    /* 抢占优先级 */
    #define TIM2_NVIC_SUB  0                    /* 响应优先级 */
#endif

/* TIM3 的配置项 */
#if TIM3_SWITCH == 1  
    #define TIM3_ARR (1000-1)                    /* 计数周期，即ARR的值 */
    #define TIM3_PSC (72-1)                      /* 预分频器，即PSC的值 */
    #define TIM3_NVIC_PRE  2                     /* 抢占优先级 */
    #define TIM3_NVIC_SUB  0                     /* 响应优先级 */
#endif

/* TIM4 的配置项 */
#if TIM4_SWITCH == 1  
    #define TIM4_ARR (1000-1)                    /* 计数周期，即ARR的值 */
    #define TIM4_PSC (72-1)                      /* 预分频器，即PSC的值 */    
    #define TIM4_NVIC_PRE  2                     /* 抢占优先级 */
    #define TIM4_NVIC_SUB  0                     /* 响应优先级 */
#endif


/* TIM5 的配置项 */
#if TIM5_SWITCH == 1  
    #define TIM5_ARR (1000-1)                   /* 计数周期，即ARR的值 */
    #define TIM5_PSC (72-1)                     /* 预分频器，即PSC的值 */
    #define TIM5_NVIC_PRE  2                    /* 抢占优先级 */
    #define TIM5_NVIC_SUB  0                    /* 响应优先级 */
#endif

/* TIM6 的配置项 */
#if TIM6_SWITCH == 1  
    #define TIM6_ARR (1000-1)                   /* 计数周期，即ARR的值 */
    #define TIM6_PSC (72-1)                     /* 预分频器，即PSC的值 */
    #define TIM6_NVIC_PRE  5                    /* 抢占优先级 */
    #define TIM6_NVIC_SUB  0                    /* 响应优先级 */
#endif

/* TIM7 的配置项 */
#if TIM7_SWITCH == 1  
    #define TIM7_ARR (1000-1)                   /* 计数周期，即ARR的值 */
    #define TIM7_PSC (72-1)                     /* 预分频器，即PSC的值 */
    #define TIM7_NVIC_PRE  2                    /* 抢占优先级 */
    #define TIM7_NVIC_SUB  0                    /* 响应优先级 */
#endif

/* TIM8 的配置项 */
#if TIM8_SWITCH == 1  
    #define TIM8_ARR (1000-1)                   /* 计数周期，即ARR的值 */
    #define TIM8_PSC (72-1)                     /* 预分频器，即PSC的值 */
    #define TIM8_NVIC_PRE  2                    /* 抢占优先级 */
    #define TIM8_NVIC_SUB  0                    /* 响应优先级 */
#endif
/**************************************************************/
/************************----- 定时器重映像设置 -----************************/
/*
 *     使用说明：    可以通过改变宏定义来修改重映像
                0x00  为  无重映像
                0x10  为  部分重映像1    
                0x01  为  部分重映像2
                0x11  为  完全重映像                    
 *
 */
#define TIM2_REMAP_SELECT   0x11
#define TIM3_REMAP_SELECT   0x00
/**************************************************************/





#endif

