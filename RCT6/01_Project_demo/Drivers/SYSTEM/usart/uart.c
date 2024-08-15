#include "./SYSTEM/usart/uart.h"


/*************************重定向，可以使用printf *****************************/
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
    int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
    x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
    while((UART_X->SR&0X40)==0); 
    UART_X->DR=(u8)ch;      
    return ch;
}
#endif 
/******************************************************************************/


uint8_t UART_Rx_Data;
uint8_t UART_Rx_Flag;

uint8_t UART_Tx_Packet[UART_Tx_Packet_Len];//发送数据包
uint8_t UART_Rx_Packet[UART_Rx_Packet_Len];//接受数据包

static void uart_gpio_init(void)
{
    /*开启GPIO的外设时钟*/
    UART_TX_GPIO_CLK_ENABLE();                                 /* TX脚使能 */
    UART_RX_GPIO_CLK_ENABLE();                                 /* RX脚使能  */
    
    #if UART1_REMAP == 1 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
    #endif
    
    /* TX——GPIO初始化 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                /* 发送口,推挽输出 */ 
    GPIO_InitStructure.GPIO_Pin = UART_TX_GPIO_PIN;             /* TX */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           /* 高速 */
    GPIO_Init(UART_TX_GPIO_PORT, &GPIO_InitStructure);

    
    /* RX——GPIO初始化 */
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;                    /* 上拉输入，接收端 */ 
    GPIO_InitStructure.GPIO_Pin = UART_RX_GPIO_PIN;             /* RX */
    GPIO_Init(UART_RX_GPIO_PORT, &GPIO_InitStructure);
}

void uart_init(void)
{
    uart_gpio_init();

    /* 开启串口的时钟 */
    UART_X_CLK_ENABLE();
    
    /* USART初始化 */
    USART_InitTypeDef USART_InitStructure;                            //定义结构体变量
    USART_InitStructure.USART_BaudRate = UART_BAUDRATE;                        //波特率
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    //硬件流控制，不需要
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;    //模式，发送模式和接收模式均选择
    USART_InitStructure.USART_Parity = USART_Parity_No;                //奇偶校验，不需要
    USART_InitStructure.USART_StopBits = USART_StopBits_1;            //停止位，选择1位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //字长，选择8位
    USART_Init(UART_X, &USART_InitStructure);                        //将结构体变量交给USART_Init，配置USART1
    
    /* 中断输出配置 */
    USART_ITConfig(UART_X, USART_IT_RXNE, ENABLE);            //开启串口接收数据的中断
    
    /* NVIC中断分组 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);            //配置NVIC为分组2
    
    /* NVIC配置 */
    NVIC_InitTypeDef NVIC_InitStructure;                        //定义结构体变量
    NVIC_InitStructure.NVIC_IRQChannel = UART_IRQn;                //选择配置NVIC的USART1线
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //指定NVIC线路使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    //指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            //指定NVIC线路的响应优先级为1
    NVIC_Init(&NVIC_InitStructure);                                //将结构体变量交给NVIC_Init，配置NVIC外设
    
    /* USART使能 */
    USART_Cmd(UART_X, ENABLE);                                    //使能USART，串口开始运行
    
    USART_ClearFlag(UART_X,USART_FLAG_TC);                        //清楚串口发送标志位
}

/**
 * @brief       次方函数（内部使用）
 * @retval      返回值等于X的Y次方
 */
static uint32_t uart_pow(uint32_t X,uint32_t Y)
{
    uint32_t result=1;    //设置结果初值为1
    while(Y--)            //执行Y次
    {
        result*=X;        //将X累乘到结果
    }
    return result;
}

/**
 * @brief       发送一个字节
 * @param       Byte 要发送的一个字节
 * @retval      无
 */
void uart_send_byte(uint8_t Byte)
{
    USART_SendData(UART_X, Byte);        //将字节数据写入数据寄存器，写入后USART自动生成时序波形
    while (USART_GetFlagStatus(UART_X, USART_FLAG_TXE) == RESET);    //等待发送完成
    /*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}

/**
 * @brief       串口发送一个数组
 * @param       Array 要发送数组的首地址
 * @param       Length 要发送数组的长度
 * @retval      无
 */
void uart_send_array(uint8_t *Array,uint16_t Length)//发送一个数组
{
    uint16_t i;
    for (i = 0; i < Length; i ++)        //遍历数组
    {
        uart_send_byte(Array[i]);        //依次调用uart_send_byte发送每个字节数据
    }
}

/**
 * @brief       串口发送一个数组
 * @param       Array 要发送数组的首地址
 * @param       Length 要发送数组的长度
 * @retval      无
 */
void uart_send_string(char *String)
{
    while(*String)//遍历字符数组（字符串），遇到字符串结束标志位后停止
    {
        uart_send_byte(*String++);//依次调用uart_send_byte发送每个字节数据
    }
}

/**
 * @brief       串口发送数字
 * @param       Num 要发送的数字，范围：0~4294967295
 * @param       Length 要发送数字的长度，范围：0~10
 * @retval      无
 */
void uart_send_num(uint32_t Num,uint8_t Length)
{
    uint8_t i;
    for(i=0;i<Length;i++)
    {
        uart_send_byte(Num/uart_pow(10,Length-i-1)%10+'0');  
    }
}

/**
 * @brief       自己封装的prinf函数
 * @param       format 格式化字符串
 * @param       ... 可变的参数列表
 * @retval      无
 */
void uart_printf(char *format,...)
{
    char String[100];
    va_list arg;
    va_start(arg,format);
    vsprintf(String,format,arg);
    va_end(arg);
    uart_send_string(String);
}

/**
 * @brief       获取串口接收标志位
 * @param       无
 * @retval      串口接收标志位，范围：0~1，
                接收到数据后，标志位置1，读取后标志位自动清零
 */
uint8_t uart_get_rx_flag(void)
{
    if(UART_Rx_Flag == 1)  //如果标志位为1
    {
        UART_Rx_Flag=0;
        return 1;        //则返回1，并自动清零标志位
    }
    return 0;            //如果标志位为0，则返回0
}

/**
 * @brief       获取串口接收的数据
 * @param       无
 * @retval      接收的数据，范围：0~255
 */
uint8_t uart_get_rx_data(void)
{
    return UART_Rx_Data;
}

void uart_send_packet(void)
{
    uart_send_byte(UART_Tx_Packet_FH1);
    uart_send_byte(UART_Tx_Packet_FH2);
    uart_send_array(UART_Tx_Packet,UART_Tx_Packet_Len);
    uart_send_byte(UART_Tx_Packet_FE);
}

/**
 * @brief       USART中断函数
 * @param       无
 * @retval      无
 * @note        此函数为中断函数，无需调用，中断触发后自动执行
 */
void UART_IRQHandler(void)
{
    static uint8_t RxState=0;
    static uint8_t pRxPacket=0;
    if(USART_GetFlagStatus(UART_X,USART_IT_RXNE)==SET)
    {
        UART_Rx_Data=USART_ReceiveData(UART_X);
        if(RxState==0&&UART_Rx_Data==UART_Rx_Packet_FH1) //第一个帧头
        {
            RxState=1;
        }
        else if(RxState==1&&UART_Rx_Data==UART_Rx_Packet_FH2) //第二个帧头
        {
            RxState=2;
        }
        else if(RxState==2)//传输的数据
        {    
            UART_Rx_Packet[pRxPacket++]=UART_Rx_Data;//把数据放在数据包内
            if(pRxPacket>=UART_Rx_Packet_Len)
            {
                RxState=3;
            }
        }
        else if(RxState==3&&UART_Rx_Data==UART_Rx_Packet_FE)
        {    
            pRxPacket=0;
            RxState=0;
            UART_Rx_Flag=1;
        }
        USART_ClearITPendingBit(UART_X,USART_IT_RXNE);
    }
}
