
#include "PGA204.h"
#include "AD7606.h"
#include "stm32f10x_gpio.h"
#include "DriverUsart4.h"
#include "OSType.h"

#define  AD7606_TEST	 1

#define RD_OUT164245 1
#define SN_NE		 0	
#define RD_CS		 8
#define CONYA_B		 9
#define AD_BURY      10

extern 	 ST_Value g_stVlue;
ST_Flag gstFlag;
extern TMailBox T7606Mail;

__ASM uint32_t __RBIT1(uint32_t value)
{
  rbit r0, r0
  bx lr;
}



void AD7606_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//配置成输入，读数据
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;//GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	#if AD7606_TEST
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	#endif

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_9 | GPIO_Pin_8;// 使能	164245
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,1 << RD_OUT164245);
	GPIO_ResetBits(GPIOC,1 << SN_NE);
	GPIO_SetBits(GPIOC,1 << RD_CS) ;
	GPIO_SetBits(GPIOC,1 << CONYA_B) ;


	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;// 产生时序
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	////赋值初始化
	g_stVlue.tMailBox =   &T7606Mail;
}


void AD7606_Handle(void)
{
	 u8 i = 0;																											   
	 float ulTem1 = 0;
	 GPIO_ResetBits(GPIOC, 1 << CONYA_B);
	 delay(100);
	 GPIO_SetBits(GPIOC,1 << CONYA_B); 
	 while(GPIO_ReadInputDataBit(GPIOA, 1 << AD_BURY) == 0);
	 
	 delay(10);

	 for(i = 0; i < 8; i++)
	 {
	 	GPIO_ResetBits(GPIOC, 1 << RD_CS);
  		g_stVlue.tubAD_Value[i] =  GPIO_ReadInputData(GPIOF);
		GPIO_SetBits(GPIOC,1 << RD_CS) ;	
		g_stVlue.tubAD_Value[i] =  (signed short)(__RBIT1( g_stVlue.tubAD_Value[i] & 0x0ffff) >> 16);
	 }

	 if((g_stVlue.tubAD_Value[7] < 320) &&  (g_stVlue.tubAD_Value[7] > 0))
	 {
	 	   SetAmplification(100);
	 }
	 else
	 {
	 	   g_stVlue.fADValue =  (float)(g_stVlue.tubAD_Value[7] * 10/32768.0);	
		   g_stVlue.fADValue3 =  (float)(g_stVlue.tubAD_Value[3]* 10/32768.0);
		   	
		   if(gstFlag.ubFlag7606 == 0) 
		   {
		   		g_stVlue.fADValue4Compensation =  g_stVlue.fADValue3 ;
				gstFlag.ubFlag7606 = 1;
		   }
	 }	 
 }



#if 0

void EnableL164245(void)
{
  	 GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;//
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	

	 GPIO_Init(GPIOC, &GPIO_InitStructure);

	 GPIO_ResetBits(GPIOC,RD_OUT164245);
	 GPIO_ResetBits(GPIOC,SN_NE);
}


void EXTINT2_Init()
{											  									 
#if 1
  	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
							  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置下拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource7);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;	 
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
  	NVIC_InitStructure.   = 0x02;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
  	NVIC_Init(&NVIC_InitStructure);
#endif
}

void EXTI9_5_IRQHandler(void)
{

	#if 0
	  EXTIN2_FLAG = 1;
	#endif
		  (EXTI_Line7);			
}
#endif
