/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Zephyr.h

							Describe:	基本定义

							Author:		赵洪松(xueren)

							CreateTime: 2002
							UpdateTime: 2003.09.23
*/

#ifndef _ZEPHYR_H
#define _ZEPHYR_H

#ifdef ZEPHYR_API
#undef ZEPHYR_API
#endif // ZEPHYR_API

#ifdef __ZEPHYR3_STATIC
#define ZEPHYR_API
#else//__ZEPHYR3_STATIC

#ifdef ZEPHYR_EXPORTS
#	define ZEPHYR_API	__declspec(dllexport)
#else // ZEPHYR_EXPORTS
#	define ZEPHYR_API	__declspec(dllimport)
/*
#	ifdef _DEBUG
/*
#		if defined(__ZEPHYR_NO_ASSERT)
#			pragma comment(lib, "ZephyrDNA.lib")
#		elif defined(_ZEPHYR_MUL_DEBUG)
#			pragma comment(lib, "ZephyrDMD.lib")
#		else
#			pragma comment(lib, "ZephyrD.lib")
#		endif //
* /
#		ifdef __ZEPHYR_VER_31__
#			pragma comment(lib, "Zephyr31D.lib")
#		else // __ZEPHYR_VER_31__
#			pragma comment(lib, "ZephyrD.lib")
#		endif // __ZEPHYR_VER_31__
#	else // _DEBUG
#		ifdef __ZEPHYR_VER_31__
#			pragma comment(lib, "Zephyr31.lib")
#		else // __ZEPHYR_VER_31__
#			pragma comment(lib, "Zephyr.lib")
#		endif // __ZEPHYR_VER_31__
#	endif // _DEBUG
*/
#endif // ZEPHYR_EXPORTS
#endif//__ZEPHYR3_STATIC

#include <Windows.h>

inline DWORD MakeDWORD(WORD hiWord,WORD loWord)
{
	return (((static_cast<DWORD>(hiWord)<<16) & 0xffff0000) | ((static_cast<DWORD>(loWord) & 0x0000ffff)));
}

#ifdef __ZEPHYR_VER_31__
#	include <Zephyr5\BaseDef.h>
#endif // __ZEPHYR_VER_31__

//#define	_ZEPHYR3_USE_ZEPHYRDEBUG_

#ifdef _ZEPHYR3_USE_ZEPHYRDEBUG_
#	include <ZephyrDebug/ZephyrDebug.h>

const int _ZEPHYR3_MODULE		= 3;

#endif // _ZEPHYR3_USE_ZEPHYRDEBUG_

#endif//_ZEPHYR_H
