#pragma once

#include <MFC\CZWnd.h>

#include <MFC\BaseDef.h>

class CZSplitterWnd;

// CZSplitterCtl
class ZEPHYR_MFC_API CZSplitterCtl : public CZWnd
{
public:
	enum{
		_HORIZONTAL = false,
		_VERTICAL = true
	};

	enum{
		_LEFT = 0,
		_RIGHT = 1
	};

	enum{
		_UP = 0,
		_DOWN = 1
	};

	enum{
		_MAX_WINDOWS	=	2
	};

private:
	friend class CZSplitterWnd;

	DECLARE_DYNAMIC(CZSplitterCtl)

public:
	CZSplitterCtl(ZGraph *pGraph,DWORD msgNotify);
	virtual ~CZSplitterCtl();

	CZSplitterWnd *GetSplitterWnd(int index) {
		ZASSERT(index == _LEFT || index == _RIGHT);

		return m_pSplitterWnd[index];
	}

	bool IsVertical() { return m_bVertical; }

	void Init(bool bVertical,long size1,long size2,CZSplitterWnd* pWnd1,CZSplitterWnd* pWnd2,long totalSize,long mySize,long limitSize1,long limitSize2);
protected:
	void Push(long x,long y);

	void UnPush(long x,long y);

	bool IsPush() { return m_bPush; }

	DECLARE_MESSAGE_MAP()
private:
	bool			m_bVertical;				// 方向

	long			m_lWndSize[_MAX_WINDOWS];	// 窗口大小
	long			m_lMinSize[_MAX_WINDOWS];	// 窗口的最小大小

	long			m_lOldPixel;				// 

	bool			m_bPush;

	long			m_wndSize;	// 控件大小

	DWORD			m_msgNotify;	// 通知父窗口大小改变的消息

	CZSplitterWnd*	m_pSplitterWnd[_MAX_WINDOWS];	// 子窗口

	long			m_totalSize;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};