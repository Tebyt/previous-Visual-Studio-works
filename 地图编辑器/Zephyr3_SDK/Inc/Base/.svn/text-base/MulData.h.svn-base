/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\MulData.h

							Describe:	排它存取数据

							Author:		赵洪松(xueren)

							CreateTime: 2003.12.19
							UpdateTime: 2004.04.16
*/

#ifndef _ZEPHYR_3_BASE_MULDATA_H
#define _ZEPHYR_3_BASE_MULDATA_H

#include <windows.h>

namespace Zephyr3{

	//////////////////////////////////////////////////////////////////////
	//	MulBool

	class ZEPHYR_3_API MulBool{
	public:
		// 构造函数
		MulBool(bool vol = false) {
			m_lVol = vol;
		}

		// 设置，返回值为改变以前的值
		bool Set(bool vol) {
			return InterlockedExchange(&m_lVol,vol);
		}

		// 如果现在等于cmp，则改变为dst
		bool SetIf(bool cmp,bool dst) {
			return InterlockedCompareExchange(&m_lVol, dst, cmp);
		}

		// 改变bool属性，返回改变以前的值
		bool Turn() {
			return InterlockedExchange(&m_lVol,!m_lVol);
		}

		// 等待，直到值等于vol
		void Wait(bool vol) {
			while(InterlockedCompareExchange(&m_lVol,vol,vol) != vol)
				Sleep(0);
		}

		// 等待，直到值等于comp，才改变
		void WaitTurn(long comp) {
			while(InterlockedCompareExchange(&m_lVol,comp,!comp) != comp)
				Sleep(0);
		}

		// 返回值
		bool Get() {
			return m_lVol;
		}
	private:
		// 赋值
		MulBool& operator = (const MulBool& vol) {
			return *this;
		}
	private:
		long	m_lVol;
	};

	//////////////////////////////////////////////////////////////////////
	//	MulLong

	class ZEPHYR_3_API MulLong{
	public:
		// 构造函数
		MulLong(long vol = 0) { m_lVol = vol; }

		// ++
		long Inc() { return InterlockedIncrement(&m_lVol); }
		// --
		long Dec() { return InterlockedDecrement(&m_lVol); }

		// 等待，直到值等于comp，才改变为 vol
		void Wait(long comp,long vol) {
			while(InterlockedCompareExchange(&m_lVol, vol, comp) != comp)
				Sleep(0);
		}

		// 等待，直到值等于comp
		void Wait(long comp) {
			while(InterlockedCompareExchange(&m_lVol, comp, comp) != comp)
				Sleep(0);
		}

		// 如果值等于 comp，改变为vol
		void SetIf(long comp,long vol) {
			InterlockedCompareExchange(&m_lVol, vol, comp)
		}

		long GetVol() { return m_lVol; }

		long SetVol(long vol) { return InterlockedExchange(&m_lVol,vol); }
	private:
		// 赋值
		MulLong& operator = (const MulLong& vol) {
			return *this;
		}
	private:
		long	m_lVol;
	};
};

#endif	// _ZEPHYR_3_BASE_MULDATA_H