#include "./BSP/BEEP/beep.h"

/**
 * @brief       ��ʼ��BEEP���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void beep_init(void)
{

    BEEP_GPIO_CLK_ENABLE();                             /* BEEPʱ��ʹ�� */
	
	/*����һ��GPIO_InitStructure���͵Ľṹ��*/	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            /* ������� */ 
    GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;                /* ���������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           /* ���� */
    GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);   /* ��ʼ������������ */
    BEEP(0);                                            /* �رշ����� */
}





