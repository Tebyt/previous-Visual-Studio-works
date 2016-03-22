/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\SysLog.h

							Describe:	ϵͳLog

							Author:		�Ժ���(xueren)

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
		// �����ļ�
		static void SetFile(const char* name) { m_Log.SetFile(name); }

		// ���
		static void Output(const char* dat) { m_Log.Output(dat); }

		// ���������ʱ�����
		static void Output_Time(const char* dat) { m_Log.Output(dat); }

		// �������ļ�
		static void Clear() { m_Log.Clear(); }

		// ���
		static void OutputEx(const char* dat, ...);
		// ���������ʱ�����
		static void OutputEx_Time(const char* dat, ...);
	public:
		static LogFile		m_Log;
	};
};

#endif // _ZEPHYR_3_BASE_SYSLOG_H