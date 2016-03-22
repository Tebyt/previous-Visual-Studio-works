/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Script\WordParser.h

							Describe:	�ʷ�����

							Author:		�Ժ���(xueren)

							CreateTime: 2003.09.02
							UpdateTime:
*/

#ifndef _ZEPHYR_SCRIPT_WORDPARSER_H
#define _ZEPHYR_SCRIPT_WORDPARSER_H

#include <Zephyr.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// ZParserObject

union ZParserObject{
	DWORD			dwDat;
	unsigned int	uiNums;
	int				iNums;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// ZWordParser

const DWORD ZWORDPARSER_FAIL	=	0;		// ʧ��
const DWORD	ZWORDPARSER_DAT		=	0x01;	// �Զ�������
const DWORD	ZWORDPARSER_INT		=	0x12;	// �з�������
const DWORD	ZWORDPARSER_UINT	=	0x02;	// �޷�������

class ZEPHYR_API ZWordParser{
protected:
	char	*m_strSrc;
public:
	// ȱʡ���캯��
	ZWordParser() { m_strSrc = NULL; }
	// ���캯��
	inline ZWordParser(const char *str);
	// ��������
	virtual ~ZWordParser() { Release(); }

	// ��ʼ��
	HRESULT Init(const char *str);
	// ��Դ�ͷ�
	void Release();

	// ����str�����ͽ������obj����
	// ���� -	ZWORDPARSER_DAT		�Զ�������
	//			ZWORDPARSER_INT		�з�������
	//			ZWORDPARSER_UINT	�޷�������
	virtual DWORD Parse(ZParserObject &obj,const char *str);

	// ����
	inline DWORD Parse(ZParserObject &obj) { return Parse(obj,m_strSrc); }
protected:
	// �Ƿ�Ϊ10��������
	bool IsNum(char c) { return c >= '0' && c <= '9'; }
	// �Ƿ�Ϊ����
	bool IsNums(const char *str);
	// �Ƿ�Ϊ����
	bool IsSymbol_Sub(char c) { return c == '-'; }

	// ��������
	int ParseInt(const char *str);
	// �����޷�������
	unsigned int ParseUInt(const char *str);
};


inline ZWordParser::ZWordParser(const char *str)
{ 
	m_strSrc = NULL; 

	Init(str);
}

#endif//_ZEPHYR_SCRIPT_WORDPARSER_H