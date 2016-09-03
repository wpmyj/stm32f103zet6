#include "OSType.h"
#include "OS004_Sleep.h"
#include "OS005_Mutex.h"
#include "OS001_Task.h"

//#define  TASK_ACKTIVE

static UINT32 _ulSleepFlag=0;
static UINT8* _pubSleepFlag= (UINT8*)&_ulSleepFlag;
static UINT16* _puiSleepFlag= (UINT16*)&_ulSleepFlag;
static INTSYS _psySleepCountArray[32];

void Sleep_vInit(void)
{
	
}


void Sleep_vSet(struct STTask* pstTask,INTSYS syCount)
{
	_psySleepCountArray[pstTask->ulPriority]=syCount;
	_ulSleepFlag |= pstTask->ulPriorityBit;	
}											    

void Sleep_vProcess(void)
{
	UINT32 ulPri;
	UINT32 i;
	if(_ulSleepFlag==0)
	{
		return;
	}

	if(_puiSleepFlag[0]!=0)
	{
		if(_pubSleepFlag[0]!=0)
		{
			ulPri=_pubSleepFlag[0];
			i=0;
			while(ulPri!=0)
			{
				if((ulPri&1)!=0)
				{
					if(_psySleepCountArray[i]!=0)
					{
						_psySleepCountArray[i]--;
					}
					else
					{
						_ulSleepFlag &= ~(1<<i);
						#ifndef TASK_ACKTIVE
						Task_vActive(i);
						#endif
					}	
				}
				ulPri>>=1;
				i++;	
			}	
		}
		if(_pubSleepFlag[1]!=0)
		{
			ulPri=_pubSleepFlag[1];
			i=8;
			while(ulPri!=0)
			{
				if((ulPri&1)!=0)
				{
					if(_psySleepCountArray[i]!=0)
					{
						_psySleepCountArray[i]--;
					}
					else
					{
						_ulSleepFlag &= ~(1<<i);
						#ifndef TASK_ACKTIVE
						Task_vActive(i);
						#endif
					}	
				}
				ulPri>>=1;
				i++;	
			}
		}
	}

	if(_puiSleepFlag[1]!=0)
	{
		if(_pubSleepFlag[2]!=0)
		{
			ulPri=_pubSleepFlag[2];
			i=16;
			while(ulPri!=0)
			{
				if((ulPri&1)!=0)
				{
					if(_psySleepCountArray[i]!=0)
					{
						_psySleepCountArray[i]--;
					}
					else
					{
						_ulSleepFlag &= ~(1<<i);

						#ifndef TASK_ACKTIVE
						Task_vActive(i);
						#endif
					}	
				}
				ulPri>>=1;
				i++;	
			}			
		}
		if(_pubSleepFlag[3]!=0)
		{
			ulPri=_pubSleepFlag[3];
			i=24;
			while(ulPri!=0)
			{
				if((ulPri&1)!=0)
				{
					if(_psySleepCountArray[i]!=0)
					{
						_psySleepCountArray[i]--;
					}
					else
					{
						_ulSleepFlag &= ~(1<<i);
						#ifndef TASK_ACKTIVE
						Task_vActive(i);
						#endif
					}	
				}
				ulPri>>=1;
				i++;	
			}
		}
	}

	//Mutex_vUnlock(&_stMutex);
	#ifndef TASK_ACKTIVE
	Task_vSwitchHigh();	
	#endif
}








