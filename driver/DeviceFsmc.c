#include "DeviceFsmc.h"
#include "stm32f10x_systick.h"

#define Bank1_SRAM1_ADDR    ((u32)(0x60000000))
#define Bank1_SRAM2_ADDR    ((u32)(0x64000000))
#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))
#define Bank1_SRAM4_ADDR    ((u32)(0x6c000000))


void Gpio164245_Init()
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	 GPIO_InitStructure.GPIO_Pin |= 1 << 14;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//复用推挽输出
 	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 GPIO_SetBits(GPIOB,1 << 14);
	 GPIO_ResetBits(GPIOB,1 << 14);
}

void FSMC_Init(void)
{
		FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;

		FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;
		GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
		GPIO_InitStructure.GPIO_Pin = 0xc733; 			 	//PORTD复用推挽输出  1100 0111 0011 0011
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	//复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = 0xFF80;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 		 //PORTE复用推挽输出 
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = 0xF03F;					 //	 1111 0000 0011 1111
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  			 	//PORTF复用推挽输出 
		GPIO_Init(GPIOF, &GPIO_InitStructure);
 #if 1
	GPIO_InitStructure.GPIO_Pin = 0x003F;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 			 	//PORTG复用推挽输出 
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
 #endif
    readWriteTiming.FSMC_AddressSetupTime = 0x03;	 //地址建立时间（ADDSET）为1个HCLK 1/36M=27ns
    readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
    readWriteTiming.FSMC_DataSetupTime = 0x06;		 //数据保持时间（DATAST）为3个HCLK 4/72M=55ns(对EM的SRAM芯片)	 
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
	  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit  
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//存储器写使能 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; // 读写使用相同的时序
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; //读写同样时序
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置
   	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  //使能BANK4

}


void SetAD7545_1(u8 v)
{
	 //*() = 0x0ffff
}
  
void test_164245(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);
	 GPIO_InitStructure.GPIO_Pin = 0xc733; 			 	//PORTD复用推挽输出  1100 0111 0011 0011
 	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	//复用推挽输出
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	 GPIO_Init(GPIOD, &GPIO_InitStructure);
}



