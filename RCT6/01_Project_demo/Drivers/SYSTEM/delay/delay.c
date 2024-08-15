#include "./SYSTEM/delay/delay.h"

static u16  fac_us = 0;                            //us延时倍乘数               
//static u16  fac_ms = 0;                            //ms延时倍乘数


/**
  * @brief  初始化时钟源
  * @param  无
  * @retval 无
  */
void delay_init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //选择外部时钟源 72/8=9MHz
    fac_us = SystemCoreClock / 8000000;       //1us 需要时钟振动 9次
//    fac_ms = fac_us*1000;                   //1ms 需要时钟振动 9000次
}

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_us(u32 xus)
{
    u32 temp;
    SysTick->LOAD = xus*fac_us;   //重装值
    SysTick->VAL = 0x00;          //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //使能定时器
    do
    {
        temp = SysTick->CTRL;                    //获取状态控制寄存器
    }while((temp&(0x01<<0))&&!(temp&(0x01<<16)));//判断定时器使能位（0）和数值是否数完的标志位（16）
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  //失能定时器
    SysTick->VAL = 0x00;                        //清空计数器
}
/**
  * @brief  毫秒级延时
  * @param  xms 延时时长
  * @retval 无
  */
void delay_ms(u32 xms)
{
    while(xms--)
    {
        delay_us(1000);
    }
}

