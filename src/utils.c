//
// Created by Wojcik98 on 14.10.18.
//

#include "utils.h"

volatile u32 timeLeft;

void delayDecrement() {
    if (timeLeft) timeLeft--;
}

void delay(u32 time) {
    timeLeft = time;

    while (timeLeft);
}
