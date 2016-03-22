/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	MFC\DlgSprView.h

							Describe:	MFC 显示 spr 的Dlg

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.05
							UpdateTime:
*/

#ifndef _ZEPHYR_MFC_DLGSPRVIEW_H
#define _ZEPHYR_MFC_DLGSPRVIEW_H

#include <Graph\Ani.h>
#include <MFC\CZDialog.h>

#include <string>

#include <MFC\BaseDef.h>

////////////////////////////////////////////////////////////////////////////////////
// CZDlgSprView

class ZEPHYR_MFC_API CZDlgSprView : public CZDialog
{
	DECLARE_DYNAMIC(CZDlgSprView)
protected:
	LPZSprite	m_spr;
	std::string	m_strName;
public:
	// 构造函数
	CZDlgSprView(UINT ID,CWnd *parent,HINSTANCE hInst,const char *name);
	// 析构函数
	virtual ~CZDlgSprView() { Release(); }

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
};

#endif//_ZEPHYR_MFC_DLGSPRVIEW_H