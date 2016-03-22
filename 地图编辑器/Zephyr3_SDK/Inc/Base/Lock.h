/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Lock.h

							Describe:	��

							Author:		�Ժ���(xueren)

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
	// �̻߳�����

	class ZEPHYR_3_API LockImp{
	public:
		// ���캯��
		LockImp() { InitializeCriticalSection(&m_CriticalSection); }
		// ��������
		~LockImp() { DeleteCriticalSection(&m_CriticalSection); }

		// ����
		void Lock() { EnterCriticalSection(&m_CriticalSection); }
		// ����
		void Unlock() { LeaveCriticalSection(&m_CriticalSection); }
	private:
		CRITICAL_SECTION	m_CriticalSection;
	};

	typedef LockImp*	LPLockImp;

	///////////////////////////////////////////////////////////////////////////////
	// AutoLock
	// �Զ������� - ģ����

	template<class T>
	class AutoLockMul{
	public:
		typedef T*	TYPE_PTR;
	public:
		// ���캯���Զ�����
		AutoLockMul(T* pLock) {

			ZASSERT(pLock != NULL);

			m_pLock = pLock;

			pLock->Lock();

			m_iLockNums = 1;
		}

		// ���������Զ�����
		~AutoLockMul() {

			ZASSERT(m_pLock != NULL);

			while(m_iLockNums > 0)
			{
				m_pLock->Unlock();

				m_iLockNums--;
			}
		}

		// ����
		void Lock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Lock();

			m_iLockNums++;
		}

		// ����
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
	// �Զ������� - ģ����

	template<class T>
	class AutoLock{
	public:
		typedef T*	TYPE_PTR;
	public:
		// ���캯���Զ�����
		AutoLock(T* pLock) {

			ZASSERT(pLock != NULL);

			m_pLock = pLock;

			pLock->Lock();
		}

		// ���������Զ�����
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
	// �Զ�������

	class AutoLock{
	public:
		// ���캯���Զ�����
		AutoLock(LockImp& lock) {

			m_pLock = &lock;

			m_pLock->Lock();
		}

		// ���������Զ�����
		~AutoLock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Unlock();
		}

	private:
		LPLockImp	m_pLock;
	};

	///////////////////////////////////////////////////////////////////////////////
	// AutoLockMul
	// �Զ�������

	class AutoLockMul{
	public:
		// ���캯���Զ�����
		AutoLockMul(LockImp& lock){

			m_pLock = &lock;

			m_pLock->Lock();

			m_iLockNums = 1;
		}

		// ���������Զ�����
		~AutoLockMul() {

			ZASSERT(m_pLock != NULL);

			while(m_iLockNums > 0)
			{
				m_pLock->Unlock();

				m_iLockNums--;
			}
		}

		// ����
		void Lock() {

			ZASSERT(m_pLock != NULL);

			m_pLock->Lock();

			m_iLockNums++;
		}

		// ����
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