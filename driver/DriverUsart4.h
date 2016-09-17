
#ifndef USART4_H
#define USART4_H

#include "stm32f10x_usart.h"
#include "stm32f10x.h"
#include "ostype.h"



void usart4Init(unsigned int bound);
void setDC_Value(unsigned short int num);	  //��λΪ����
void AD7545_handle(void );	
void Uart4_Event( ST_Value * p);
void RestoreUsart(u8 num);
#endif
