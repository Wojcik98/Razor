//
// Created by Wojcik98 on 14.10.18.
//

#ifndef RAZOR_LCD_H
#define RAZOR_LCD_H

#include <stm32f10x.h>

#define SPI_DC GPIO_Pin_14
#define SPI_CS GPIO_Pin_12
#define SPI_RST GPIO_Pin_8
#define SPI_SCK GPIO_Pin_13
#define SPI_MOSI GPIO_Pin_15

void lcdConfig(void);
void lcdClear(void);
inline void lcdPrintChar(u8 c);
void lcdPrintString(u8 *msg);

#endif //RAZOR_LCD_H
