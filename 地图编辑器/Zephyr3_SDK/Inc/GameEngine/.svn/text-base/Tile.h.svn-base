/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\Tile.h

							Describe:	游戏引擎 Tile 部分

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.17
							UpdateTime:
*/

#ifndef _ZEPHYR_GAMEENGINE_H
#define _ZEPHYR_GAMEENGINE_H

//////////////////////////////////////////////////////////////////////////////////////////
// ZGameTileType

const DWORD		ZGAMETILE_NULL		=	0;
const DWORD		ZGAMETILE_16X16		=	16;
const DWORD		ZGAMETILE_32X32		=	32;

class ZGameTileType{
protected:
	union _Tile{
		DWORD	dwTile;
		WORD	wTile[2];
	};

	_Tile	m_Tile;
public:
	// 缺省构造函数
	ZGameTileType() { m_Tile.dwTile = ZGAMETILE_NULL; }
	// 构造函数
	ZGameTileType(DWORD tile) { m_Tile.dwTile = tile; }
	// 拷贝构造函数
	ZGameTileType(ZGameTileType &tile) { m_Tile.dwTile = tile.m_Tile.dwTile; }
	// 析构函数
	~ZGameTileType() { ; }

	// 获得矩形Tile大小
	int GetRectTileSize() { return m_Tile.wTile[0]; }
	// 获得Tile属性
	WORD GetTileState() { return m_Tile.wTile[1]; }

	void SetRectTile(int tileSize) { m_Tile.dwTile = tileSize; }
};

//////////////////////////////////////////////////////////////////////////////////////////
// ZGameTileData

template<class T>
class ZGameTileData{
protected:
	T		**m_Data;
	long	m_lWidth,m_lHeight;
public:
	// 构造函数
	inline ZGameTileData();
	// 构造函数
	ZGameTileData(long w,long h) { Init(w,h); }
	// 析构函数
	~ZGameTileData() { Release(); }

	// 初始化
	HRESULT Init(long w,long h);

	// 获得 (x,y) 坐标下每一格的数据
	DWORD GetData(long x,long y);

	// 设置 (x,y) 坐标的数据
	void SetData(long x,long y,DWORD dat);

	// 获得Tile数据大小
	int GetTileDataLen() { return sizeof(T); }

	// 释放资源
	void Release();

	// 储存数据到文件
	// 注意 -	文件应该是已经打开的
	HRESULT SaveLayerData(ZFile &file);

	// 从文件读取数据
	// 注意 -	文件应该是已经打开的
	HRESULT LoadLayerData(ZFile &file);
};

// 构造函数
template<class T>
inline ZGameTileData<T>::ZGameTileData() 
{
	m_lWidth = 0;
	m_lHeight = 0;

	m_Data = NULL;
}

// 初始化
template<class T>
HRESULT ZGameTileData<T>::Init(long w,long h)
{
	ZASSERT(m_lWidth == 0 && m_lHeight == 0);
	ZASSERT(w > 0 && h > 0);
	ZASSERT(m_Data == NULL);

	m_lWidth = w;
	m_lHeight = h;

	m_Data = (T **)malloc(sizeof(T *) * h + sizeof(T) * w * h);
	assert(m_Data != NULL);

	memset(m_Data,0,sizeof(T *) * h + sizeof(T) * w * h);

	BYTE *tmp = (BYTE *)((BYTE *)m_Data + sizeof(BYTE *) * h);

	for(int i = 0; i < h; i++)
	{
		m_Data[i] = (T *)tmp;

		tmp += sizeof(T) * w;
	}

	return S_OK;
}

// 获得 (x,y) 坐标下每一格的数据
template<class T>
DWORD ZGameTileData<T>::GetData(long x,long y)
{
	ZASSERT(m_Data != NULL);
	ZASSERT(x >= 0 && x < m_lWidth);
	ZASSERT(y >= 0 && y < m_lHeight);

	return m_Data[y][x];
}

// 设置 (x,y) 坐标的数据
template<class T>
void ZGameTileData<T>::SetData(long x,long y,DWORD dat)
{
	ZASSERT(m_Data != NULL);
	ZASSERT(x >= 0 && x < m_lWidth);
	ZASSERT(y >= 0 && y < m_lHeight);

	m_Data[y][x] = (T)dat;
}

// 释放资源
template<class T>
void ZGameTileData<T>::Release()
{
	if(m_Data != NULL)
	{
		free(m_Data);

		m_Data = NULL;
	}

	m_lWidth = m_lHeight = 0;
}

// 储存数据到文件
// 注意 -	文件应该是已经打开的
template<class T>
HRESULT ZGameTileData<T>::SaveLayerData(ZFile &file)
{
	ZASSERT(file.IsOpen());
	ZASSERT(m_Data != NULL);

	for(int y = 0; y < m_lHeight; y++)
		file.Write(m_Data[y],sizeof(T) * m_lWidth);

	return S_OK;
}

// 从文件读取数据
// 注意 -	文件应该是已经打开的
template<class T>
HRESULT ZGameTileData<T>::LoadLayerData(ZFile &file)
{
	ZASSERT(file.IsOpen());
	ZASSERT(m_Data != NULL);

	for(int y = 0; y < m_lHeight; y++)
		file.Read(m_Data[y],sizeof(T) * m_lWidth);

	return S_OK;
}

#endif//_ZEPHYR_GAMEENGINE_H