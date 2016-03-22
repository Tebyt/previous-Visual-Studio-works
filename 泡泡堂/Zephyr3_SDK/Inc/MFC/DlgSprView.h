/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	MFC\DlgSprView.h

							Describe:	MFC ��ʾ spr ��Dlg

							Author:		�Ժ���(xueren)

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
	// ���캯��
	CZDlgSprView(UINT ID,CWnd *parent,HINSTANCE hInst,const char *name);
	// ��������
	virtual ~CZDlgSprView() { Release(); }

	// ��ȡ�ļ�
	void Load();

	// ��ʼ�� Dlg
	virtual BOOL OnInitDialog();
	// �ͷ���Դ
	void Release();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};

#endif//_ZEPHYR_MFC_DLGSPRVIEW_H