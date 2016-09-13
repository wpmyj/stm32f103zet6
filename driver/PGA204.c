#include "PGA204.h"

#define A0_1 	(1 << 8 )
#define A1_1 	(1 << 9 )

void PGA204Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
#if 1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
}

void SetAmplification( u32 num) 
{
	switch(num)
	{
	  	case 1:
		{
		   GPIO_ResetBits(GPIOB,A0_1 | A1_1);
		}
		break;

		case 10:
		{
			GPIO_SetBits(GPIOB,A0_1);
			GPIO_ResetBits(GPIOB,A1_1);
		}
		break;

		case 100:
		{
			GPIO_ResetBits (GPIOB,A0_1);
			GPIO_SetBits(GPIOB,A1_1);
		}
		break;

		case 1000:
		{
			GPIO_SetBits(GPIOB,A0_1 | A1_1);
    	}												   
		break;
		default:
		  break;
	}
}

