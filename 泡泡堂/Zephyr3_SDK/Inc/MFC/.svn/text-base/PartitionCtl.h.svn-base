/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	MFC\PartitionCtl.h

							Describe:	MFC 分割窗口 控件支持

							Author:		赵洪松(xueren)

							CreateTime: 2003.10.10
							UpdateTime:
*/

#ifndef _ZEPHYR_MFC_PARTITION_CTRL_H
#define _ZEPHYR_MFC_PARTITION_CTRL_H

#include <MFC\CZWnd.h>
#include <Windows\WndBack.h>

#include <MFC\BaseDef.h>

const DWORD		WM_ZPARTITIONCTL_CHG	=	WM_USER + 3;

////////////////////////////////////////////////////////////////////////////////////////
// ZPartitionWnd

class ZPartitionCtl;

class ZEPHYR_MFC_API ZPartitionWnd : public CZWnd{
private:
	ZPartitionCtl		*m_PartitionCtl;
private:
	DECLARE_DYNAMIC(ZPartitionWnd)
public:
	ZPartitionWnd(HINSTANCE	hInst,ZGraph *pGraph);
	virtual ~ZPartitionWnd() { ; }

	inline void SetPartitionCtl(ZPartitionCtl *pPartitionCtl);
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

inline void ZPartitionWnd::SetPartitionCtl(ZPartitionCtl *pPartitionCtl)
{
	ZASSERT(pPartitionCtl != NULL);

	m_PartitionCtl = pPartitionCtl;
}

////////////////////////////////////////////////////////////////////////////////////////
// ZPartitionCtl

class ZEPHYR_MFC_API ZPartitionCtl : public CZWnd{
protected:
	bool			m_bVertical;

	long			m_lWndSize[2];	// 2窗口大小

	long			m_lMinSize[2];

	long			m_lOldPixel;

	ZWndBack_Ex2	*m_backWnd;

	long			m_wndSize;	// 控件大小

	bool			m_bPush;

	long			m_totalSize;	// 总大小

	ZPartitionWnd	*m_PartitionWnd[2];
private:
	DECLARE_DYNAMIC(ZPartitionCtl)
public:
	ZPartitionCtl(HINSTANCE	hInst,ZGraph *pGraph,const char *name);
	virtual ~ZPartitionCtl() { Release(); }

	void Release();

	virtual void Draw(RECT *rect);

	bool Create(const char *wndName,DWORD dwStyle,long size,CWnd *pParent,UINT nID,bool bVertical,long size1,long size2);

	void SetPartitionWnd(ZPartitionWnd *wnd1,ZPartitionWnd *wnd2);

	void Push(long x,long y);

	void UnPush(long x,long y);

	bool IsPush() { return m_bPush; }

	bool IsVertical() { return m_bVertical; }

	inline ZPartitionWnd *GetPartitionWnd(int index);

	inline long GetWndSize(int index);

	void SetTotalSize(long size);

	void SetLimitMinSize(long size1,long size2);
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

inline ZPartitionWnd *ZPartitionCtl::GetPartitionWnd(int index)
{
	ZASSERT(index == 0 || index == 1);

	return m_PartitionWnd[index];
}

inline long ZPartitionCtl::GetWndSize(int index)
{
	ZASSERT(index == 0 || index == 1);

	return m_lWndSize[index];
}

#endif//_ZEPHYR_MFC_PARTITION_CTRL_H