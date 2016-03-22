/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\TileObject.h

							Describe:	游戏引擎 TileObject 部分

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.02
							UpdateTime:
*/

#ifndef _ZEPHYR_GAMEENGINE_TILEOBJECT_H
#define _ZEPHYR_GAMEENGINE_TILEOBJECT_H

#include <GameEngine\Object.h>
#include <GameEngine\Tile.h>
#include <GameEngine\MapLayer.h>

//////////////////////////////////////////////////////////////////////////////////////////
// ZGameObject_SprTile

struct OBJ_Head_NameRect_TileData{
	char	name[32];
	RECT	rect;
	int		tileSize;
	long	tileW;
	long	tileH;
};

template<class T>
class ZGameObject_SprTile : public ZGameObject_Spr, private ZGameMapLayer_Tile<T>{
protected:
	ZGameTileType	m_GameTile;
public:
	// 构造函数
	ZGameObject_SprTile(ZFile &file,ZGraph *pGraph);
	// 构造函数
	// 保存形式
	ZGameObject_SprTile(const char *objName,OBJ_Head_NameRect_TileData &param);

	// 保存 .obj 文件
	virtual HRESULT Save(const char *name,void *param);

	// 获得 Tile 大小
	virtual int GetRectTileSize() { return m_GameTile.GetRectTileSize(); }
	// 获得 宽度，以Tile为单位
	virtual int GetWidth_Tile() { return ZGameMapLayer_Tile<T>::m_Width; }
	// 获得 高度，以Tile为单位
	virtual int GetHeight_Tile() { return ZGameMapLayer_Tile<T>::m_Height; }

	// 设置Tile信息
	virtual void SetTileData(int x,int y,DWORD dat) { ZGameMapLayer_Tile<T>::SetData(x,y,dat); }
	// 获取Tile信息
	virtual DWORD GetTileData(int x,int y) { return ZGameMapLayer_Tile<T>::GetData(x,y); }
protected:
	// 读取
	virtual HRESULT Load(ZFile &file,ZGraph *pGraph);
};

// 构造函数
template<class T>
ZGameObject_SprTile<T>::ZGameObject_SprTile(ZFile &file,ZGraph *pGraph)
	: ZGameMapLayer_Tile<T>("\0",0)
{
	Load(file,pGraph);
}

// 构造函数
// 保存形式
template<class T>
ZGameObject_SprTile<T>::ZGameObject_SprTile(const char *objName,OBJ_Head_NameRect_TileData &param)
	: ZGameMapLayer_Tile<T>("\0",0)
{
	ZGameMapLayer_Tile<T>::Init(param.tileW,param.tileH);

	Save(objName,&param);
}

// 保存 .obj 文件
template<class T>
HRESULT ZGameObject_SprTile<T>::Save(const char *name,void *param)
{
	ZASSERT(name != NULL);
	ZASSERT(param != NULL);

	ZFile file;

	ZephyrFileHead zfh;
	OBJ_FileHead ofh;

	zfh.flag = OBJ_FILE_FLAG;
	zfh.size = sizeof(ofh);

	ofh.ver = OBJ_VER_1_0_SPR_STATE;

	if(file.Open(name,ZFILE_WRITE) != S_OK)
		return ZRet(E_FAIL,"ZGameObject_SprTile::Save(%s) open file fail!",name);

	file.Write(&zfh,sizeof(zfh));

	file.Write(&ofh,sizeof(ofh));

	file.Write(param,sizeof(OBJ_Head_NameRect_TileData));

	ZGameMapLayer_Tile<T>::SaveLayerData(file);

	file.Close();

	return S_OK;
}

// 读取
template<class T>
HRESULT ZGameObject_SprTile<T>::Load(ZFile &file,ZGraph *pGraph)
{
	OBJ_Head_NameRect_TileData nrth;

	ULONG len = file.Read(&nrth,sizeof(nrth));
	assert(len == sizeof(nrth));

	m_spr = pGraph->Load(nrth.name,ZEPHYRSPRITE_VMEM);
	assert(m_spr != NULL);

	m_spr->SetRect(nrth.rect);

	m_GameTile.SetRectTile(nrth.tileSize);

	ZGameMapLayer_Tile<T>::Init(nrth.tileW,nrth.tileH);

	ZGameObject_Spr::m_dwState += ZGAMEOBJECT_STATE_TILEDATA;

	return ZGameMapLayer_Tile<T>::LoadLayerData(file);
}

//////////////////////////////////////////////////////////////////////////////////////////
// ZGameObject_AniTile

template<class T>
class ZGameObject_AniTile : public ZGameObject_Ani, private ZGameMapLayer_Tile<T>{
	// 获得 Tile 大小
	virtual int GetRectTileSize() { return 0; }
protected:
	// 读取
	virtual HRESULT Load(ZFile &file,ZGraph *pGraph);
};

// 读取
template<class T>
HRESULT ZGameObject_AniTile<T>::Load(ZFile &file,ZGraph *pGraph)
{
	if(ZGameObject_Ani::Load(file,pGraph) != S_OK)
		return ZRet(E_FAIL,"ZGameObject_AniTile<T>::Load() : ZGameObject_Ani::Load() fail!");

	return ZGameMapLayer_Tile<T>::LoadLayerData(file);
}

#endif//_ZEPHYR_GAMEENGINE_TILEOBJECT_H