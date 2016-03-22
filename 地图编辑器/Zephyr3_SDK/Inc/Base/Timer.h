/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Timer.h

							Describe:	��ʱ��

							Author:		�Ժ���(xueren)

							CreateTime: 2004.09.25
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_TIMER_H
#define _ZEPHYR_3_BASE_TIMER_H

#include <Base\Thread.h>

namespace Zephyr3{

	//////////////////////////////////////////////////////////////////////
	//	Timer

	class ZEPHYR_3_API Timer : public Thread{
	public:
		Timer() { m_dwTimer = 0; }

		Timer(DWORD timer) { m_dwTimer = timer; }

		virtual ~Timer() { ; }

		HRESULT SetTimer(DWORD timer,unsigned long (__stdcall *start_addr)(void *),void* param = NULL);
	protected:
		// Timer����
		virtual HRESULT TimerFunc(LPVOID param);
	private:
		// �߳�������
		virtual HRESULT Run(LPVOID param);
	protected:
		DWORD	m_dwTimer;
	};

	typedef Timer* LPTimer;
};

#endif // _ZEPHYR_3_BASE_TIMER_H