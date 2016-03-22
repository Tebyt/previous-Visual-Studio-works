/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	MulData.h

							Describe:	排它存取数据

							Author:		赵洪松(xueren)

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

		// 设置，返回值为改变以前的值
		bool Set(bool vol) {
			return static_cast<bool>(InterlockedExchange(&m_lVol, static_cast<long>(vol)));
		}

		// 如果现在等于cmp，则改变为dst
		bool SetIf(bool cmp, bool dst) {
			return static_cast<bool>(InterlockedCompareExchange(&m_lVol, static_cast<long>(dst), static_cast<long>(cmp)));
		}

		// 改变bool属性，返回改变以前的值
		bool Turn() {
			return static_cast<bool>(InterlockedExchange(&m_lVol, !static_cast<bool>(m_lVol)));
		}

		// 返回值
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
		// 赋值
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

		// 如果值等于 comp，改变为vol
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