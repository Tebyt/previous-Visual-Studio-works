#ifndef ZEPHYR_LOCK_H
#define ZEPHYR_LOCK_H

#include <Zephyr.h>

#include <windows.h>

#include <zdebug.h>

//////////////////////////////////////////////////////////////////////
//	ZCriticalSection

class ZEPHYR_API ZCriticalSection{
private:
	CRITICAL_SECTION m_CritSect;
public:
	ZCriticalSection() { InitializeCriticalSection(&m_CritSect); }
	~ZCriticalSection() { DeleteCriticalSection(&m_CritSect); }

	void Lock() { EnterCriticalSection(&m_CritSect); }
	void Unlock() { LeaveCriticalSection(&m_CritSect); }

	void operator = (const ZCriticalSection& right) {}
};

//////////////////////////////////////////////////////////////////////
//	ZInterlockedVol

class ZEPHYR_API ZInterlockedVol{
private:
	long	m_lVol;
public:
	ZInterlockedVol() { m_lVol = 0; }
	~ZInterlockedVol() { m_lVol = 0; }

	long Inc() { return InterlockedIncrement(&m_lVol); }
	long Dec() { return InterlockedDecrement(&m_lVol); }

	inline void Wait(long comp,long vol);

	inline void Wait(long comp);

	long GetVol() { return InterlockedCompareExchange(&m_lVol, 0, 0); }

	long SetVol(long vol) { return InterlockedExchange(&m_lVol,vol); }
};

inline void ZInterlockedVol::Wait(long comp,long vol)
{ 
	while(InterlockedCompareExchange(&m_lVol, vol, comp) != comp)
		Sleep(0);
}

inline void ZInterlockedVol::Wait(long comp)
{ 
	while(InterlockedCompareExchange(&m_lVol, comp, comp) != comp)
		Sleep(0);
}

//////////////////////////////////////////////////////////////////////
//	ZLock_Leader

class ZEPHYR_API ZLock_Leader{
private:
	ZInterlockedVol		m_Main;
	ZInterlockedVol		m_Other;
public:
	void LeaderLock() { m_Main.Wait(0,-1); }
	void LeaderUnlock() { m_Main.SetVol(0); }

	inline void NormalLock();
	inline void NormalUnlock();
};

inline void ZLock_Leader::NormalLock()
{
	if(m_Main.GetVol() != 1)
		m_Main.Wait(0,1);

	m_Other.Inc();
}

inline void ZLock_Leader::NormalUnlock()
{
	m_Other.Dec();

	if(m_Other.GetVol() == 0)
		m_Main.SetVol(0);
}

#endif