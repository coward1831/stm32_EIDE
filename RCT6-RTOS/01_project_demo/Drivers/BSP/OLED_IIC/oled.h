#ifndef __OLED_H
#define __OLED_H
#include "stm32f10x.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* OLED IIC模式引脚 定义 */
#define OLED_IIC_SCL_PORT               GPIOC
#define OLED_IIC_SCL_PIN                GPIO_Pin_8
#define OLED_IIC_SCL_CLK_ENABLE()       do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); }while(0)

#define OLED_IIC_SDA_PORT               GPIOC
#define OLED_IIC_SDA_PIN                GPIO_Pin_9
#define OLED_IIC_SDA_CLK_ENABLE()       do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); }while(0)


#define OLED_W_SCL(x)   do{ x ? \
                      GPIO_WriteBit(OLED_IIC_SCL_PORT, OLED_IIC_SCL_PIN, Bit_SET) : \
                      GPIO_WriteBit(OLED_IIC_SCL_PORT, OLED_IIC_SCL_PIN, Bit_RESET); \
                  }while(0)        /*OLED写SCL高低电平*/

#define OLED_W_SDA(x)   do{ x ? \
                      GPIO_WriteBit(OLED_IIC_SDA_PORT, OLED_IIC_SDA_PIN, Bit_SET) : \
                      GPIO_WriteBit(OLED_IIC_SDA_PORT, OLED_IIC_SDA_PIN, Bit_RESET); \
                  }while(0)        /*OLED写SDA高低电平*/          


void oled_clear(void);
void oled_show_char(uint8_t Line, uint8_t Column, char Char);
void oled_show_string(uint8_t Line, uint8_t Column, char *String);
void oled_show_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void oled_show_signed_num(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void oled_show_hex_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void oled_show_bin_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void oled_show_float_num(uint8_t Line, uint8_t Column, double Number, uint8_t IntLength,uint8_t FraLength);
void oled_init(void);
#endif
