//
// Created by Wojcik98 on 07.10.18.
//

#include <stm32f10x.h>
#include <system_stm32f10x.h>
#include "encoders.h"
#include "lcd.h"
#include "main.h"
#include "motors.h"
#include "sensors.h"
#include "ui.h"
#include "utils.h"

static void setClockInterrupt(void);

int main(void) {
    SystemInit();
    setClockInterrupt();

    uiConfig();
    motorsConfig();
    encodersConfig();
    sensorsConfig();
    lcdConfig();

    while (1) {
    }
}

void setClockInterrupt() {
    // Set interrupt every 1ms
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }
}

void SysTick_Handler(){
    delayDecrement();
}
