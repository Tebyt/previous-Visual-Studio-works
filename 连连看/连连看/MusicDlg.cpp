// MusicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "连连看.h"
#include "MusicDlg.h"
#include "afxdialogex.h"
#include "连连看Dlg.h"
#include "mmsystem.h"				//导入声音头文件
#pragma comment(lib,"winmm.lib")	//导入声音头文件库


// CMusicDlg 对话框

IMPLEMENT_DYNAMIC(CMusicDlg, CDialog)

CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicDlg::IDD, pParent)
{

}

CMusicDlg::~CMusicDlg()
{
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMusicDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CMusicDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMusicDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMusicDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDOK, &CMusicDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMusicDlg 消息处理程序


void CMusicDlg::OnBnClickedRadio1()
{
	if (MusicSelection::music_type != _IDR_WAVE1)
	{
		MusicSelection::music_type = _IDR_WAVE1;
		PlaySound(MusicSelection::music_type,AfxGetInstanceHandle(),SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}
}


void CMusicDlg::OnBnClickedRadio2()
{
	if (MusicSelection::music_type != _IDR_WAVE3)
	{
		MusicSelection::music_type = _IDR_WAVE3;
		PlaySound(MusicSelection::music_type,AfxGetInstanceHandle(),SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}
}


void CMusicDlg::OnBnClickedRadio3()
{
	if (MusicSelection::music_type != _IDR_WAVE2)
	{
		MusicSelection::music_type = _IDR_WAVE2;
		PlaySound(MusicSelection::music_type,AfxGetInstanceHandle(),SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}
}


void CMusicDlg::OnBnClickedOk()
{
	GetParent();
	CDialog::OnOK();
}
