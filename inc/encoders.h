//
// Created by Wojcik98 on 14.10.18.
//

#ifndef RAZOR_ENCODERS_H
#define RAZOR_ENCODERS_H

#include <stm32f10x_gpio.h>

#define ENC_LA_Pin GPIO_Pin_0
#define ENC_LB_Pin GPIO_Pin_1
#define ENC_RA_Pin GPIO_Pin_8
#define ENC_RB_Pin GPIO_Pin_9

extern volatile s32 enkL, enkR;
void encodersConfig(void);

#endif //RAZOR_ENCODERS_H
