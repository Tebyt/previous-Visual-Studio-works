/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Assert.h

							Describe:	调试模块 － 断言

							Author:		赵洪松(xueren)

							CreateTime: 2004.03.09
							UpdateTime: 2004.04.16
*/

#ifndef _ZEPHYR_3_BASE_ASSERT_H
#define _ZEPHYR_3_BASE_ASSERT_H

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

#ifndef ZASSERT
#include <crtdbg.h>
#define ZASSERT(expr)	_ASSERT_BASE((expr), #expr)
#endif	// ZASSERT

#ifndef ZASSERT_RET
#include <crtdbg.h>
#define ZASSERT_RET(expr)	_ASSERT_BASE((expr), #expr); if(!(expr)) return 
#endif	// ZASSERT_RET

#ifndef ZASSERT_RET_V
#include <crtdbg.h>
#define ZASSERT_RET_V(expr,value)	_ASSERT_BASE((expr), #expr); if(!(expr)) return value 
#endif	// ZASSERT_RET_V

#ifndef ZASSERT_R
#include <crtdbg.h>
#define ZASSERT_R(expr)	_ASSERT_BASE((expr), #expr)
#endif	// ZASSERT_R

#endif	// NDEBUG

//#endif	// ZASSERT_TO_LOG

#endif//_ZEPHYR_3_BASE_ASSERT_H