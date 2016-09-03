
#include "OS005_Mutex.h"
#include "OS003_CPU.h"
#include "OS001_Task.h"

void Mutex_vInit(struct STMutex* pstMutex)
{
	memset(pstMutex,0,sizeof(struct STMutex));
}

void Mutex_vLock(struct STMutex* pstMutex)
{
	INTSYS syFlagIE;
	INTSYS syLock=0;
	struct STTask* pstCurTask;
	DISABLE_INTERRUPT
	if(pstMutex->ubFlag!=0)
	{
		syLock=1;
		pstCurTask=g_pstCurTask;			
	}
	else
	{
		pstMutex->ubFlag=1;	
	}
	ENABLE_INTERRUPT

	if(syLock!=0)
	{
		pstMutex->ulPriorityGroup|=pstCurTask->ulPriorityBit;

		DISABLE_INTERRUPT
		g_ulTaskGroup&= ~g_pstCurTask->ulPriorityBit;
		ENABLE_INTERRUPT
		Task_vSwitchHigh();
	}	
}

void Mutex_vUnlock(struct STMutex* pstMutex)
{
	INTSYS syFlagIE;
	UINT8 ubPriValue;
	UINT8 ubHighPriority;
	UINT8* pub;
	struct STTask* pstHighTask;

	DISABLE_INTERRUPT
	if(pstMutex->ulPriorityGroup==0)
	{
		pstMutex->ubFlag=0;	
		ENABLE_INTERRUPT
		return;
	}
	TASK_GET_HIGH_PRI(ubHighPriority,pstMutex->ulPriorityGroup,pub);
    //ubHighPriority = Task_syGetHighPri(pstMutex->ulPriorityGroup);
	ENABLE_INTERRUPT	
	
	pstHighTask=g_ppTaskTable[ubHighPriority];
	pstMutex->ulPriorityGroup&= ~pstHighTask->ulPriorityBit;
	
	//DISABLE_INTERRUPT
	Task_vActive(ubHighPriority);
	Task_vSwitchHigh();
	//ENABLE_INTERRUPT
}








