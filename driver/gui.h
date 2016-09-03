#ifndef GUI_H
#define GUI_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_spi.h"
#include "ostype.h"


#define    INT8U unsigned char// 无符号8位整型变量 // 
#define    INT8S signed char  // 有符号8位整型变量 // 
#define    INT16U  unsigned int   // 无符号16位整型变量 // 
#define    INT16S  signed int  // 有符号16位整型变量 // 
#define    INT32U  unsigned long // 无符号32位整型变量 // 
#define      INT32S signed long // 有符号32位整型变量 // 
#define         FP32 float    // 单精度浮点数(32位长度) // 
#define           FP64 double // 双精度浮点数(64位长度) // 

#define  LcdCommand(x)	   WriteCommandRA8835P(x)
#define	 LcdDataWrite(x)   WriteDataRA8835P(x) 


#endif
