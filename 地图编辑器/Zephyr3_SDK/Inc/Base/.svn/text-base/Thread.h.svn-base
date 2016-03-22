/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Thread.h

							Describe:	线程

							Author:		赵洪松(xueren)

							CreateTime: 2003.04.22
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_THREAD_H
#define _ZEPHYR_3_BASE_THREAD_H

#include <Base\Lock.h>
#include <Base\List.h>
#include <Base\Assert.h>

namespace Zephyr3{

	class ThreadSystem;
	typedef ThreadSystem* LPThreadSystem;

	class Thread;
	typedef Thread*	LPThread;

	struct ThreadData{
		DWORD			dwThreadID;		// 线程ID
		HANDLE			hThreadHandle;	// 线程句柄
		HANDLE			hEventExit;		// 线程退出事件
		LPVOID			pDat;			// 附属线程数据－用户可设置&获取
	};

	typedef ThreadData*	LPThreadData;

	/////////////////////////////////////////////////////////////////////////////////////
	// Thread

	class ZEPHYR_3_API Thread{
		friend class ThreadSystem;
		friend DWORD WINAPI _threadfunc(LPVOID param);
	public:
		typedef unsigned long (__stdcall *THREAD_FUNC)(void *);
	public:
		// 构造函数
		Thread();
		// 析构函数
		virtual ~Thread();

		//create thread
		HRESULT CreateThread(DWORD swStackSize,unsigned long (__stdcall *start_addr)(void *),LPVOID param,DWORD dwCreationFlags);

		// 获得线程数据
		const LPThreadData GetData() const { return m_pDat; }

		// get handle
		HANDLE GetHandle() const { return m_pDat != NULL ? m_pDat->hThreadHandle : NULL; }

		// 是否在运行中
		bool IsRunning() const { return m_pDat != NULL; }

		// 唤醒线程
		void ResumeThread() {
			WakeUp();
		}
		// 挂起线程，只到线程结束、进程结束，或者被WakeUp
		void SuspendThread() {
			Sleep(INFINITE);
		}

		// 发送关闭线程消息，即时返回
		void ExitThread();
		// 关闭线程，阻塞操作
		void WaitForExitThread();

		// sleep，可以唤醒；Sleep(INFINITE)相当于挂起线程
		// 如果返回为false，表示线程需要结束
		bool Sleep(DWORD time);
		// Wake Up Thread
		void WakeUp();
	protected:
		// 线程主函数
		virtual HRESULT Run(LPVOID param);

		// 是否已经结束，在线程循环中检查
		bool IsEnd();

		// 线程结束后释放资源
		// Run()函数会自动调用，重载Run()以后需要自己在线程结束时调用
		void CleanUp();
	protected:
		THREAD_FUNC			m_func;
	private:
		LPThreadData		m_pDat;

		LPVOID				m_param;

		HANDLE				m_hExitEvent;
		HANDLE				m_hWakeUpEvent;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	// ThreadSystem

	class ZEPHYR_3_API ThreadSystem{
		friend class Thread;

		typedef Link<ThreadData, 32, 4>	DataList;
	public:
		// 构造函数
		ThreadSystem() {
			m_exitEvent = m_releaseEvent = NULL;
		}

		// 析构函数
		~ThreadSystem() {

			ZASSERT_R(m_list.GetUsed() == 0);
		}

		// 初始化
		HRESULT Init();
		// 结束所有线程
		void Release();

		//获得当前线程数据
		void GetCurThreadData(ThreadData& dat);
	private:
		//创建线程
		LPThreadData CreateThread(DWORD swStackSize,unsigned long (__stdcall *start_addr)(void *),LPVOID param,DWORD dwCreationFlags);

		//结束线程
		void KillThread(LPThreadData pThreadData);

		// 获得主线程数据
		void GetMainThreadData() { GetCurThreadData(m_mainThreadData); }
	private:
		DataList		m_list;
		LockImp			m_lock;

		HANDLE			m_exitEvent;
		HANDLE			m_releaseEvent;

		ThreadData		m_mainThreadData;
	};

	typedef ThreadSystem& ThreadSystemReference;
};

#endif // _ZEPHYR_3_BASE_THREAD_H