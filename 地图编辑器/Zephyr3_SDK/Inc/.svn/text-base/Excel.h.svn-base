/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Excel.h

							Describe:	Excel 文本文件读取

							Author:		赵洪松(xueren)

							CreateTime: 2003.08.25
							UpdateTime:
*/

#ifndef _ZEPHYR_EXCEL_H
#define _ZEPHYR_EXCEL_H

#include <Zephyr.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZExcelTXT
// 说明：Excel 文本文件读取
//		只允许顺序读取一遍！

const DWORD ZEXCELTXT_END		=	0;		// 结束
const DWORD ZEXCELTXT_OBJECT	=	0x01;	// Object
const DWORD ZEXCELTXT_NEXTLINE	=	0x02;	// 换行符

class ZEPHYR_API ZExcelTXT{
protected:
	char	*m_Buff;	// 缓冲
	char	*m_curBuff;	// 当前缓冲位置
public:
	// 缺省构造函数
	ZExcelTXT() { m_Buff = m_curBuff = NULL; }
	// 构造函数
	inline ZExcelTXT(const char *filename);
	// 析构函数
	~ZExcelTXT() { Release(); }

	// 资源释放
	void Release();

	// 读取文件
	HRESULT Load(const char *filename);
	// 从缓冲中读取一个单元
	const char *Read(DWORD &ret);

	// 获得列数量
	int GetWidth();
	// 获得行数量
	int GetHeight();
};

inline ZExcelTXT::ZExcelTXT(const char *filename) 
{ 
	m_Buff = m_curBuff = NULL;

	Load(filename); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZExcelTable
// 说明：Excel 表

#include <ZTable.h>

class ZEPHYR_API ZExcelTable : public ZTable<char *>, private ZExcelTXT{
private:
	char	m_FileName[64];
public:
	// 构造函数
	inline ZExcelTable(const char *filename);
	// 析构函数
	~ZExcelTable() { Release(); }

	// 资源释放
	void Release();

	int GetRow() { return ZTable<char *>::GetHeight(); }

	const char *GetFileName() { return m_FileName; }

	int Find_Y(int x,const char *dat);

	HRESULT Save(const char* name);
private:
	// 对 Table 做初始化
	HRESULT InitTable();
};

// 构造函数
inline ZExcelTable::ZExcelTable(const char *filename) 
	: ZExcelTXT(filename) 
{
	strcpy(m_FileName,filename);

	InitTable(); 
}

typedef ZExcelTable *	LPZExcelTable;

#endif//_ZEPHYR_EXCEL_H