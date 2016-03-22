/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZLogFile.h

							Describe:	��̬����

							Author:		�Ժ���(xueren)

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
		// ���캯��
		LogFile(const char* name) { SetFile(name); }
		// ���캯��
		LogFile() { SetFile(LOGFILE_DEFAULT_FILENAME); }

		// �����ļ�
		void SetFile(const char* name);

		// ���
		void Output(const char* dat);

		// ���������ʱ�����
		void Output_Time(const char* dat);

		// �������ļ�
		void Clear();

		// �Ƿ��ʼ��
		bool IsInited() { return m_fileName[0] != '\0'; }
	private:
		char	m_fileName[FILENAME_LEN];
		DWORD	m_dwNums;
	};

	/////////////////////////////////////////////////////////////////////////////////
	// LogFile Name

	// �����Զ�����һ���µ� LogFile �ļ���
	// ������bInLocal���Ƿ��ڵ�ǰĿ¼�ڣ����Ϊ�������Ŀ¼��C�̸�Ŀ¼
	// ���أ�����һ�����õ��ļ���
	const char* AutoLogFileName(bool bInLocal = true);
};

#endif	// _ZEPHYR_3_LOGFILE_H