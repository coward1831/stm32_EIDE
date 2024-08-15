#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       ������ʼ������
 * @param       ��
 * @retval      ��
 */
void key_init(void)
{

    KEY0_GPIO_CLK_ENABLE();                                     /* KEY0ʱ��ʹ�� */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1ʱ��ʹ�� */
    WKUP_GPIO_CLK_ENABLE();                                     /* WKUPʱ��ʹ�� */
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                 /* �������� */
    GPIO_InitStructure.GPIO_Pin = KEY0_GPIO_PIN;                  /* KEY0���� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             /* ���� */
    GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStructure);                 /* KEY0����ģʽ����,�������� */

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                 /* �������� */
    GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;                  /* KEY0���� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             /* ���� */
    GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStructure);                 /* KEY0����ģʽ����,�������� */

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                 /* �������� */
    GPIO_InitStructure.GPIO_Pin = WKUP_GPIO_PIN;                  /* WKUP���� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             /* ���� */
    GPIO_Init(WKUP_GPIO_PORT, &GPIO_InitStructure);                 /* KEY0����ģʽ����,�������� */
}

/**
 * @brief       ����ɨ�躯��
 * @note        �ú�������Ӧ���ȼ�(ͬʱ���¶������): WK_UP > KEY1 > KEY0!!
 * @param       mode:0 / 1, ���庬������:
 *   @arg       0,  ��֧��������(���������²���ʱ, ֻ�е�һ�ε��û᷵�ؼ�ֵ,
 *                  �����ɿ��Ժ�, �ٴΰ��²Ż᷵��������ֵ)
 *   @arg       1,  ֧��������(���������²���ʱ, ÿ�ε��øú������᷵�ؼ�ֵ)
 * @retval      ��ֵ, ��������:
 *              KEY0_PRES, 1, KEY0����
 *              KEY1_PRES, 2, KEY1����
 *              WKUP_PRES, 3, WKUP����
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* �������ɿ���־ */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* ֧������ */

    if (key_up && (KEY0 == 0 || KEY1 == 0 || WK_UP == 1))  /* �����ɿ���־Ϊ1, ��������һ������������ */
    {
        delay_ms(10);           /* ȥ���� */
        key_up = 0;

        if (KEY0 == 0)  keyval = KEY0_PRES;

        if (KEY1 == 0)  keyval = KEY1_PRES;

        if (WK_UP == 1) keyval = WKUP_PRES;
    }
    else if (KEY0 == 1 && KEY1 == 1 && WK_UP == 0) /* û���κΰ�������, ��ǰ����ɿ� */
    {
        key_up = 1;
    }

    return keyval;              /* ���ؼ�ֵ */
}




















