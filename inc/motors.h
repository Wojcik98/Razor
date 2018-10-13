//
// Created by Wojcik98 on 14.10.18.
//

#ifndef RAZOR_MOTORS_H
#define RAZOR_MOTORS_H

#include <stm32f10x_gpio.h>

#define M_R_Port GPIOB
#define M_R1_Pin GPIO_Pin_3
#define M_R2_Pin GPIO_Pin_4
#define PWM_R_Pin GPIO_Pin_5

#define M_L_Port GPIOA
#define M_L1_Pin GPIO_Pin_15
#define M_L2_Pin GPIO_Pin_12
#define PWM_L_Pin GPIO_Pin_11

#define M_R1_ON M_R_Port->BSRR = M_R1_Pin
#define M_R1_OFF M_R_Port->BRR = M_R1_Pin

#define M_R2_ON M_R_Port->BSRR = M_R2_Pin
#define M_R2_OFF M_R_Port->BRR = M_R2_Pin

#define M_L1_ON M_L_Port->BSRR = M_L1_Pin
#define M_L1_OFF M_L_Port->BRR = M_L1_Pin

#define M_L2_ON M_L_Port->BSRR = M_L2_Pin
#define M_L2_OFF M_L_Port->BRR = M_L2_Pin

#define PWM_L TIM1->CCR4
#define PWM_R TIM3->CCR2

#define M_L_FORWARD do {M_L1_ON; M_L2_OFF;} while (0)
#define M_L_BACKWARD do {M_L1_OFF; M_L2_ON;} while (0)

#define M_R_FORWARD do {M_R1_ON; M_R2_OFF;} while (0)
#define M_R_BACKWARD do {M_R1_OFF; M_R2_ON;} while (0)

#define PERIOD (1<<12)

void motorsConfig(void);
void setPwmL(s32 pwm);
void setPwmR(s32 pwm);
void setPwm(s32 pwmL, s32 pwmR);

#endif //RAZOR_MOTORS_H
