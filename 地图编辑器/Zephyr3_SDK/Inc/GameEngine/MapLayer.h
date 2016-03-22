/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\MapLayer.h

							Describe:	游戏引擎 Map 部分

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.02
							UpdateTime:
*/

#ifndef _ZEPHYR_GAMEENGINE_MAPLAYER_H
#define _ZEPHYR_GAMEENGINE_MAPLAYER_H

#include <ZFile.h>
#include <GameEngine\Tile.h>

const BYTE	ZGMAE_TILE_NULL			=	0;	//无特殊属性的Tile
const BYTE	ZGMAE_TILE_NOTMOVE		=	1;	//不可被占用的Tile
//const BYTE	ZGMAE_TILE_UPMOVE		=	2;	//该Tile有物件，但客户可以在物件上面行动

// 地图层属性
const DWORD	GAMEMAP_TILE			=	1;
const DWORD	GAMEMAP_TILE_COLORKEY	=	2;
const DWORD	GAMEMAP_OBJ				=	3;
const DWORD	GAMEMAP_OBJ_COVER		=	4;
const DWORD	GAMEMAP_OBJ_COVER_BLOCK	=	5;
const DWORD	GAMEMAP_STATE			=	6;
const DWORD GAMEMAP_TILE_LAND		=	7;

////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZGameMapLayer

const DWORD	ZGAMEMAPLAYER_NAME_LEN	=	32;

class ZEPHYR_API ZGameMapLayer{
	friend class ZGameMap;
protected:
	long	m_Width,m_Height;
	bool	m_bShow;

	char	m_strName[ZGAMEMAPLAYER_NAME_LEN];
	DWORD	m_State;
public:
	// 构造函数
	inline ZGameMapLayer(const char *name,DWORD state);
	// 析构函数
	virtual ~ZGameMapLayer() { ; }

	// 初始化
	virtual HRESULT Init(long w,long h) = 0;

	// 获得 (x,y) 坐标下每一格的数据
	virtual DWORD GetData(long x,long y) = 0;

	// 设置 (x,y) 坐标的数据
	virtual void SetData(long x,long y,DWORD dat) = 0;

	// 获得Tile数据大小
	virtual int GetTileDataLen() = 0;

	// 获得宽度
	long GetWidth() { return m_Width; }
	// 获得高度
	long GetHeight() { return m_Height; }

	// 设置是否显示
	void SetShow(bool bShow) { m_bShow = true; }

	// 是否显示该图层
	bool IsShow() { return m_bShow; }

	// 获得名字
	const char *GetName() { return m_strName; }

	// 获得类型属性
	DWORD GetState() { return m_State; }

	// 储存数据到文件
	// 注意 -	文件应该是已经打开的
	virtual HRESULT SaveLayerData(ZFile &file) = 0;

	// 从文件读取数据
	// 注意 -	文件应该是已经打开的
	virtual HRESULT LoadLayerData(ZFile &file) = 0;
};

// 构造函数
inline ZGameMapLayer::ZGameMapLayer(const char *name,DWORD state) 
{ 
	ZASSERT(name != NULL);

	m_Width = m_Height = 0;
	m_bShow = true;

	m_State = state;

#ifdef _DEBUG
	size_t len = strlen(name);
	assert(len < ZGAMEMAPLAYER_NAME_LEN);

	strcpy(m_strName,name);
#else
	strcpy(m_strName,name);
#endif
}

typedef ZGameMapLayer *		LPZGameMapLayer;

////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZGameMapLayer_Tile

template<class T>
class ZGameMapLayer_Tile : public ZGameMapLayer{
protected:
	ZGameTileData<T>	m_Data;
public:
	// 构造函数
	ZGameMapLayer_Tile(const char *name,DWORD state) : ZGameMapLayer(name,state) { ; }
	// 析构函数
	virtual ~ZGameMapLayer_Tile() { Release(); }

	// 初始化
	virtual HRESULT Init(long w,long h);

	// 获得 (x,y) 坐标下每一格的数据
	virtual DWORD GetData(long x,long y) { return m_Data.GetData(x,y); }

	// 设置 (x,y) 坐标的数据
	virtual void SetData(long x,long y,DWORD dat) { m_Data.SetData(x,y,dat); }

	// 获得Tile数据大小
	virtual int GetTileDataLen() { return sizeof(T); }

	// 释放资源
	void Release();

	// 储存数据到文件
	// 注意 -	文件应该是已经打开的
	virtual HRESULT SaveLayerData(ZFile &file) { return m_Data.SaveLayerData(file); }

	// 从文件读取数据
	// 注意 -	文件应该是已经打开的
	virtual HRESULT LoadLayerData(ZFile &file) { return m_Data.LoadLayerData(file); }
};

// 初始化
template<class T>
HRESULT ZGameMapLayer_Tile<T>::Init(long w,long h) 
{ 
	m_Width = w;
	m_Height = h;

	return m_Data.Init(w,h); 
}

// 释放资源
template<class T>
void ZGameMapLayer_Tile<T>::Release()
{
	m_Data.Release();

	m_Width = 0;

	m_Height = 0;
}

/*

template<class T>
class ZGameMapLayer_Tile : public ZGameMapLayer{
protected:
	T	**m_Data;
public:
	// 构造函数
	ZGameMapLayer_Tile(const char *name,DWORD state) : ZGameMapLayer(name,state) { m_Data = NULL; }
	// 析构函数
	virtual ~ZGameMapLayer_Tile() { Release(); }

	// 初始化
	virtual HRESULT Init(long w,long h);

	// 获得 (x,y) 坐标下每一格的数据
	virtual DWORD GetData(long x,long y);

	// 设置 (x,y) 坐标的数据
	virtual void SetData(long x,long y,DWORD dat);

	// 获得Tile数据大小
	virtual int GetTileDataLen() { return sizeof(T); }

	// 释放资源
	void Release();

	// 储存数据到文件
	// 注意 -	文件应该是已经打开的
	virtual HRESULT SaveLayerData(ZFile &file);

	// 从文件读取数据
	// 注意 -	文件应该是已经打开的
	virtual HRESULT LoadLayerData(ZFile &file);
};

// 初始化
template<class T>
HRESULT ZGameMapLayer_Tile<T>::Init(long w,long h)
{
	ZASSERT(m_Width == 0 && m_Height == 0);
	ZASSERT(w > 0 && h > 0);
	ZASSERT(m_Data == NULL);

	m_Width = w;
	m_Height = h;

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
DWORD ZGameMapLayer_Tile<T>::GetData(long x,long y)
{
	ZASSERT(m_Data != NULL);
	ZASSERT(x >= 0 && x < m_Width);
	ZASSERT(y >= 0 && y < m_Height);

	return m_Data[y][x];
}

// 设置 (x,y) 坐标的数据
template<class T>
void ZGameMapLayer_Tile<T>::SetData(long x,long y,DWORD dat)
{
	ZASSERT(m_Data != NULL);
	ZASSERT(x >= 0 && x < m_Width);
	ZASSERT(y >= 0 && y < m_Height);

	m_Data[y][x] = (T)dat;
}

// 释放资源
template<class T>
void ZGameMapLayer_Tile<T>::Release()
{
	if(m_Data != NULL)
	{
		free(m_Data);

		m_Data = NULL;
	}

	m_Width = m_Height = 0;
}

// 储存数据到文件
// 注意 -	文件应该是已经打开的
template<class T>
HRESULT ZGameMapLayer_Tile<T>::SaveLayerData(ZFile &file)
{
	ZASSERT(file.IsOpen());
	ZASSERT(m_Data != NULL);

	for(int y = 0; y < m_Height; y++)
		file.Write(m_Data[y],sizeof(T) * m_Width);

	return S_OK;
}

// 从文件读取数据
// 注意 -	文件应该是已经打开的
template<class T>
HRESULT ZGameMapLayer_Tile<T>::LoadLayerData(ZFile &file)
{
	ZASSERT(file.IsOpen());
	ZASSERT(m_Data != NULL);

	for(int y = 0; y < m_Height; y++)
		file.Read(m_Data[y],sizeof(T) * m_Width);

	return S_OK;
}
*/

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZGameMapLayer_WordTile

class ZEPHYR_API ZGameMapLayer_WordTile : public ZGameMapLayer{
protected:
	WORD	**m_Data;
public:
	// 构造函数
	ZGameMapLayer_WordTile() { m_Data = NULL; }
	// 析构函数
	virtual ~ZGameMapLayer_WordTile() { Release(); }

	// 初始化
	virtual HRESULT Init(long w,long h);

	// 获得 (x,y) 坐标下每一格的数据
	virtual DWORD GetData(long x,long y);

	// 设置 (x,y) 坐标的数据
	virtual void SetData(long x,long y,DWORD dat);

	// 释放资源
	void Release();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZGameMapLayer_DWordTile

class ZEPHYR_API ZGameMapLayer_DWordTile : public ZGameMapLayer{
protected:
	DWORD	**m_Data;
public:
	// 构造函数
	ZGameMapLayer_DWordTile() { m_Data = NULL; }
	// 析构函数
	virtual ~ZGameMapLayer_DWordTile() { Release(); }

	// 初始化
	virtual HRESULT Init(long w,long h);

	// 获得 (x,y) 坐标下每一格的数据
	virtual DWORD GetData(long x,long y);

	// 设置 (x,y) 坐标的数据
	virtual void SetData(long x,long y,DWORD dat);

	// 释放资源
	void Release();
};
*/
#endif//_ZEPHYR_GAMEENGINE_MAPLAYER_H