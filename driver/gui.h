#ifndef GUI_H
#define GUI_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_spi.h"
#include "ostype.h"


#define    INT8U unsigned char// �޷���8λ���ͱ��� // 
#define    INT8S signed char  // �з���8λ���ͱ��� // 
#define    INT16U  unsigned int   // �޷���16λ���ͱ��� // 
#define    INT16S  signed int  // �з���16λ���ͱ��� // 
#define    INT32U  unsigned long // �޷���32λ���ͱ��� // 
#define      INT32S signed long // �з���32λ���ͱ��� // 
#define         FP32 float    // �����ȸ�����(32λ����) // 
#define           FP64 double // ˫���ȸ�����(64λ����) // 

#define  LcdCommand(x)	   WriteCommandRA8835P(x)
#define	 LcdDataWrite(x)   WriteDataRA8835P(x) 


#endif
