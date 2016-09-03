

#ifndef OS005_MUTEX_H
#define OS005_MUTEX_H
#include "OSType.h"

struct STMutex
{
	UINT8 ubFlag;
	UINT32 ulPriorityGroup;
};

void Mutex_vInit(struct STMutex* pstMutex);
void Mutex_vLock(struct STMutex* pstMutex);
void Mutex_vUnlock(struct STMutex* pstMutex);


#endif

