#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/uart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/OLED_IIC/oled.h"

void all_init(void);

uint8_t test_num = 0;
uint8_t cnt = 0;
int main(void)
{
    all_init();
    while (1)
    {
        oled_show_num(1, 16, test_num, 1);
        oled_show_string(4, 1, "Hello World!");
        delay_ms(500);
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
        if (tim_count >= 1000)
        {
            test_num++;
            tim_count = 0;
        }
        if (led_count >= 500)
        {
            // LED0_TOGGLE();
            LED1_TOGGLE();
            led_count = 0;
        }
        TIM_ClearITPendingBit(TIM_TIM6_INT, TIM_IT_Update);
    }
}
#endif

void all_init(void)
{
    delay_init();
    led_init();
    key_init();
    uart_init();
    oled_init();

    timx_init();
    timx_run();

    oled_show_string(1, 1, "Load...");
    delay_ms(1000);
    oled_clear();
}
