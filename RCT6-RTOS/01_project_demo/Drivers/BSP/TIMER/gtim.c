#include "./BSP/TIMER/gtim.h"


/**
 * @brief       ��ʱ����ʼ��
 * @param       TIMx                     ѡ���ĸ���ʱ��
 * @param       TIMx_ARR                  �������ڣ���ARR��ֵ
 * @param       TIMx_PSC                  Ԥ��Ƶ������PSC��ֵ
 * @param       TIMx_INT_SWITCH          �жϿ��� 
 * @param       TIMx_INT_IRQn              �ж���        
 * @param       TIMx_NVIC_PRE              �ж���ռ���ȼ�
 * @param       TIMx_NVIC_SUB              �ж���Ӧ���ȼ�
 * @retval      ��
 */
static void tim_timx_int_init(TIM_TypeDef* TIMx,uint16_t TIMx_ARR,uint16_t TIMx_PSC,uint8_t TIMx_INT_SWITCH,uint8_t TIMx_INT_IRQn,uint8_t TIMx_NVIC_PRE,uint8_t TIMx_NVIC_SUB)
{
    
    /*����ʱ��Դ*/
    TIM_InternalClockConfig(TIMx);        //ѡ��TIMΪ�ڲ�ʱ�ӣ��������ô˺�����TIMĬ��ҲΪ�ڲ�ʱ��
    
    /*ʱ����Ԫ��ʼ��*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                //����ṹ�����
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;        //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;    //������ģʽ��ѡ�����ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = TIMx_ARR;                    //�������ڣ���ARR��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = TIMx_PSC;                //Ԥ��Ƶ������PSC��ֵ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //�ظ����������߼���ʱ���Ż��õ�
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure);                //���ṹ���������TIM_TimeBaseInit������TIM��ʱ����Ԫ    
    
    
    /*�ж��������*/
    if(TIMx_INT_SWITCH)
    {
        
        TIM_ClearFlag(TIMx, TIM_FLAG_Update);                    //�����ʱ�����±�־λ
                                                                //TIM_TimeBaseInit����ĩβ���ֶ������˸����¼�
                                                                //��������˱�־λ�������жϺ󣬻����̽���һ���ж�
                                                                //�������������⣬������˱�־λҲ��
        TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);              //����TIM�ĸ����ж�
        
        /* NVIC�жϷ��� */
        //    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //����NVICΪ����2
                                                                //����ռ���ȼ���Χ��0~3����Ӧ���ȼ���Χ��0~3
                                                                //�˷������������������н������һ��
                                                                //���ж���жϣ����԰Ѵ˴������main�����ڣ�whileѭ��֮ǰ
                                                                //�����ö�����÷���Ĵ��룬���ִ�е����ûḲ����ִ�е�����
        /*NVIC����*/
        NVIC_InitTypeDef NVIC_InitStructure;                        //����ṹ�����
        NVIC_InitStructure.NVIC_IRQChannel = TIMx_INT_IRQn;    //ѡ������NVIC��TIM��
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //ָ��NVIC��·ʹ��
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_NVIC_PRE;    //ָ��NVIC��·����ռ���ȼ�Ϊ2
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_NVIC_SUB;            //ָ��NVIC��·����Ӧ���ȼ�Ϊ1
        NVIC_Init(&NVIC_InitStructure);                                //���ṹ���������NVIC_Init������NVIC����
    
    }
}


/**
 * @brief       ��ʱ����ʼ��
 * @param       ��
 * @retval      ��
 */
void timx_init(void)
{
    #if TIM1_SWITCH == 1
    TIM_TIM1_INT_CLK_ENABLE();                  //����TIM��ʱ��
    tim_timx_int_init(TIM_TIM1_INT,TIM1_ARR,TIM1_PSC,TIM1_NVIC_SWITCH,TIM_TIM1_INT_IRQn,TIM1_NVIC_PRE,TIM1_NVIC_SUB);
    #endif
    
    #if TIM2_SWITCH == 1
    TIM_TIM2_INT_CLK_ENABLE();                  //����TIM��ʱ��
        #if TIM2_REMAP_SELECT                   //��ӳ������
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
            GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  // �л���SWJ���ԣ��ͷ�PA15��PB4, PB3
            switch(TIM2_REMAP_SELECT)
            {
                case 0x10: GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);break;
                case 0x01: GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);break;
                case 0x11: GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);break;
                default :break;
            }
        #endif
    tim_timx_int_init(TIM_TIM2_INT,TIM2_ARR,TIM2_PSC,TIM2_NVIC_SWITCH,TIM_TIM2_INT_IRQn,TIM2_NVIC_PRE,TIM2_NVIC_SUB);
    #endif
    
    #if TIM3_SWITCH == 1
    TIM_TIM3_INT_CLK_ENABLE();                  //����TIM��ʱ��
        #if TIM3_REMAP_SELECT                   //��ӳ������
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
            GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  // �л���SWJ���ԣ��ͷ�PA15��PB4, PB3
            switch(TIM3_REMAP_SELECT)
            {
                case 0x10: GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);break;
                case 0x11: GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);break;
                default :break;
            }
        #endif
    tim_timx_int_init(TIM_TIM3_INT,TIM3_ARR,TIM3_PSC,TIM3_NVIC_SWITCH,TIM_TIM3_INT_IRQn,TIM3_NVIC_PRE,TIM3_NVIC_SUB);
    #endif
    
    #if TIM4_SWITCH == 1
    TIM_TIM4_INT_CLK_ENABLE();                  //����TIM��ʱ��
    tim_timx_int_init(TIM_TIM4_INT,TIM4_ARR,TIM4_PSC,TIM4_NVIC_SWITCH,TIM_TIM4_INT_IRQn,TIM4_NVIC_PRE,TIM4_NVIC_SUB);
    #endif
    
    #if TIM5_SWITCH == 1
    TIM_TIM5_INT_CLK_ENABLE();                  //����TIM��ʱ��
    tim_timx_int_init(TIM_TIM5_INT,TIM5_ARR,TIM5_PSC,TIM5_NVIC_SWITCH,TIM_TIM5_INT_IRQn,TIM5_NVIC_PRE,TIM5_NVIC_SUB);
    #endif
    
    #if TIM6_SWITCH == 1
    TIM_TIM6_INT_CLK_ENABLE();                  //����TIM��ʱ��
    tim_timx_int_init(TIM_TIM6_INT,TIM6_ARR,TIM6_PSC,TIM6_NVIC_SWITCH,TIM_TIM6_INT_IRQn,TIM6_NVIC_PRE,TIM6_NVIC_SUB);
    #endif
    
    #if TIM7_SWITCH == 1
    TIM_TIM7_INT_CLK_ENABLE();                  //����TIM��ʱ��
    tim_timx_int_init(TIM_TIM7_INT,TIM7_ARR,TIM7_PSC,TIM7_NVIC_SWITCH,TIM_TIM7_INT_IRQn,TIM7_NVIC_PRE,TIM7_NVIC_SUB);
    #endif
    
    #if TIM8_SWITCH == 1
    TIM_TIM8_INT_CLK_ENABLE();                  //����TIM��ʱ��
    tim_timx_int_init(TIM_TIM8_INT,TIM8_ARR,TIM8_PSC,TIM8_NVIC_SWITCH,TIM_TIM8_INT_IRQn,TIM8_NVIC_PRE,TIM8_NVIC_SUB);
    #endif
}
/**
 * @brief       ������ʱ��
 * @param       ��
 * @retval      ��
 */
void timx_run(void)
{
    #if TIM1_SWITCH == 1
    TIM_Cmd(TIM1,ENABLE);
    #endif    
    
    #if TIM2_SWITCH == 1
    TIM_Cmd(TIM2,ENABLE);
    #endif
    
    #if TIM3_SWITCH == 1
    TIM_Cmd(TIM3,ENABLE);
    #endif
    
    #if TIM4_SWITCH == 1
    TIM_Cmd(TIM4,ENABLE);
    #endif
    
    #if TIM5_SWITCH == 1
    TIM_Cmd(TIM5,ENABLE);
    #endif
    
    #if TIM6_SWITCH == 1
    TIM_Cmd(TIM6,ENABLE);
    #endif
    
    #if TIM7_SWITCH == 1
    TIM_Cmd(TIM7,ENABLE);
    #endif
    
    #if TIM8_SWITCH == 1
    TIM_Cmd(TIM8,ENABLE);
    #endif
}

/*
#if TIM1_NVIC_SWITCH == 1
void TIM_TIM1_INT_IRQHandler(void)
{
    static uint16_t tim_count;
    if (TIM_GetITStatus(TIM_TIM1_INT, TIM_IT_Update) == SET)
    {
        tim_count++;
        if(tim_count>=1000)
        {
            test_num++;
            tim_count=0;
        }
        TIM_ClearITPendingBit(TIM_TIM1_INT, TIM_IT_Update);
    }
}
#endif
*/

