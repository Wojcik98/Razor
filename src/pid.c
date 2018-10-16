//
// Created by Wojcik98 on 16.10.18.
//

#include <stm32f10x.h>
#include "encoders.h"
#include "math.h"
#include "motors.h"
#include "pid.h"
#include "settings.h"

volatile u8 run = 0;

volatile s32 pwmL = 0, pwmR = 0;
volatile s32 targetVTr_16 = 0;
volatile s32 currVTr_16 = 0;
volatile s32 accTr_16 = 0;
volatile s32 zadSTr = 0;

volatile s32 targetVRot_16 = 0;
volatile s32 currVRot_16 = 0;
volatile s32 accRot_16 = 0;
volatile s32 zadSRot = 0;
volatile s32 targetSRot = 0;

volatile s32 enkTr = 0, enkRot = 0;
volatile s32 regCurrErrTr = 0, regCurrErrRot = 0;
volatile s32 regPrevErrTr = 0, regPrevErrRot = 0;

void translation() {
    if (currVTr_16 < targetVTr_16) {
        currVTr_16 = min(currVTr_16 + accTr_16, targetVTr_16);
    }

    if (currVTr_16 > targetVTr_16) {
        currVTr_16 = max(currVTr_16 - accTr_16, targetVTr_16);
    }

    zadSTr += ((currVTr_16 + (1 << 15)) >> 16);
}

void rotation() {
    targetVRot_16 = set_targetVRot_16;
    if (currVRot_16 * (currVRot_16 >> 16) / (2 * accRot_16) >= abs(targetSRot - zadSRot)) {
        targetVRot_16 = 0;
    }

    if (currVRot_16 < targetVRot_16) {
        currVRot_16 = min(currVRot_16 + accRot_16, targetVRot_16);
    }

    if (currVRot_16 > targetVRot_16) {
        currVRot_16 = max(currVRot_16 - accRot_16, targetVRot_16);
    }

    if (zadSRot < targetSRot) {
        zadSRot = min(zadSRot + ((currVRot_16 + (1 << 15)) >> 16), targetSRot);
    } else if (zadSRot > targetSRot) {
        zadSRot = max(zadSRot - ((currVRot_16 + (1 << 15)) >> 16), targetSRot);
    }
}

void pid() {
    enkTr = enkL + enkR;
    enkRot = enkL - enkR;

    translation();
    rotation();

    regCurrErrTr = zadSTr - enkTr;
    regCurrErrRot = zadSRot - enkRot;

    pwmL = regPTr * regCurrErrTr
           + regDTr * (regCurrErrTr - regPrevErrTr)

           + regPRot * regCurrErrRot
           + regDRot * (regCurrErrRot - regPrevErrRot);

    pwmR = regPTr * regCurrErrTr
           + regDTr * (regCurrErrTr - regPrevErrTr)

           - regPRot * regCurrErrRot
           - regDRot * (regCurrErrRot - regPrevErrRot);

    regPrevErrTr = regCurrErrTr;
    regPrevErrRot = regCurrErrRot;

    setPwm(pwmL, pwmR);
}

void setSpeed(s32 speed) {
    targetVTr_16 = speed;
}

void rotate(s32 rotation) {
    targetSRot = enkRot + rotation;
}

void applySettings() {
    targetVTr_16 = set_targetVTr_16;
    accTr_16 = set_accTr_16;

    targetVRot_16 = set_targetVRot_16;
    accRot_16 = set_accRot_16;
}
