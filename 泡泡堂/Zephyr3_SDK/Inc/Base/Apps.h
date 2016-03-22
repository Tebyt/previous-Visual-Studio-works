/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Apps.h

							Describe:	程序

							Author:		赵洪松(xueren)

							CreateTime: 2003.04.16
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_APPS_H
#define _ZEPHYR_3_BASE_APPS_H

#include <Base\Debug.h>
#include <Base\Thread.h>

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////////////
	// AppData

	class ZEPHYR_3_API AppData{
	public:
		// 释放资源
		void Release();
	public:
		Debuger			m_debuger;
		LPVOID			m_pDat;
		ThreadSystem	m_threadSystem;
	};

	typedef AppData*	LPAppData;

	/////////////////////////////////////////////////////////////////////////////////
	// 函数

	// 设置自己的程序核心变量
	void ZEPHYR_3_API SetMyAppData(LPVOID pDat);

	// 获取自己的程序核心变量
	LPVOID ZEPHYR_3_API GetMyAppData();

	// 返回输出
	HRESULT ZEPHYR_3_API Ret(HRESULT hRet,const char* str,...);

	// 返回输出
	HRESULT ZEPHYR_3_API Ret_Time(HRESULT hRet,const char* str,...);

	// 输出log
	void ZEPHYR_3_API OutputLog(const char* str,...);

	// 输出log
	void ZEPHYR_3_API OutputLog_Time(const char* str,...);

	// 字符串格式化
	// 你必须自己保证目标字符串不会溢出
	void ZEPHYR_3_API _StrFormat(char* buf,DWORD bufSize,const char* str,...);

	// 获得线程系统
	ThreadSystemReference ZEPHYR_3_API GetThreadSystem();
};

#ifndef _DEBUG
#define OUTPUTLOG_TIME(param)	Zephyr3::PutputLog_Time(param)
#define OUTPUTLOG_TIME2(param1,param2)	Zephyr3::PutputLog_Time(param1,param2)
#define OUTPUTLOG_TIME3(param1,param2,param3)	Zephyr3::PutputLog_Time(param1,param2,param3)
#else
#define OUTPUTLOG_TIME(param)	
#define OUTPUTLOG_TIME2(param1,param2)	
#define OUTPUTLOG_TIME3(param1,param2,param3)	
#endif

#endif // _ZEPHYR_3_BASE_APPS_H