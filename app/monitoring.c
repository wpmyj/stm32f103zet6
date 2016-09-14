#include "monitoring.h"
#include "OSType.h"
#include "math.h"
#include "OS003_CPU.h"

extern TMailBox T7606Mail;
extern  ST_Value g_stVlue;
extern AD7606_INFO stAd7606;

#define MAIL_FULL 1


void  Sample_Chanal(u8 num )
{
	u8 i =0, j= 0;
	double z = 0ul;
	double ulValueX= 0ul;
	double ulValueY= 0ul;
	short  *tub = 0;

	switch(num)
	{
	    case 1:
		   tub =   stAd7606.ch0;
		   break;
		case 2:
		   tub =   stAd7606.ch1;
		   break;

		case 3:
		   tub =   stAd7606.ch2;
		   break;

		case 4:
		   tub =   stAd7606.ch3;
		   break;

		case 5:
		   tub =   stAd7606.ch4;
		   break;

		case 6:
		   tub =   stAd7606.ch5;
		   break;


		case 7:
		   tub =   stAd7606.ch6;
		   break;

		case 8:
		   tub =   stAd7606.ch7;
		   break;

		default: 
		  break;
	}

	if(tub == 0)///0914
	{
		return;
	}

	if(g_stVlue.ad7606Count >= SAMPLE_RATE)
	{
			 
		for(i= 0; i< SAMPLE_RATE ;i ++)
		{
			ulValueX +=(double) (tub[i]* cos(2*Pi*i/SAMPLE_RATE ))/(SAMPLE_RATE/2) ;
			ulValueY +=(double) (tub[i] * sin(2*Pi*i/SAMPLE_RATE))/(SAMPLE_RATE/2) ;
		}	
				
		z=sqrt(ulValueX*ulValueX+ulValueY*ulValueY);	
				    
		g_stVlue.fADValue4 = z*10/(32768*1.4142135623);

		ulValueX = 0;
		ulValueY = 0;

		g_stVlue.ad7606Count = 0;		
	}
}

void Sample_ch6(void)
{
	u8 i =0;
	double z = 0ul;
	double ulValueX= 0ul;
	double ulValueY= 0ul;
	if(g_stVlue.ad7606Count >= SAMPLE_RATE)
	{
			 
		for(i= 0; i< SAMPLE_RATE ;i ++)
		{
			ulValueX +=(double) (stAd7606.ch6[i] * cos(2*Pi*i/SAMPLE_RATE ))/(SAMPLE_RATE/2) ;
			ulValueY +=(double) (stAd7606.ch6[i] * sin(2*Pi*i/SAMPLE_RATE))/(SAMPLE_RATE/2) ;
		}			
		z=sqrt(ulValueX*ulValueX+ulValueY*ulValueY);			    
		g_stVlue.fADValue4 = z*10/(32768*1.4142135623);
		ulValueX = 0;
		ulValueY = 0;
		g_stVlue.ad7606Count = 0;		
	}
	
}

void Sample_ch4(void)
{
	u16 i =0;
	double z = 0ul;
    double ulValueX= 0ul;
    double ulValueY= 0ul;
	
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
    
	if(g_stVlue.ad7606Count >= SAMPLE_RATE)
	{
			 
		for(i= 0; i< SAMPLE_RATE ;i ++)
		{
			ulValueX +=(double) (stAd7606.ch7[i] * cos(2*Pi*i/SAMPLE_RATE ))/(SAMPLE_RATE/2) ;
			ulValueY +=(double) (stAd7606.ch7[i] * sin(2*Pi*i/SAMPLE_RATE))/(SAMPLE_RATE/2) ;
		}		
		z=sqrt(ulValueX*ulValueX+ulValueY*ulValueY);			    
		g_stVlue.fADValue4 = z*10/(32768*1.4142135623);
		ulValueX = 0;
		ulValueY = 0;
		g_stVlue.ad7606Count = 0;		
	}	
}
