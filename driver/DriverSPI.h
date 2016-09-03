#ifndef DRIVER_SPI_H
#define DRIVER_SPI_H

#include "stm32f10x_usart.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

void spi_1_innit(void);

#define AH320240_NSS    (1 << 4)
#define AH320240_SCK    (1 << 5)
#define AH320240_MISO   (1 << 6)
#define AH320240_MISI   (1 << 7)

u16 SPI1_Write(u16 TxData);
u16   SPI1_Read(void);
u16   SPI1_WriteRead(u16 TxData);

typedef struct
{
    u8 x;
	u8 y;
	u16 z1;
	u16 z2;
}SPI_INFO;

#endif