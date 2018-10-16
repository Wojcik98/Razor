//
// Created by Wojcik98 on 16.10.18.
//

#ifndef RAZOR_PID_H
#define RAZOR_PID_H

#include <stm32f10x.h>

void pid(void);
void setSpeed(s32 speed);
void rotate(s32 rotation);
void applySettings();

#endif //RAZOR_PID_H
