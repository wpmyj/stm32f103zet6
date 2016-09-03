#ifndef __AD_H
#define __AD_H					
#include "sys.h"
#include "AD.h"
#define	os0 PCout(0)
#define	os1 PCout(1)
#define	os2 PCout(2)
#define busy  PCin(3)
#define	CONV_IN PCout(4)
#define LED0 PEout(5)

void FSMC_AD_Init(void);
void AD_init(void);
void read_AD(u16* addr);
//void AD7545(u16 num,u32 addr);

											  
void FSMC_SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 NumHalfwordToWrite);
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 NumHalfwordToRead);


void fsmc_sram_test_write(u8 data,u32 addr);
u16 fsmc_sram_test_read(u32 addr);

#endif
