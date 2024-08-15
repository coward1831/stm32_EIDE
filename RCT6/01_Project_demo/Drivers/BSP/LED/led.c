#include "./BSP/LED/led.h"


/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void led_init(void)
{
    /*����GPIO������ʱ��*/
    LED0_GPIO_CLK_ENABLE();                                 /* LED0ʱ��ʹ�� */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1ʱ��ʹ�� */
    
    /*����һ��GPIO_InitStructure���͵Ľṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            /* ������� */ 
    GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;                /* LED0���� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           /* ���� */
    GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);               /* ��ʼ��LED0���� */

    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;                /* LED1���� */
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);             /* ��ʼ��LED1���� */
    

    LED0(0);                                                /* �ر� LED0 */
    LED1(0);                                                /* �ر� LED1 */
}

