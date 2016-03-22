/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Lock.h

							Describe:	锁

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.16
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_LOCK_H
#define _ZEPHYR_3_BASE_LOCK_H

#include <windows.h>
#include <Base\Assert.h>

namespace Zephyr3{

	//////////////////////////////////////////////////////////////////////////////////
	// LockImp
	// 线程互斥锁

	class ZEPHYR_3_API LockImp{
	public:
		// 构造函数
		LockImp() { InitializeCriticalSection(&m_CriticalSection); }
		// 析构函数
		~LockImp() { DeleteCriticalSection(&m_CriticalSection); }

		// 锁定
		void Lock() { EnterCriticalSection(&m_CriticalSection); }
		// 解锁
		void Unlock() { LeaveCriticalSection(&m_CriticalSection); }
	private:
		CRITICAL_SECTION	m_CriticalSection;
	};

	typedef LockImp*	LPLockImp;

	///////////////////////////////////////////////////////////////////////////////
	// AutoLock
	// 自动互斥锁 - 模板类

	template<class T>
	class AutoLockMul{
	public:
		typedef T*	TYPE_PTR;
	public:
		// 构造函数自动锁定
		AutoLockMul(T* pLock) {

			ZASSERT(pLock != NULL);

			m_pLock = pLock;

			pLock->Lock();

			m_iLockNums = 1;
		}

		// 析构函数自动解锁
		~AutoLockMul() {

			ZASSERT(m_pLock != NULL);

			while(m_iLockNums > 0)
			{
				m_pLock->Unlock();

				m_iLockNums--;
			}
		}

		// 锁定
		void Lock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Lock();

			m_iLockNums++;
		}

		// 解锁
		void Unlock() {

			ZASSERT(m_pLock != NULL);

			if(m_iLockNums > 0)
			{
				m_pLock->Unlock();

				m_iLockNums--;
			}
		}
	private:
		TYPE_PTR	m_pLock;
		int			m_iLockNums;
	};

	///////////////////////////////////////////////////////////////////////////////
	// AutoLock
	// 自动互斥锁 - 模板类

	template<class T>
	class AutoLock{
	public:
		typedef T*	TYPE_PTR;
	public:
		// 构造函数自动锁定
		AutoLock(T* pLock) {

			ZASSERT(pLock != NULL);

			m_pLock = pLock;

			pLock->Lock();
		}

		// 析构函数自动解锁
		~AutoLock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Unlock();
		}
	private:
		TYPE_PTR	m_pLock;
	};

	//////////////////////////////////////////////////////////////////////////////

	typedef AutoLock<LockImp>		AutoLockEx;
	typedef AutoLockMul<LockImp>	AutoLockMulEx;
/*
	///////////////////////////////////////////////////////////////////////////////
	// AutoLock
	// 自动互斥锁

	class AutoLock{
	public:
		// 构造函数自动锁定
		AutoLock(LockImp& lock) {

			m_pLock = &lock;

			m_pLock->Lock();
		}

		// 析构函数自动解锁
		~AutoLock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Unlock();
		}

	private:
		LPLockImp	m_pLock;
	};

	///////////////////////////////////////////////////////////////////////////////
	// AutoLockMul
	// 自动互斥锁

	class AutoLockMul{
	public:
		// 构造函数自动锁定
		AutoLockMul(LockImp& lock){

			m_pLock = &lock;

			m_pLock->Lock();

			m_iLockNums = 1;
		}

		// 析构函数自动解锁
		~AutoLockMul() {

			ZASSERT(m_pLock != NULL);

			while(m_iLockNums > 0)
			{
				m_pLock->Unlock();

				m_iLockNums--;
			}
		}

		// 锁定
		void Lock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Lock();

			m_iLockNums++;
		}

		// 解锁
		void Unlock() {

			ZASSERT(m_pLock != NULL);

			if(m_iLockNums > 0)
			{
				m_pLock->Unlock();

				m_iLockNums--;
			}
		}
	private:
		LPLockImp	m_pLock;
		int			m_iLockNums;
	};
*/
};

#endif // _ZEPHYR_3_BASE_LOCK_H