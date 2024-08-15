#include "./BSP/TIMER/gtim.h"


/**
 * @brief       定时器初始化
 * @param       TIMx                     选择哪个定时器
 * @param       TIMx_ARR                  计数周期，即ARR的值
 * @param       TIMx_PSC                  预分频器，即PSC的值
 * @param       TIMx_INT_SWITCH          中断开关 
 * @param       TIMx_INT_IRQn              中断线        
 * @param       TIMx_NVIC_PRE              中断抢占优先级
 * @param       TIMx_NVIC_SUB              中断响应优先级
 * @retval      无
 */
static void tim_timx_int_init(TIM_TypeDef* TIMx,uint16_t TIMx_ARR,uint16_t TIMx_PSC,uint8_t TIMx_INT_SWITCH,uint8_t TIMx_INT_IRQn,uint8_t TIMx_NVIC_PRE,uint8_t TIMx_NVIC_SUB)
{
    
    /*配置时钟源*/
    TIM_InternalClockConfig(TIMx);        //选择TIM为内部时钟，若不调用此函数，TIM默认也为内部时钟
    
    /*时基单元初始化*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                //定义结构体变量
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;        //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;    //计数器模式，选择向上计数
    TIM_TimeBaseInitStructure.TIM_Period = TIMx_ARR;                    //计数周期，即ARR的值
    TIM_TimeBaseInitStructure.TIM_Prescaler = TIMx_PSC;                //预分频器，即PSC的值
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure);                //将结构体变量交给TIM_TimeBaseInit，配置TIM的时基单元    
    
    
    /*中断输出配置*/
    if(TIMx_INT_SWITCH)
    {
        
        TIM_ClearFlag(TIMx, TIM_FLAG_Update);                    //清除定时器更新标志位
                                                                //TIM_TimeBaseInit函数末尾，手动产生了更新事件
                                                                //若不清除此标志位，则开启中断后，会立刻进入一次中断
                                                                //如果不介意此问题，则不清除此标志位也可
        TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);              //开启TIM的更新中断
        
        /* NVIC中断分组 */
        //    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //配置NVIC为分组2
                                                                //即抢占优先级范围：0~3，响应优先级范围：0~3
                                                                //此分组配置在整个工程中仅需调用一次
                                                                //若有多个中断，可以把此代码放在main函数内，while循环之前
                                                                //若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
        /*NVIC配置*/
        NVIC_InitTypeDef NVIC_InitStructure;                        //定义结构体变量
        NVIC_InitStructure.NVIC_IRQChannel = TIMx_INT_IRQn;    //选择配置NVIC的TIM线
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //指定NVIC线路使能
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_NVIC_PRE;    //指定NVIC线路的抢占优先级为2
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_NVIC_SUB;            //指定NVIC线路的响应优先级为1
        NVIC_Init(&NVIC_InitStructure);                                //将结构体变量交给NVIC_Init，配置NVIC外设
    
    }
}


/**
 * @brief       定时器初始化
 * @param       无
 * @retval      无
 */
void timx_init(void)
{
    #if TIM1_SWITCH == 1
    TIM_TIM1_INT_CLK_ENABLE();                  //开启TIM的时钟
    tim_timx_int_init(TIM_TIM1_INT,TIM1_ARR,TIM1_PSC,TIM1_NVIC_SWITCH,TIM_TIM1_INT_IRQn,TIM1_NVIC_PRE,TIM1_NVIC_SUB);
    #endif
    
    #if TIM2_SWITCH == 1
    TIM_TIM2_INT_CLK_ENABLE();                  //开启TIM的时钟
        #if TIM2_REMAP_SELECT                   //重映像设置
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
            GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  // 切换到SWJ调试，释放PA15，PB4, PB3
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
    TIM_TIM3_INT_CLK_ENABLE();                  //开启TIM的时钟
        #if TIM3_REMAP_SELECT                   //重映像设置
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
            GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  // 切换到SWJ调试，释放PA15，PB4, PB3
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
    TIM_TIM4_INT_CLK_ENABLE();                  //开启TIM的时钟
    tim_timx_int_init(TIM_TIM4_INT,TIM4_ARR,TIM4_PSC,TIM4_NVIC_SWITCH,TIM_TIM4_INT_IRQn,TIM4_NVIC_PRE,TIM4_NVIC_SUB);
    #endif
    
    #if TIM5_SWITCH == 1
    TIM_TIM5_INT_CLK_ENABLE();                  //开启TIM的时钟
    tim_timx_int_init(TIM_TIM5_INT,TIM5_ARR,TIM5_PSC,TIM5_NVIC_SWITCH,TIM_TIM5_INT_IRQn,TIM5_NVIC_PRE,TIM5_NVIC_SUB);
    #endif
    
    #if TIM6_SWITCH == 1
    TIM_TIM6_INT_CLK_ENABLE();                  //开启TIM的时钟
    tim_timx_int_init(TIM_TIM6_INT,TIM6_ARR,TIM6_PSC,TIM6_NVIC_SWITCH,TIM_TIM6_INT_IRQn,TIM6_NVIC_PRE,TIM6_NVIC_SUB);
    #endif
    
    #if TIM7_SWITCH == 1
    TIM_TIM7_INT_CLK_ENABLE();                  //开启TIM的时钟
    tim_timx_int_init(TIM_TIM7_INT,TIM7_ARR,TIM7_PSC,TIM7_NVIC_SWITCH,TIM_TIM7_INT_IRQn,TIM7_NVIC_PRE,TIM7_NVIC_SUB);
    #endif
    
    #if TIM8_SWITCH == 1
    TIM_TIM8_INT_CLK_ENABLE();                  //开启TIM的时钟
    tim_timx_int_init(TIM_TIM8_INT,TIM8_ARR,TIM8_PSC,TIM8_NVIC_SWITCH,TIM_TIM8_INT_IRQn,TIM8_NVIC_PRE,TIM8_NVIC_SUB);
    #endif
}
/**
 * @brief       开启定时器
 * @param       无
 * @retval      无
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

