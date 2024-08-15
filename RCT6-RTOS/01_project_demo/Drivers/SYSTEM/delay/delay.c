#include "./SYSTEM/delay/delay.h"
#include "FreeRTOS.h"

static uint16_t  g_fac_us = 0;     //1us内时钟振动的次数               


/**
  * @brief  初始化时钟源
  * @param  无
  * @retval 无
  */
void delay_init(void)
{
    uint32_t reload;
    
    /* SysTick 的工作时钟频率为 72MHz
     * 选择不分频，与freertos保持一致
     */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); /* 选择系统时钟 72MHz */
    reload = SystemCoreClock;                /* 72000000次(1s) */
    reload = reload/configTICK_RATE_HZ;      /* 重装值要跟FreeRTOS的时钟节拍一致 即 72000次 (1ms) */
    
    SysTick->LOAD = reload;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; /* 使能定时器 */
    
    g_fac_us =  SystemCoreClock/1000000; /* 1us振动的次数 如：1s跳动了72M次，故1us跳动了72次 */
}

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void delay_us(u32 xus)
{
    uint32_t ticks;
    uint32_t reload;
    uint32_t told,tnow,tcnt = 0;
    
    reload  = SysTick->LOAD;   /* 获取SysTick重装值 */
    ticks = xus * g_fac_us;    /* 1us需要计数的次数 */
    told = SysTick->VAL;       /* 获取当前计数值 */
    
    while(1)
    {
        tnow = SysTick->VAL;   /* 获取当前计数值 */
        
        if(tnow != told)
        {
            if(tnow < told)     /* 计数值还未清0过时，即当前计数循环 */
            {
                tcnt += told - tnow;
            }
            else                /* 已经超过一次计数循环 */
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if(tcnt >= ticks)   /* 到达需要延迟的时间后退出 */
            {
                break;
            }
        }
    }
    
    /* 这里没有计次完就关闭滴答定时器以及清空计数值
     * 是因为滴答定时器是与RTOS的心跳节拍有关，如果关掉了滴答定时器。
     * 或者重装了计数器，就会出现RTOS任务卡死，或者心跳节拍出错问题。
    */
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

