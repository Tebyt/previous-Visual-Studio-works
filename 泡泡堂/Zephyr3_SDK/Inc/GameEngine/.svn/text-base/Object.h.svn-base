/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\Object.h

							Describe:	游戏引擎 Object 部分

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.02
							UpdateTime:
*/

#ifndef _ZEPHYR_GAMEENGINE_OBJECT_H
#define _ZEPHYR_GAMEENGINE_OBJECT_H

#include <ZFile.h>
#include <Graph\Ani.h>

///////////////////////////////////////////////////////////////////////////////////////////////
// ZGameObject

const	DWORD	ZGAMEOBJECT_STATE_ANI		=	0x00000001;
const	DWORD	ZGAMEOBJECT_STATE_TILEDATA	=	0x00000002;

class ZEPHYR_API ZGameObject{
	friend class ZGameObjecManager;
protected:
	ZState<DWORD>		m_dwState;
public:
	// 构造函数
	ZGameObject() {}
	// 析构函数
	~ZGameObject() {}

	// 显示
	virtual void Draw(ZSprite &dst,long x,long y,long w,long h) = 0;
	// 显示
	virtual void Draw(ZSprite &dst,long x,long y) = 0;
	// 显示
	virtual void Draw(long x,long y) = 0;

	// 获得宽度
	virtual long GetWidth() = 0;
	// 获得高度
	virtual long GetHeight() = 0;
	// 获得 Tile 大小
	virtual int GetRectTileSize() { return 0; }
	// 获得 宽度，以Tile为单位
	virtual int GetWidth_Tile() { return 0; }
	// 获得 高度，以Tile为单位
	virtual int GetHeight_Tile() { return 0; }

	// 设置Tile信息
	virtual void SetTileData(int x,int y,DWORD dat) { ; }
	// 获取Tile信息
	virtual DWORD GetTileData(int x,int y) { return 0; }

	// 是否包含动画
	bool IsAni() { return m_dwState.Has(ZGAMEOBJECT_STATE_ANI); }
	// 是否包含TileData
	bool HasTileData() { return m_dwState.Has(ZGAMEOBJECT_STATE_TILEDATA); }

	// 保存 .obj 文件
	virtual HRESULT Save(const char *name,void *param) = 0;
protected:
	// 读取
	virtual HRESULT Load(ZFile &file,ZGraph *pGraph) = 0;
};

typedef ZGameObject *	LPZGameObject;

///////////////////////////////////////////////////////////////////////////////////////////////
// ZGameObject_Ani

class ZEPHYR_API ZGameObject_Ani : public ZGameObject{
protected:
	ZAni	*m_ani;
public:
	// 构造函数
	ZGameObject_Ani(ZFile &file,ZGraph *pGraph);
	// 构造函数
	// 非读取式的构造，bNotLoad 必须为 true
	ZGameObject_Ani(const char *aniName,ZGraph *pGraph,bool bNotLoad);
	// 构造函数
	// 保存形式
	ZGameObject_Ani(const char *objName,const char *aniName);
	// 析构函数
	virtual ~ZGameObject_Ani() { Release(); }

	// 显示
	virtual void Draw(ZSprite &dst,long x,long y,long w,long h);
	// 显示
	virtual void Draw(ZSprite &dst,long x,long y);
	// 显示
	virtual void Draw(long x,long y);

	// 获得宽度
	virtual long GetWidth();
	// 获得高度
	virtual long GetHeight();

	// 保存 .obj 文件
	virtual HRESULT Save(const char *name,void *param);
protected:
	// 读取
	virtual HRESULT Load(ZFile &file,ZGraph *pGraph);
	// 释放资源
	void Release();
};

///////////////////////////////////////////////////////////////////////////////////////////////
// ZGameObject_Spr

class ZEPHYR_API ZGameObject_Spr : public ZGameObject{
protected:
	LPZSprite	m_spr;
public:
	// 构造函数
	ZGameObject_Spr(ZFile &file,ZGraph *pGraph);
	// 构造函数
	ZGameObject_Spr(const char *sprName,RECT &rect,ZGraph *pGraph);
	// 构造函数
	// 保存形式
	ZGameObject_Spr(const char *objName,const char *sprName,RECT &rect);
	// 析构函数
	virtual ~ZGameObject_Spr() { Release(); }

	// 显示
	virtual void Draw(ZSprite &dst,long x,long y,long w,long h);
	// 显示
	virtual void Draw(ZSprite &dst,long x,long y);
	// 显示
	virtual void Draw(long x,long y);

	// 获得宽度
	virtual long GetWidth();
	// 获得高度
	virtual long GetHeight();

	// 保存 .obj 文件
	virtual HRESULT Save(const char *name,void *param);
protected:
	// 构造函数
	ZGameObject_Spr() { m_spr = NULL; }
	// 读取
	virtual HRESULT Load(ZFile &file,ZGraph *pGraph);
	// 释放资源
	void Release();
};

///////////////////////////////////////////////////////////////////////////////////////////////
// ZGameObjecManager

const DWORD LOADOBJ_STATE_NOTILEDATA	=	0x01;

class ZEPHYR_API ZGameObjecManager{
private:
	ZGraph	*m_Graph;
public:
	// 构造函数
	ZGameObjecManager(ZGraph *pGraph) { m_Graph = pGraph; }

	// 读取
	LPZGameObject Load(const char *name,DWORD state);

	// 释放Object
	void ReleaseObject(LPZGameObject &obj);
};

////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJ_FileHead{
	DWORD	ver;
};

struct OBJ_Head_OnlyName{
	char name[32];
};

struct OBJ_Head_Name_Rect{
	char name[32];
	RECT rect;
};

const DWORD	OBJ_VER_1_0_SPR			=	0x00010000;
const DWORD	OBJ_VER_1_0_SPR_STATE	=	0x00010001;
const DWORD	OBJ_VER_1_0_ANI			=	0x00010010;
const DWORD	OBJ_VER_1_0_ANI_STATE	=	0x00010011;

const DWORD	OBJ_FILE_FLAG	=	'.jbo';

#endif//_ZEPHYR_GAMEENGINE_OBJECT_H