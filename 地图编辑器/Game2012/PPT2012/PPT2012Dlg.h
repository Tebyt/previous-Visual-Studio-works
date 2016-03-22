// PPT2012Dlg.h : ͷ�ļ�
//

#pragma once

#include <MFC\CZDialog.h>


// CPPT2012Dlg �Ի���
class CPPT2012Dlg : public CZDialog
{
// ����
public:
	CPPT2012Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PPT2012_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	//�� ���ڻ��ƺ���
	virtual void Draw(RECT* rect);

	void Load();
	void Release();

	void Init();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
