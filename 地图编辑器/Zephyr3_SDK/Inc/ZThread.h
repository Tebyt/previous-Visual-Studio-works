//	ZThread.h
//	Zephyr Thread
//	Write by zhs007			y2k2

#ifndef ZEPHYR_THREAD_H
#define ZEPHYR_THREAD_H

#include <Zephyr.h>

#include <windows.h>

#include <zdebug.h>
#include <zlink.h>
#include <zlock.h>

struct ZEPHYR_API ZThreadData{
	DWORD			dwThreadID;
	HANDLE			hThreadHandle;
	HANDLE			hEventExit;

	ZThreadData(){
		hThreadHandle = hEventExit = 0;
	}

	inline bool operator == (const ZThreadData &s) const;

	inline bool operator != (const ZThreadData &s) const;
};

inline bool ZThreadData::operator == (const ZThreadData &s) const
{
	return this->dwThreadID == s.dwThreadID;
}

inline bool ZThreadData::operator != (const ZThreadData &s) const 
{ 
	return !((*this) == s); 
}

typedef unsigned long (__stdcall *_ZTHREADFUNC)(void *);

DWORD WINAPI _zthreadfunc(void *lpparam);

//////////////////////////////////////////////////////////////////////
//	ZThreadSystem


class ZEPHYR_API ZThreadSystem{
private:
	ZCriticalSection			m_ThreadsLock;
	ZLinkEx<ZThreadData,16,4>	m_Threads;

	HANDLE						m_EventExit;
	HANDLE						m_ICanExit;

	ZThreadData					m_MainThread;
public:
	ZThreadSystem()	{ m_EventExit = m_ICanExit = NULL; }
	~ZThreadSystem() { ZASSERT(m_Threads.GetUsed() == 0); }

	//释放所有资源(Cleanup())
	//等待所有线程关闭
	void Release();

	//初始化
	HRESULT Init();

	//创建线程
	ZThreadData *CreateThread(DWORD swStackSize,unsigned long (__stdcall *start_addr)(void *),void *srglist,DWORD dwCreationFlags);

	//清除线程
	void KillThread(ZThreadData *thread);

	//获得当前线程数据
	void GetCurThreadData(ZThreadData &thread);

	HANDLE GetExitEvent() { return m_EventExit; }
private:
	void GetMainThreadData() { GetCurThreadData(m_MainThread); }
};

//////////////////////////////////////////////////////////////////////
//	ZThread

class ZEPHYR_API ZThread{
	friend DWORD WINAPI _zthreadfunc(void *lpparam);
protected:
	ZThreadData		*m_ThreadData;

	_ZTHREADFUNC	m_Func;

	ZThreadSystem	*m_ThreadSystem;

	LPVOID			m_pData;
private:
	void			*m_Param;
	HANDLE			m_hExitEvent;
	HANDLE			m_hWakeUpEvent;
public:
	inline ZThread();
	virtual ~ZThread() { DEBUGMESSAGE("ZThread Release!"); }

	//run
	//线程主运行函数
	virtual HRESULT Run(void *lpparam);

	//create thread
	virtual HRESULT CreateThread(DWORD swStackSize,unsigned long (__stdcall *start_addr)(void *),void *srglist,DWORD dwCreationFlags);

	//设置ThreadSystem
	//属于初始化部分的设置，必须被调用
	inline void SetThreadSystem(ZThreadSystem *threadsystem);

	inline ZThreadSystem *GetThreadSystem() const { return m_ThreadSystem; }

	//每个线程都必须调用这个函数，且如果返回true退出线程
	bool ICanExit();

	bool IAmRunning() { return m_ThreadData != NULL; }

	//唤醒线程
	inline void ResumeThread();
	//挂起线程，只到线程结束、进程结束，或者被WakeUp
	inline void SuspendThread();

	//get handle
	inline HANDLE GetHandle();

	//发送关闭线程消息，即时结束
	inline void ExitThread();

	//关闭线程，阻塞操作
	void WaitForExitThread();

	//sleep，可以唤醒；Sleep(INFINITE)相当于挂起线程
	bool Sleep(DWORD time);
	//Wake Up Thread
	inline void WakeUp();

	HANDLE GetExitEvent() { return m_hExitEvent; }
	inline HANDLE GetThreadSystemExitEvent();

	// 设置数据
	void SetData(LPVOID pData) {

		m_pData = pData;
	}

	// 获得数据
	LPVOID GetData() {

		return m_pData;
	}
protected:
	//线程离开，Run()函数自动调用
	//重载Run()以后需要自己在线程结束时调用
	void CleanUp();
};

inline ZThread::ZThread()
{
	m_Param = NULL;
	m_Func = NULL;
	m_ThreadData = NULL;
	m_hExitEvent = NULL;
	m_hWakeUpEvent = NULL;
	m_ThreadSystem = NULL;

	m_pData = NULL;
};

inline void ZThread::ExitThread()
{
	if(m_ThreadData)
		SetEvent(m_hExitEvent);
}

inline void ZThread::SetThreadSystem(ZThreadSystem *threadsystem)
{
	ZASSERT(threadsystem);

	m_ThreadSystem = threadsystem;
}

inline void ZThread::ResumeThread()
{
	ZASSERT(m_hWakeUpEvent);

	WakeUp();
}

inline void ZThread::SuspendThread()
{
	Sleep(INFINITE);
}

inline HANDLE ZThread::GetHandle()
{
	ZASSERT(m_ThreadData);

	return m_ThreadData->hThreadHandle;
}

inline void ZThread::WakeUp()
{
	ZASSERT(m_hWakeUpEvent);

	SetEvent(m_hWakeUpEvent);
}

inline HANDLE ZThread::GetThreadSystemExitEvent()
{
	ZASSERT(m_ThreadSystem != NULL);

	return m_ThreadSystem->GetExitEvent();
}

#endif	//#ifndef ZEPHYR_THREAD_H