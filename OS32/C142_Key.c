#include "C142_Key.h"

void Key_vInit(struct STKey* pstKey)
{
	memset(pstKey,0,sizeof(struct STKey));
}

void Key_vUpdate(struct STKey* pstKey)
{
	if(pstKey->ubIO!=0)
	{
		if(pstKey->ubStatus!=0)
		{
			if(pstKey->ubPressCounter<pstKey->ubPressLimit)
			{
				pstKey->ubPressCounter++;
			}
			else
			{
				if(pstKey->fuEventProcess!=0)
				{
					pstKey->fuEventProcess(KEY_EVENT_PRESS);
				}	
			}
		}
		else
		{
			if(pstKey->fuEventProcess!=0)
			{
				pstKey->fuEventProcess(KEY_EVENT_DOWN);
			}
			pstKey->ubPressCounter=0;
			pstKey->ubStatus=1;	
		}
	}//pstKey->ubIO!=0
	else//pstKey->ubIO==0
	{
		if(pstKey->ubStatus!=0)
		{
			if(pstKey->fuEventProcess!=0)
			{
				pstKey->fuEventProcess(KEY_EVENT_UP);
			}
			pstKey->ubStatus=0;		
		}
	}//pstKey->ubIO==0
}

static void _vProcess(INTSYS syEvent)
{
	switch(syEvent)
	{
		case KEY_EVENT_PRESS:

		break;
		case KEY_EVENT_UP:

		break;
		case KEY_EVENT_DOWN:

		break;
	}
}


void Key_vTest()
{
	struct STKey stKey;
	Key_vInit(&stKey);
	stKey.fuEventProcess=_vProcess;
	stKey.ubPressLimit=2;
	stKey.ubIO=1;

	Key_vUpdate(&stKey);//_vDown()
	Key_vUpdate(&stKey);//null
	Key_vUpdate(&stKey);//null
	Key_vUpdate(&stKey);//_vPress()
	Key_vUpdate(&stKey);//_vPress()	

	stKey.ubIO=0;
	Key_vUpdate(&stKey);//_vUp()
	stKey.ubIO=1;
	Key_vUpdate(&stKey);//_vDown()		
}
