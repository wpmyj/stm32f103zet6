
#ifndef CPU_H
#define CPU_H

#include "OSType.h"


INTSYS *CPU_psyInitSP (void (*fuTask)(void *pvArg), 
						void* pvArg,INTSYS* psySP);

 

#define DISABLE_INTERRUPT  		 syFlagIE = IE_syDisable();//syFlagIE = IE_syDisable();//
#define ENABLE_INTERRUPT		 IE_vSet(syFlagIE);//OS_CPU_SR_Restore();//

#endif




