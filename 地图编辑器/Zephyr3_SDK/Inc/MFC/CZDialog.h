/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	MFC\CZDialog.h

							Describe:	MFC CDialog ����չ֧��

							Author:		�Ժ���(xueren)

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
	DWORD				m_dwRenderTime;		//! ���һ��ˢ�µ�ʱ�䣨��������OnPaint��Ƶ�ʣ�

	bool				m_bAutoRender;		//! �Ƿ��Զ����ݴ����Ƿ�ǰ̨����֡
public:
	// ���캯����ģʽ�Ի���
	CZDialog(UINT id,CWnd *parent,HINSTANCE hInst);
	// ���캯������ģʽ�Ի���
	CZDialog(HINSTANCE hInst);
	// ��������
	virtual ~CZDialog() { Release(); }

	// ���ڻ��ƺ���
	virtual void Draw(RECT *rect);

	// ��ʼ�� Dlg
	virtual BOOL OnInitDialog();
	// �ͷ���Դ
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