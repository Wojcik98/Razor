//
// Created by Wojcik98 on 16.10.18.
//

#ifndef RAZOR_SETTINGS_H
#define RAZOR_SETTINGS_H

#include <stm32f10x.h>

#define M_S (1907270)
#define STANDARD_TR_ACC (1<<14)
#define STANDARD_ROT_V (1 << 29)
#define STANDARD_ROT_ACC (1<<17)

#define MAP_RUN 0
#define FAST_RUN 1
#define FAST_SMOOTH_RUN 2

typedef struct {
    u32 vTr, aTr;
    u32 vRot, aRot;
    u16 pTr, dTr;
    u16 pRot, dRot;
} setting;

extern s16 regPTr;
extern s16 regDTr;

extern s16 regPRot;
extern s16 regDRot;

extern s32 set_targetVTr_16;
extern s32 set_accTr_16;

extern s32 set_targetVRot_16;
extern s32 set_accRot_16;

void loadSettings(u8 num);

#endif //RAZOR_SETTINGS_H
