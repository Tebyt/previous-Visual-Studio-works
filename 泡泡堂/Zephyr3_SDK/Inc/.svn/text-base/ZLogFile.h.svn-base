/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZLogFile.h

							Describe:	动态数组

							Author:		赵洪松(xueren)

							CreateTime: 2003.12.24
							UpdateTime:
*/

#ifndef _ZEPHYR_3_LOGFILE_H
#define _ZEPHYR_3_LOGFILE_H

#include <Zephyr.h>

#include <ZDebug.h>

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////////
	// LogFile

	const char	LOGFILE_DEFAULT_FILENAME[]	=	"output.log";

	class ZEPHYR_API LogFile{
	public:
		static const int	FILENAME_LEN	=	256;
	public:
		// 构造函数
		LogFile(const char* name) { SetFile(name); }
		// 构造函数
		LogFile() { SetFile(LOGFILE_DEFAULT_FILENAME); }

		// 设置文件
		void SetFile(const char* name);

		// 输出
		void Output(const char* dat);

		// 输出，附加时间输出
		void Output_Time(const char* dat);

		// 清空输出文件
		void Clear();

		// 是否初始化
		bool IsInited() { return m_fileName[0] != '\0'; }
	private:
		char	m_fileName[FILENAME_LEN];
		DWORD	m_dwNums;
	};

	/////////////////////////////////////////////////////////////////////////////////
	// LogFile Name

	// 功能自动生成一个新的 LogFile 文件名
	// 参数：bInLocal，是否在当前目录内，如果为否，则输出目录在C盘根目录
	// 返回：返回一个可用的文件名
	const char* AutoLogFileName(bool bInLocal = true);
};

#endif	// _ZEPHYR_3_LOGFILE_H