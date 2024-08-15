#include "./FreeRTOS/freertos_run.h"


int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  /* ÅäÖÃNVICÎª·Ö×é4 */
    delay_init();
    led_init();
    key_init();
    oled_init();
    
    oled_show_string(1,1,"LOAD...");
    delay_ms(1000);
    oled_clear();
    
    uart_init();
    timx_init();
    timx_run();
    os_run();

    while(1)
    {
        
    }
}

#if TIM6_NVIC_SWITCH == 1
void TIM_TIM6_INT_IRQHandler(void)
{
    static uint16_t tim_count;
    static uint16_t led_count;    
    if (TIM_GetITStatus(TIM_TIM6_INT, TIM_IT_Update) == SET)
    {
        tim_count++;
        led_count++;
        if(led_count>=500)
        {
//            LED1_TOGGLE();
            led_count=0;
        }
        TIM_ClearITPendingBit(TIM_TIM6_INT, TIM_IT_Update);
    }
}
#endif
