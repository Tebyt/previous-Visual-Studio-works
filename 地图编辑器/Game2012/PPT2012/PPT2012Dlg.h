// PPT2012Dlg.h : 头文件
//

#pragma once

#include <MFC\CZDialog.h>


// CPPT2012Dlg 对话框
class CPPT2012Dlg : public CZDialog
{
// 构造
public:
	CPPT2012Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PPT2012_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	//！ 窗口绘制函数
	virtual void Draw(RECT* rect);

	void Load();
	void Release();

	void Init();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//LPZSprite	m_sprBoy;
	LPZSprite	m_background;
	LPZSprite	m_stuff;
	LPZSprite	m_fengche;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
};
