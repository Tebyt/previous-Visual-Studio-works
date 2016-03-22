/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Script\WordParser.h

							Describe:	词法翻译

							Author:		赵洪松(xueren)

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

const DWORD ZWORDPARSER_FAIL	=	0;		// 失败
const DWORD	ZWORDPARSER_DAT		=	0x01;	// 自定义数据
const DWORD	ZWORDPARSER_INT		=	0x12;	// 有符号整数
const DWORD	ZWORDPARSER_UINT	=	0x02;	// 无符号整数

class ZEPHYR_API ZWordParser{
protected:
	char	*m_strSrc;
public:
	// 缺省构造函数
	ZWordParser() { m_strSrc = NULL; }
	// 构造函数
	inline ZWordParser(const char *str);
	// 析构函数
	virtual ~ZWordParser() { Release(); }

	// 初始化
	HRESULT Init(const char *str);
	// 资源释放
	void Release();

	// 解释str，解释结果放在obj里面
	// 返回 -	ZWORDPARSER_DAT		自定义数据
	//			ZWORDPARSER_INT		有符号整数
	//			ZWORDPARSER_UINT	无符号整数
	virtual DWORD Parse(ZParserObject &obj,const char *str);

	// 解释
	inline DWORD Parse(ZParserObject &obj) { return Parse(obj,m_strSrc); }
protected:
	// 是否为10进制数字
	bool IsNum(char c) { return c >= '0' && c <= '9'; }
	// 是否为数字
	bool IsNums(const char *str);
	// 是否为减号
	bool IsSymbol_Sub(char c) { return c == '-'; }

	// 解释整数
	int ParseInt(const char *str);
	// 解释无符号整数
	unsigned int ParseUInt(const char *str);
};


inline ZWordParser::ZWordParser(const char *str)
{ 
	m_strSrc = NULL; 

	Init(str);
}

#endif//_ZEPHYR_SCRIPT_WORDPARSER_H