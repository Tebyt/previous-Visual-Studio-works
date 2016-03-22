/*
							Zephyr Debug

							基于 C 的跨平台调试基础库

							by 赵洪松(xueren) 2006

							E-mail:sssxueren@gmail.com

							FileName:	ZephyrDebug\ZephyrDebug.h

							Describe:	定义文件

							Author:		赵洪松(zhs007)

							CreateTime: 2006.07.26
							UpdateTime: 
*/

#ifndef __ZEPHYRDEBUG_ZEPHYRDEBUG_H__
#define __ZEPHYRDEBUG_ZEPHYRDEBUG_H__

//////////////////////////////////////////////////////////////////////////////////////
// 全局宏定义
// 如果改变，需要重新编译

/*******************************************************************
*	其它编译器宏定义说明
*
*  _MSC_VER	表示使用MSVC编译器，且标示版本号
*	_DEBUG		表示使用Debug版本
*	NDEBUG		表示使用Release版本，如果同时定义 _DEBUG 和 NDEBUG，以 NDEBUG 优先
*
*******************************************************************/

//!	如果定义了 _ZEPHYRDEBUG_PLATFORM_WIN32_ 则表示为Win32平台
#define _ZEPHYRDEBUG_PLATFORM_WIN32_

//!	如果定义了 _ZEPHYRDEBUG_PLATFORM_WINCE_ 则表示为WinCE平台
//#define _ZEPHYRDEBUG_PLATFORM_WINCE_

//!	如果定义了 _ZEPHYRDEBUG_MACHINE_I386_ 则表示为Intel 32位 指令集
#define _ZEPHYRDEBUG_MACHINE_I386_

//!	如果定义了 _ZEPHYRDEBUG_DEBUG 则表示为 DEBUG
#ifdef _DEBUG
#define _ZEPHYRDEBUG_DEBUG
#endif

#ifdef NDEBUG
#undef _ZEPHYRDEBUG_DEBUG
#endif 

#ifdef _ZEPHYRDEBUG_DLL_
#	ifdef _ZEPHYRDEBUG_DLL_EXPORT_
#		define ZEPHYRDEBUG_API	__declspec(dllexport)
#	else // _ZEPHYRDEBUG_DLL_EXPORT_
#		define ZEPHYRDEBUG_API	__declspec(dllimport)
#	endif // _ZEPHYRDEBUG_DLL_EXPORT_
#else // _ZEPHYRDEBUG_DLL_
#	define ZEPHYRDEBUG_API
#endif // _ZEPHYRDEBUG_DLL_

//////////////////////////////////////////////////////////////////////////////////////
// 内部宏定义
// 如果改变，需要重新编译

//! 定义调用堆栈的深度
#define _ZEPHYRDEBUG_CALLSTACK_MAX		64
//! 定义输出缓冲大小
#define _ZEPHYRDEBUG_MAX_LOGBUFF_SIZE	1024
////! 自定义的 Module 号
//#define _ZEPHYRDEBUG_MODULE				ZSTR("ZephyrDebug")

//////////////////////////////////////////////////////////////////////////////////////
// 全局头文件
#ifdef _ZEPHYRDEBUG_PLATFORM_WIN32_
#include <Windows.h>
#pragma warning(push)
#pragma warning(disable : 4201)	//! 使用了非标准扩展 : 无名称的结构/联合
#include <DBGHelp.h>
#pragma warning(pop)
#endif // _ZEPHYRDEBUG_PLATFORM_WIN32_

//////////////////////////////////////////////////////////////////////////////////////
// 类型定义

typedef int				ZDBGInt32;
typedef void*			ZDBGPVoid;

typedef int				ZDBGInt;
typedef long			ZDBGLong;
typedef size_t			ZDBGSizeType;

#ifdef UNICODE
typedef wchar_t			ZDGBChar;
#else // UNICODE
typedef char			ZDGBChar;
#endif // UNICODE

typedef unsigned char	ZDBGByte;
typedef unsigned short	ZDBGWord;
typedef unsigned int	ZDBGDWord;

typedef const ZDGBChar*	ZDBGCString;

typedef enum __zdbgBool{
	ZDBG_FALSE	= 0,
	ZDBG_TRUE	= 1
} ZDBGBool;

#ifdef UNICODE
#define _ZDBGSTR(str)	L##str
#else // UNICODE
#define _ZDBGSTR(str)	str
#endif // UNICODE

//////////////////////////////////////////////////////////////////////////////////////
// 返回

typedef ZDBGInt32		ZDBGResult;

#define ZDBG_OK			0
#define ZDBG_FAIL		0xffffffff

//////////////////////////////////////////////////////////////////////////////////////
// 断言
// 如果改变，需要重新编译

//! 断言内核
#ifdef _ZEPHYRDEBUG_DEBUG
// debug mode
#ifdef _ZEPHYRDEBUG_PLATFORM_WIN32_

#include <crtdbg.h>

//#ifdef  __cplusplus
//extern "C" {
//#endif
//
//	_CRTIMP void __cdecl _assert(const char *, const char *, unsigned);
//
//#ifdef  __cplusplus
//}
//#endif

//#define __ZDBGASSERT_BASE(expr, msg)	(void)( (expr) || (_assert(msg, __FILE__, __LINE__), 0) )

#ifdef UNICODE
#define __ZDBGASSERT_BASE(expr, msg) \
	(void) ((!!(expr)) || \
	(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg)) || \
	(_CrtDbgBreak(), 0))
#else // UNICODE
#define __ZDBGASSERT_BASE(expr, msg) \
	(void) ((!!(expr)) || \
	(1 != _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, msg)) || \
	(_CrtDbgBreak(), 0))
#endif // UNICODE

#else // _ZEPHYRDEBUG_PLATFORM_WIN32_
#define __ZDBGASSERT_BASE(expr, msg)	assert(expr);
#endif // _ZEPHYRDEBUG_PLATFORM_WIN32_

#else // _ZEPHYRDEBUG_DEBUG
// ndebug mode
#define __ZDBGASSERT_BASE(expr, msg)	((void)0)
#endif // _ZEPHYRDEBUG_DEBUG

#ifdef _ZEPHYRDEBUG_DEBUG

//! 普通断言
#define ZDBGASSERT(expr)	__ZDBGASSERT_BASE(expr, _ZDBGSTR(#expr))
//! 显示消息的断言
#define ZDBGASSERT_MSG(expr, msg)	__ZDBGASSERT_BASE(expr, msg)
//! 带堆栈输出的普通断言 output call stack
#define ZDBGASSERT_OCS(expr)	{ if(!(expr)){ ZDBGOutputCallStack(); __ZDBGASSERT_BASE(0, _ZDBGSTR(#expr)); } }
//! 带堆栈输出，且显示消息的断言 output call stack
#define ZDBGASSERT_MSG_OCS(expr, msg)	{ if(!(expr)){ ZDBGOutputCallStack(); __ZDBGASSERT_BASE(0, msg); } }

#else // _ZEPHYRDEBUG_DEBUG

//! 普通断言
#define ZDBGASSERT(expr)	((void)0)
//! 显示消息的断言
#define ZDBGASSERT_MSG(expr, msg)	((void)0)
//! 带堆栈输出的普通断言 output call stack
#define ZDBGASSERT_OCS(expr)	((void)0)
//! 带堆栈输出，且显示消息的断言 output call stack
#define ZDBGASSERT_MSG_OCS(expr, msg)	((void)0)

#endif // _ZEPHYRDEBUG_DEBUG

//////////////////////////////////////////////////////////////////////////////////////
// Log 等级

//! 一般来说，调试输出 和 警告，可以在最终发布版 不输出
#define ZDBG_LOG_LEVEL_DEBUG		ZSTR("Debug")
#define ZDBG_LOG_LEVEL_WARNING		ZSTR("Warning")
#define ZDBG_LOG_LEVEL_ERROR		ZSTR("Error")
#define ZDBG_LOG_LEVEL_MSG			ZSTR("Msg")

//////////////////////////////////////////////////////////////////////////////////////
//! 特殊断言
//! 一般用于向下类型转换前判断是否越界

#define ZDBGASSERT_ISBYTE(nums)		ZDBGASSERT(nums >= 0 && nums <= 0xff)
#define ZDBGASSERT_ISWORD(nums)		ZDBGASSERT(nums >= 0 && nums <= 0xffff)
#define ZDBGASSERT_ISDWORD(nums)	ZDBGASSERT(nums >= 0 && nums <= 0xffffffff)


//////////////////////////////////////////////////////////////////////////////////////
//! 消除警告
//! 一般用于参数未使用

#ifndef ZDBGUNUSED
#define ZDBGUNUSED(x)	((void)(x))
#endif


//////////////////////////////////////////////////////////////////////////////////////
//! 安全类型转换

#define ZDBGSAFECAST_BYTE(dest, src)	{ ZDBGASSERT_ISBYTE(src); dest = (ZDBGByte)src; }
#define ZDBGSAFECAST_WORD(dest, src)	{ ZDBGASSERT_ISWORD(src); dest = (ZDBGWord)src; }
#define ZDBGSAFECAST_DWORD(dest, src)	{ ZDBGASSERT_ISDWORD(src); dest = (ZDBGDWord)src; }

#ifdef  __cplusplus

namespace ZephyrDebug{

	//! 无符号整数安全转换
	template<typename T>
	class safe_unum_cast{
	public:
		template<typename U>
		explicit safe_unum_cast(typename U num) : m_unum(static_cast<typename T>(num)) {
			ZDBGASSERT(sizeof(typename T) <= 4);
			ZDBGASSERT(num >= 0 && num <= ( sizeof(typename T) == 1 ? 0xff : ( sizeof(typename T) == 2 ? 0xffff : 0xffffffff ) ));
		}

		operator T() const {
			return m_unum;
		}
	private:
		typename T m_unum;
	};

	//! 有符号整数安全转换
	template<typename T>
	class safe_num_cast{
	public:
		template<typename U>
		explicit safe_num_cast(typename U num) : m_num(static_cast<typename T>(num)) {
			ZDBGASSERT(sizeof(typename T) <= 4);
			ZDBGASSERT(sizeof(typename T) == 1 ? (num >= -128 && num <= 127) : 
				(sizeof(typename T) == 2 ? (num >= -32768 && num <= 32767) : (num >= -2147483648 && num <= 2147483647)));
		}

		operator T() const {
			return m_num;
		}
	private:
		typename T m_num;
	};

	//ZDBGByte safebyte_cast(typename T nums) {
	//	ZDBGASSERT_ISBYTE(nums);

	//	return static_cast<ZDBGByte>(nums);
	//}

	//template<typename T>
	//ZDBGByte safebyte_cast(typename T nums) {
	//	ZDBGASSERT_ISBYTE(nums);

	//	return static_cast<ZDBGByte>(nums);
	//}

	//template<typename T>
	//ZDBGWord safeword_cast(typename T nums) {
	//	ZDBGASSERT_ISWORD(nums);

	//	return static_cast<ZDBGWord>(nums);
	//}

	//template<typename T>
	//ZDBGDWord safedword_cast(typename T nums) {
	//	ZDBGASSERT_ISDWORD(nums);

	//	return static_cast<ZDBGDWord>(nums);
	//}

}

#endif

#ifdef  __cplusplus
extern "C" {
#endif
	//-------------------------------------------------------------------------
	// call stack

	typedef struct __zdbgCallStack{
		ZDBGInt32		i32Deep;
		ZDBGPVoid		stack[_ZEPHYRDEBUG_CALLSTACK_MAX];
	} ZDBGCallStack;

	//! 获得当前 call stack，保存在 pStack 中
	void ZEPHYRDEBUG_API ZDBGGetCallStack(ZDBGCallStack* pStack);

	//! 在Log里输出当前 call stack
	void ZEPHYRDEBUG_API ZDBGOutputCallStack();

	//! 获得当前 call stack，保存在 pStack 中
	void ZEPHYRDEBUG_API _ZDBGGetCallStack(ZDBGCallStack* pStack, CONTEXT* pContext);

	//! 在Log里输出当前 call stack
	void ZEPHYRDEBUG_API _ZDBGOutputCallStack(CONTEXT* pContext);

	//-------------------------------------------------------------------------
	// Log

	ZDBGCString ZEPHYRDEBUG_API ZDBGGetOutputLogFileName();

	void ZEPHYRDEBUG_API ZDBGSetOutputLogFileName(const ZDGBChar* str);

	void ZEPHYRDEBUG_API ZDBGOutputLog(const ZDGBChar* strModule, const ZDGBChar* strLevel, const ZDGBChar* str);

	void ZEPHYRDEBUG_API ZDBGOutputLogEx(const ZDGBChar* strModule, const ZDGBChar* strLevel, const ZDGBChar* str, ...);

	//-------------------------------------------------------------------------
	// 内部 log，主要用来配置内部 Log 输出
	//! 默认内部 log 使用 OutputLog，且 iModule 为 _ZEPHYRDEBUG_MODULE

	//! Log 输出函数
	typedef void (*ZDBGFuncOutputLog)(const ZDGBChar* strLevel, const ZDGBChar* str);

	//! 设置 log 输出函数
	ZDBGFuncOutputLog ZEPHYRDEBUG_API ZDBGSetFunc_OutputLog(ZDBGFuncOutputLog pFunc);

	//-------------------------------------------------------------------------
	// file ctrl

	enum ZDBG_OPENFILE_STATE{
		ZDBG_OPENFILE_STATE_READ		=	0,
		ZDBG_OPENFILE_STATE_WRITE		=	1,
		ZDBG_OPENFILE_STATE_READWRITE	=	2
	};

	enum ZDBG_SEEKFILE_STATE{
		ZDBG_SEEKFILE_BEGIN		=	0,
		ZDBG_SEEKFILE_CUR		=	1,
		ZDBG_SEEKFILE_END		=	2
	};

	typedef void* ZDBGFileImp;

	typedef ZDBGFileImp (*ZDBGFuncOpenFile)(const ZDGBChar* filename, enum ZDBG_OPENFILE_STATE state);

	typedef void (*ZDBGFuncCloseFile)(ZDBGFileImp file);

	typedef ZDBGSizeType (*ZDBGFuncReadFile)(ZDBGFileImp file, void* pBuff, ZDBGSizeType lBuffLen);

	typedef ZDBGSizeType (*ZDBGFuncWriteFile)(ZDBGFileImp file, const void* pBuff, ZDBGSizeType lBuffLen);

	typedef ZDBGSizeType (*ZDBGFuncSeekFile)(ZDBGFileImp file, enum ZDBG_SEEKFILE_STATE state, ZDBGLong lLen);

	typedef struct __zdbgFileCtrlFunc{
		ZDBGFuncOpenFile	pFunc_Open;
		ZDBGFuncCloseFile	pFunc_Close;
		ZDBGFuncReadFile	pFunc_Read;
		ZDBGFuncWriteFile	pFunc_Write;
		ZDBGFuncSeekFile	pFunc_Seek;
	} ZDBGFileCtrlFunc;

	//! 设置 文件操作 函数
	ZDBGFileCtrlFunc ZEPHYRDEBUG_API ZDBGSetFunc_FileCtrl(ZDBGFileCtrlFunc func);

#ifdef __cplusplus
}
#endif

#endif // __ZEPHYRDEBUG_ZEPHYRDEBUG_H__
