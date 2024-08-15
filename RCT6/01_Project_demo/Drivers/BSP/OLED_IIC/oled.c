#include "./BSP/OLED_IIC/oled.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/OLED_IIC/oled_font.h"

/**********************************----- 软件IIC -----************************************/
/**
 * @brief           IIC延时函数,用于控制IIC读写速度
 * @param           无
 * @retval          无
 */
static void oled_iic_delay(void)
{
    delay_us(2);
}
/**
 * @brief           产生IIC起始信号
 * @param           无
 * @retval          无
 */
static void oled_iic_start(void)
{
    OLED_W_SDA(1);        //释放SDA，确保SDA为高电平
    OLED_W_SCL(1);        //释放SCL，确保SCL为高电平
    oled_iic_delay();
    OLED_W_SDA(0);        //在SCL高电平期间，拉低SDA，产生起始信号
    oled_iic_delay();
    OLED_W_SCL(0);        //起始后把SCL也拉低，即为了占用总线，也为了方便总线时序的拼接
    oled_iic_delay();
}

/**
 * @brief           产生IIC停止信号
 * @param           无
 * @retval          无
 */
static void oled_iic_stop(void)
{
    OLED_W_SDA(0);        //拉低SDA，确保SDA为低电平
    oled_iic_delay();
    OLED_W_SCL(1);        //释放SCL，使SCL呈现高电平
    oled_iic_delay();
    OLED_W_SDA(1);        //在SCL高电平期间，释放SDA，产生终止信号
    oled_iic_delay();
}

/**
 * @brief           I2C发送一个字节
 * @param           Byte 要发送的一个字节数据，范围：0x00~0xFF
 * @retval          无
 */
static void oled_iic_send_byte(uint8_t Byte)
{
    uint8_t i;
    
    /*循环8次，主机依次发送数据的每一位*/
    for (i = 0; i < 8; i++)
    {
        /*使用掩码的方式取出Byte的指定一位数据并写入到SDA线*/
        /*两个!的作用是，让所有非零的值变为1*/
        OLED_W_SDA(!!(Byte & (0x80 >> i)));
        oled_iic_delay();
        OLED_W_SCL(1);    //释放SCL，从机在SCL高电平期间读取SDA
        oled_iic_delay();
        OLED_W_SCL(0);    //拉低SCL，主机开始发送下一位数据
    }
    
    OLED_W_SCL(1);        //额外的一个时钟，不处理应答信号
    OLED_W_SCL(0);
}

/**
 * @brief           OLED写命令
 * @param           Command 要写入的命令值，范围：0x00~0xFF
 * @retval          无
 */
static void oled_write_command(uint8_t Command)
{
    oled_iic_start();                //I2C起始
    oled_iic_send_byte(0x78);        //发送OLED的I2C从机地址
    oled_iic_send_byte(0x00);        //控制字节，给0x00，表示即将写命令
    oled_iic_send_byte(Command);    //写入指定的命令
    oled_iic_stop();                //I2C终止
}

/**
  * @brief            OLED写数据
  * @param             Data 要写入数据的起始地址
  * @retval            无
  */
static void oled_write_data(uint8_t Data)
{
    oled_iic_start();                //I2C起始
    oled_iic_send_byte(0x78);        //发送OLED的I2C从机地址
    oled_iic_send_byte(0x40);        //控制字节，给0x40，表示即将写数据
    oled_iic_send_byte(Data);    //依次发送Data的每一个数据
    oled_iic_stop();                //I2C终止
}
/*****************************************************************************************************/

/**********************************----- 硬件配置 -----************************************/

/**
 * @brief           初始化OLED相关IO口, 并使能时钟
 * @param           无
 * @retval          无
 */
static void oled_gpio_init(void)
{
    /*在初始化前，加入适量延时，待OLED供电稳定*/
    delay_ms(1000);
    /*将SCL和SDA引脚初始化为开漏模式*/
    OLED_IIC_SCL_CLK_ENABLE();
    OLED_IIC_SDA_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = OLED_IIC_SCL_PIN;
     GPIO_Init(OLED_IIC_SCL_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = OLED_IIC_SDA_PIN;
     GPIO_Init(OLED_IIC_SDA_PORT, &GPIO_InitStructure);
    
    /*释放SCL和SDA*/
    OLED_W_SCL(1);
    OLED_W_SDA(1);
}

/**
 * @brief           次方函数
 * @param           X 底数
 * @param           Y 指数
 * @retval          无
 */
static uint32_t oled_pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;    //结果默认为1
    while (Y --)            //累乘Y次
    {
        Result *= X;        //每次把X累乘到结果上
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
    oled_write_command(0xB0 | Y);                    //设置Y位置
    oled_write_command(0x10 | ((X & 0xF0) >> 4));    //设置X位置高4位
    oled_write_command(0x00 | (X & 0x0F));            //设置X位置低4位
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
    oled_set_pos((Line - 1) * 2, (Column - 1) * 8);        //设置光标位置在上半部分
    for (i = 0; i < 8; i++)
    {
        oled_write_data(OLED_F8x16[Char - ' '][i]);            //显示上半部分内容
    }
    oled_set_pos((Line - 1) * 2 + 1, (Column - 1) * 8);    //设置光标位置在下半部分
    for (i = 0; i < 8; i++)
    {
        oled_write_data(OLED_F8x16[Char - ' '][i + 8]);        //显示下半部分内容
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
  * @brief  OLED显示小数（浮点数，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字
  * @param  IntLength 要显示小数的整数长度，范围：1~10
  * @param  FraLength 要显示小数的小数长度，范围：1~10
  * @retval 无
  */
void oled_show_float_num(uint8_t Line, uint8_t Column, double Number, uint8_t IntLength,uint8_t FraLength)
{
    uint32_t PowNum, IntNum, FraNum;
    
    if (Number >= 0)                        //数字大于等于0
    {
        oled_show_char(Line, Column, '+');    //显示+号
    }
    else                                    //数字小于0
    {
        oled_show_char(Line, Column, '-');    //显示-号
        Number = -Number;                    //Number取负
    }
    /*提取整数部分和小数部分*/
    IntNum = Number;                        //直接赋值给整型变量，提取整数
    Number -= IntNum;                        //将Number的整数减掉，防止之后将小数乘到整数时因数过大造成错误
    PowNum = oled_pow(10, FraLength);        //根据指定小数的位数，确定乘数
    FraNum = round(Number * PowNum);        //将小数乘到整数，同时四舍五入，避免显示误差
    IntNum += FraNum / PowNum;                //若四舍五入造成了进位，则需要再加给整数
    
    
    /*显示整数部分*/
    oled_show_num(Line, Column + 1, IntNum, IntLength);
    
    /*显示小数点*/
    oled_show_char(Line,Column + (IntLength + 1), '.');
    
    /*显示小数部分*/
    oled_show_num(Line,Column + (IntLength + 2), FraNum, FraLength);    
}

/**
 * @brief           OLED初始化
 * @param           无
 * @retval          无
 */
void oled_init(void)
{
    oled_gpio_init();            //先调用底层的端口初始化
    
    /*写入一系列的命令，对OLED进行初始化配置*/
    oled_write_command(0xAE);    //设置显示开启/关闭，0xAE关闭，0xAF开启
    
    oled_write_command(0xD5);    //设置显示时钟分频比/振荡器频率
    oled_write_command(0x80);    //0x00~0xFF
    
    oled_write_command(0xA8);    //设置多路复用率
    oled_write_command(0x3F);    //0x0E~0x3F
    
    oled_write_command(0xD3);    //设置显示偏移
    oled_write_command(0x00);    //0x00~0x7F
    
    oled_write_command(0x40);    //设置显示开始行，0x40~0x7F
    
    oled_write_command(0xA1);    //设置左右方向，0xA1正常，0xA0左右反置
    
    oled_write_command(0xC8);    //设置上下方向，0xC8正常，0xC0上下反置

    oled_write_command(0xDA);    //设置COM引脚硬件配置
    oled_write_command(0x12);
    
    oled_write_command(0x81);    //设置对比度
    oled_write_command(0xCF);    //0x00~0xFF

    oled_write_command(0xD9);    //设置预充电周期
    oled_write_command(0xF1);

    oled_write_command(0xDB);    //设置VCOMH取消选择级别
    oled_write_command(0x30);

    oled_write_command(0xA4);    //设置整个显示打开/关闭

    oled_write_command(0xA6);    //设置正常/反色显示，0xA6正常，0xA7反色

    oled_write_command(0x8D);    //设置充电泵
    oled_write_command(0x14);

    oled_write_command(0xAF);    //开启显示
    
    oled_clear();                //清空显存数组
}
