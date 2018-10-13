//
// Created by Wojcik98 on 07.10.18.
//

#include <stm32f10x.h>
#include <system_stm32f10x.h>
#include "basic_ui.h"
#include "main.h"
#include "motors.h"

int main(void) {
    SystemInit();

    uiConfig();
    motorsConfig();

    while (1) {
    }
}
