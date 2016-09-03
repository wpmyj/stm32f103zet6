#include "DriverSystick.h"
#include "ostype.h"
#include "DriverIt.h"
#include "testConfig.h"
#include "stm32f10x_gpio.h"


u32    g_ulSystemCounter;
extern void taskSw(void);
extern void AD7606_Handle(void);
extern ST_Value g_stVlue;

TMailBox T7606Mail;
AD7606_INFO stAd7606;

static void _vInterruptProcess() 
{      
	g_ulSystemCounter++;

	if(g_ulSystemCounter > 5)
	{
		g_ulSystemCounter = 0;	
		GPIO_WriteBit(GPIOE, GPIO_Pin_2, (BitAction) (1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_2)));
	}

	if((T7606Mail.Value[6] < SAMPLE_RATE) && (T7606Mail.Status[6] == 0))
	{
		T7606Mail.Value[6]++;
		AD7606_Handle(); 
		stAd7606.ch6[T7606Mail.Value[6]] = g_stVlue.tubAD_Value[6]; 

		if(T7606Mail.Value[6] >= SAMPLE_RATE )
		{
			  T7606Mail.Status[6] = 1;
			  T7606Mail.Value[6]  =0;
		}
	}
	#if RTOS
	taskSw();
	IE_vGeneratePendSV();
	#endif
}

 void DriverSystickInit(void)
 {
   RCC_DeInit();
   RCC_Configuration();
   SysTick_SetReload(6250 / 5);
   SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
   SysTick_CounterCmd(SysTick_Counter_Enable);
   SysTick_ITConfig(ENABLE);
   It_vSetException(SysTickHandlerChannel,_vInterruptProcess);
 }

void testClockInit(void)
{
   GPIO_InitTypeDef 	GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE,ENABLE );
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2	;	
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								         
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ÍÆÍìÊä³ö		
	 GPIO_Init (GPIOE, &GPIO_InitStructure);
}

void Timer_vStart(void)
{
	SysTick_CounterCmd(SysTick_Counter_Enable);	
}

void Timer_vStop(void)
{
	SysTick_CounterCmd(SysTick_Counter_Disable);	
}


