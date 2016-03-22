/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\WndBack.h

							Describe:	窗口背景

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.24
							UpdateTime:
*/

#ifndef _ZEPHYR_WINDOWS_WNDBACK_H
#define _ZEPHYR_WINDOWS_WNDBACK_H

#include <Graph\ZGraph.h>

/////////////////////////////////////////////////////////////////////////////////////////
// ZWndBack

class ZEPHYR_API ZWndBack{
protected:
	LPZSprite	m_sprBack;
	ZGraph		*m_Graph;
public:
	// 构造函数
	inline ZWndBack(ZGraph *pGraph);
	// 析构函数
	virtual ~ZWndBack() { Release(); }

	// 读取外部配置脚本
	virtual void Load(const char *name) = 0;

	// 创建
	void Create(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	// 更新
	virtual void Update(long w,long h) = 0;
	// 获得数据
	LPZSprite GetData() { return m_sprBack; }

	// 获得 标题栏 高度
	virtual long GetTitleHeight() { return 0; }
	// 获得 左边框 宽度
	virtual long GetLBorderWidth() { return 0; }
	// 获得 右边框 宽度
	virtual long GetRBorderWidth() { return 0; }
	// 获得 下边框 高度
	virtual long GetDBorderHeight() { return 0; }

	// 获得 标题栏 高度
	virtual long GetTitleHeight_noColorKey() { return 0; }
	// 获得 左边框 宽度
	virtual long GetLBorderWidth_noColorKey() { return 0; }
	// 获得 右边框 宽度
	virtual long GetRBorderWidth_noColorKey() { return 0; }
	// 获得 下边框 高度
	virtual long GetDBorderHeight_noColorKey() { return 0; }
	// 资源释放
	virtual void Release();
protected:
	// 更新大小
	void Resize(long w,long h);
};

// 构造函数
inline ZWndBack::ZWndBack(ZGraph *pGraph) 
{ 
	ZASSERT(pGraph != NULL);

	m_sprBack = NULL; 

	m_Graph = pGraph;
}

/////////////////////////////////////////////////////////////////////////////////////////
// ZWndBack_Ex

class ZEPHYR_API ZWndBack_Ex : public ZWndBack{
protected:
	LPZSprite	m_sprSrc[9];
public:
	// 构造函数
	inline ZWndBack_Ex(ZGraph *pGraph,const char *name);
	// 析构函数
	virtual ~ZWndBack_Ex() { Release(); }

	// 读取外部配置脚本
	virtual void Load(const char *name);
	// 更新
	virtual void Update(long w,long h);
	// 获得 标题栏 高度
	virtual long GetTitleHeight();
	// 获得 左边框 宽度
	virtual long GetLBorderWidth();
	// 获得 右边框 宽度
	virtual long GetRBorderWidth();
	// 获得 下边框 高度
	virtual long GetDBorderHeight();

	// 获得 标题栏 高度
	virtual long GetTitleHeight_noColorKey();
	// 获得 左边框 宽度
	virtual long GetLBorderWidth_noColorKey();
	// 获得 右边框 宽度
	virtual long GetRBorderWidth_noColorKey();
	// 获得 下边框 高度
	virtual long GetDBorderHeight_noColorKey();

	// 资源释放
	virtual void Release();
};

inline ZWndBack_Ex::ZWndBack_Ex(ZGraph *pGraph,const char *name) : ZWndBack(pGraph)
{
	for(int i = 0; i < 9; i++)
		m_sprSrc[i] = NULL;

	Load(name);
}

/////////////////////////////////////////////////////////////////////////////////////////
// ZWndBack_Ex2

class ZEPHYR_API ZWndBack_Ex2 :public ZWndBack{
protected:
	LPZSprite	m_sprSrc;
public:
	// 构造函数
	inline ZWndBack_Ex2(ZGraph *pGraph,const char *name);
	// 析构函数
	virtual ~ZWndBack_Ex2() { Release(); }

	// 读取外部配置脚本
	virtual void Load(const char *name);
	// 更新
	virtual void Update(long w,long h);

	// 资源释放
	virtual void Release();
};

// 构造函数
inline ZWndBack_Ex2::ZWndBack_Ex2(ZGraph *pGraph,const char *name) : ZWndBack(pGraph)
{ 
	ZASSERT(pGraph != NULL);
	ZASSERT(name != NULL);

	m_sprSrc = NULL;

	Load(name);
}

#endif//_ZEPHYR_WINDOWS_WNDBACK_H