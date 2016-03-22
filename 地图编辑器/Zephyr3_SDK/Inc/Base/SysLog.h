/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\SysLog.h

							Describe:	系统Log

							Author:		赵洪松(xueren)

							CreateTime: 2004.11.06
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_SYSLOG_H
#define _ZEPHYR_3_BASE_SYSLOG_H

#include <Base\LogFile.h>

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////////
	// SysLog

	class ZEPHYR_3_API SysLog{
	public:
		enum{ _BUFF_LEN	=	LogFile::_BUFF_LEN };
	public:
		// 设置文件
		static void SetFile(const char* name) { m_Log.SetFile(name); }

		// 输出
		static void Output(const char* dat) { m_Log.Output(dat); }

		// 输出，附加时间输出
		static void Output_Time(const char* dat) { m_Log.Output(dat); }

		// 清空输出文件
		static void Clear() { m_Log.Clear(); }

		// 输出
		static void OutputEx(const char* dat, ...);
		// 输出，附加时间输出
		static void OutputEx_Time(const char* dat, ...);
	public:
		static LogFile		m_Log;
	};
};

#endif // _ZEPHYR_3_BASE_SYSLOG_H