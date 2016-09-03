#ifndef DRIVERIT_H
#define DRIVERIT_H

//#include "stm32f10x_Lib.h"
#include "OSType.h"

#define NMIExceptionChannel 		0
#define HardFaultExceptionChannel	1
#define MemManageExceptionChannel	2
#define BusFaultExceptionChannel	3
#define UsageFaultExceptionChannel	4
#define DebugMonitorChannel			5
#define SVCHandlerChannel			6
#define PendSVCChannel				7
#define SysTickHandlerChannel		8

#define MAX_EXCEPTION  (SysTickHandlerChannel+1)

typedef void(*FUInterrupt)();

void It_vSetException(u8 syIndex,FUInterrupt fuInterrupt);

#define CPU_CLOCK_HZ			( ( UINT32) 72000000 )	
#define TICK_RATE_HZ			( ( UINT32 ) 1000 )

#endif
