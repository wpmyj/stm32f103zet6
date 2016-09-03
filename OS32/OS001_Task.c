
#include "OS001_Task.h"
#include "OS003_CPU.h"
#include "OSType.h"
#include "OS004_Sleep.h"

struct STTask *g_pstCurTask=0;
struct STTask *g_pstHighTask=0;

INTSYS g_sySleepFlag=0;
INTSYS g_syInterruptNest=0;

UINT8  const  g_pubMapTbl[256] = 
{
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                            
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                           
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                         
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                               
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                      
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                   
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                 
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                    
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                   
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                     
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                           
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                      
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                      
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                            
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,                      
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0                      
};

UINT32 g_ulTaskGroup=0x00000000;


struct STTask* g_ppTaskTable[32]=
{
0,
};

static INTSYS _syInitFlag=0;

static void _vInit(void)
{
	UINT8* pub;
	INTSYS i;

	for(i=0;i<32;i++)
	{
		g_ppTaskTable[i]=0;
	}
	_syInitFlag=1;

}
void Task_vCreate(struct STTask* pstTask,void (*fuEntry)(void* pvArg),
					void* pvArg,INTSYS* psySP,UINT8 ubPriority)
{
	UINT8 ubTableIndex;
	UINT8 ubPriValue;
	UINT8 ubHighestPri;
	INTSYS i;

	if(_syInitFlag==0)
	{
		_vInit();
	}
	if(g_ppTaskTable[ubPriority]!=0)
	{
		while(1);
	}

	g_ppTaskTable[ubPriority]=pstTask;
	pstTask->psySP=CPU_psyInitSP(fuEntry,pvArg,psySP);
	pstTask->ulPriority= ubPriority;
	pstTask->ulPriorityBit= 1<<pstTask->ulPriority;
	pstTask->syMessage=0;
	pstTask->pvParameter=0;
	g_ulTaskGroup|=pstTask->ulPriorityBit;

}

INTSYS Task_syGetHighPri(UINT32 ulPriGroup)
{
	UINT8* pubPri=(UINT8*)&ulPriGroup;
	INTSYS syReturn;

	if(pubPri[0]!=0)
	{
		syReturn=	g_pubMapTbl[pubPri[0]];
	}
	else if(pubPri[1]!=0)
 	{
		syReturn=	g_pubMapTbl[pubPri[1]]+8;
	}
	else if(pubPri[2]!=0)
 	{
		syReturn=	g_pubMapTbl[pubPri[2]]+16;
	}
	else
 	{
	   syReturn=	g_pubMapTbl[pubPri[3]]+24;
	}
	return syReturn; 
}

void Task_vSwitchHigh(void)
{
	INTSYS syFlagIE;
	UINT8* pub;
	UINT32 ulHighPri;

	DISABLE_INTERRUPT
	TASK_GET_HIGH_PRI(ulHighPri,g_ulTaskGroup,pub);
	g_pstHighTask=g_ppTaskTable[ulHighPri];

	if(g_pstHighTask!=g_pstCurTask)
	{
		IE_vGeneratePendSV();		
	}
	ENABLE_INTERRUPT	
	
}

void Task_vSleep(INTSYS syCount)
{
	INTSYS syFlagIE;
	DISABLE_INTERRUPT
	Sleep_vSet(g_pstCurTask,syCount);	
	g_ulTaskGroup &= ~g_pstCurTask->ulPriorityBit;
	ENABLE_INTERRUPT
	Task_vSwitchHigh();		
}

void Task_vWaitMessage(INTSYS syMessage)
{
	INTSYS syFlagIE;
	UINT8* pub;
	UINT32 ulHighPri;

	DISABLE_INTERRUPT
	g_ulTaskGroup&= ~g_pstCurTask->ulPriorityBit;
	g_pstCurTask->syMessage=  syMessage;
	ENABLE_INTERRUPT
	Task_vSwitchHigh();	
}


void Task_vSendMessage(struct STTask* pstTask,INTSYS syMessage,void* pvParameter)
{
	INTSYS syFlagIE;
	UINT8* pub;
	UINT32 ulHighPri;

	DISABLE_INTERRUPT
 	if(pstTask->syMessage!=syMessage)
	{
		ENABLE_INTERRUPT
		return;	
	}
	pstTask->syMessage=0;
	pstTask->pvParameter=  pvParameter;
	g_ulTaskGroup|= pstTask->ulPriorityBit;
	ENABLE_INTERRUPT
	Task_vSwitchHigh();		
}
void Task_vSuspend(void)
{
	INTSYS syFlagIE;
	DISABLE_INTERRUPT
	g_ulTaskGroup&= ~g_pstCurTask->ulPriorityBit;
	ENABLE_INTERRUPT
	Task_vSwitchHigh();		
}


void Task_vActive(UINT8 ubPriority)
{
	struct STTask* pstTask;
	INTSYS syFlagIE;
	DISABLE_INTERRUPT
	pstTask=g_ppTaskTable[ubPriority];
	g_ulTaskGroup|=pstTask->ulPriorityBit;
	ENABLE_INTERRUPT
}

void Task_vSwitchTo(UINT8 ubPriority)
{
	INTSYS syFlagIE;
	DISABLE_INTERRUPT
	g_pstHighTask = g_ppTaskTable[ubPriority];
	IE_vGeneratePendSV();
	ENABLE_INTERRUPT
}

static struct STTask _stTaskIdle;
static INTSYS _psyTaskIdle[128];

static void _vTaskIdle(void* pvParameter)
{
	while(1)
	{
		//Task_vSwitchTo(2);

		if(g_sySleepFlag!=0)
		{
			//Sleep_vProcess();
			g_sySleepFlag=0;
		}
		else 
		{
			g_sySleepFlag=~g_sySleepFlag;
		}	
	}	
}

static struct STTask _stTaskFIFO;
static INTSYS _psyTaskFIFO[256];

static void _vTaskFIFOPro(void* pvParameter)
{
	while(1)
	{
	//	FIFOProcess_vProcess();		
	}	
}

static struct STTask _stTaskSleep;
static INTSYS _psyTaskSleep[128];
UINT32 t_ulSleepCount=0;
static void _vTaskSleep(void* pvParameter)
{
	
	while(1)
	{	
		Task_vSuspend();
		t_ulSleepCount++;
		Sleep_vProcess();
	}	
}



void Task_vStart(void)
{
	UINT8 ubPriValue;
	UINT8* pub;
	UINT32 ulHighPri;
	Sleep_vInit();
	
	Task_vCreate(&_stTaskIdle,_vTaskIdle,0,&_psyTaskIdle[128-1],TASK_IDLE_PRI);
	Task_vCreate(&_stTaskFIFO,_vTaskFIFOPro,0,&_psyTaskFIFO[256-1],TASK_FIFO_PRI);
	Task_vCreate(&_stTaskSleep,_vTaskSleep,0,&_psyTaskSleep[128-1],TASK_SLEEP_PRI);

	CPU_vSetSysIEPri(14,0xFF);
		
	TASK_GET_HIGH_PRI(ulHighPri,g_ulTaskGroup,pub);
	g_pstHighTask=g_ppTaskTable[ulHighPri];
	IE_vGenerateFirstPendSV();	
}

static struct STTask _stTask_1;
static INTSYS _psyTaskStack_1[128];
static void _vTestTask_1(void* pvParameter)
{
	while(1)
	{
		//Task_vSwitchTo(2);
		Task_vSleep(10);	
	}	
}


static struct STTask _stTask_2;
static INTSYS _psyTaskStack_2[128];
static void _vTestTask_2(void* pvParameter)
{
	while(1)
	{
		//Task_vSwitchTo(1);
	}	
}

void Task_vTest(void)
{
	Task_vCreate(&_stTask_1,_vTestTask_1,0,&_psyTaskStack_1[128-1],1);
	//Task_vCreate(&_stTask_2,_vTestTask_2,0,&_psyTaskStack_2[128-1],2);
	Task_vStart();
}




#ifdef MEMERY_USE

struct STTaskSys* TaskSys_pstCreate(void (*fuEntry)(void* pvArg),
	void* pvParament,INTSYS syStackSize,UINT8 ubPriority)
{
	struct STTaskSys* pstReturn;
	
	pstReturn=(struct STTaskSys*)Memery_pubBorrow(sizeof(struct STTaskSys)+(syStackSize-1)*sizeof(INTSYS));	
	Task_vCreate(&pstReturn->stTask,fuEntry,pvParament,
			&pstReturn->psyStackBuffer[syStackSize-1],ubPriority);
	return pstReturn;
}
#endif




