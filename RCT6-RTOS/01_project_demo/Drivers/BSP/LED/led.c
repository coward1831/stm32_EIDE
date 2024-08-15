#include "./BSP/LED/led.h"


/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void led_init(void)
{
    /*开启GPIO的外设时钟*/
    LED0_GPIO_CLK_ENABLE();                                 /* LED0时钟使能 */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1时钟使能 */
    
    /*定义一个GPIO_InitStructure类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            /* 推挽输出 */ 
    GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;                /* LED0引脚 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           /* 高速 */
    GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);               /* 初始化LED0引脚 */

    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;                /* LED1引脚 */
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);             /* 初始化LED1引脚 */
    

    LED0(0);                                                /* 关闭 LED0 */
    LED1(0);                                                /* 关闭 LED1 */
}

