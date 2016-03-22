
// ������Dlg.h : ͷ�ļ�
//

#pragma once
#include "background.h"
#include "Coordinate.h"
#include "musicdlg.h"
#include "musicselection.h"



// C������Dlg �Ի���
class C������Dlg : public CDialogEx
{
// ����
public:
	friend class CMusicDlg;
public:
	C������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
//	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEnd();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
private:
	BackGround back;
	Coordinate c;
	bool set;			//����ָ����״�任
	CMusicDlg dlg;		//��Ƶ����
};
