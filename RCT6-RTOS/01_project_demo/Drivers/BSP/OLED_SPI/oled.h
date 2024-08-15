#ifndef __OLED_H
#define __OLED_H
#include "stm32f10x.h"


/* OLED 六针脚模式引脚 定义 */
#define OLED_SPI_SCL_PORT               GPIOC
#define OLED_SPI_SCL_PIN                GPIO_Pin_8
#define OLED_SPI_SCL_CLK_ENABLE()       do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); }while(0)

#define OLED_SPI_SDA_PORT               GPIOC
#define OLED_SPI_SDA_PIN                GPIO_Pin_9
#define OLED_SPI_SDA_CLK_ENABLE()       do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); }while(0)


#define OLED_SPI_RES_PORT               GPIOC
#define OLED_SPI_RES_PIN                GPIO_Pin_10
#define OLED_SPI_RES_CLK_ENABLE()       do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); }while(0)

#define OLED_SPI_DC_PORT               GPIOB
#define OLED_SPI_DC_PIN                GPIO_Pin_7
#define OLED_SPI_DC_CLK_ENABLE()       do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); }while(0)



#define OLED_W_SCL(x)   do{ x ? \
                      GPIO_WriteBit(OLED_SPI_SCL_PORT, OLED_SPI_SCL_PIN, Bit_SET) : \
                      GPIO_WriteBit(OLED_SPI_SCL_PORT, OLED_SPI_SCL_PIN, Bit_RESET); \
                  }while(0)

#define OLED_W_SDA(x)   do{ x ? \
                      GPIO_WriteBit(OLED_SPI_SDA_PORT, OLED_SPI_SDA_PIN, Bit_SET) : \
                      GPIO_WriteBit(OLED_SPI_SDA_PORT, OLED_SPI_SDA_PIN, Bit_RESET); \
                  }while(0)	  

#define OLED_W_RES(x)   do{ x ? \
                      GPIO_WriteBit(OLED_SPI_RES_PORT, OLED_SPI_RES_PIN, Bit_SET) : \
                      GPIO_WriteBit(OLED_SPI_RES_PORT, OLED_SPI_RES_PIN, Bit_RESET); \
                  }while(0)	  

#define OLED_W_DC(x)   do{ x ? \
                      GPIO_WriteBit(OLED_SPI_DC_PORT, OLED_SPI_DC_PIN, Bit_SET) : \
                      GPIO_WriteBit(OLED_SPI_DC_PORT, OLED_SPI_DC_PIN, Bit_RESET); \
                  }while(0)	  
			  
void oled_clear(void);
void oled_show_char(uint8_t Line, uint8_t Column, char Char);
void oled_show_string(uint8_t Line, uint8_t Column, char *String);
void oled_show_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void oled_show_signed_num(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void oled_show_hex_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void oled_show_bin_num(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void oled_init(void);
#endif
