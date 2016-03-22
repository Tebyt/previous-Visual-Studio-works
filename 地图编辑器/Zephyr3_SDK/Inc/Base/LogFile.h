/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\LogFile.h

							Describe:	��̬����

							Author:		�Ժ���(xueren)

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
		// ���캯��
		LogFile(const char* name) : m_dwNums(0) { SetFile(name); }
		// ���캯��
		LogFile() : m_dwNums(0) { AutoLogFileName(); }

		// �����ļ�
		void SetFile(const char* name);

		// ���
		void Output(const char* dat);
		// ���������ʱ�����
		void Output_Time(const char* dat);

		// ���
		void OutputEx(const char* dat, ...);
		// ���������ʱ�����
		void OutputEx_Time(const char* dat, ...);

		// �������ļ�
		void Clear();

		// �Ƿ��ʼ��
		bool IsInited() { return m_fileName[0] != '\0'; }

		// �����Զ�����һ���µ� LogFile �ļ���
		// ������bInLocal���Ƿ��ڵ�ǰĿ¼�ڣ����Ϊ�������Ŀ¼��C�̸�Ŀ¼
		// ���أ�����һ�����õ��ļ���
		const char* AutoLogFileName(bool bInLocal = true);
	private:
		char			m_fileName[_FILENAME_LEN];
//		std::string		m_fileName;
		DWORD			m_dwNums;
	};
};

#endif	// _ZEPHYR_3_BASE_LOGFILE_H