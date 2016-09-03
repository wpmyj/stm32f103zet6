

#ifndef SLEEP_H
#define SLEEP_H

#include "OSType.h"
#include "OS001_Task.h"


void Sleep_vInit(void);
void Sleep_vProcess(void);
void Sleep_vSet(struct STTask* pstTask,INTSYS syCount);

#endif






