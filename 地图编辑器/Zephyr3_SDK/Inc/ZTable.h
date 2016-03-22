/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZTable.h

							Describe:	底层数据结构 表

							Author:		赵洪松(xueren)

							CreateTime: 2003.08.25
							UpdateTime:
*/

#ifndef _ZEPHYR_TABLE_H
#define _ZEPHYR_TABLE_H

#include <Zephyr.h>

#include <ZDebug.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZTable
// 说明：表，2维数组
//		不会执行到 T 的构造函数，如果需要构造初始化，在具体使用以前自行初始化

template<class T>
class ZTable{
protected:
	T		**m_Table;
	int		m_Width,m_Height;
public:
	// 构造函数
	inline ZTable();
	// 析构函数
	~ZTable() { Release(); }

	// 资源释放
	void Release();

	// 初始化
	HRESULT Init(int w,int h);

	// 获得数据
	inline T &GetData(int x,int y);
	// 设置数据
	inline void SetData(int x,int y,T &t);
	
	int GetWidth() { return m_Width; }
	
	int GetHeight() { return m_Height; }
};

// 构造函数
template<class T>
inline ZTable<T>::ZTable()
{
	m_Table = NULL;
	m_Width = m_Height = 0;
}

// 资源释放
template<class T>
void ZTable<T>::Release()
{
	if(m_Table != NULL)
	{
		free(m_Table);

		m_Table = NULL;
	}

	m_Width = m_Height = 0;
}

// 初始化
template<class T>
HRESULT ZTable<T>::Init(int w,int h)
{
	ZASSERT(w > 0 && h > 0);
	ZASSERT(m_Table == NULL);

	m_Table = (T **)malloc(sizeof(T *) * h + sizeof(T) * w * h);
	assert(m_Table != NULL);
	BYTE *tmp = (BYTE *)m_Table + sizeof(T *) * h;

	for(int i = 0; i < h; i++)
	{
		m_Table[i] = (T *)tmp;
		tmp += sizeof(T *) * w;
	}

	m_Width = w;
	m_Height = h;

	return S_OK;
}

// 获得数据
template<class T>
inline T &ZTable<T>::GetData(int x,int y)
{
	ZASSERT(x >= 0 && x < m_Width);
	ZASSERT(y >= 0 && y < m_Height);

	return m_Table[y][x];
}

// 设置数据
template<class T>
inline void ZTable<T>::SetData(int x,int y,T &t)
{
	ZASSERT(x >= 0 && x < m_Width);
	ZASSERT(y >= 0 && y < m_Height);

	m_Table[y][x] = t;
}

#endif//_ZEPHYR_TABLE_H