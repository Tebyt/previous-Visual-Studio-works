#ifndef ZEPHYR_TIME_H
#define ZEPHYR_TIME_H

#include <Zephyr.h>

//time & date
union ZSYSTIME{
	WORD	wTime;
	struct	{	BYTE	bHour,bMinute;	}	bTime;
};

union ZSYSDATE{
	__int64	Date;
	struct	{	WORD	wYear,wMonth,wDay,wDayOfWeek;	}	wDate;
};

WORD ZEPHYR_API GetSysTime();

void ZEPHYR_API GetSysDate(ZSYSDATE &dat);

#endif