#ifndef ZEPHYR_TIMER_H
#define ZEPHYR_TIMER_H

#include <Zephyr.h>

#include <ZThread.h>
#include <ZTime.h>
//#include zbasedef.h"
#include <ZLock.h>

//////////////////////////////////////////////////////////////////////
//	ZTimer

class ZEPHYR_API ZTimer : public ZThread{
protected:
	ULONG	m_Timer;
public:
	ZTimer() { ; }

	virtual ~ZTimer() { ; }

	HRESULT SetTimer(ULONG timer,_ZTHREADFUNC func,void *param=NULL);

//virtual
	HRESULT Run(void *lpparam);
};

typedef ZTimer* LPZTimer;

//////////////////////////////////////////////////////////////////////
//	zwnd timer

struct _zwndTimer{
	HWND				hWnd;
	DWORD				timerID;
	ZTimer				*pTimer;
//	ZCriticalSection	*pLock;
	int					iNums;
};

DWORD WINAPI _zwndtimerfunc(void *lpparam);

_zwndTimer*	SetZTimer(ZThreadSystem *pThreadSystem,HWND hWnd,DWORD timerID,DWORD Timer);

void KillZTimer(_zwndTimer* &timer);

void ZTimerRun(_zwndTimer* &timer);

#endif