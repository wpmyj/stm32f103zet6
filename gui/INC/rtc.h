#ifndef __RTC_H__
#define __RTC_H__

//#include "uTypes.h"
#include "DEF.h"
/*
typedef struct tagTIME{
	U16 wYear;
	U8   byMonth;
	U8   byDay;
	U8   byWeekday;
	U8   byHour;
	U8   byMin;
	U8   bySec;
}TIME, *PTIME;
*/
void rtcInit (PTIME pTime);
void rtcShowTime (void);

const char *WeekDate[] ={  "  ", "一", "二", "三", "四", "五", "六", "日"  };

#endif //__RTC_H__
