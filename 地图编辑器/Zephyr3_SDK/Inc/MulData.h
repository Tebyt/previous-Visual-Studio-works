/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	MulData.h

							Describe:	������ȡ����

							Author:		�Ժ���(xueren)

							CreateTime: 2003.12.19
							UpdateTime:
*/

#ifndef _ZEPHYR_3_MULDATA_H
#define _ZEPHYR_3_MULDATA_H

#include <Zephyr.h>

#include <windows.h>

namespace Zephyr3{

	//////////////////////////////////////////////////////////////////////
	//	MulBool

	class MulBool{
	public:
		MulBool(bool vol = false) {
			m_lVol = vol;
		}

		// ���ã�����ֵΪ�ı���ǰ��ֵ
		bool Set(bool vol) {
			return static_cast<bool>(InterlockedExchange(&m_lVol, static_cast<long>(vol)));
		}

		// ������ڵ���cmp����ı�Ϊdst
		bool SetIf(bool cmp, bool dst) {
			return static_cast<bool>(InterlockedCompareExchange(&m_lVol, static_cast<long>(dst), static_cast<long>(cmp)));
		}

		// �ı�bool���ԣ����ظı���ǰ��ֵ
		bool Turn() {
			return static_cast<bool>(InterlockedExchange(&m_lVol, !static_cast<bool>(m_lVol)));
		}

		// ����ֵ
		bool Get() {
			return static_cast<bool>(m_lVol);
		}
/*
		void Wait(bool comp, bool vol) {
			while(InterlockedCompareExchange(&m_lVol, comp, vol) != comp)
				Sleep(0);
		}

		void Wait(bool comp) {
			while(InterlockedCompareExchange(&m_lVol, comp, comp) != comp)
				Sleep(0);
		}
*/
	private:
		// ��ֵ
		MulBool& operator = (const bool vol) {
			Set(vol);
		}
	private:
		long	m_lVol;
	};

	//////////////////////////////////////////////////////////////////////
	//	MulLong

	class MulLong{
	private:
		long	m_lVol;
	public:
		MulLong() { m_lVol = 0; }
		~MulLong() { m_lVol = 0; }

		long Inc() { return InterlockedIncrement(&m_lVol); }
		long Dec() { return InterlockedDecrement(&m_lVol); }

		void Wait(long comp,long vol) {
			while(InterlockedCompareExchange(&m_lVol, vol, comp) != comp)
				Sleep(0);
		}

		void Wait(long comp) {
			while(InterlockedCompareExchange(&m_lVol, comp, comp) != comp)
				Sleep(0);
		}

		long GetVol() { return m_lVol; }

		long SetVol(long vol) { return InterlockedExchange(&m_lVol, vol); }

		// ���ֵ���� comp���ı�Ϊvol
		long SetIf(long comp, long vol) {
			return InterlockedCompareExchange(&m_lVol, vol, comp);
		}
	};
/*
	//////////////////////////////////////////////////////////////////////
	//	MulDWord

	class MulDWord{
	private:
		DWORD	m_dwVol;
	public:
		MulDWord() { m_dwVol = 0; }
		~MulDWord() { m_dwVol = 0; }

		DWORD Inc() { return InterlockedIncrement(&m_dwVol); }
		DWORD Dec() { return InterlockedDecrement(&m_dwVol); }

		void Wait(DWORD comp,DWORD vol) {
			while(InterlockedCompareExchange(&m_dwVol,comp,vol) != comp)
				Sleep(0);
		}

		void Wait(DWORD comp) {
			while(InterlockedCompareExchange(&m_dwVol,comp,comp) != comp)
				Sleep(0);
		}

		DWORD GetVol() { return m_lVol; }

		DWORD SetVol(DWORD vol) { return InterlockedExchange(&m_lVol,vol); }
	};
*/
};

#endif	// _ZEPHYR_3_MULDATA_H