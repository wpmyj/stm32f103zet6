#ifndef C142_KEY_H
#define C142_KEY_H

#include "C202_In.h"

#define KEY_EVENT_PRESS  1
#define KEY_EVENT_UP     2
#define KEY_EVENT_DOWN   3


struct STKey
{
	UINT8 ubStatus;
	UINT8 ubIO;
	UINT8 ubPressCounter;
	UINT8 ubPressLimit;
	void (*fuEventProcess)(INTSYS syEvent);
};

void Key_vInit(struct STKey* pstKey);
void Key_vTest();
void Key_vUpdate(struct STKey* pstKey);

#endif