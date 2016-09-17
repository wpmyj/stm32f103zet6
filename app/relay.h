#ifndef REALY_H
#define RELAY_H

#include "stm32f10x_gpio.h"

#define CURRENT_TUPE 2
#define VOLTAGE_TYPE 1
#define RATION_100   1
#define RATIO_5574   2

#define RATION_5A   3
#define RATION_1A   4

void setViltageCurrent(u8 type, u8 ratio);

#endif