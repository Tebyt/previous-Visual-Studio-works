/*
							Zephyr Debug

							���� C �Ŀ�ƽ̨���Ի�����

							by �Ժ���(xueren) 2006

							E-mail:sssxueren@gmail.com

							FileName:	ZephyrDebug\ZephyrDebug.h

							Describe:	�����ļ�

							Author:		�Ժ���(zhs007)

							CreateTime: 2006.07.26
							UpdateTime: 
*/

#ifndef __ZEPHYRDEBUG_ZEPHYRDEBUG_H__
#define __ZEPHYRDEBUG_ZEPHYRDEBUG_H__

//////////////////////////////////////////////////////////////////////////////////////
// ȫ�ֺ궨��
// ����ı䣬��Ҫ���±���

/*******************************************************************
*	�����������궨��˵��
*
*  _MSC_VER	��ʾʹ��MSVC���������ұ�ʾ�汾��
*	_DEBUG		��ʾʹ��Debug�汾
*	NDEBUG		��ʾʹ��Release�汾�����ͬʱ���� _DEBUG �� NDEBUG���� NDEBUG ����
*
*******************************************************************/

//!	��������� _ZEPHYRDEBUG_PLATFORM_WIN32_ ���ʾΪWin32ƽ̨
#define _ZEPHYRDEBUG_PLATFORM_WIN32_

//!	��������� _ZEPHYRDEBUG_PLATFORM_WINCE_ ���ʾΪWinCEƽ̨
//#define _ZEPHYRDEBUG_PLATFORM_WINCE_

//!	��������� _ZEPHYRDEBUG_MACHINE_I386_ ���ʾΪIntel 32λ ָ�
#define _ZEPHYRDEBUG_MACHINE_I386_

//!	��������� _ZEPHYRDEBUG_DEBUG ���ʾΪ DEBUG
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
// �ڲ��궨��
// ����ı䣬��Ҫ���±���

//! ������ö�ջ�����
#define _ZEPHYRDEBUG_CALLSTACK_MAX		64
//! ������������С
#define _ZEPHYRDEBUG_MAX_LOGBUFF_SIZE	1024
////! �Զ���� Module ��
//#define _ZEPHYRDEBUG_MODULE				ZSTR("ZephyrDebug")

//////////////////////////////////////////////////////////////////////////////////////
// ȫ��ͷ�ļ�
#ifdef _ZEPHYRDEBUG_PLATFORM_WIN32_
#include <Windows.h>
#pragma warning(push)
#pragma warning(disable : 4201)	//! ʹ���˷Ǳ�׼��չ : �����ƵĽṹ/����
#include <DBGHelp.h>
#pragma warning(pop)
#endif // _ZEPHYRDEBUG_PLATFORM_WIN32_

//////////////////////////////////////////////////////////////////////////////////////
// ���Ͷ���

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
// ����

typedef ZDBGInt32		ZDBGResult;

#define ZDBG_OK			0
#define ZDBG_FAIL		0xffffffff

//////////////////////////////////////////////////////////////////////////////////////
// ����
// ����ı䣬��Ҫ���±���

//! �����ں�
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

//! ��ͨ����
#define ZDBGASSERT(expr)	__ZDBGASSERT_BASE(expr, _ZDBGSTR(#expr))
//! ��ʾ��Ϣ�Ķ���
#define ZDBGASSERT_MSG(expr, msg)	__ZDBGASSERT_BASE(expr, msg)
//! ����ջ�������ͨ���� output call stack
#define ZDBGASSERT_OCS(expr)	{ if(!(expr)){ ZDBGOutputCallStack(); __ZDBGASSERT_BASE(0, _ZDBGSTR(#expr)); } }
//! ����ջ���������ʾ��Ϣ�Ķ��� output call stack
#define ZDBGASSERT_MSG_OCS(expr, msg)	{ if(!(expr)){ ZDBGOutputCallStack(); __ZDBGASSERT_BASE(0, msg); } }

#else // _ZEPHYRDEBUG_DEBUG

//! ��ͨ����
#define ZDBGASSERT(expr)	((void)0)
//! ��ʾ��Ϣ�Ķ���
#define ZDBGASSERT_MSG(expr, msg)	((void)0)
//! ����ջ�������ͨ���� output call stack
#define ZDBGASSERT_OCS(expr)	((void)0)
//! ����ջ���������ʾ��Ϣ�Ķ��� output call stack
#define ZDBGASSERT_MSG_OCS(expr, msg)	((void)0)

#endif // _ZEPHYRDEBUG_DEBUG

//////////////////////////////////////////////////////////////////////////////////////
// Log �ȼ�

//! һ����˵��������� �� ���棬���������շ����� �����
#define ZDBG_LOG_LEVEL_DEBUG		ZSTR("Debug")
#define ZDBG_LOG_LEVEL_WARNING		ZSTR("Warning")
#define ZDBG_LOG_LEVEL_ERROR		ZSTR("Error")
#define ZDBG_LOG_LEVEL_MSG			ZSTR("Msg")

//////////////////////////////////////////////////////////////////////////////////////
//! �������
//! һ��������������ת��ǰ�ж��Ƿ�Խ��

#define ZDBGASSERT_ISBYTE(nums)		ZDBGASSERT(nums >= 0 && nums <= 0xff)
#define ZDBGASSERT_ISWORD(nums)		ZDBGASSERT(nums >= 0 && nums <= 0xffff)
#define ZDBGASSERT_ISDWORD(nums)	ZDBGASSERT(nums >= 0 && nums <= 0xffffffff)


//////////////////////////////////////////////////////////////////////////////////////
//! ��������
//! һ�����ڲ���δʹ��

#ifndef ZDBGUNUSED
#define ZDBGUNUSED(x)	((void)(x))
#endif


//////////////////////////////////////////////////////////////////////////////////////
//! ��ȫ����ת��

#define ZDBGSAFECAST_BYTE(dest, src)	{ ZDBGASSERT_ISBYTE(src); dest = (ZDBGByte)src; }
#define ZDBGSAFECAST_WORD(dest, src)	{ ZDBGASSERT_ISWORD(src); dest = (ZDBGWord)src; }
#define ZDBGSAFECAST_DWORD(dest, src)	{ ZDBGASSERT_ISDWORD(src); dest = (ZDBGDWord)src; }

#ifdef  __cplusplus

namespace ZephyrDebug{

	//! �޷���������ȫת��
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

	//! �з���������ȫת��
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

	//! ��õ�ǰ call stack�������� pStack ��
	void ZEPHYRDEBUG_API ZDBGGetCallStack(ZDBGCallStack* pStack);

	//! ��Log�������ǰ call stack
	void ZEPHYRDEBUG_API ZDBGOutputCallStack();

	//! ��õ�ǰ call stack�������� pStack ��
	void ZEPHYRDEBUG_API _ZDBGGetCallStack(ZDBGCallStack* pStack, CONTEXT* pContext);

	//! ��Log�������ǰ call stack
	void ZEPHYRDEBUG_API _ZDBGOutputCallStack(CONTEXT* pContext);

	//-------------------------------------------------------------------------
	// Log

	ZDBGCString ZEPHYRDEBUG_API ZDBGGetOutputLogFileName();

	void ZEPHYRDEBUG_API ZDBGSetOutputLogFileName(const ZDGBChar* str);

	void ZEPHYRDEBUG_API ZDBGOutputLog(const ZDGBChar* strModule, const ZDGBChar* strLevel, const ZDGBChar* str);

	void ZEPHYRDEBUG_API ZDBGOutputLogEx(const ZDGBChar* strModule, const ZDGBChar* strLevel, const ZDGBChar* str, ...);

	//-------------------------------------------------------------------------
	// �ڲ� log����Ҫ���������ڲ� Log ���
	//! Ĭ���ڲ� log ʹ�� OutputLog���� iModule Ϊ _ZEPHYRDEBUG_MODULE

	//! Log �������
	typedef void (*ZDBGFuncOutputLog)(const ZDGBChar* strLevel, const ZDGBChar* str);

	//! ���� log �������
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

	//! ���� �ļ����� ����
	ZDBGFileCtrlFunc ZEPHYRDEBUG_API ZDBGSetFunc_FileCtrl(ZDBGFileCtrlFunc func);

#ifdef __cplusplus
}
#endif

#endif // __ZEPHYRDEBUG_ZEPHYRDEBUG_H__
