
// 连连看Dlg.h : 头文件
//

#pragma once
#include "background.h"
#include "Coordinate.h"
#include "musicdlg.h"
#include "musicselection.h"



// C连连看Dlg 对话框
class C连连看Dlg : public CDialogEx
{
// 构造
public:
	friend class CMusicDlg;
public:
	C连连看Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	bool set;			//用于指针形状变换
	CMusicDlg dlg;		//音频窗口
};
