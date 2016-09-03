#ifndef __AD7606_H
#define __AD7606_H	 

#include "stm32f10x_exti.h"
#include "misc.h"	
#include "stm32f10x_gpio.h"
/* 声明 float DATA[12]；
   main	
				DATA[12]={0};
				count_flag=0;
				count=0;
   			EXTINT2_Init();
				NVIC_Configuration();
				FSMC_Init(); 总线初始化
	while 里面RD_7606_DATA(); 读取数据
 */
//void RD_7606_DATA(void);
 void EXTINT2_Init(void);
 void AD7606_Handle(void);
 void AD7606_Init(void);
//void 	RD_7606_Init(void);
//void read_AD(u16* addr);
//extern double DATA[13];
//extern 
//extern int count_flag;
//extern int count_test;
extern int EXTIN2_FLAG;
//extern int count_N;
#endif


