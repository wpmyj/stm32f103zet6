
#include "DriverUsart4.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "stdio.h"
#include "relay.h"
//#include "misc.h"

extern ST_Value g_stVlue;

#if 1
void usart4Init(u32 bound)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	USART_InitTypeDef   USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	USART_DeInit(UART4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE); //RCC_APB2Periph_USART1
	
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(UART4, &USART_InitStructure); //初始化串口

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启中断
	//USART_ITConfig(UART4,USART_IT_IDLE,ENABLE);
	USART_Cmd(UART4,ENABLE); 
    USART_ClearFlag(UART4,USART_FLAG_TC);                    //使能串口 
	//UART4->CR1 |= 1 << 8;//	PEIE
}
#else
void usart4Init(u32 bound)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	 //使能USART3
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
     //USART3_TX   PB.10
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
   
    //USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
   //Usart3 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART3, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART3, ENABLE);  
}
#endif

void USART3_IRQHandler(void)
{
   if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
   {	
	  USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	  USART_ClearITPendingBit(USART3,USART_FLAG_TC); 
	  setDC_Value(USART_ReceiveData(USART3)); 				          
   }
}

void SetCurentPercent( u8 v)  //设置电流百分比
{
	u16 tem = 0;
	u8 i = 0 ;
	i=  v& 0xff;

 #if 1

	g_stVlue.uitem1 =   i * 50 ;
	setDC_Value(g_stVlue.uitem1);

 #else

 #if 1
	if (v < 40)
	{
		 i *= 10;
		 tem =(u16)(29.36387041598274 + 4.875721690697347*i + 0.0006904675012370284*i*i - 2.1638228474485206e-6*i*i*i) ;
		 setDC_Value(tem);
	}

	else if ((v >= 80) &&	(v < 100)  )
	{
	     g_stVlue.uitem1 =   i * 50 *  0.99;
		   setDC_Value(g_stVlue.uitem1);
	}

					    
	else
	{
		 g_stVlue.uitem1 =   i * 50 ;
		 setDC_Value(g_stVlue.uitem1);
	}
#endif

#endif
	
}

 

void UART4_IRQHandler (void)  //UART4_IRQHandler IMPORT  UART4_IRQHandler
{
#if 0
	 if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	 {

		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		USART_ClearITPendingBit(UART4,USART_FLAG_TC); 

		if(g_stVlue.ubUsartCount > 100 )
		{
		   g_stVlue.ubUsartCount = 0;
		}
	     
		if( UART4->DR != 0xaa )
		{
			g_stVlue.tabUsartValue[g_stVlue.ubUsartCount ++]  =    UART4->DR ;
		}				          
	 }
	 AD7545_handle();
#else
	#if 0
	 
	 if(UART4->DR == 0)
	 {
	 		setDC_Value(0);
	 }
	
	 else
	 {
	 		SetCurentPercent (UART4->DR );
		//setDC_Value(UART4->DR);
	 }
	
	if((UART4->SR )& 0X10)//if(USART_GetITStatus(UART4, USART_IT_IDLE))
	{
		g_stVlue.ubUsartCount = 0;
	}
	else
	{
		 g_stVlue.ubUsartCount ++;
		 USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		 USART_ClearITPendingBit(UART4,USART_FLAG_TC);
	}
	#else
	 
		if(UART4->DR != 0xfe)
		{	
			g_stVlue.ubUsartCount++;
			if(g_stVlue.pUsartBuffer < g_stVlue.pUsartBuffer + UART4BuferSize)
			{
				*g_stVlue.pUsartBuffer = UART4->DR;
				 g_stVlue.pUsartBuffer ++;
			}
			else
			{
         g_stVlue.pUsartBuffer = g_stVlue.tabUsartValue;
      }
		}
		else
		{
				g_stVlue.ubUsart4Event  = 1;
			  Uart4_Event(&g_stVlue);
			  RestoreUsart(4);
    }
		
	#endif
#endif	
}

void AD7545_handle(void )								    
{	 
	 u16 ubValue = 0;
	
	 
#if  1
	 if(g_stVlue.ubUsartCount >= 2)
	 { 
	 	  ubValue = g_stVlue.tabUsartValue [0];
		  ubValue <<= 8;
		  ubValue |= g_stVlue.tabUsartValue [1];
		  setDC_Value(ubValue);
		  memset(g_stVlue.tabUsartValue, 0, 100);
		  g_stVlue.ubUsartCount = 0;
	 }
#endif
}  
#define AD7545 1
#define CONFIG 2

void RestoreUsart(u8 num)
{
		switch(num)
		{
			 case 1:
				 break;
			 
			 case 2:
				 break;
			 
			 case 3:
				 break;
			 
			 case 4:
			 {
					g_stVlue.pUsartBuffer = g_stVlue.tabUsartValue;
				  memset(g_stVlue.tabUsartValue, 0, UART4BuferSize);
       }
				 break;
			 
			 default :
				 break;
			 
    }

}

void Uart4_Event( ST_Value * p)
{
		u8 ubEvent = 0;
	
		if(p->ubUsart4Event != 1)
		{
				return;
    }
		ubEvent = p->tabUsartValue[1];
		
		switch(ubEvent)
		{
				case AD7545:
					SetCurentPercent (p->tabUsartValue[2] );
				break;
				
				case CONFIG:
					setViltageCurrent(p->tabUsartValue[2],p->tabUsartValue[3]);//(CURRENT_TUPE,RATION_100);
				break;
				
				default:
					break;
					
    }
	

}









