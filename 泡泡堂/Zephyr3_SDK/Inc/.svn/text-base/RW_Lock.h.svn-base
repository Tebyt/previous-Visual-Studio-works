/*
							Zephyr Engine v3.0

							by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\RW_Lock.h

							Describe:	Read Write Lock

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2005.02.21
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_RW_LOCK_H
#define _ZEPHYR_3_BASE_RW_LOCK_H

#include <Zephyr.h>

#include <MulData.h>

namespace Zephyr3{

	class RWLock{
	public:
		enum{
			_READ	=	-1,
			_FREE	=	0,
			_WRITE	=	1
		};
	public:
		RWLock() {
			m_dat.SetVol(_FREE);
		}

		void LockRead() {
			while(m_dat.SetIf(_FREE, _READ) == _WRITE)
				Sleep(0);
		}

		void UnlockRead() {
			m_dat.SetVol(_FREE);
		}

		void LockWrite() {
			while(m_dat.SetIf(_FREE, _WRITE) == _READ)
				Sleep(0);
		}

		void UnlockWrite() {
			m_dat.SetVol(_FREE);
		}
	private:
		MulLong		m_dat;
	};

	class AutoReadLock{
	public:
		AutoReadLock(RWLock* pLock) : m_pLock(pLock) {
			ZASSERT(m_pLock != NULL);

			m_pLock->LockRead();
		}

		~AutoReadLock() {
			m_pLock->UnlockRead();
		}

		void Lock() {
			m_pLock->LockRead();
		}

		void Unlock() {
			m_pLock->UnlockRead();
		}
	private:
		RWLock*	m_pLock;
	};

	class AutoWriteLock{
	public:
		AutoWriteLock(RWLock* pLock) : m_pLock(pLock) {
			ZASSERT(m_pLock != NULL);

			m_pLock->LockWrite();
		}

		~AutoWriteLock() {
			m_pLock->UnlockWrite();
		}

		void Lock() {
			m_pLock->LockWrite();
		}

		void Unlock() {
			m_pLock->UnlockWrite();
		}
	private:
		RWLock*	m_pLock;
	};
}

#endif // _ZEPHYR_3_BASE_RW_LOCK_H
