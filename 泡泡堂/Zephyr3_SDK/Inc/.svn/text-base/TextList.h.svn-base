/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	TextList.h

							Describe:	Text List

							Author:		赵洪松(xueren)

							CreateTime: 2002.10
							UpdateTime: 2003.08.20
*/

#ifndef _ZEPHYR_TEXTLIST_H
#define _ZEPHYR_TEXTLIST_H

#include <Zephyr.h>

///////////////////////////////////////////////////////////////////////////////////
// ZTextList
// 说明： 类似 char TextList[i][j] 的字符串数组
//		支持Remove(从iBegin开始，删除iLen个结点)
//		主要使用在 WndTextList中，作为其核心结构

class ZEPHYR_API ZTextList{
private:
	char	**m_Data;	// 字符串资源
	int		m_iUsed;	// 使用到的字符串数量

	int		m_iLength;	// 字符串长度
	int		m_iSize;	// 字符串数量
public:
	// 构造函数
	ZTextList(int iSize,int iLength);
	// 析构函数
	~ZTextList() { Release(); }

	//Release 释放资源
	void Release();

	// 在尾部增加结点
	// 返回 已经使用到的字符串数量
	int Add(const char *data);
	// 删除结点
	void Del(const char *data);
	// 删除结点
	void Del(int iIndex);

	// 获得某个结点指针
	char *GetData(int iIndex);
	// 清空列表
	void Clear() { m_iUsed = 0; }
	// 从iBegin开始，删除iLen个结点
	void Remove(int iBegin,int iLen);

	// 是否已经满了
	bool IsFull() { return m_iUsed == m_iSize; }

	// 获得当前已经使用到的结点数量
	int GetUsed() { return m_iUsed; }
	// 返回最多结点数量
	int GetSize() { return m_iSize; }
	// 返回每个结点字符串长度
	int GetLength() { return m_iLength; }
};

#endif//_ZEPHYR_TEXTLIST_H