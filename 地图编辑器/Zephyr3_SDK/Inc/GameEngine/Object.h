/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\Object.h

							Describe:	��Ϸ���� Object ����

							Author:		�Ժ���(xueren)

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
	// ���캯��
	ZGameObject() {}
	// ��������
	~ZGameObject() {}

	// ��ʾ
	virtual void Draw(ZSprite &dst,long x,long y,long w,long h) = 0;
	// ��ʾ
	virtual void Draw(ZSprite &dst,long x,long y) = 0;
	// ��ʾ
	virtual void Draw(long x,long y) = 0;

	// ��ÿ��
	virtual long GetWidth() = 0;
	// ��ø߶�
	virtual long GetHeight() = 0;
	// ��� Tile ��С
	virtual int GetRectTileSize() { return 0; }
	// ��� ��ȣ���TileΪ��λ
	virtual int GetWidth_Tile() { return 0; }
	// ��� �߶ȣ���TileΪ��λ
	virtual int GetHeight_Tile() { return 0; }

	// ����Tile��Ϣ
	virtual void SetTileData(int x,int y,DWORD dat) { ; }
	// ��ȡTile��Ϣ
	virtual DWORD GetTileData(int x,int y) { return 0; }

	// �Ƿ��������
	bool IsAni() { return m_dwState.Has(ZGAMEOBJECT_STATE_ANI); }
	// �Ƿ����TileData
	bool HasTileData() { return m_dwState.Has(ZGAMEOBJECT_STATE_TILEDATA); }

	// ���� .obj �ļ�
	virtual HRESULT Save(const char *name,void *param) = 0;
protected:
	// ��ȡ
	virtual HRESULT Load(ZFile &file,ZGraph *pGraph) = 0;
};

typedef ZGameObject *	LPZGameObject;

///////////////////////////////////////////////////////////////////////////////////////////////
// ZGameObject_Ani

class ZEPHYR_API ZGameObject_Ani : public ZGameObject{
protected:
	ZAni	*m_ani;
public:
	// ���캯��
	ZGameObject_Ani(ZFile &file,ZGraph *pGraph);
	// ���캯��
	// �Ƕ�ȡʽ�Ĺ��죬bNotLoad ����Ϊ true
	ZGameObject_Ani(const char *aniName,ZGraph *pGraph,bool bNotLoad);
	// ���캯��
	// ������ʽ
	ZGameObject_Ani(const char *objName,const char *aniName);
	// ��������
	virtual ~ZGameObject_Ani() { Release(); }

	// ��ʾ
	virtual void Draw(ZSprite &dst,long x,long y,long w,long h);
	// ��ʾ
	virtual void Draw(ZSprite &dst,long x,long y);
	// ��ʾ
	virtual void Draw(long x,long y);

	// ��ÿ��
	virtual long GetWidth();
	// ��ø߶�
	virtual long GetHeight();

	// ���� .obj �ļ�
	virtual HRESULT Save(const char *name,void *param);
protected:
	// ��ȡ
	virtual HRESULT Load(ZFile &file,ZGraph *pGraph);
	// �ͷ���Դ
	void Release();
};

///////////////////////////////////////////////////////////////////////////////////////////////
// ZGameObject_Spr

class ZEPHYR_API ZGameObject_Spr : public ZGameObject{
protected:
	LPZSprite	m_spr;
public:
	// ���캯��
	ZGameObject_Spr(ZFile &file,ZGraph *pGraph);
	// ���캯��
	ZGameObject_Spr(const char *sprName,RECT &rect,ZGraph *pGraph);
	// ���캯��
	// ������ʽ
	ZGameObject_Spr(const char *objName,const char *sprName,RECT &rect);
	// ��������
	virtual ~ZGameObject_Spr() { Release(); }

	// ��ʾ
	virtual void Draw(ZSprite &dst,long x,long y,long w,long h);
	// ��ʾ
	virtual void Draw(ZSprite &dst,long x,long y);
	// ��ʾ
	virtual void Draw(long x,long y);

	// ��ÿ��
	virtual long GetWidth();
	// ��ø߶�
	virtual long GetHeight();

	// ���� .obj �ļ�
	virtual HRESULT Save(const char *name,void *param);
protected:
	// ���캯��
	ZGameObject_Spr() { m_spr = NULL; }
	// ��ȡ
	virtual HRESULT Load(ZFile &file,ZGraph *pGraph);
	// �ͷ���Դ
	void Release();
};

///////////////////////////////////////////////////////////////////////////////////////////////
// ZGameObjecManager

const DWORD LOADOBJ_STATE_NOTILEDATA	=	0x01;

class ZEPHYR_API ZGameObjecManager{
private:
	ZGraph	*m_Graph;
public:
	// ���캯��
	ZGameObjecManager(ZGraph *pGraph) { m_Graph = pGraph; }

	// ��ȡ
	LPZGameObject Load(const char *name,DWORD state);

	// �ͷ�Object
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