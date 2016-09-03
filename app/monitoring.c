#include "monitoring.h"
#include "OSType.h"
#include "math.h"

extern TMailBox T7606Mail;
extern AD7606_INFO stAd7606;
extern  ST_Value g_stVlue;

#define MAIL_FULL 1


u8 Sample_Chanal(u8 num )
{
	u8 i =0, j= 0;
	double z = 0ul;
	double ulValueX= 0ul;
	double ulValueY= 0ul;

	if((T7606Mail.Status[6] & MAIL_FULL) != 0)
	{
		for(i= 0; i< SAMPLE_RATE ;i ++)
		{
			 ulValueX +=(double) (stAd7606.ch6[i] * cos(2*Pi*i/SAMPLE_RATE))/(SAMPLE_RATE/2) ;
			 ulValueY +=(double) (stAd7606.ch6[i] * sin(2*Pi*i/SAMPLE_RATE))/(SAMPLE_RATE/2) ;
		}
		z=sqrt(ulValueX*ulValueX+ulValueY*ulValueY);			    
		g_stVlue.fADValue6 = z*10/(32768*1.4142135623); //
		T7606Mail.Status[6] &= ~T7606Mail.Status[6];
	}
}

void Sample_ch6(void)
{
	u8 i =0;
	double z = 0ul;
	double ulValueX= 0ul;
	double ulValueY= 0ul;
	if((T7606Mail.Status[6] & MAIL_FULL) != 0)
	{
		for(i= 0; i< SAMPLE_RATE ;i ++)
		{
			 ulValueX +=(double) (stAd7606.ch6[i] * cos(2*Pi*i/SAMPLE_RATE ))/(SAMPLE_RATE/2) ;
			 ulValueY +=(double) (stAd7606.ch6[i] * sin(2*Pi*i/SAMPLE_RATE))/(SAMPLE_RATE/2) ;
		}
		z=sqrt(ulValueX*ulValueX+ulValueY*ulValueY);			    
		g_stVlue.fADValue6 = z*10/(32768*1.4142135623);
		T7606Mail.Status[6] &= ~T7606Mail.Status[6];
	}
	
}
