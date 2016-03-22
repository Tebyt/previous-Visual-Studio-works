/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZApps.h

							Describe:	程序核心变量

							Author:		赵洪松(xueren)

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

	// 获得程序核心变量
	LPAppData ZEPHYR_API GetAppData();

	// 设置自己的程序核心变量
	void ZEPHYR_API SetMyAppData(LPVOID pDat);

	// 获取自己的程序核心变量
	LPVOID ZEPHYR_API GetMyAppData();


	// 检查文件是否存在
	bool ZEPHYR_API HasFile(const char* name);
	// 删除文件
	void ZEPHYR_API DelFile(const char* name);
	// 删除文件，支持通配符
	void ZEPHYR_API DelFileEx(const char* name);
	// 文件改名
	void ZEPHYR_API RenameFile(const char* src,const char* dst);
};

#endif	// _ZEPHYR_3_APPS_H