/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	PackFile.h

							Describe:	�ײ����ļ�ϵͳ

							Author:		�Ժ���(xueren)

							CreateTime: 2002.3
							UpdateTime: 2003.09.04
*/

#ifndef _ZEPHYR_PACKFILE_H
#define _ZEPHYR_PACKFILE_H

#include <Zephyr.h>

#include <ZFile.h>

#include <string>
#include <set>

class PackFile{
public:
	typedef std::string		String;
protected:
	String		m_Dir;
	String		m_Name;

	ZLocalFileImp	m_fileImp;
public:

};

//////////////////////////////////////////////////////////////////////////////////////////////////
// ZPackFileManager

class ZPackFileManager{
private:
public:
};

#endif//_ZEPHYR_PACKFILE_H