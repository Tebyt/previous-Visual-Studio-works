/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	MFC\CZDialog.h

							Describe:	MFC CDialog 的扩展支持

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.05
							UpdateTime:
*/

#ifndef _ZEPHYR_MFC_CDIALOG_H
#define _ZEPHYR_MFC_CDIALOG_H

#include <Graph\BaseDef.h>
#include <Windows\ZWnd.h>

#include <Graph\ZArea.h>

#include <MFC\BaseDef.h>

////////////////////////////////////////////////////////////////////////////////////
// CZDialog

const DWORD	CZDIALOG_STATE_ACTIVE		=	0x0001;
const DWORD	CZDIALOG_STATE_CLICKACTIVE	=	0x0002;

class ZEPHYR_MFC_API CZDialog : public CDialog
{
	DECLARE_DYNAMIC(CZDialog)
protected:
	HINSTANCE			m_hInst;

	ZGraph				*m_Graph;
	VirtualZephyrWnd	m_zWnd;
	bool				m_bModal;
	HFONT				m_hFont12;
	ZFont				*m_Font12;

	ZState_DWord		m_dwState;

	ZArea				m_Area;

	bool				m_bInit;

	int					m_iRenderNums;
	DWORD				m_dwRenderTime;		//! 最后一次刷新的时间（用来控制OnPaint的频率）

	bool				m_bAutoRender;		//! 是否自动根据窗口是否前台来跳帧
public:
	// 构造函数，模式对话框
	CZDialog(UINT id,CWnd *parent,HINSTANCE hInst);
	// 构造函数，无模式对话框
	CZDialog(HINSTANCE hInst);
	// 析构函数
	virtual ~CZDialog() { Release(); }

	// 窗口绘制函数
	virtual void Draw(RECT *rect);

	// 初始化 Dlg
	virtual BOOL OnInitDialog();
	// 释放资源
	void Release();

	void Render(RECT &rect);

	ZArea& GetArea() { return m_Area; }

	void SetAutoRender(bool bAutoRender) { 
		m_bAutoRender = bAutoRender;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
};

#endif//_ZEPHYR_MFC_CDIALOG_H