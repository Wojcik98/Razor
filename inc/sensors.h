//
// Created by Wojcik98 on 14.10.18.
//

#ifndef RAZOR_SENSORS_H
#define RAZOR_SENSORS_H

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#define LED_S_Pin GPIO_Pin_15
#define LED_S_Port GPIOC
#define LED_S_ON LED_S_Port->BSRR = LED_S_Pin
#define LED_S_OFF LED_S_Port->BRR = LED_S_Pin

#define LED_F_Pin GPIO_Pin_14
#define LED_F_Port GPIOC
#define LED_F_ON LED_F_Port->BSRR = LED_F_Pin
#define LED_F_OFF LED_F_Port->BRR = LED_F_Pin

#define FRONT_RIGHT 0
#define SIDE_RIGHT 1
#define SIDE_LEFT 2
#define FRONT_LEFT 3

void sensorsConfig(void);
u16 readADC(u8 channel);

#endif //RAZOR_SENSORS_H
