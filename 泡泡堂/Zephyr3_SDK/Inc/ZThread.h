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

	//�ͷ�������Դ(Cleanup())
	//�ȴ������̹߳ر�
	void Release();

	//��ʼ��
	HRESULT Init();

	//�����߳�
	ZThreadData *CreateThread(DWORD swStackSize,unsigned long (__stdcall *start_addr)(void *),void *srglist,DWORD dwCreationFlags);

	//����߳�
	void KillThread(ZThreadData *thread);

	//��õ�ǰ�߳�����
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
	//�߳������к���
	virtual HRESULT Run(void *lpparam);

	//create thread
	virtual HRESULT CreateThread(DWORD swStackSize,unsigned long (__stdcall *start_addr)(void *),void *srglist,DWORD dwCreationFlags);

	//����ThreadSystem
	//���ڳ�ʼ�����ֵ����ã����뱻����
	inline void SetThreadSystem(ZThreadSystem *threadsystem);

	inline ZThreadSystem *GetThreadSystem() const { return m_ThreadSystem; }

	//ÿ���̶߳��������������������������true�˳��߳�
	bool ICanExit();

	bool IAmRunning() { return m_ThreadData != NULL; }

	//�����߳�
	inline void ResumeThread();
	//�����̣߳�ֻ���߳̽��������̽��������߱�WakeUp
	inline void SuspendThread();

	//get handle
	inline HANDLE GetHandle();

	//���͹ر��߳���Ϣ����ʱ����
	inline void ExitThread();

	//�ر��̣߳���������
	void WaitForExitThread();

	//sleep�����Ի��ѣ�Sleep(INFINITE)�൱�ڹ����߳�
	bool Sleep(DWORD time);
	//Wake Up Thread
	inline void WakeUp();

	HANDLE GetExitEvent() { return m_hExitEvent; }
	inline HANDLE GetThreadSystemExitEvent();

	// ��������
	void SetData(LPVOID pData) {

		m_pData = pData;
	}

	// �������
	LPVOID GetData() {

		return m_pData;
	}
protected:
	//�߳��뿪��Run()�����Զ�����
	//����Run()�Ժ���Ҫ�Լ����߳̽���ʱ����
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