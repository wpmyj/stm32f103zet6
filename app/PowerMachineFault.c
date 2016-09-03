#include "PowerMachineFault.h"
#include "DriverEXTLine.h"

void MachineFaultInit(void)
{
	  ExtLineConfig(GPIO_PortSourceGPIOA, 12 );
	  ExtLineConfig(GPIO_PortSourceGPIOG, 7);
}
