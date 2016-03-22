/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZLock2.h

							Describe:	锁

							Author:		赵洪松(xueren)

							CreateTime: 2003.12.22
							UpdateTime:
*/

#ifndef _ZEPHYR_3_LOCK_H
#define _ZEPHYR_3_LOCK_H

#include <Zephyr.h>

#include <ZLock.h>

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////////////
	// AutoLock
	// 自动互斥锁

	class AutoLock{
	public:
		// 构造函数自动锁定
		AutoLock(ZCriticalSection* pLock) {

			ZASSERT(pLock != NULL);

			m_pLock = pLock;

			pLock->Lock();

			m_LockNums = 1;
		}

		// 析构函数自动解锁
		~AutoLock() {

			ZASSERT(m_pLock != NULL);

			while(m_LockNums > 0)
			{
				m_pLock->Unlock();

				m_LockNums--;
			}
		}

		// 锁定
		void Lock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Lock();

			m_LockNums++;
		}

		// 解锁
		void Unlock() {

			ZASSERT(m_pLock != NULL);

			if(m_LockNums > 0)
			{
				m_pLock->Unlock();

				m_LockNums--;
			}
		}
	private:
		ZCriticalSection*	m_pLock;
		int					m_LockNums;
	};

	///////////////////////////////////////////////////////////////////////////////
	// AutoLockEx
	// 自动互斥锁 - 模板类

	template<class T>
	class AutoLockEx{
	public:
		typedef T*	TYPE_PTR;
	public:
		// 构造函数自动锁定
		AutoLockEx(T* pLock) {

			ZASSERT(pLock != NULL);

			m_pLock = pLock;

			pLock->Lock();

			m_LockNums = 1;
		}

		// 析构函数自动解锁
		~AutoLockEx() {

			ZASSERT(m_pLock != NULL);

			while(m_LockNums > 0)
			{
				m_pLock->Unlock();

				m_LockNums--;
			}
		}

		// 锁定
		void Lock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Lock();

			m_LockNums++;
		}

		// 解锁
		void Unlock() {

			ZASSERT(m_pLock != NULL);

			if(m_LockNums > 0)
			{
				m_pLock->Unlock();

				m_LockNums--;
			}
		}
	private:
		TYPE_PTR	m_pLock;
		int			m_LockNums;
	};
};

#endif	// _ZEPHYR_3_LOCK_H