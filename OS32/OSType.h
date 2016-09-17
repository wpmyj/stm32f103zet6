#ifndef SYS_TYPE_H
#define SYS_TYPE_H

#include "monitoring.h"

 #define SAMPLE_RATE (80*5)

#define u32 unsigned int
#define u16 unsigned   short  int
#define u8    unsigned char
#define UINT8 unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned int
#define INT8 signed char
#define INT16 signed short
#define INT32 signed int
#define INTSYS unsigned int
#define CH char

#define F32 float

#define AD7545_1 (0x010 << 1)
#define AD7545_2 (0x020 << 1)
#define AD7545_3 (0x030 << 1)
#define AD7545_4 (0x040 << 1)
#define AD7545_5 (0x050 << 1)
#define AD7545_6 (0x060 << 1)
#define AD7545_7 (0x070 << 1)



typedef struct
{
	u8	ubFlag7606;
	u8  ubSPIFlag;
}ST_Flag;

typedef struct
{
	 u16 Value[8];
	 u8 Status[8];

}TMailBox;

typedef struct
{
	short  	ch0[SAMPLE_RATE];
	short  	ch1[SAMPLE_RATE];
	short  	ch2[SAMPLE_RATE];
	short  	ch3[SAMPLE_RATE];
	short  	ch4[SAMPLE_RATE];
	short  	ch6[SAMPLE_RATE];
	short  	ch5[SAMPLE_RATE];
	short  	ch7[SAMPLE_RATE];
}AD7606_INFO;

typedef struct 
{
    u16 Chanal[SAMPLE_RATE];
}CH_INFO;

typedef struct 
{
	   CH_INFO ch0;
	   CH_INFO ch1;
	   CH_INFO ch2;
	   CH_INFO ch3;
	   CH_INFO ch4;
	   CH_INFO ch5;
	   CH_INFO ch6;
	   CH_INFO ch7;
	   
}AD7606_DATA_INFO;


#define  UART4BuferSize 32
 typedef struct
 {
 	  u8  tem1;
	  u8  ubUsartCount;
	  u8  ubUsart4Event;
	 
	  u8  tabUsartValue[UART4BuferSize];	 
	  u16  ad7606Count;    
	  u16 uitem1; 
	  u16 uitem2; 
	  u8  *pUsartBuffer;
	  signed short tubAD_Value[8];
	  float fADValue;
	  float fADValue1;
	  float fADValue2;
	  float fADValue3;
	  float fADValue4;
	  float fADValue5;
	  float fADValue6;
	  float fADValue7;
	  float fADValue4Compensation  ;

	  
	 
	  //TMailBox * tMailBox;

 }ST_Value;
 

#endif


										   