//
// Created by Wojcik98 on 07.10.18.
//

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include "basic_ui.h"

static void GPIO_Config(void);

static void RCC_Config(void);

void uiConfig() {
    RCC_Config();
    GPIO_Config();

    LED_1_OFF;
    LED_2_OFF;
    LED_3_OFF;
    LED_4_OFF;
    LED_5_OFF;
    LED_6_OFF;
    LED_S_OFF;
    LED_F_OFF;
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // LEDs
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Pin = LED_1_Pin;
    GPIO_Init(LED_1_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_2_Pin;
    GPIO_Init(LED_2_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_3_Pin;
    GPIO_Init(LED_3_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_4_Pin;
    GPIO_Init(LED_4_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_5_Pin;
    GPIO_Init(LED_5_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_6_Pin;
    GPIO_Init(LED_6_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_S_Pin;
    GPIO_Init(LED_S_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_F_Pin;
    GPIO_Init(LED_F_Port, &GPIO_InitStructure);

    // Switches
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = SW_1_Pin | SW_2_Pin | SW_3_Pin | SW_4_Pin;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}
