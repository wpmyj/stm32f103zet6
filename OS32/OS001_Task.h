#ifndef OS001_TASK_H
#define OS001_TASK_H

#include "OSType.h"

#define TASK_SLEEP_PRI    0
#define TASK_FIFO_PRI    30 
#define TASK_IDLE_PRI	 31



#if 0
#define TASK_GET_HIGH_PRI(__hi,__group,__pub)   \
{										  \
	__pub=(UINT8*)&__group;	\
	if(__pub[0]!=0)					  \
	{									  \
		__hi=	g_pubMapTbl[__pub[0]];	  \
	}									  \
	else if(__pub[1]!=0)				  \
 	{									  \
		__hi=	g_pubMapTbl[__pub[1]]+8; \
	}									  \
	else if(__pub[2]!=0)				  \
 	{									  \
		__hi=	g_pubMapTbl[__pub[2]]+16;\
	}									  \
	else								  \
 	{									  \
	   __hi=	g_pubMapTbl[__pub[3]]+24;\
	}									  \
}
#endif

struct STTask
{
	INTSYS *psySP;
	UINT32 ulPriority;
	UINT32 ulPriorityBit;
	INTSYS syMessage;
	void* pvParameter;
	struct STTask* pstNext;
};


struct STTaskSys
{
	struct STTask stTask;
	INTSYS psyStackBuffer[1];
};

struct STTaskSys* TaskSys_pstCreate(void (*fuEntry)(void* pvArg),
	void* pvParament,INTSYS syStackSize,UINT8 ubPriority);


#define MESSAGE_RX 1
#define MESSAGE_TX 2
#define MESSAGE_REMOTE_CAN_WRITE  3
#define MESSAGE_REMOTE_CAN_READ   4

typedef void* PV;
 

INTSYS Task_syGetHighPri(UINT32 ulPriGroup);
void Task_vCreate(struct STTask* pstTask,void (*fuEntry)(void* pvArg),
					void* pvArg,INTSYS* psySP,UINT8 ubPriority);
void Task_vStart(void);
void Task_vTest(void);
void Task_vSwitchHigh(void);
void Task_vSwitchTo(UINT8 ubPriority);
void Task_vSleep(INTSYS syCount);
void Task_vActive(UINT8 ubPriority);
void Task_vSuspend(void);
void Task_vWaitMessage(INTSYS syMessage);
void Task_vSendMessage(struct STTask* pstTask,INTSYS syMessage,void* pvParameter);
void myTest(void);
#endif


extern UINT8 g_ubTaskGroupMask;
extern UINT32 g_ulTaskGroup;
extern UINT8 *g_pubTaskGroupTable_1,*g_pubTaskGroupTable_2,
		*g_pubTaskGroupTable_3,*g_pubTaskGroupTable_4;

extern struct STTask *g_pstCurTask;
extern UINT8 g_ubCurPriority;
extern INTSYS g_sySleepFlag;
extern struct STTask *g_pstHighTask;
extern UINT8 g_ubHighPriority;
extern INTSYS g_syInterruptNest;
extern UINT8  const  g_pubMapTbl[256];
extern struct STTask* g_ppTaskTable[32];

#define INTERRUPT_NEST_INCREASE   DISABLE_INTERRUPT; g_syInterruptNest++; ENABLE_INTERRUPT;

#define INTERRUPT_EXIT     DISABLE_INTERRUPT;g_syInterruptNest--;\
if(g_syInterruptNest==0) \
{						 \
	Task_vSwitchHigh();	 \
} ENABLE_INTERRUPT



