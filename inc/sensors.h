//
// Created by Wojcik98 on 14.10.18.
//

#ifndef RAZOR_SENSORS_H
#define RAZOR_SENSORS_H

#include <stm32f10x.h>

#define FRONT_RIGHT 0
#define SIDE_RIGHT 1
#define SIDE_LEFT 2
#define FRONT_LEFT 3

void sensorsConfig(void);
u16 readADC(u8 channel);

#endif //RAZOR_SENSORS_H
