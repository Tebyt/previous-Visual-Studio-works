/*
							Zephyr Engine v3.0

							by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	SE_Exception.h

							Describe:	Ω·ππ“Ï≥£

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2004.03.15
							UpdateTime:
*/

#ifndef _ZEPHYR_SE_EXCEPTION_H
#define _ZEPHYR_SE_EXCEPTION_H

#include <Zephyr.h>

#include <eh.h>

class ZEPHYR_API SE_Exception
{
public:
	SE_Exception(unsigned int n, EXCEPTION_POINTERS* ptr) : m_nSE(n), m_dat(*ptr) {}
	~SE_Exception() {}

#ifdef _ZEPHYR3_USE_ZEPHYRDEBUG_
	void OutputCallStack() {
		_ZDBGOutputCallStack(m_dat.ContextRecord);
	}
#endif // _ZEPHYR3_USE_ZEPHYRDEBUG_
public:
	unsigned int m_nSE;
	EXCEPTION_POINTERS m_dat;
};

inline void trans_func(unsigned int nSE, EXCEPTION_POINTERS* pDat)
{
	throw SE_Exception(nSE,pDat);
}

inline void SEHInit() {
	_set_se_translator(trans_func);
}

#endif // _ZEPHYR_SE_EXCEPTION_H