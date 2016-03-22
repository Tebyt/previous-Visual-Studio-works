/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\BaseDef.h

							Describe:	基本定义

							Author:		赵洪松(xueren)

							CreateTime: 2003.04.22
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_BASEDEF_H
#define _ZEPHYR_3_BASE_BASEDEF_H

namespace Zephyr3{

	// 返回输出
	HRESULT ZEPHYR_3_API Ret(HRESULT hRet,const char* str, ...);

	// 返回输出
	HRESULT ZEPHYR_3_API Ret_Time(HRESULT hRet,const char* str, ...);

	// 输出log
	void ZEPHYR_3_API OutputLog(const char* str, ...);

	// 输出log
	void ZEPHYR_3_API OutputLog_Time(const char* str, ...);

	// 字符串格式化
	// 你必须自己保证目标字符串不会溢出
	void ZEPHYR_3_API _StrFormat(char* buf, DWORD bufSize, const char* str,...);
};

#ifndef _DEBUG
#define OUTPUTLOG_TIME(param)	Zephyr3::PutputLog_Time(param)
#define OUTPUTLOG_TIME2(param1,param2)	Zephyr3::PutputLog_Time(param1,param2)
#else
#define OUTPUTLOG_TIME(param)	
#define OUTPUTLOG_TIME2(param1,param2)	
#endif

#endif // _ZEPHYR_3_BASE_BASEDEF_H