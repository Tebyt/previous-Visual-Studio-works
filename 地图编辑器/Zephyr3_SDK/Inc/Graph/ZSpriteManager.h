/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZSpriteManager.h

							Describe:	ZSprite 管理器

							Author:		赵洪松(xueren)

							CreateTime: 2003.08.30
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_ZSPRITE_MANAGE_H
#define _ZEPHYR_GRAPH_ZSPRITE_MANAGE_H

#include <Graph\ZSpriteData.h>

#include <set>
#include <list>

const DWORD	ZSPRITEMANAGER_MAX_FILENAME	=	128;

///////////////////////////////////////////////////////////////////////////////////////////////
// ZSpriteManager

class ZSpriteManager{
public:
	struct Node_Name{
		char			name[ZSPRITEMANAGER_MAX_FILENAME];
		LPSPRITE_DATA	spr;
		LPSPRITE_DATA	alpha;

		Node_Name() { spr = NULL, alpha = NULL, name[0] = '\0'; }
		Node_Name(const char *str) { strcpy(name,str); spr = NULL, alpha = NULL; }
	};

	struct Node_Spr{
		char			name[ZSPRITEMANAGER_MAX_FILENAME];
		LPSPRITE_DATA	spr;
		LPSPRITE_DATA	alpha;

		Node_Spr() { spr = NULL, alpha = NULL, name[0] = '\0'; }

		Node_Spr(const Node_Name& node) {
			strcpy(name, node.name);
			spr = node.spr;
			alpha = NULL;
		}
/*
		void operator = (const Node_Name& node) {
			strcpy(name, node.name);
			spr = node.spr;
		}
*/
	};

	typedef std::set<Node_Name>	List_Name;
	typedef std::set<Node_Spr>	List_Spr;

	typedef std::set<LPSPRITE_DATA>		_ListSprite;

	typedef std::list<LPSPRITE_DATA>	_ListReleaseSprite;
public:
	// 构造函数
	inline ZSpriteManager(ZGraph *pGraph);
	// 析构函数
	~ZSpriteManager() { Release(); }

	// 资源释放
	void Release();

	void AddSpr(LPSPRITE_DATA spr);

	bool DelSpr(LPSPRITE_DATA spr);

	// 读取文件
	LPSPRITE_DATA Load(LPSPRITE_DATA& pAlpha,const char *name,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	// 读取文件
	LPSPRITE_DATA LoadZPC(LPSPRITE_DATA& pAlpha,const char *name,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	// 读取文件
	LPSPRITE_DATA LoadJPG(LPSPRITE_DATA& pAlpha,const char *name,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	// 读取文件
	LPSPRITE_DATA LoadBMP(LPSPRITE_DATA& pAlpha,const char *name,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	// 读取文件
	LPSPRITE_DATA LoadTGA(LPSPRITE_DATA& pAlpha,const char *name,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	// 读取文件
	LPSPRITE_DATA LoadPNG(LPSPRITE_DATA& pAlpha,const char *name,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	// 读取文件
	LPSPRITE_DATA LoadGIF(LPSPRITE_DATA& pAlpha,const char *name,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	// 释放spr
	void ReleaseSprite(LPSPRITE_DATA spr);

	// 增加到 release sprite list
	void Add_ReleaseSpriteList(LPSPRITE_DATA spr);

	// 清空 release sprite list
	void Clear_ReleaseSpriteList();
protected:
	ZGraph*				m_Graph;
	List_Name			m_ListName;
	List_Spr			m_ListSpr;

	_ListReleaseSprite	m_lstReleaseSprite;

	_ListSprite			m_lstSprite;
};

// 构造函数
inline ZSpriteManager::ZSpriteManager(ZGraph *pGraph)
{
	m_Graph = pGraph;
}

inline bool operator < (const ZSpriteManager::Node_Name &left,const ZSpriteManager::Node_Name &right) { 
	return (strcmp(left.name, right.name) < 0); 
}

inline bool operator < (const ZSpriteManager::Node_Spr &left,const ZSpriteManager::Node_Spr &right) { 
	return left.spr < right.spr; 
}

#endif//_ZEPHYR_GRAPH_ZSPRITE_MANAGE_H