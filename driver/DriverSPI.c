#include "DriverSPI.h"



void spi_1_innit(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	SPI_InitTypeDef     SPI_InitStructure;
		
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO |   RCC_APB2Periph_GPIOA,ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = AH320240_SCK |AH320240_MISI;	 //AH320240_MISO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AH320240_NSS  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 配置AD_SPI引脚: MISO */
	GPIO_InitStructure.GPIO_Pin = AH320240_MISO  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#if 1
	/* 配置AD_SPI引脚: MISI */ 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_SSOutputCmd(SPI1,ENABLE);
	SPI_Cmd(SPI1, ENABLE);

#endif 
}


void test_NSS(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = AH320240_NSS;	 //AH320240_MISO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,AH320240_NSS);
	GPIO_ResetBits(GPIOA,AH320240_NSS);
}

u16   SPI1_Write(u16 TxData)
{
	 u8 retry=0; 
	 GPIO_ResetBits(GPIOA,AH320240_NSS);  
     while((SPI1->SR&1<<1)==0)//等待发送区空 
     {
          retry++;
          if(retry>200)return 0;
     }     
	 SPI1->DR=TxData;       
	 GPIO_SetBits(GPIOA,AH320240_NSS);      
     return 1;  
}

u16   SPI1_WriteRead(u16 TxData)
{
     u16 retry=0;  
	 u32 date = 0; 

	 GPIO_ResetBits(GPIOA,AH320240_NSS);  
     while((SPI1->SR&1<<1)==0)//等待发送区空 
     {
          retry++;
          if(retry>200)return 0;
     }   
	 retry=0;  
     SPI1->DR=TxData;     //发送一个byte 
	 while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
     {
          retry++;
          if(retry>200)return 0;
     }    
     date = SPI1->DR;
     retry=0;
	 while((SPI1->SR&1<<1)==0)//等待发送区空 
     {
          retry++;
          if(retry>200)return 0;
     } 
	 SPI1->DR= 0;     //发送一个byte 
	 retry=0;
     while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
     {
          retry++;
          if(retry>200)return 0;
     } 
  
	 date <<= 8;
	 date |=  SPI1->DR;
	   
	 GPIO_SetBits(GPIOA,AH320240_NSS);      
     return date;          //返回收到的数据  
}


u16 SPI1_Read(void)
{
#if 0  
     u16 retry=0;   

	 GPIO_ResetBits(GPIOA,AH320240_NSS);  
     while((SPI1->SR&1<<1)==0)//等待发送区空 
     {
          retry++;
          if(retry>2000)return 0;
     }   
	 retry=0;  
     SPI1->DR=TxData;     //发送一个byte 
	 while((SPI1->SR&1<<1)==0)//等待发送区空 
     {
          retry++;
          if(retry>2000)return 0;
     }     
     SPI1->DR= 0;     //发送一个byte 
     retry=0;
     while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
     {
          retry++;
          if(retry>2000)return 0;
     }       
	 GPIO_SetBits(GPIOA,AH320240_NSS);      
     return SPI1->DR;          //返回收到的数据  
 #else
  	 u8 retry=0; 
	 GPIO_ResetBits(GPIOA,AH320240_NSS);  
     while((SPI1->SR&1<<1)==0)//等待发送区空 
     {
          retry++;
          if(retry>200)return 0;
     } 
	 SPI1->DR= 0;     //发送一个byte   
	 retry=0;  
    
     while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
     {
          retry++;
          if(retry>200)return 0;
     }  
	      
	 GPIO_SetBits(GPIOA,AH320240_NSS);  
	     
     return SPI1->DR;          //返回收到的数据        
#endif      
}

u8 SPI1_ReadByte(u8 TxData)
{  
     u8 retry=0;    
      while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
     {
          retry++;
          if(retry>200)return 0;
     }             
     return SPI1->DR;          //返回收到的数据        
}



