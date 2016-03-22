/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZApps.h

							Describe:	������ı���

							Author:		�Ժ���(xueren)

							CreateTime: 2004.03.10
							UpdateTime:
*/

#ifndef _ZEPHYR_3_APPS_H
#define _ZEPHYR_3_APPS_H

#include <Zephyr.h>

#include <ZLogFile.h>

namespace Zephyr3{

	struct AppData{
		LogFile	logFile;
		LPVOID	pDat;
	};

	typedef AppData*	LPAppData;

	// ��ó�����ı���
	LPAppData ZEPHYR_API GetAppData();

	// �����Լ��ĳ�����ı���
	void ZEPHYR_API SetMyAppData(LPVOID pDat);

	// ��ȡ�Լ��ĳ�����ı���
	LPVOID ZEPHYR_API GetMyAppData();


	// ����ļ��Ƿ����
	bool ZEPHYR_API HasFile(const char* name);
	// ɾ���ļ�
	void ZEPHYR_API DelFile(const char* name);
	// ɾ���ļ���֧��ͨ���
	void ZEPHYR_API DelFileEx(const char* name);
	// �ļ�����
	void ZEPHYR_API RenameFile(const char* src,const char* dst);
};

#endif	// _ZEPHYR_3_APPS_H