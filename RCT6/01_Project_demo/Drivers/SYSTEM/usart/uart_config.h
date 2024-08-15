#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H
#include "stm32f10x.h"     // Device header



/************************* 串口选择  *****************************/
/* 定义使用哪个串口 */
#define  UARTX            2


/* 在选择串口1 后进而选择是否进行重映射 */
#if UARTX == 1
    #define  UART1_REMAP    0 
#endif
/************************************************************/



/************************* 数据包配置  *****************************/
/* 数据包长度设置 */
#define UART_Tx_Packet_Len  2        /* 发送数据包长度 */
#define UART_Rx_Packet_Len  2        /* 接受数据包长度 */

/* 发送数据包帧头帧尾设置 */
#define UART_Tx_Packet_FH1        0x3C
#define UART_Tx_Packet_FH2        0x2C
#define UART_Tx_Packet_FE        0x5B

/* 接收数据包帧头帧尾设置 */
#define UART_Rx_Packet_FH1        0x2C
#define UART_Rx_Packet_FH2        0x12
#define UART_Rx_Packet_FE        0x5B
/************************************************************/


#endif
