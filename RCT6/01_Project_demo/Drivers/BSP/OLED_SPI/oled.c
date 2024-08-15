#include "./BSP/OLED_SPI/oled.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/OLED_SPI/oled_font.h"

/**********************************----- 软件SPI -----************************************/
/**
 * @brief       	SPI发送一个字节
 * @param       	Byte 要发送的一个字节数据，范围：0x00~0xFF
 * @retval      	无
 */
static void oled_spi_send_byte(uint8_t Byte)
{
	uint8_t i;
	
	/*循环8次，主机依次发送数据的每一位*/
	for (i = 0; i < 8; i++)
	{
		/*使用掩码的方式取出Byte的指定一位数据并写入到SDA线*/
		/*两个!的作用是，让所有非零的值变为1*/
		OLED_W_SDA(!!(Byte & (0x80 >> i)));
		OLED_W_SCL(1);	//拉高SCL，从机在D0上升沿读取SDA
		OLED_W_SCL(0);	//拉低SCL，主机开始发送下一位数据
	}
}

/**
 * @brief       	OLED写命令
 * @param       	Command 要写入的命令值，范围：0x00~0xFF
 * @retval      	无
 */
static void oled_write_command(uint8_t Command)
{
	OLED_W_DC(0);					//拉低DC，表示即将发送命令
	oled_spi_send_byte(Command);	//写入指定的命令
}

/**
  * @brief			OLED写数据
  * @param 			Data 要写入数据的起始地址
  * @param 			Count 要写入数据的数量
  * @retval			无
  */
static void oled_write_data(uint8_t Data)
{

	OLED_W_DC(1);						//拉高DC，表示即将发送数据
	oled_spi_send_byte(Data);			//发送Data

}
/*****************************************************************************************************/

/**********************************----- 硬件配置 -----************************************/

/**
 * @brief       	初始化OLED相关IO口, 并使能时钟
 * @param       	无
 * @retval      	无
 */
static void oled_gpio_init(void)
{
	delay_ms(1000);

	OLED_SPI_SCL_CLK_ENABLE();
	OLED_SPI_SDA_CLK_ENABLE();
    OLED_SPI_RES_CLK_ENABLE();
	OLED_SPI_DC_CLK_ENABLE();
	
	/*将引脚初始化为推挽模式*/
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = OLED_SPI_SCL_PIN;
 	GPIO_Init(OLED_SPI_SCL_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = OLED_SPI_SDA_PIN;
 	GPIO_Init(OLED_SPI_SDA_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = OLED_SPI_RES_PIN;
 	GPIO_Init(OLED_SPI_RES_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = OLED_SPI_DC_PIN;
 	GPIO_Init(OLED_SPI_DC_PORT, &GPIO_InitStructure);	
	
	/*置引脚默认电平*/
	OLED_W_SCL(0);
	OLED_W_SDA(1);
	OLED_W_RES(1);
	OLED_W_DC(1);
}
/**
 * @brief       	次方函数
 * @param       	X 底数
 * @param       	Y 指数
 * @retval      	无
 */
static uint32_t oled_pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//结果默认为1
	while (Y --)			//累乘Y次
	{
		Result *= X;		//每次把X累乘到结果上
	}
	return Result;
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
static void oled_set_pos(uint8_t Y, uint8_t X)
{
	oled_write_command(0xB0 | Y);					//设置Y位置
	oled_write_command(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	oled_write_command(0x00 | (X & 0x0F));			//设置X位置低4位
}

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void oled_clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		oled_set_pos(j, 0);
		for(i = 0; i < 128; i++)
		{
			oled_write_data(0x00);
		}
	}
}

/**
  * @brief  OLED显示一个字符
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void oled_show_char(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	oled_set_pos((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		oled_write_data(OLED_F8x16[Char - ' '][i]);			//显示上半部分内容
	}
	oled_set_pos((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		oled_write_data(OLED_F8x16[Char - ' '][i + 8]);		//显示下半部分内容
	}
}

/**
  * @brief  OLED显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void oled_show_string(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		oled_show_char(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLED显示数字（十进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void oled_show_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		oled_show_char(Line, Column + i, Number / oled_pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void oled_show_signed_num(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		oled_show_char(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		oled_show_char(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		oled_show_char(Line, Column + i + 1, Number1 / oled_pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void oled_show_hex_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / oled_pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			oled_show_char(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			oled_show_char(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  OLED显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void oled_show_bin_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		oled_show_char(Line, Column + i, Number / oled_pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
 * @brief       	OLED初始化
 * @param       	无
 * @retval      	无
 */
void oled_init(void)
{
	oled_gpio_init();			//先调用底层的端口初始化
	
	/*写入一系列的命令，对OLED进行初始化配置*/
	oled_write_command(0xAE);	//设置显示开启/关闭，0xAE关闭，0xAF开启
	
	oled_write_command(0xD5);	//设置显示时钟分频比/振荡器频率
	oled_write_command(0x80);	//0x00~0xFF
	
	oled_write_command(0xA8);	//设置多路复用率
	oled_write_command(0x3F);	//0x0E~0x3F
	
	oled_write_command(0xD3);	//设置显示偏移
	oled_write_command(0x00);	//0x00~0x7F
	
	oled_write_command(0x40);	//设置显示开始行，0x40~0x7F
	
	oled_write_command(0xA1);	//设置左右方向，0xA1正常，0xA0左右反置
	
	oled_write_command(0xC8);	//设置上下方向，0xC8正常，0xC0上下反置

	oled_write_command(0xDA);	//设置COM引脚硬件配置
	oled_write_command(0x12);
	
	oled_write_command(0x81);	//设置对比度
	oled_write_command(0xCF);	//0x00~0xFF

	oled_write_command(0xD9);	//设置预充电周期
	oled_write_command(0xF1);

	oled_write_command(0xDB);	//设置VCOMH取消选择级别
	oled_write_command(0x30);

	oled_write_command(0xA4);	//设置整个显示打开/关闭

	oled_write_command(0xA6);	//设置正常/反色显示，0xA6正常，0xA7反色

	oled_write_command(0x8D);	//设置充电泵
	oled_write_command(0x14);

	oled_write_command(0xAF);	//开启显示
	
	oled_clear();				//清空显存数组
}
