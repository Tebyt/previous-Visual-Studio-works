/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\MapLayer_TileLand.h

							Describe:	游戏引擎 Map 部分

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.12
							UpdateTime:
*/

#ifndef _ZEPHYR_GAMEENGINE_MAPLAYER_TILELAND_H
#define _ZEPHYR_GAMEENGINE_MAPLAYER_TILELAND_H

#include <GameEngine\MapLayer.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZGameMapLayer_TileLand

const BYTE	_LT	=	8;
const BYTE	_TR	=	4;
const BYTE	_RB	=	1;
const BYTE	_BL	=	2;

template<class T>
class ZGameMapLayer_TileLand : public ZGameMapLayer_Tile<T>{
protected:
	ZGameMapLayer_Tile<T>	m_dataLayer;
public:
	// 构造函数
	inline ZGameMapLayer_TileLand(const char *name,DWORD state);
	// 析构函数
	~ZGameMapLayer_TileLand() { Release(); }

	// 初始化
	virtual HRESULT Init(long w,long h);

	// 设置 (x,y) 坐标的数据
	virtual void SetData(long x,long y,DWORD dat);

	// 资源释放
	void Release();
protected:
	// 根据 属性层 更新 显示层
	// 仅更新 (x,y) 坐标周围 9 个位置
	void Update(long x,long y);

	// 根据 属性层 更新 显示层
	// 更新全部
	void Update();

	// 确定 (x,y) 的实际显示块
	BYTE Make(long x,long y);

	// 储存数据到文件
	// 注意 -	文件应该是已经打开的
	virtual HRESULT SaveLayerData(ZFile &file) { return m_dataLayer.SaveLayerData(file); }

	// 从文件读取数据
	// 注意 -	文件应该是已经打开的
	virtual HRESULT LoadLayerData(ZFile &file);
};

// 构造函数
template<class T>
inline ZGameMapLayer_TileLand<T>::ZGameMapLayer_TileLand(const char *name,DWORD state) 
	: ZGameMapLayer_Tile<T>(name,state) 
	, m_dataLayer("",state)
{
	;
}

// 资源释放
template<class T>
void ZGameMapLayer_TileLand<T>::Release()
{
	m_dataLayer.Release();

	ZGameMapLayer_Tile<T>::Release();
}

// 初始化
template<class T>
HRESULT ZGameMapLayer_TileLand<T>::Init(long w,long h)
{
	ZGameMapLayer_Tile<T>::Init(w,h);

	m_dataLayer.Init(w,h);

	return S_OK;
}

// 设置 (x,y) 坐标的数据
template<class T>
void ZGameMapLayer_TileLand<T>::SetData(long x,long y,DWORD dat) 
{
	ZASSERT(x >= 0 && x < m_dataLayer.GetWidth());
	ZASSERT(y >= 0 && y < m_dataLayer.GetHeight());

	m_dataLayer.SetData(x,y,dat);

	Update(x,y);
}

// 根据 属性层 更新 显示层
// 仅更新 (x,y) 坐标周围 9 个位置
template<class T>
void ZGameMapLayer_TileLand<T>::Update(long x,long y)
{
	ZASSERT(x >= 0 && x < m_dataLayer.GetWidth());
	ZASSERT(y >= 0 && y < m_dataLayer.GetHeight());

	T src = (T)m_dataLayer.GetData(x,y);

	if(y > 0)
	{
		if(x > 0 && m_dataLayer.GetData(x - 1,y - 1))
			ZGameMapLayer_Tile<T>::SetData(x - 1,y - 1,src + Make(x - 1, y - 1));

		if(x < m_dataLayer.GetWidth() - 1 && m_dataLayer.GetData(x + 1,y - 1))
			ZGameMapLayer_Tile<T>::SetData(x + 1,y - 1,src + Make(x + 1, y - 1));
		
		if(m_dataLayer.GetData(x,y - 1))
			ZGameMapLayer_Tile<T>::SetData(x,y - 1,src + Make(x, y - 1));
	}

	if(y < m_dataLayer.GetHeight() - 1)
	{
		if(x > 0 && m_dataLayer.GetData(x - 1,y + 1))
			ZGameMapLayer_Tile<T>::SetData(x - 1,y + 1,src + Make(x - 1, y + 1));

		if(x < m_dataLayer.GetWidth() - 1 && m_dataLayer.GetData(x + 1,y + 1))
			ZGameMapLayer_Tile<T>::SetData(x + 1,y + 1,src + Make(x + 1, y + 1));
		
		if(m_dataLayer.GetData(x,y + 1))
			ZGameMapLayer_Tile<T>::SetData(x,y + 1,src + Make(x, y + 1));
	}

	if(x > 0 && m_dataLayer.GetData(x - 1,y))
		ZGameMapLayer_Tile<T>::SetData(x - 1,y,src + Make(x - 1, y));

	if(x < m_dataLayer.GetWidth() - 1 && m_dataLayer.GetData(x + 1,y))
		ZGameMapLayer_Tile<T>::SetData(x + 1,y,src + Make(x + 1, y));
		
	if(m_dataLayer.GetData(x,y))
		ZGameMapLayer_Tile<T>::SetData(x,y,src + Make(x, y));
}

// 根据 属性层 更新 显示层
// 更新全部
template<class T>
void ZGameMapLayer_TileLand<T>::Update()
{
	for(int y = 0; y < GetHeight(); y++)
	{
		for(int x = 0; x < GetWidth(); x++)
			ZGameMapLayer_Tile<T>::SetData(x,y,m_dataLayer.GetData(x,y) + Make(x, y));
	}
}

// 确定 (x,y) 的实际显示块
template<class T>
BYTE ZGameMapLayer_TileLand<T>::Make(long x,long y)
{
	ZASSERT(x >= 0 && x < m_dataLayer.GetWidth());
	ZASSERT(y >= 0 && y < m_dataLayer.GetHeight());

	T src = (T)m_dataLayer.GetData(x,y);

	if(src == 0)
		return 0;

	BYTE dst = 0;
	int len_x = 0;
	int len = 0;

	if(y > 0)
	{
		if(x > 0 && m_dataLayer.GetData(x - 1, y - 1) == src && m_dataLayer.GetData(x, y - 1) == src && m_dataLayer.GetData(x - 1, y) == src)
			dst |= _LT;
		
		if(x < m_dataLayer.GetWidth() - 1 && m_dataLayer.GetData(x + 1, y - 1) == src && m_dataLayer.GetData(x, y - 1) == src && m_dataLayer.GetData(x + 1, y) == src)
			dst |= _TR;
	}
	
	if(y < m_dataLayer.GetHeight() - 1)
	{
		if(x > 0 && m_dataLayer.GetData(x - 1, y + 1) == src && m_dataLayer.GetData(x - 1, y) == src && m_dataLayer.GetData(x, y + 1) == src)
			dst |= _BL;
		
		if(x < m_dataLayer.GetWidth() - 1 && m_dataLayer.GetData(x + 1, y + 1) == src && m_dataLayer.GetData(x + 1, y) == src && m_dataLayer.GetData(x, y + 1) == src)
			dst |= _RB;
	}

	return dst;
}

// 从文件读取数据
// 注意 -	文件应该是已经打开的
template<class T>
HRESULT ZGameMapLayer_TileLand<T>::LoadLayerData(ZFile &file)
{
	m_dataLayer.LoadLayerData(file);

	Update();

	return S_OK;
}

#endif//_ZEPHYR_GAMEENGINE_MAPLAYER_TILELAND_H