#ifndef __UART_H
#define __UART_H
#include "./SYSTEM/usart/uart_config.h"
#include <stdarg.h>
#include <stdio.h>


#if UARTX == 1
/******************************************************************************************/
#if UART1_REMAP == 1
#define UART_TX_GPIO_PORT                   GPIOB
#define UART_TX_GPIO_PIN                    GPIO_Pin_6
#define UART_TX_GPIO_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); }while(0)             /* TX时钟使能 */

#define UART_RX_GPIO_PORT                   GPIOB
#define UART_RX_GPIO_PIN                    GPIO_Pin_7
#define UART_RX_GPIO_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); }while(0)             /* RX时钟使能 */
#else
#define UART_TX_GPIO_PORT                   GPIOA
#define UART_TX_GPIO_PIN                    GPIO_Pin_9
#define UART_TX_GPIO_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)             /* TX时钟使能 */

#define UART_RX_GPIO_PORT                   GPIOA
#define UART_RX_GPIO_PIN                    GPIO_Pin_10
#define UART_RX_GPIO_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)             /* RX时钟使能 */
#endif
/******************************************************************************************/
/* UART 定义 */
#define UART_X                          USART1 
#define UART_X_CLK_ENABLE()          do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); }while(0)             /* 注意在APB1还是APB2 */
#define UART_BAUDRATE                 115200
#define UART_IRQn                     USART1_IRQn
#define UART_IRQHandler              USART1_IRQHandler
/******************************************************************************************/
#endif

#if UARTX == 2
/******************************************************************************************/
/* 引脚 定义 */
#define UART_TX_GPIO_PORT                   GPIOA
#define UART_TX_GPIO_PIN                    GPIO_Pin_2
#define UART_TX_GPIO_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)             /* TX时钟使能 */

#define UART_RX_GPIO_PORT                   GPIOA
#define UART_RX_GPIO_PIN                    GPIO_Pin_3
#define UART_RX_GPIO_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)             /* RX时钟使能 */
/******************************************************************************************/
/******************************************************************************************/
/* UART 定义 */
#define UART_X                          USART2  
#define UART_X_CLK_ENABLE()          do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); }while(0)             /* 注意在APB1还是APB2 */
#define UART_BAUDRATE                 115200
#define UART_IRQn                     USART2_IRQn
#define UART_IRQHandler              USART2_IRQHandler
/******************************************************************************************/
#endif

#if UARTX == 3
/******************************************************************************************/
/* 引脚 定义 */
#define UART_TX_GPIO_PORT                   GPIOB
#define UART_TX_GPIO_PIN                    GPIO_Pin_10
#define UART_TX_GPIO_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); }while(0)             /* TX时钟使能 */

#define UART_RX_GPIO_PORT                   GPIOB
#define UART_RX_GPIO_PIN                    GPIO_Pin_11
#define UART_RX_GPIO_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); }while(0)             /* RX时钟使能 */
/******************************************************************************************/
/******************************************************************************************/
/* UART 定义 */
#define UART_X                          USART3 
#define UART_X_CLK_ENABLE()          do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); }while(0)             /* 注意在APB1还是APB2 */
#define UART_BAUDRATE                 115200
#define UART_IRQn                     USART3_IRQn
#define UART_IRQHandler              USART3_IRQHandler
/******************************************************************************************/
#endif




extern uint8_t UART_Rx_Data;
extern uint8_t UART_Rx_Flag;

extern uint8_t UART_Tx_Packet[UART_Tx_Packet_Len];//发送数据包
extern uint8_t UART_Rx_Packet[UART_Rx_Packet_Len];//接受数据包

void uart_init(void);
void uart_send_byte(uint8_t Byte);
void uart_send_array(uint8_t *Array,uint16_t Length);
void uart_send_string(char *String);
void uart_send_num(uint32_t Num,uint8_t Length);
void uart_printf(char *format,...);
uint8_t uart_get_rx_flag(void);
uint8_t uart_get_rx_data(void);
void uart_send_packet(void);

#endif

