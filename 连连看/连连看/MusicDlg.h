#pragma once


// CMusicDlg �Ի���

class CMusicDlg : public CDialog
{
	DECLARE_DYNAMIC(CMusicDlg)

public:
	CMusicDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMusicDlg();

// �Ի�������
	//enum { IDD = IDD_MUSICDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedOk();
};


