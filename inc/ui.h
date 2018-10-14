//
// Created by Wojcik98 on 07.10.18.
//

#ifndef RAZOR_UI_H
#define RAZOR_UI_H

#include <stm32f10x_gpio.h>

#define LED_1_Pin GPIO_Pin_2
#define LED_1_Port GPIOB
#define LED_1_ON LED_1_Port->BRR = LED_1_Pin;
#define LED_1_OFF LED_1_Port->BSRR = LED_1_Pin

#define LED_2_Pin GPIO_Pin_9
#define LED_2_Port GPIOA
#define LED_2_ON LED_2_Port->BRR = LED_2_Pin
#define LED_2_OFF LED_2_Port->BSRR = LED_2_Pin

#define LED_3_Pin GPIO_Pin_10
#define LED_3_Port GPIOA
#define LED_3_ON LED_3_Port->BRR = LED_3_Pin
#define LED_3_OFF LED_3_Port->BSRR = LED_3_Pin

#define LED_4_Pin GPIO_Pin_6
#define LED_4_Port GPIOB
#define LED_4_ON LED_4_Port->BRR = LED_4_Pin
#define LED_4_OFF LED_4_Port->BSRR = LED_4_Pin

#define LED_5_Pin GPIO_Pin_7
#define LED_5_Port GPIOB
#define LED_5_ON LED_5_Port->BRR = LED_5_Pin
#define LED_5_OFF LED_5_Port->BSRR = LED_5_Pin

#define LED_6_Pin GPIO_Pin_13
#define LED_6_Port GPIOC
#define LED_6_ON LED_6_Port->BRR = LED_6_Pin
#define LED_6_OFF LED_6_Port->BSRR = LED_6_Pin


#define SW_1_Pin GPIO_Pin_4
#define SW_1 (!(GPIOA->IDR & SW_1_Pin))

#define SW_2_Pin GPIO_Pin_5
#define SW_2 (!(GPIOA->IDR & SW_2_Pin))

#define SW_3_Pin GPIO_Pin_6
#define SW_3 (!(GPIOA->IDR & SW_3_Pin))

#define SW_4_Pin GPIO_Pin_7
#define SW_4 (!(GPIOA->IDR & SW_4_Pin))

void uiConfig(void);

#endif //RAZOR_UI_H
