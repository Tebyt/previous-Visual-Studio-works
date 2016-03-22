/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Excel.h

							Describe:	Excel �ı��ļ���ȡ

							Author:		�Ժ���(xueren)

							CreateTime: 2003.08.25
							UpdateTime:
*/

#ifndef _ZEPHYR_EXCEL_H
#define _ZEPHYR_EXCEL_H

#include <Zephyr.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZExcelTXT
// ˵����Excel �ı��ļ���ȡ
//		ֻ����˳���ȡһ�飡

const DWORD ZEXCELTXT_END		=	0;		// ����
const DWORD ZEXCELTXT_OBJECT	=	0x01;	// Object
const DWORD ZEXCELTXT_NEXTLINE	=	0x02;	// ���з�

class ZEPHYR_API ZExcelTXT{
protected:
	char	*m_Buff;	// ����
	char	*m_curBuff;	// ��ǰ����λ��
public:
	// ȱʡ���캯��
	ZExcelTXT() { m_Buff = m_curBuff = NULL; }
	// ���캯��
	inline ZExcelTXT(const char *filename);
	// ��������
	~ZExcelTXT() { Release(); }

	// ��Դ�ͷ�
	void Release();

	// ��ȡ�ļ�
	HRESULT Load(const char *filename);
	// �ӻ����ж�ȡһ����Ԫ
	const char *Read(DWORD &ret);

	// ���������
	int GetWidth();
	// ���������
	int GetHeight();
};

inline ZExcelTXT::ZExcelTXT(const char *filename) 
{ 
	m_Buff = m_curBuff = NULL;

	Load(filename); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZExcelTable
// ˵����Excel ��

#include <ZTable.h>

class ZEPHYR_API ZExcelTable : public ZTable<char *>, private ZExcelTXT{
private:
	char	m_FileName[64];
public:
	// ���캯��
	inline ZExcelTable(const char *filename);
	// ��������
	~ZExcelTable() { Release(); }

	// ��Դ�ͷ�
	void Release();

	int GetRow() { return ZTable<char *>::GetHeight(); }

	const char *GetFileName() { return m_FileName; }

	int Find_Y(int x,const char *dat);

	HRESULT Save(const char* name);
private:
	// �� Table ����ʼ��
	HRESULT InitTable();
};

// ���캯��
inline ZExcelTable::ZExcelTable(const char *filename) 
	: ZExcelTXT(filename) 
{
	strcpy(m_FileName,filename);

	InitTable(); 
}

typedef ZExcelTable *	LPZExcelTable;

#endif//_ZEPHYR_EXCEL_H