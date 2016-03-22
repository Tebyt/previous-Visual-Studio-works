/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZArea.h

							Describe:	区域 控制

							Author:		赵洪松(xueren)

							CreateTime: 2003.10.23
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_AREA_H
#define _ZEPHYR_GRAPH_AREA_H

#include <ZState.h>
#include <ZLink.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZAreaData

const BYTE	ZAREADATA_STATE_HIDE	=	0x01;

class ZEPHYR_API ZAreaData{
	union _Data{
		void	*pVoid;
		DWORD	dwData;
	};
public:
	// 构造函数
	inline ZAreaData();
	// 析构函数
	~ZAreaData() {}

	// 是否隐藏
	bool IsHide() { return m_bState.Has(ZAREADATA_STATE_HIDE); }
	// 隐藏
	void Hide() { m_bState += ZAREADATA_STATE_HIDE; }

	// 设置数据，DWORD
	void SetData(DWORD dwData) { m_Data.dwData = dwData; }
	// 设置数据，指针
	void SetData(void *pVoid) { m_Data.pVoid = pVoid; }

	// 获取数据，DWORD
	DWORD GetData_DWord() { return m_Data.dwData; }
	// 获取数据，指针
	void *GetData_pVoid() { return m_Data.pVoid; }

	// 设置属性
	void SetState(BYTE bState) { m_bState = bState; }
	// 获取属性
	BYTE GetState() { return m_bState.Get(); }

	// 设置矩形
	void SetRect(RECT &rect) { memcpy(&m_Rect,&rect,sizeof(rect)); }
	// 获取矩形
	RECT *GetRect() { return &m_Rect; }

	// 赋值
	void Equ(ZAreaData &dat);
private:
	RECT			m_Rect;
	_Data			m_Data;
	ZState_Byte		m_bState;
};

// 构造函数
inline ZAreaData::ZAreaData()
{
	m_Data.dwData = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZArea

// 切分 AreaData 函数使用的方向参数
const BYTE	ZAREA_CUT_DIR_LT		=	0;
const BYTE	ZAREA_CUT_DIR_RT		=	1;
const BYTE	ZAREA_CUT_DIR_LB		=	2;
const BYTE	ZAREA_CUT_DIR_RB		=	3;

class ZEPHYR_API ZArea{
	typedef ZDLinkEx<ZAreaData,4,4>	_AreaLink;
public:
	// 构造函数
	inline ZArea();
	// 析构函数
	~ZArea() { Release(); }

	// 增加区域
	void Add(ZArea &area);
	// 增加矩形区域
	void Add(ZAreaData &dat);
	// 增加矩形区域
	void Add(RECT &rect,DWORD dwData,BYTE bState);
	// 增加矩形区域
	void Add(RECT &rect,void *pVoid,BYTE bState);

	// 减少
	void Sub(ZArea &area);
	// 减少矩形
	void Sub(RECT &rect);

	// 清空
	void Clear() { m_Link.Clear(); }
	// 是否为空
	bool IsEmpty() { return m_Link.GetUsed() == 0; }

	// 资源释放
	void Release();

	// 遍历
	void GetData(ZAreaData* &dat,void* &index) { m_Link.GetData(dat,index); }
private:
	// 插入
	ZAreaData *Insert(RECT &rect,DWORD dwData,BYTE bState);
	// 插入
	ZAreaData *Insert(RECT &rect,void *pVoid,BYTE bState);
	// 插入
	ZAreaData *Insert(ZAreaData &dat);
	// 插入
	void Insert(ZArea &area);

	// 切分AreaData
	bool CutArea(void* &index,ZAreaData* &dat,long x,long y,BYTE dir);
	// 切分AreaData
	bool CutArea_X(void* &index,ZAreaData* &dat,long x,bool bLeft);
	// 切分AreaData
	bool CutArea_Y(void* &index,ZAreaData* &dat,long y,bool bTop);

	bool IsInRect(RECT &dst,RECT &src);

	bool IsInRect(RECT &dst,long x,long y,long dx,long dy);

	// 调试输出
	void DebugLink();

	// 获取运算需要的临时区域
	ZArea *GetTmpArea();
	// 释放临时区域内存
	void ReleaseTmpArea();
private:
	_AreaLink	m_Link;
	ZArea		*m_pTmp;
};

// 构造函数
inline ZArea::ZArea()
{
	m_pTmp = NULL;
}

#endif//_ZEPHYR_GRAPH_AREA_H