#ifndef SYS_TYPE_H
#define SYS_TYPE_H

#include "monitoring.h"

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
	short  	ch6[SAMPLE_RATE];
	short  	ch5[SAMPLE_RATE];
}AD7606_INFO;

 typedef struct
 {
 	  u8  tem1;
	  u8  ubUsartCount;
	  u8  tabUsartValue[8];
	  u16 uitem1; 
	  u16 uitem2; 
	  signed short tubAD_Value[16];
	  float fADValue;
	  float fADValue3;
	  float fADValue4;
	  float fADValue6;
	  float fADValue4Compensation;
	  TMailBox * tMailBox;

 }ST_Value;
 

#endif


										   