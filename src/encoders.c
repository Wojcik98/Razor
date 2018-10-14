//
// Created by Wojcik98 on 14.10.18.
//

#include <stm32f10x_gpio.h>
#include <misc.h>
#include <stm32f10x_exti.h>
#include <stm32f10x_rcc.h>
#include <stdbool.h>
#include "encoders.h"

static void GPIO_Config(void);

static void NVIC_Config(void);

static void EXTI_Config(void);

static void RCC_Config(void);

volatile s32 enkL = 0, enkR = 0;
volatile bool dirL = 0, dirR = 0;

void encodersConfig() {
    RCC_Config();
    GPIO_Config();
    NVIC_Config();
    EXTI_Config();

    // Starting direction
    dirL = (GPIOB->IDR & ENC_LA_Pin) != (GPIOB->IDR & ENC_LB_Pin);
    dirR = (GPIOB->IDR & ENC_RA_Pin) != (GPIOB->IDR & ENC_RB_Pin);
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Pin = ENC_LA_Pin | ENC_LB_Pin | ENC_RA_Pin | ENC_RB_Pin;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);
}

void NVIC_Config() {
    NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_Init(&NVIC_InitStruct);
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Init(&NVIC_InitStruct);
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_Init(&NVIC_InitStruct);

}

void EXTI_Config() {
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;

    //Encoder LA
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    EXTI_Init(&EXTI_InitStruct);

    //Enocoder LB
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;
    EXTI_Init(&EXTI_InitStruct);

    //Encoder RA
    EXTI_InitStruct.EXTI_Line = EXTI_Line8;
    EXTI_Init(&EXTI_InitStruct);

    //Encoder RB
    EXTI_InitStruct.EXTI_Line = EXTI_Line9;
    EXTI_Init(&EXTI_InitStruct);
}

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void EXTI0_IRQHandler(void) {
    if (dirL) {
        dirL = 0;
        enkL--;
    } else {
        dirL = 1;
        enkL++;
    }
    EXTI->PR = EXTI_Line0;
}

void EXTI1_IRQHandler(void) {
    if (dirL) {
        dirL = 0;
        enkL++;
    } else {
        dirL = 1;
        enkL--;
    }
    EXTI->PR = EXTI_Line1;
}

void EXTI9_5_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
        if (dirR) {
            dirR = 0;
            enkR++;
        } else {
            dirR = 1;
            enkR--;
        }
        EXTI->PR = EXTI_Line8;
    }
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
        if (dirR) {
            dirR = 0;
            enkR--;
        } else {
            dirR = 1;
            enkR++;
        }
        EXTI->PR = EXTI_Line9;
    }
}
