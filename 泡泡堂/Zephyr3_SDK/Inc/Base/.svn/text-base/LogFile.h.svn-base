/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\LogFile.h

							Describe:	动态数组

							Author:		赵洪松(xueren)

							CreateTime: 2003.12.24
							UpdateTime: 2004.04.16
*/

#ifndef _ZEPHYR_3_BASE_LOGFILE_H
#define _ZEPHYR_3_BASE_LOGFILE_H

//#include <string>

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////////
	// LogFile

	class ZEPHYR_3_API LogFile{
	public:
		enum{ _FILENAME_LEN	=	64 };
		enum{ _BUFF_LEN	=	512 };
	public:
		// 构造函数
		LogFile(const char* name) : m_dwNums(0) { SetFile(name); }
		// 构造函数
		LogFile() : m_dwNums(0) { AutoLogFileName(); }

		// 设置文件
		void SetFile(const char* name);

		// 输出
		void Output(const char* dat);
		// 输出，附加时间输出
		void Output_Time(const char* dat);

		// 输出
		void OutputEx(const char* dat, ...);
		// 输出，附加时间输出
		void OutputEx_Time(const char* dat, ...);

		// 清空输出文件
		void Clear();

		// 是否初始化
		bool IsInited() { return m_fileName[0] != '\0'; }

		// 功能自动生成一个新的 LogFile 文件名
		// 参数：bInLocal，是否在当前目录内，如果为否，则输出目录在C盘根目录
		// 返回：返回一个可用的文件名
		const char* AutoLogFileName(bool bInLocal = true);
	private:
		char			m_fileName[_FILENAME_LEN];
//		std::string		m_fileName;
		DWORD			m_dwNums;
	};
};

#endif	// _ZEPHYR_3_BASE_LOGFILE_H