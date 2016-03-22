/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\Map.h

							Describe:	游戏引擎 Map 部分

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.02
							UpdateTime:
*/

#ifndef _ZEPHYR_GAMEENGINE_MAP_H
#define _ZEPHYR_GAMEENGINE_MAP_H

#include <GameEngine\MapLayer.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZGameMap

class ZEPHYR_API ZGameMap{
protected:
	LPZGameMapLayer		*m_Layer;
	int					m_LayerNums;
	int					m_tileSize;
public:
	// 构造函数
	inline ZGameMap();
	// 构造函数
	ZGameMap(const char *name,bool bMapFile);
	// 析构函数
	~ZGameMap() { Release(); }

	// 读取MAP文件
	HRESULT LoadMap(const char *name);
	// 读取层配置文件
	HRESULT LoadLayer(const char *name);

	// 保存MAP文件
	HRESULT SaveMap(const char *name);

	// 资源释放
	void Release();

	// 初始化，这个必须在LoadLayer()执行后执行
	HRESULT Init(long w,long h);

	// 获取图层
	inline LPZGameMapLayer GetLayer(int index);

	// 设置 Tile 大小
	void SetTileSize(int size) { m_tileSize = size; }
	// 获得 Tile 大小
	int GetTileSize() { return m_tileSize; }

	// 获得宽度
	inline long GetWidth();
	// 获得高度
	inline long GetHeight();
};

// 构造函数
inline ZGameMap::ZGameMap() 
{ 
	m_Layer = NULL; 
	m_LayerNums = 0;
	m_tileSize = 16;
}

// 获取图层
inline LPZGameMapLayer ZGameMap::GetLayer(int index)
{
	ZASSERT(index >= 0 && index < m_LayerNums);
	ZASSERT(m_Layer != NULL);
	ZASSERT(m_Layer[index] != NULL);

	return m_Layer[index];
}

// 获得宽度
inline long ZGameMap::GetWidth()
{
	ZASSERT(m_Layer != NULL);
	ZASSERT(m_Layer[0] != NULL);

	return m_Layer[0]->GetWidth();
}

// 获得高度
inline long ZGameMap::GetHeight()
{
	ZASSERT(m_Layer != NULL);
	ZASSERT(m_Layer[0] != NULL);

	return m_Layer[0]->GetHeight();
}

#endif//_ZEPHYR_GAMEENGINE_MAP_H