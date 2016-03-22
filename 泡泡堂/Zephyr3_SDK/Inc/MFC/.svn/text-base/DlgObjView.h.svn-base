/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	MFC\DlgObjView.h

							Describe:	MFC 显示 obj 的Dlg

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.08
							UpdateTime:
*/

#ifndef _ZEPHYR_MFC_DLGOBJVIEW_H
#define _ZEPHYR_MFC_DLGOBJVIEW_H

#include <Graph\Ani.h>
#include <MFC\CZDialog.h>
#include <GameEngine\Object.h>

#include <string>

#include <MFC\BaseDef.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CZDlgObjView

const DWORD		DLGOBJVIEW_STATE_EDIT	=	0x01;

class ZEPHYR_MFC_API CZDlgObjView : public CZDialog
{
	DECLARE_DYNAMIC(CZDlgObjView)
protected:
	LPZGameObject		m_obj;
	std::string			m_strName;
	ZGameObjecManager	*m_objManager;
	ZState<DWORD>		m_dwState;
public:
	// 构造函数
	CZDlgObjView(UINT ID,CWnd *parent,HINSTANCE hInst,const char *name,DWORD state);
	// 析构函数
	virtual ~CZDlgObjView() { Release(); }

	// 读取文件
	void Load();

	// 初始化 Dlg
	virtual BOOL OnInitDialog();
	// 释放资源
	void Release();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
protected:
	// 画Tile信息
	void DrawTileData();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#endif//_ZEPHYR_MFC_DLGOBJVIEW_H