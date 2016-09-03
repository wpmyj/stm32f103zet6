 #include "DriverSystick.h"
 #include "OS003_CPU.h"
 #include "DA7545.h"
 #include "DriverUsart4.h"
 #include "PGA204.h"
#include "testConfig.h"

 void testClockInit(void);
 void Sample_ch6(void);
 #define VER_0 0

#define AG320240

 ST_Value g_stVlue;
 char TabString	[10] = {0} ;

int main()

{	
																			    
	INTSYS syFlagIE;
	DriverSystickInit();
	DISABLE_INTERRUPT//DISABLE_INTERRUPT	     
 
 #if (!RTOS)
 #if VER_0	
 											     
	EXTI_DeInit();
	test_NSS();
	testClockInit() ;
	usart4Init(9600);
	UART4->CR1 |= 1 << 8;//	PEIE
	AD7545_Init();
	PGA204Init();
	AD7606_Init();
	MachineFaultInit();
#ifdef AG320240
	AG320240_Init();
	
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
	setDC_Value(0);
	AD7606_Handle(); 
	test_gui();
	while(1)																							    
    {																						     
		sprintf(TabString,"%10.4f",g_stVlue.fADValue3 - g_stVlue.fADValue4Compensation);
		chdisp(7,44,TabString,1);
		sprintf(TabString,"%10.4f",g_stVlue.fADValue6 );
		chdisp(7,78,TabString,1);
		Sample_ch6();
	}
	#else
		Gpio164245_Init();
		while(1);
	#endif

#else

	ENABLE_INTERRUPT
	myTest();
	while(1);

#endif
 }

