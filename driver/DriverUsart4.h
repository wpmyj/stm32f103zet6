
#ifndef USART4_H
#define USART4_H

#include "stm32f10x_usart.h"
#include "stm32f10x.h"
#include "ostype.h"



void usart4Init(unsigned int bound);
void setDC_Value(unsigned short int num);	  //µ¥Î»ÎªºÁ·ü
void AD7545_handle(void );	
#endif
