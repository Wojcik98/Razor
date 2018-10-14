//
// Created by Wojcik98 on 14.10.18.
//

#include <stm32f10x_adc.h>
#include <stm32f10x_rcc.h>
#include "sensors.h"

static void ADC_Config(void);

static void GPIO_Config(void);

static void RCC_Config(void);

void sensorsConfig() {
    RCC_Config();
    GPIO_Config();
    ADC_Config();
    // TODO calibration

    LED_S_OFF;
    LED_F_OFF;
}

void ADC_Config() {
    ADC_InitTypeDef ADC_InitStructure;

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);   // TODO turn off?

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Pin = LED_S_Pin;
    GPIO_Init(LED_S_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED_F_Pin;
    GPIO_Init(LED_F_Port, &GPIO_InitStructure);
}

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
}

u16 readADC(u8 channel) {
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_71Cycles5);
    // Start the conversion
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    // Wait until conversion completion
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    // Get the conversion value
    return ADC_GetConversionValue(ADC1);
}
