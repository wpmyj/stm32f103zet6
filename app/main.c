 #include "DriverSystick.h"
 #include "OS003_CPU.h"
 #include "DA7545.h"
 #include "DriverUsart4.h"
 #include "PGA204.h"
#include "testConfig.h"
#include "DeviceFsmc.h"
#include "led.h"
#include "monitoring.h"

 void testClockInit(void);
 void Sample_ch6(void);
 void relay_test(void);
 #define VER_0 1

#define AG320240

 ST_Value g_stVlue;
 char TabString	[10] = {0} ;
 
void sysclk_int(void)
 {
   RCC_DeInit(); /*???RCC????????? */ 
   RCC_HSICmd(ENABLE); 
   while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)== RESET);//??HSI?? 
   RCC_HCLKConfig(RCC_SYSCLK_Div1);   /*??AHB??(HCLK) RCC_SYSCLK_Div1——AHB?? = ???*/  
   RCC_PCLK2Config(RCC_HCLK_Div1);   /* ????AHB??(PCLK2)RCC_HCLK_Div1——APB2?? = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2); /*????AHB??(PCLK1)RCC_HCLK_Div2——APB1?? = HCLK / 2*/      
   //FLASH_SetLatency(FLASH_Latency_2);   /*??FLASH??????????FLASH_Latency_2  2????*/   
   //FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  /*??FLASH???????,???????*/ 
   RCC_PLLConfig(RCC_HCLK_Div1, RCC_PLLMul_9);/*??PLL????????,???8/2*16=64Mhz*/    
   RCC_PLLCmd(ENABLE); 	 /*??PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*?????RCC???(PLL?????)????*/    
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*??????(SYSCLK) */  
   while(RCC_GetSYSCLKSource() != 0x08);     /*0x08:PLL?????? */	  
}

int main()

{	
																			    
	INTSYS syFlagIE;
	//DriverSystickInit();
	DISABLE_INTERRUPT//DISABLE_INTERRUPT	     
 
 #if (!RTOS)
 #if VER_0	
	//delay(60000);
  sysclk_int();
  led_init();	
	EXTI_DeInit();
	test_NSS();
	testClockInit() ;
	usart4Init(9600);
	UART4->CR1  |= 1 << 8;//	PEIE
  g_stVlue.pUsartBuffer = g_stVlue.tabUsartValue;
	AD7545_Init();
	PGA204Init();
	AD7606_Init();
	MachineFaultInit();
#ifdef AG320240
	AG320240_Init();
	relay_test();
	delay(60000);
	delay(60000);
	screen1();
	delay(60000);
	delay(60000);
	screen2();
#endif 
	ENABLE_INTERRUPT 
		
	delay(60000);
	delay(60000);
	setDC_Value(1000);
	setDC_Value(1500);
 	setDC_Value(2000);
	setDC_Value(2500);
	setDC_Value(3000);	
	setDC_Value(4000);
  setDC_Value(5000);	
	setDC_Value(6200);
	setDC_Value(0);
	AD7606_Handle(); 
	test_gui();
	while(1)																							    
  {																						     
		sprintf(TabString,"%10.4f",g_stVlue.fADValue3 - g_stVlue.fADValue4Compensation);
		chdisp(7,44,TabString,1);
		sprintf(TabString,"%10.4f",g_stVlue.fADValue6 );
		chdisp(7,78,TabString,1);
		Sample_Chanal(5);
	}
	#else
		//Gpio164245_Init();
		ENABLE_INTERRUPT 
	  PGA204Init();
		FSMC_Init();	
		{
			SetAD7545(0x0000,0x07ff);// a5
			SetAD7545(0x0020,0x07ff);// a5
			SetAD7545(0x0040,0x07ff);// a6
			SetAD7545(0x0060,0x07ff);// a5 a6 
			SetAD7545(0x0080,0x07ff);// a7
			SetAD7545(0x00a0,0x07ff);//  a7 a5
			SetAD7545(0x00c0,0x07ff);//  a7 a6
			SetAD7545(0x00e0,0x07ff);//  a7 a6 a5		
			SetAD7545(0x0000,0x0fff);// a5
			SetAD7545(0x0020,0x0fff);// a5
			SetAD7545(0x0040,0x0fff);// a6
			SetAD7545(0x0060,0x0fff);// a5 a6 
			SetAD7545(0x0080,0x0fff);// a7
			SetAD7545(0x00a0,0x0fff);//  a7 a5
			SetAD7545(0x00c0,0x0fff);//  a7 a6
			SetAD7545(0x00e0,0x0fff);//  a7 a6 a5
		}
		while(1);	
	#endif   

#else

	ENABLE_INTERRUPT
	 myTest();
	while(1);

#endif
 }

