/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZTimerEx.h

							Describe:	计时器

							Author:		赵洪松(xueren)

							CreateTime: 2004.03.15
							UpdateTime:
*/

#ifndef _ZEPHYR_3_TIMEREX_H
#define _ZEPHYR_3_TIMEREX_H

#include <Zephyr.h>

#include <ZThread.h>

namespace Zephyr3{

	template<class T>
	class Timer : public ZThread{
	public:
		// 构造函数
		Timer() {

			m_pObj = NULL;
			m_dwTimer = 0;
		}

		// 构造函数
		Timer(T* pObj) {

			ZASSERT(pObj != NULL);

			SetObj(pObj);

			m_dwTimer = 0;
		}

		// 析构函数
		~Timer() {

			if(IAmRunning())
				KillTimer();
		}

		// 设置对象
		void SetObj(T* pObj) {

			ZASSERT(pObj != NULL);

			m_pObj = pObj;
		}

		// 启动计时器
		HRESULT SetTimer(DWORD dwTimer,LPVOID pParam) {

			m_dwTimer = dwTimer;

			return CreateThread(0,NULL,pParam,0);
		}

		// 关闭计时器
		// 即时返回
		void KillTimer() {

			ExitThread();
		}

		// 关闭计时器
		// 等待计时器关闭才返回
		void KillTimerEx() {

			WaitForExitThread();
		}

		// virtual from ZThread
		// 核心线程
		virtual HRESULT Run(void *lpParam) {

			ZASSERT_R(m_pObj != NULL);

			while(true)
			{
				ZASSERT(m_pObj != NULL);

				if(Sleep(m_dwTimer))
					m_pObj->TimerFunc(lpParam);
				else
				{
					DEBUGMESSAGE2("Zephyr3::Timer 0x%x Main Thread Exit!",this);

					ZThread::CleanUp();

					break;
				}

				if(ICanExit())
				{
					DEBUGMESSAGE2("Zephyr3::Timer 0x%x Main Thread Exit!",this);

					ZThread::CleanUp();

					break;
				}
			}

			return S_OK;
		}
	private:
		T*		m_pObj;
		DWORD	m_dwTimer;
	};
};

#endif	// _ZEPHYR_3_TIMEREX_H