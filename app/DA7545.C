
#include "DA7545.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


 

void AD7545_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD,ENABLE );
#if 0
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | 
	GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
	| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11;
#else
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All	;	
#endif
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;								         

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出


		
	GPIO_Init (GPIOD, &GPIO_InitStruct);

	GPIO_SetBits(GPIOD,AD7545_WR);


}

void setDC_Value(u16 num)	  //单位为毫伏
{
	u8 i = 0;
	float tem = 0;


	if(num > 6200)
	{
		return;
	}

	GPIO_ResetBits(GPIOD,AD7545_WR);

	tem = num *  0.6605;		 // 660.5 = 4095 /      

	num =(u16)tem & 0x0fff;


	for( ;i < 12; i++)

	{
		if(num & 0x01)
		{
			 GPIO_SetBits(GPIOD,1 << i);////GPIO_WriteBit(GPIOD,1 << i, 1);
		}

		else
		{
			 GPIO_ResetBits(GPIOD,1 << i);	  //GPIO_WriteBit(GPIOD,1 << i, 0);//
		}

		num >>=	1;
	}
   	GPIO_SetBits(GPIOD,AD7545_WR);
}


