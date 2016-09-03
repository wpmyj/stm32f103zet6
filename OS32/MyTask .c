
#include "OS001_Task.h"
#include "OS003_CPU.h"
#include "DA7545.h"

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


void TASK_GET_HIGH_PRI(UINT8 __hi,UINT32 __group, UINT8* __pub)   
{										  
	__pub=(UINT8*)&__group;			  
	if(__pub[0]!=0)					  
	{									  
		__hi=	g_pubMapTbl[__pub[0]];	  
	}									  
	else if(__pub[1]!=0)				  
 	{									  
		__hi=	g_pubMapTbl[__pub[1]]+8; 
	}									  
	else if(__pub[2]!=0)				  
 	{									  
		__hi=	g_pubMapTbl[__pub[2]]+16;
	}									  
	else								  
 	{									 
	   __hi=	g_pubMapTbl[__pub[3]]+24;
	}									  
}


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

INTSYS *CPU_psyInitSP (void (*fuTask)(void *pvArg), void* pvArg,INTSYS* psySP)
{
    INTSYS *psyStk;
                   
    psyStk       = psySP;                         /* Load stack pointer                                     */
                                                  /* Registers stacked as if auto-saved on exception        */
    *(psyStk)    = (INTSYS)0x01000000L;           /* xPSR                                                   */
    *(--psyStk)  = (INTSYS)fuTask;                  /* Entry Point                                            */
    *(--psyStk)  = (INTSYS)0xFFFFFFFEL;           /* R14 (LR) (init value will cause fault if ever used)    */
    *(--psyStk)  = (INTSYS)0x12121212L;           /* R12                                                    */
    *(--psyStk)  = (INTSYS)0x03030303L;           /* R3                                                     */
    *(--psyStk)  = (INTSYS)0x02020202L;           /* R2                                                     */
    *(--psyStk)  = (INTSYS)0x01010101L;           /* R1                                                     */
    *(--psyStk)  = (INTSYS)pvArg;                 /* R0 : argument                                          */

                                               /* Remaining registers saved on process stack             */
    *(--psyStk)  = (INTSYS)0x11111111L;           /* R11                                                    */
    *(--psyStk)  = (INTSYS)0x10101010L;           /* R10                                                    */
    *(--psyStk)  = (INTSYS)0x09090909L;           /* R9                                                     */
    *(--psyStk)  = (INTSYS)0x08080808L;           /* R8                                                     */
    *(--psyStk)  = (INTSYS)0x07070707L;           /* R7                                                     */
    *(--psyStk)  = (INTSYS)0x06060606L;           /* R6                                                     */
    *(--psyStk)  = (INTSYS)0x05050505L;           /* R5                                                     */
    *(--psyStk)  = (INTSYS)0x04040404L;           /* R4                                                     */

    return (psyStk);
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

void test1(void* pvArg)
{		   
		int a = 0;  
	    while(1)
	    {

			setDC_Value(5555);
		}
}

void test2(void* pvArg)
{
		  AD7545_Init();
		  
		  while(1)
		  {
		   	setDC_Value(5555);
			while(1);
		  }
}
struct STTask st1,st2,st3;
INTSYS t1[128],t2[128],t3[128];

void myTest(void)
{
		UINT32 ulHighPri;
		UINT8* pub;
		
		Task_vCreate(&st1,test1,0,&t1[127],0);
		Task_vCreate(&st2,test2,0,&t2[127],1);

		g_pstCurTask = &st1;
		g_pstHighTask = &st1;

		IE_vGenerateFirstPendSV();

				
//		TASK_GET_HIGH_PRI(ulHighPri,g_ulTaskGroup,pub);
//		g_pstHighTask=g_ppTaskTable[ulHighPri];	
}

void taskSw(void)
{
	  if(g_pstHighTask == &st1)
	  {
	  		g_pstHighTask = &st2;
	  }
	  else
	  {
	  		g_pstHighTask = &st1;
	  }
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
	g_ulTaskGroup&= ~g_pstCurTask->ulPriorityBit;
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
	g_pstCurTask->syMessage= syMessage;
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
 #if 0
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

#endif




