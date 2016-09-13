#include "DriverEXTLine.h"
#include "DA7545.h"
#include "DriverSPI.h"


void ExtLineConfig(u8 x,u8 nun)
{
	u8 uba1 = 0,uba2 = 0 ;
	EXTI_InitTypeDef    EXTI_InitStructure;
	NVIC_InitTypeDef    NVIC_InitStructure;
	GPIO_InitTypeDef    GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	 switch(nun)
	 {
	 	 case 12:
		 {
				GPIO_InitStructure.GPIO_Pin = 1 << nun ;	
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
				GPIO_Init(GPIOA, &GPIO_InitStructure);

		 	    GPIO_EXTILineConfig(x,nun);
			  	EXTI_InitStructure.EXTI_Line= 1 << nun;	 
			  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
			  	EXTI_InitStructure .EXTI_Trigger = EXTI_Trigger_Falling;
			  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
			  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
			
			    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			
			  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
			  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					
			  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
			  	NVIC_Init(&NVIC_InitStructure);
		 }
		 break;

		 case 7:
		 {

			  GPIO_InitStructure.GPIO_Pin = 1 << nun ;	
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
				GPIO_Init(GPIOG, &GPIO_InitStructure);		 			

		 	    GPIO_EXTILineConfig(x,nun);
			  	EXTI_InitStructure.EXTI_Line= 1 << nun;	 
			  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
			  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
			  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
			  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
			
			    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
			  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
			  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					
			  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
			  	NVIC_Init(&NVIC_InitStructure);
		 }
		 break;

		 case 6:
		 {
			GPIO_InitStructure.GPIO_Pin = 1 << nun ;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			GPIO_Init(GPIOG, &GPIO_InitStructure);

			GPIO_EXTILineConfig(x,nun);
			EXTI_InitStructure.EXTI_Line= 1 << nun ;	 
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;
			EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
			
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
			NVIC_Init(&NVIC_InitStructure);
		 }
		 break;
		 
		 case 8:
		 {
			GPIO_InitStructure.GPIO_Pin = 1 << nun ;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			GPIO_Init(GPIOG, &GPIO_InitStructure);

			GPIO_EXTILineConfig(x,nun);
			EXTI_InitStructure.EXTI_Line= 1 << nun ;	 
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;
			EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
			
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0X02;	
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
			NVIC_Init(&NVIC_InitStructure);
		 }
		 break;


		 default:
		   break;
	 }
}

SPI_INFO	   stSPIvalue = 0;

extern ST_Flag gstFlag;
extern void AD7606_Handle(void);

void EXTI9_5_IRQHandler(void)
{
	u8 statue = 0;
	u16 i =0 ;
	if(EXTI_GetFlagStatus(EXTI_Line7))
	{ 
		EXTI_ClearITPendingBit(EXTI_Line7);  //清除LINE2上的中断标志位 
		setDC_Value(0);
	}
	
	if(EXTI_GetFlagStatus(EXTI_Line8))
	{ 
		
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction) (1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_6)));
		//UART4->DR  = 0x55;
		//UART4->DR  = 0xaa;
    AD7606_Handle();

		EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE2上的中断标志位 
	}

	if(EXTI_GetFlagStatus(EXTI_Line6))
	{ 	
	#if 0	
		stSPIvalue.x = SPI1_ReadWriteByte(0xd000);
		stSPIvalue.y = SPI1_ReadWriteByte(0x9000);
		stSPIvalue.z1 = SPI1_ReadWriteByte(0xb000);
		stSPIvalue.z2 = SPI1_ReadWriteByte(0xc000);
		EXTI_ClearITPendingBit(EXTI_Line6);	 //清除LINE2上的中断标志位
	#else
		stSPIvalue.x = SPI1_WriteRead(0xd0);	
 		stSPIvalue.y = SPI1_WriteRead(0x90);
		stSPIvalue.z1 = SPI1_WriteRead(0xb0);
		stSPIvalue.z2 = SPI1_WriteRead(0xc0);
		EXTI_ClearITPendingBit(EXTI_Line6);	 //清除LINE2上的中断标志位	
	#endif

	if((stSPIvalue.x  > 0x50)&& ((stSPIvalue.x  < 0x6f) ) && ((stSPIvalue.y  > 0x3e) && (stSPIvalue.y  < 0x54)  ) )
	 {
		  setDC_Value(0); 
	 }
		 	
	}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line12))
	{ 
		setDC_Value(0);EXTI_ClearITPendingBit(EXTI_Line12);  //清除LINE2上的中断标志位 
	}
}

void  test_chumo(void)
{
	//stSPIvalue.x = SPI1_ReadWriteByte(0xd000);
    //stSPIvalue.y = SPI1_ReadWriteByte(0x9000);
    //stSPIvalue.z1 = SPI1_ReadWriteByte(0xb000);
    //stSPIvalue.z2 = SPI1_ReadWriteByte(0xc000);
	 if(GPIO_ReadInputDataBit(GPIOG, 1 << 6) == 0)
	 {
	 #if 0
	 	   SPI1_Write(0xd000);
		   while(GPIO_ReadInputDataBit(GPIOG, 1 << 6) == 1);
		   while(GPIO_ReadInputDataBit(GPIOG, 1 << 6) == 0);
		   stSPIvalue.x =  SPI1_Read();
	#else
		   //stSPIvalue.x = SPI1_WriteRead(0xd000);
 		   //stSPIvalue.y = SPI1_WriteRead(0x9000);
		   //stSPIvalue.z1 = SPI1_WriteRead(0xb000);
		   //stSPIvalue.z2 = SPI1_WriteRead(0xc000);

		   stSPIvalue.x = SPI1_WriteRead(0xd0);	
 		   stSPIvalue.y = SPI1_WriteRead(0x90);
		   stSPIvalue.z1 = SPI1_WriteRead(0xb0);
		   stSPIvalue.z2 = SPI1_WriteRead(0xc0);
	#endif

		   
	 }
}






