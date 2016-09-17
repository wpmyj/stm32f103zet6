#include "relay.h"


void relay_init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_5;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//复用推挽输出
 	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//复用推挽输出
 	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
}



void setViltageCurrent(u8 type, u8 ratio)
{
		switch (type)
	  {
				case VOLTAGE_TYPE ://电压
				{
						GPIO_SetBits(GPIOB,GPIO_Pin_5);			//电压
					
						if(ratio == RATION_100)
						{
								GPIO_SetBits(GPIOA,GPIO_Pin_11);    //100
						}
						if(ratio == RATIO_5574)
						{
								GPIO_ResetBits(GPIOA,GPIO_Pin_11);	//57.74
						}
				}
				break;
				
				case CURRENT_TUPE :
				{
						GPIO_ResetBits(GPIOB,GPIO_Pin_5);   //电流
					
					  if(ratio == RATION_5A)
						{
								GPIO_SetBits(GPIOA,GPIO_Pin_11);    //5A
						}
						if(ratio == RATION_1A)
						{
								GPIO_ResetBits(GPIOA,GPIO_Pin_11);	//1A
						}
        }
				break;
				
				default:
					break;
    }
}

void relay_test(void)
{
	relay_init();
	GPIO_SetBits(GPIOA,GPIO_Pin_11);    //100
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);	//57.74
	GPIO_SetBits(GPIOB,GPIO_Pin_5);			//电压
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);   //电流
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_9);
	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);

}