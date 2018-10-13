//
// Created by Wojcik98 on 14.10.18.
//

#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>
#include "math.h"
#include "motors.h"

static void GPIO_Config(void);

static void RCC_Config(void);

static void TIM_Config(void);

void motorsConfig() {
    RCC_Config();
    GPIO_Config();
    TIM_Config();

    M_L_FORWARD;
    M_R_FORWARD;
    PWM_L = 0;
    PWM_R = 0;
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // Control pins
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Pin = M_R1_Pin | M_R2_Pin;
    GPIO_Init(M_R_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = M_L1_Pin | M_L2_Pin;
    GPIO_Init(M_L_Port, &GPIO_InitStructure);

    // PWM pins
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    GPIO_InitStructure.GPIO_Pin =  PWM_R_Pin;
    GPIO_Init(M_R_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = PWM_L_Pin;
    GPIO_Init(M_L_Port, &GPIO_InitStructure);

    // Remapping
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
}

void TIM_Config() {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    TIM_TimeBaseStructure.TIM_Period = PERIOD;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;

    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_ARRPreloadConfig(TIM3, ENABLE);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);   // only TIM1

    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

void RCC_Config() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void setPwmL(s32 pwm) {
    if (pwm > 0) {
        M_L_FORWARD;
    } else {
        M_L_BACKWARD;
    }

    PWM_L = (u16) abs(pwm);
}

void setPwmR(s32 pwm) {
    if (pwm > 0) {
        M_R_FORWARD;
    } else {
        M_R_BACKWARD;
    }

    PWM_R = (u16) abs(pwm);
}

void setPwm(s32 pwmL, s32 pwmR) {
    setPwmL(pwmL);
    setPwmR(pwmR);
}
