#ifndef DEVICE_FSMC_H
#define	DEVICE_FSMC_H

#include "stm32f10x_fsmc.h"
#include "stm32f10x_gpio.h"

void FSMC_Init(void);
void SetAD7545(u16 addr,u16 v);

#endif
