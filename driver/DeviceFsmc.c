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
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//�����������
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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
		GPIO_InitStructure.GPIO_Pin = 0xc733; 			 	//PORTD�����������  1100 0111 0011 0011
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	//�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = 0xFF80;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 		 //PORTE����������� 
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = 0xF03F;					 //	 1111 0000 0011 1111
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  			 	//PORTF����������� 
		GPIO_Init(GPIOF, &GPIO_InitStructure);
 #if 1
	GPIO_InitStructure.GPIO_Pin = 0x003F;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 			 	//PORTG����������� 
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
 #endif
    readWriteTiming.FSMC_AddressSetupTime = 0x03;	 //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK 1/36M=27ns
    readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
    readWriteTiming.FSMC_DataSetupTime = 0x06;		 //���ݱ���ʱ�䣨DATAST��Ϊ3��HCLK 4/72M=55ns(��EM��SRAMоƬ)	 
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
	  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit  
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//�洢��дʹ�� 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; // ��дʹ����ͬ��ʱ��
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; //��дͬ��ʱ��
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����
   	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  //ʹ��BANK4

}


void SetAD7545_1(u8 v)
{
	 //*() = 0x0ffff
}
  
void test_164245(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);
	 GPIO_InitStructure.GPIO_Pin = 0xc733; 			 	//PORTD�����������  1100 0111 0011 0011
 	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	//�����������
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	 GPIO_Init(GPIOD, &GPIO_InitStructure);
}



