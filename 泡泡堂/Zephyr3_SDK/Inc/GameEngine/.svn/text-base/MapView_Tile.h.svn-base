/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\MapView_Tile.cpp

							Describe:	游戏引擎 Map 显示部分

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.03
							UpdateTime:
*/

#ifndef _ZEPHYR_GAMEENGINE_MAPVIEW_TILE_H
#define _ZEPHYR_GAMEENGINE_MAPVIEW_TILE_H

#include <ZDebug.h>
#include <Graph\BaseDef.h>
#include <GameEngine\MapLayer.h>

/////////////////////////////////////////////////////////////////////////////////////
// ZGameMapView_Tile
// 说明：Tile 方式 地图显示

class ZEPHYR_API ZGameMapView_Tile{
protected:
	ZGraph		*m_Graph;		// ZGraph
	LPZSprite	*m_sprData;		// spr
	int			*m_tileNums;	// tile nums
	int			m_sprNums;		// spr nums
	int			m_tileSize;		// tile size
public:
	// 缺省构造函数
	inline ZGameMapView_Tile();
	~ZGameMapView_Tile() { Release(); }

	// 初始化
	HRESULT Init(const char *name);
	// 资源释放
	void Release();

	// 画地图层
	void Draw(ZSprite &dst,ZGameMapLayer &layer,RECT &screen,long xOff,long yOff,long xMap,long yMap,bool bColorKey = true);

	// 设置 Tile Size
	void SetTileSize(int size) { m_tileSize = size; }
	// 设置ZGraph
	inline void SetGraph(ZGraph *pGraph);

	// 地图编辑部分用
	// 获得第index幅源图的起始Tile
	DWORD GetBeginTileData(int index);

	// 地图编辑部分用
	// 获得第index幅源图的横向Tile数量
	long GetTileNums_W(int index);
protected:
	// 获得Tile所在的源数据索引
	int GetTileSrc(DWORD tile,long &x,long &y);
};

// 缺省构造函数
inline ZGameMapView_Tile::ZGameMapView_Tile()
{
	m_Graph = NULL;
	m_sprData = NULL;
	m_tileNums = NULL;
	m_sprNums = 0;
	m_tileSize = 16;
}

// 设置ZGraph
inline void ZGameMapView_Tile::SetGraph(ZGraph *pGraph)
{
	ZASSERT(pGraph != NULL);

	m_Graph = pGraph;
}

#endif//_ZEPHYR_GAMEENGINE_MAPVIEW_TILE_H