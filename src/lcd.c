//
// Created by Wojcik98 on 14.10.18.
//

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_spi.h>
#include "lcd.h"
#include "utils.h"

static void GPIO_Config(void);

static void RCC_Config(void);

static void SPI_Config(void);

static void lcdInit(void);

static void SPISelectLcd(void);

static void lcdCmd(u8 c);

void lcdData(u8 c);

static u8 lcdSendByte(u8 byte);

static void lcdSetX(u8 x);

static void lcdSetY(u8 y);

u8 font[][6] = {
#include "font.h"
};

void lcdConfig() {
    RCC_Config();
    GPIO_Config();
    SPI_Config();
    lcdInit();
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // SPI control pins
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Pin = SPI_CS | SPI_DC;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = SPI_RST;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // SPI pins
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = SPI_SCK | SPI_MOSI;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SPI_Config() {
    SPI_InitTypeDef SPI_InitStructure;

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);

    SPI_Cmd(SPI2, ENABLE);
}

void RCC_Config() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void SPISelectLcd() {
    GPIO_SetBits(GPIOB, SPI_CS);
    GPIO_ResetBits(GPIOA, SPI_RST);
    delay(15);
    GPIO_SetBits(GPIOA, SPI_RST);
}

void lcdInit() {
    SPISelectLcd();

    lcdCmd(0x21); // Extended instruction set (H)
    lcdCmd(0xC0); // Vop setting
    lcdCmd(0x06); // Temperature Coefficient
    lcdCmd(0x13); // Set bias system
    lcdCmd(0x0A); // HV-gen voltage multiplication
    lcdCmd(0x20); // H=0 <- Basic Instruction set
    lcdCmd(0x11); // VLCD Programming range
    lcdCmd(0x0C); // display configuration
    lcdCmd(0x40); // Set Y-Address of RAM (=0)
    lcdCmd(0x80); // Set X-Address of RAM (=0)

    lcdClear();
    lcdSetX(0);
    lcdSetY(0);
}

void lcdClear() {
    u16 i;
    for (i = 0; i < 96 * 9; i++) {
        lcdData(0x00);
    }
}

u8 lcdSendByte(u8 byte) {
    SPI_I2S_ReceiveData(SPI2);
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI2, byte);
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI2);
}

void lcdCmd(u8 c) {
    GPIO_ResetBits(GPIOB, GPIO_Pin_12); // Select the device
    GPIO_ResetBits(GPIOB, GPIO_Pin_14); // sending command
    lcdSendByte(c);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);// Deselect the device
}

void lcdData(u8 c) {
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);// Select the device
    GPIO_SetBits(GPIOB, GPIO_Pin_14); // sending data
    lcdSendByte(c);
    GPIO_SetBits(GPIOB, GPIO_Pin_12); // Deselect the device
}

void lcdSetX(u8 x) {
    x |= (1 << 7);
    lcdCmd(x);
}

void lcdSetY(u8 y) {
    y |= (1 << 6);
    lcdCmd(y);
}

inline void lcdPrintChar(u8 c) {
    int i;
    for (i = 0; i < 6; i++) {
        lcdData(font[c - 32][i]);
    }
}

void lcdPrintString(u8 *msg) {
    int i = 0;

    while (msg[i] != '\0') {
        lcdPrintChar(msg[i]);
        i++;
    }
}
