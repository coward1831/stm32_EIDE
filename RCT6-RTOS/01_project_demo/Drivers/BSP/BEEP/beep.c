#include "./BSP/BEEP/beep.h"

/**
 * @brief       初始化BEEP相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void beep_init(void)
{

    BEEP_GPIO_CLK_ENABLE();                             /* BEEP时钟使能 */
	
	/*定义一个GPIO_InitStructure类型的结构体*/	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            /* 推挽输出 */ 
    GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;                /* 蜂鸣器引脚 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           /* 高速 */
    GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);   /* 初始化蜂鸣器引脚 */
    BEEP(0);                                            /* 关闭蜂鸣器 */
}





