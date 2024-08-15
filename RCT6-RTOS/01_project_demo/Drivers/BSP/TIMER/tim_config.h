#ifndef __TIM_CONFIG_H
#define __TIM_CONFIG_H
#include "stm32f10x.h"     // Device header

/************************-----  ��ʱ���жϿ������� -----************************/
/*
 *
 *     ʹ��˵����������Ӧ�Ķ�ʱ���������������е������Ӧ���ж�    
              ����ͨ���޸���������������ı�����жϵ�Ƶ��
              �������޸��Ƿ����ж�
              �������޸Ķ�Ӧ����ռ���ȼ�����Ӧ���ȼ�
              ���ڸ�����ʹ����RTOS�У���5-15���ж����ȼ��ŻᱻRTOS����
              ����RTOS,�ô���Ĭ�������жϷ���Ϊ NVIC_PriorityGroup_4,��ֻ������ռ���ȼ�
 *
 *
 *
 */
#define TIM1_SWITCH   0                        /* ��ʱ��1�Ŀ��� */
#define TIM1_NVIC_SWITCH  0                    /* ��ʱ��1�жϵĿ��� */
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

/* TIM1 �������� */
#if TIM1_SWITCH == 1  
    #define TIM1_ARR (1000-1)                   /* �������ڣ���ARR��ֵ */
    #define TIM1_PSC (72-1)                     /* Ԥ��Ƶ������PSC��ֵ */
    #define TIM1_NVIC_PRE  2                    /* ��ռ���ȼ� */
    #define TIM1_NVIC_SUB  0                    /* ��Ӧ���ȼ� */
#endif

/* TIM2 �������� */
#if TIM2_SWITCH == 1  
    #define TIM2_ARR (1000-1)                   /* �������ڣ���ARR��ֵ */
    #define TIM2_PSC (72-1)                     /* Ԥ��Ƶ������PSC��ֵ */
    #define TIM2_NVIC_PRE  2                    /* ��ռ���ȼ� */
    #define TIM2_NVIC_SUB  0                    /* ��Ӧ���ȼ� */
#endif

/* TIM3 �������� */
#if TIM3_SWITCH == 1  
    #define TIM3_ARR (1000-1)                    /* �������ڣ���ARR��ֵ */
    #define TIM3_PSC (72-1)                      /* Ԥ��Ƶ������PSC��ֵ */
    #define TIM3_NVIC_PRE  2                     /* ��ռ���ȼ� */
    #define TIM3_NVIC_SUB  0                     /* ��Ӧ���ȼ� */
#endif

/* TIM4 �������� */
#if TIM4_SWITCH == 1  
    #define TIM4_ARR (1000-1)                    /* �������ڣ���ARR��ֵ */
    #define TIM4_PSC (72-1)                      /* Ԥ��Ƶ������PSC��ֵ */    
    #define TIM4_NVIC_PRE  2                     /* ��ռ���ȼ� */
    #define TIM4_NVIC_SUB  0                     /* ��Ӧ���ȼ� */
#endif


/* TIM5 �������� */
#if TIM5_SWITCH == 1  
    #define TIM5_ARR (1000-1)                   /* �������ڣ���ARR��ֵ */
    #define TIM5_PSC (72-1)                     /* Ԥ��Ƶ������PSC��ֵ */
    #define TIM5_NVIC_PRE  2                    /* ��ռ���ȼ� */
    #define TIM5_NVIC_SUB  0                    /* ��Ӧ���ȼ� */
#endif

/* TIM6 �������� */
#if TIM6_SWITCH == 1  
    #define TIM6_ARR (1000-1)                   /* �������ڣ���ARR��ֵ */
    #define TIM6_PSC (72-1)                     /* Ԥ��Ƶ������PSC��ֵ */
    #define TIM6_NVIC_PRE  5                    /* ��ռ���ȼ� */
    #define TIM6_NVIC_SUB  0                    /* ��Ӧ���ȼ� */
#endif

/* TIM7 �������� */
#if TIM7_SWITCH == 1  
    #define TIM7_ARR (1000-1)                   /* �������ڣ���ARR��ֵ */
    #define TIM7_PSC (72-1)                     /* Ԥ��Ƶ������PSC��ֵ */
    #define TIM7_NVIC_PRE  2                    /* ��ռ���ȼ� */
    #define TIM7_NVIC_SUB  0                    /* ��Ӧ���ȼ� */
#endif

/* TIM8 �������� */
#if TIM8_SWITCH == 1  
    #define TIM8_ARR (1000-1)                   /* �������ڣ���ARR��ֵ */
    #define TIM8_PSC (72-1)                     /* Ԥ��Ƶ������PSC��ֵ */
    #define TIM8_NVIC_PRE  2                    /* ��ռ���ȼ� */
    #define TIM8_NVIC_SUB  0                    /* ��Ӧ���ȼ� */
#endif
/**************************************************************/
/************************----- ��ʱ����ӳ������ -----************************/
/*
 *     ʹ��˵����    ����ͨ���ı�궨�����޸���ӳ��
                0x00  Ϊ  ����ӳ��
                0x10  Ϊ  ������ӳ��1    
                0x01  Ϊ  ������ӳ��2
                0x11  Ϊ  ��ȫ��ӳ��                    
 *
 */
#define TIM2_REMAP_SELECT   0x11
#define TIM3_REMAP_SELECT   0x00
/**************************************************************/





#endif

