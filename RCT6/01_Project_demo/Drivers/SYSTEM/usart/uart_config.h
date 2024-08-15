#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H
#include "stm32f10x.h"     // Device header



/************************* ����ѡ��  *****************************/
/* ����ʹ���ĸ����� */
#define  UARTX            2


/* ��ѡ�񴮿�1 �����ѡ���Ƿ������ӳ�� */
#if UARTX == 1
    #define  UART1_REMAP    0 
#endif
/************************************************************/



/************************* ���ݰ�����  *****************************/
/* ���ݰ��������� */
#define UART_Tx_Packet_Len  2        /* �������ݰ����� */
#define UART_Rx_Packet_Len  2        /* �������ݰ����� */

/* �������ݰ�֡ͷ֡β���� */
#define UART_Tx_Packet_FH1        0x3C
#define UART_Tx_Packet_FH2        0x2C
#define UART_Tx_Packet_FE        0x5B

/* �������ݰ�֡ͷ֡β���� */
#define UART_Rx_Packet_FH1        0x2C
#define UART_Rx_Packet_FH2        0x12
#define UART_Rx_Packet_FE        0x5B
/************************************************************/


#endif
