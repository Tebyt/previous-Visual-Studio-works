/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZAssert.h

							Describe:	调试模块 － 断言

							Author:		赵洪松(xueren)

							CreateTime: 2004.03.09
							UpdateTime:
*/

#ifndef _ZEPHYR_ASSERT_H
#define _ZEPHYR_ASSERT_H

#include <Zephyr.h>

//////////////////////////////////////////////////////////////////////////////////////
// 断言

// ZASSERT			-	普通的断言，Debug模式下会弹出对话框，Release模式下，为空操作

// ZASSERT_RET		-	强制return的断言，Debug模式下和普通断言一样，Release模式下，
//					如果断言失败，则直接返回，适用于无返回值的函数

// ZASSERT_RET_V	-	强制return的断言，Debug模式下和普通断言一样，Release模式下，
//					如果断言失败，则直接返回，适用于有返回值的函数，第二个参数为返回值

// ZASSERT_R		-	强制断言，即使在Release模式下，也会弹出对话框，不要使用在服务
//					器等无人监守的程序内部

#include <assert.h>
/*
#ifdef ZASSERT_TO_LOG

#ifndef ZASSERT
#define ZASSERT(expr)	Debug("%s file : %s line : %d",#expr, __FILE__, __LINE__)
#endif // ZASSERT

#ifndef ZASSERT_RET
#include <crtdbg.h>
#define ZASSERT_RET(expr)	Debug("%s file : %s line : %d",#expr, __FILE__, __LINE__); \
							if(!(expr)) return 
#endif	// ZASSERT_RET

#ifndef ZASSERT_RET_V
#include <crtdbg.h>
#define ZASSERT_RET_V(expr,value)	Debug("%s file : %s line : %d",#expr, __FILE__, __LINE__); \
									if(!(expr)) return value
#endif	// ZASSERT_RET_V

#ifndef ZASSERT_R
#include <crtdbg.h>
#define ZASSERT_R(expr)	Debug("%s file : %s line : %d",#expr, __FILE__, __LINE__)
#endif	// ZASSERT_R

#else
*/
#ifndef __ZEPHYR_VER_31__
#ifdef __ZEPHYR_NO_ASSERT

#ifndef ZASSERT
#include <crtdbg.h>
#define ZASSERT(expr)	((void)0)
#endif	// ZASSERT

#ifndef ZASSERT_RET
#include <crtdbg.h>
#define ZASSERT_RET(expr)	if(!(expr)) return 
#endif	// ZASSERT_RET

#ifndef ZASSERT_RET_V
#include <crtdbg.h>
#define ZASSERT_RET_V(expr,value)	if(!(expr)) return value
#endif	// ZASSERT_RET_V

#ifndef ZASSERT_R
#define ZASSERT_R	((void)0)
#endif // ZASSERT_R

#else // __ZEPHYR_NO_ASSERT
#ifdef NDEBUG

#ifndef ZASSERT
#include <crtdbg.h>
#define ZASSERT(expr)	((void)0)
#endif	// ZASSERT

#ifndef ZASSERT_RET
#include <crtdbg.h>
#define ZASSERT_RET(expr)	if(!(expr)) return 
#endif	// ZASSERT_RET

#ifndef ZASSERT_RET_V
#include <crtdbg.h>
#define ZASSERT_RET_V(expr,value)	if(!(expr)) return value
#endif	// ZASSERT_RET_V

#ifndef ZASSERT_R

#ifdef  __cplusplus
extern "C" {
#endif

_CRTIMP void __cdecl _assert(const char *, const char *, unsigned);

#ifdef  __cplusplus
}
#endif

#define ZASSERT_R(expr)	(void)( (expr) || (_assert(#expr, __FILE__, __LINE__), 0) )

#endif	// ZASSERT_R

#else	// NDEBUG

#ifdef _ZEPHYR3_USE_ZEPHYRDEBUG_
#define _ZASSERT_BASE(expr, msg)	ZDBGASSERT_MSG_OCS(expr, msg)
#else // _ZEPHYR3_USE_ZEPHYRDEBUG_
#define _ZASSERT_BASE(expr, msg)	_ASSERT_BASE(expr, _CRT_WIDE(msg))
#endif // _ZEPHYR3_USE_ZEPHYRDEBUG_

#ifndef ZASSERT
#include <crtdbg.h>
#define ZASSERT(expr)	_ZASSERT_BASE((expr), #expr)
#endif	// ZASSERT

#ifndef ZASSERT_RET
#include <crtdbg.h>
#define ZASSERT_RET(expr)	_ZASSERT_BASE((expr), #expr); if(!(expr)) return 
#endif	// ZASSERT_RET

#ifndef ZASSERT_RET_V
#include <crtdbg.h>
#define ZASSERT_RET_V(expr,value)	_ZASSERT_BASE((expr), #expr); if(!(expr)) return value
#endif	// ZASSERT_RET_V

#ifndef ZASSERT_R
#include <crtdbg.h>
#define ZASSERT_R(expr)	_ZASSERT_BASE((expr), #expr)
#endif	// ZASSERT_R

#endif	// NDEBUG
#endif // __ZEPHYR_NO_ASSERT
#endif // __ZEPHYR_VER_31__
//#endif	// ZASSERT_TO_LOG

#endif//_ZEPHYR_ASSERT_H