#include "DriverIt.h"

//#include "DriverUsart4.h"

//#include "stm32f10x.h"

//#include "stm32f10x_gpio.h"
//#include "misc.h"

#include "OSType.h"


static FUInterrupt _pfuExceptionArray[MAX_EXCEPTION]=
{
	0,0,0,0,0,0,0,0,0
};

void It_vSetException(u8 syIndex,FUInterrupt fuInterrupt)
{
	if(syIndex>=MAX_EXCEPTION)
	{
		while(1);
	}
	_pfuExceptionArray[syIndex]	 = fuInterrupt;
}

void PendSVC(void)
{
	if(_pfuExceptionArray[PendSVCChannel]!=0)	 
	{
		_pfuExceptionArray[PendSVCChannel]();
	}
}

void SysTickHandler(void)
{
	if(_pfuExceptionArray[SysTickHandlerChannel]!=0)	 
	{
		_pfuExceptionArray[SysTickHandlerChannel]();
	}
}







