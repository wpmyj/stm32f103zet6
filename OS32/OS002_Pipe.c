
#include "OS002_Pipe.h"

#ifdef MEMERY_USE

static void _vRxTask(void * pv);

void PipeRx_vInitBufferSys(struct STPipeRx* pstPipeRx,
				INTSYS sySize,
				INTSYS syMaxCount,
				void (*fuRxProcess)(void* pv),
				UINT8 ubPriority,
				INTSYS syStackSize)
{
	struct STTaskSys* pstTaskSys;
	Memery_vCutConfigure(&pstPipeRx->stCutSys,sySize+sizeof(struct STSLink),syMaxCount);
	pstPipeRx->pstHead = pstPipeRx->stCutSys.pstHead;
	pstPipeRx->pstTail = SLink_pstEnd(pstPipeRx->pstHead);
	pstPipeRx->fuRxProcess = fuRxProcess;
	pstPipeRx->pstCurrent = 0;
	pstTaskSys=TaskSys_pstCreate(_vRxTask,
									pstPipeRx,
									syStackSize,
									ubPriority);
	pstPipeRx->pstTask=	&pstTaskSys->stTask;
}

void PipeRx_vInit(struct STPipeRx* pstPipeRx,
				INTSYS sySize,
				INTSYS syMaxCount)
{
	Memery_vCutConfigure(&pstPipeRx->stCutSys,sySize+sizeof(struct STSLink),syMaxCount);
	
	pstPipeRx->pstHead = pstPipeRx->stCutSys.pstHead;
	pstPipeRx->pstTail = SLink_pstEnd(pstPipeRx->pstHead);
	pstPipeRx->fuRxProcess = 0;
	pstPipeRx->pstCurrent = 0;
}

UINT8* PipeRx_pubGetBuffer(struct STPipeRx* pstPipeRx)
{
	struct STSLink* pstSLink;
	if(pstPipeRx->pstHead==0)
	{
		return 0;
	}
	if(pstPipeRx->pstCurrent==0)
	{
		pstPipeRx->pstCurrent=pstPipeRx->pstHead;	
	}
	else if(pstPipeRx->pstCurrent!=pstPipeRx->pstTail)
	{
		pstPipeRx->pstCurrent=pstPipeRx->pstCurrent->pstBack;	
	}
	else
	{
		return 0;		
	}
	return 	(UINT8*)&pstPipeRx->pstCurrent[1];
}

void PipeRx_vCopyData(struct STSLinkSys* pstData,struct STPipeRx* pstPipeRx)
{
	pstData->pstHead = pstPipeRx->pstHead;
	pstData->pstTail = pstPipeRx->pstCurrent;
	
	if( pstPipeRx->pstCurrent == pstPipeRx->pstTail )
	{
		pstPipeRx->pstHead = 0;
		pstPipeRx->pstTail = 0;
	}
	else
	{
		pstPipeRx->pstHead = pstPipeRx->pstCurrent->pstBack;
	}
	pstPipeRx->pstCurrent=0;		
}

void PipeRx_vReturnBuffer(struct STPipeRx* pstPipeRx,struct STSLinkSys* pstData)
{
	//pstData->pstTail->pstBack=0;
	if(pstPipeRx->pstHead==0)
	{
		pstPipeRx->pstHead=	pstData->pstHead;
		pstPipeRx->pstTail=	pstData->pstTail;
		pstPipeRx->pstCurrent=0;
	}
	else
	{
		pstPipeRx->pstTail->pstBack=pstData->pstHead;
		pstPipeRx->pstTail=pstData->pstTail;	
	}
}

void PipeTx_vTansmit(struct STPipeTx* pstPipeTx,UINT8* pubData,INTSYS sySize)
{
	INTSYS syFlagIE;
	DISABLE_INTERRUPT
	pstPipeTx->pstTask=g_pstCurTask;
	ENABLE_INTERRUPT
	pstPipeTx->fuTx(pubData,sySize);
	//Task_vSuspend();	
}


//static struct STTaskSys* _pstTaskSys;
//static struct STPipeRx _stPipeRx;

//static void (*_fuRxProcess)(CanRxMsg* pstRxMsg);

static void _vRxTask(void * pv)
{
	INTSYS syFlagIE;
	struct STPipeRx* pstPipeRx= (struct STPipeRx*)pv;
	struct STSLinkSys stSLinkSys;
	struct STSLink *pstSLink;
	//CanRxMsg* pstData;

	//_pstSLinkSys= &stSLinkSys;

	stSLinkSys.pstHead=0;
	stSLinkSys.pstTail=0;

	while(1)
	{
		DISABLE_INTERRUPT;
		if(pstPipeRx->pstCurrent!=0)
		{
			PipeRx_vCopyData(&stSLinkSys,pstPipeRx);
			ENABLE_INTERRUPT;
			goto process;
		}
		else
		{
			Task_vWaitMessage(MESSAGE_RX);
			ENABLE_INTERRUPT;
		}
		
		DISABLE_INTERRUPT
		PipeRx_vCopyData(&stSLinkSys,pstPipeRx);
		ENABLE_INTERRUPT
process:
		
		pstSLink=stSLinkSys.pstHead;
		stSLinkSys.pstTail->pstBack=0;
	
		while(pstSLink!=0)
		{
			//pstData= (CanRxMsg *)&pstSLink[1];
			//CMD_ubDo(pstData);
			pstPipeRx->fuRxProcess(&pstSLink[1]);
			pstSLink=pstSLink->pstBack;	
		}

		DISABLE_INTERRUPT;
		PipeRx_vReturnBuffer(pstPipeRx,&stSLinkSys);
		ENABLE_INTERRUPT;
		stSLinkSys.pstHead=0;
		stSLinkSys.pstTail=0;		
	}
}
#endif




