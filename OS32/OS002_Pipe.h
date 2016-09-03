
#ifndef OS002_PIPE_RX_H
#define OS002_PIPE_RX_H

#ifdef MEMERY_USE

struct STPipeRx
{
	struct STCutMemSys stCutSys;
	struct STTask* pstTask;
	struct STSLink* pstHead;
	struct STSLink* pstCurrent;
	struct STSLink* pstTail;
	void (*fuRxProcess)(void* pv);
};

struct STPipeTx
{
	struct STTask* pstTask;
	void (*fuTx)(void* pvData,INTSYS sySize);
};

void PipeTx_vTansmit(struct STPipeTx* pstPipeTx,UINT8* pubData,INTSYS sySize);

void PipeRx_vInitBufferSys(struct STPipeRx* pstPipeRx,
				INTSYS sySize,
				INTSYS syMaxCount,
				void (*fuRxProcess)(void* pv),
				UINT8 ubPriority,
				INTSYS syStackSize);
void PipeRx_vInit(struct STPipeRx* pstPipeRx,
				INTSYS sySize,
				INTSYS syMaxCount);
UINT8* PipeRx_pubGetBuffer(struct STPipeRx* pstPipeRx);
void PipeRx_vCopyData(struct STSLinkSys* pstData,struct STPipeRx* pstPipeRx);
void PipeRx_vReturnBuffer(struct STPipeRx* pstPipeRx,struct STSLinkSys* pstData);
#endif

#endif













