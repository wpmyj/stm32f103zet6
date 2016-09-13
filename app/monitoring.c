#include "monitoring.h"
#include "OSType.h"
#include "math.h"
#include "OS003_CPU.h"

extern TMailBox T7606Mail;
extern  ST_Value g_stVlue;
extern AD7606_INFO stAd7606;

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

void Sample_ch4(void)
{
	u16 i =0;
	double z = 0ul;
	static double ulValueX= 0ul;
	static double ulValueY= 0ul;
	
   INTSYS syFlagIE;
	
   //DISABLE_INTERRUPT	
		if(g_stVlue.ad7606Count >= SAMPLE_RATE)
		{
			 
			for(i= 0; i< SAMPLE_RATE ;i ++)
			{
					ulValueX +=(double) (stAd7606.ch4[i] * cos(2*Pi*i/SAMPLE_RATE ))/(SAMPLE_RATE/2) ;
			    ulValueY +=(double) (stAd7606.ch4[i] * sin(2*Pi*i/SAMPLE_RATE))/(SAMPLE_RATE/2) ;
			}			
			z=sqrt(ulValueX*ulValueX+ulValueY*ulValueY);			    
			g_stVlue.fADValue4 = z*10/(32768*1.4142135623);
			ulValueX = 0;
			ulValueY = 0;
			g_stVlue.ad7606Count = 0;		
		}
		
   //ENABLE_INTERRUPT
	
}

void Sample_ch7(void)
{
	u8 i =0;
	double z = 0ul;
	double ulValueX= 0ul;
	double ulValueY= 0ul;
	if((T7606Mail.Status[7] & MAIL_FULL) != 0)
	{
		for(i= 0; i< SAMPLE_RATE ;i ++)
		{
			 //ulValueX +=(double) (stAd7606.ch7[i] * cos(2*Pi*i/SAMPLE_RATE ))/(SAMPLE_RATE/2) ;
			 //ulValueY +=(double) (stAd7606.ch7[i] * sin(2*Pi*i/SAMPLE_RATE))/(SAMPLE_RATE/2) ;
		}
		z=sqrt(ulValueX*ulValueX+ulValueY*ulValueY);			    
		g_stVlue.fADValue7 = z*10/(32768*1.4142135623);
		T7606Mail.Status[7] &= ~T7606Mail.Status[7];
	}
	
}
