
// 连连看Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "连连看.h"
#include "连连看Dlg.h"
#include "afxdialogex.h"
#include "MusicDlg.h"
#include "mmsystem.h"				//导入声音头文件
#pragma comment(lib,"winmm.lib")	//导入声音头文件库


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C连连看Dlg 对话框




C连连看Dlg::C连连看Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C连连看Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	set = 0; //判断鼠标是否需要变成手型
	back.imageSource=IDB_BITMAP1; //初始化背景图片为开始图片
	back.backSwitch=1;
	MusicSelection::music_type = _IDR_WAVE1;//初始化音乐
	PlaySound(MusicSelection::music_type,AfxGetInstanceHandle(),SND_RESOURCE | SND_ASYNC | SND_LOOP);//播放默认背景音乐

}

void C连连看Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C连连看Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// C连连看Dlg 消息处理程序

BOOL C连连看Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C连连看Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C连连看Dlg::OnPaint()
{
	//插入背景图片
	CPaintDC   dc(this);   
    CRect   rect;   
    GetClientRect(&rect);   
    CDC   dcMem;   
    dcMem.CreateCompatibleDC(&dc);   
    CBitmap   bmpBackground;   
    bmpBackground.LoadBitmap(back.imageSource);   //IDB_BITMAP1是图对应的ID
                  
    BITMAP   bitmap;   
    bmpBackground.GetBitmap(&bitmap);   
    CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
    dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
    bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
//HCURSOR C连连看Dlg::OnQueryDragIcon()
//{
//	return static_cast<HCURSOR>(m_hIcon);
//}


void C连连看Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(::MessageBox(this->m_hWnd, "确定要退出吗？","程序退出",MB_YESNO) == IDYES)
	{
		back.imageSource = IDB_BITMAP4;
		Invalidate(true); 
		UpdateWindow(); 
		Sleep (500);
		PostQuitMessage(0);
	}

	
}



void C连连看Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	bool set_music = 0; //判断是否打开音频窗口
	switch(back.backSwitch)	// 切换界面
	{
		case 1:	//开始界面
			c.Init START_GAME;	//点击开始游戏
			if (FIT)
			{
				back.backSwitch=3;					//更改界面判定程序
				back.imageSource=IDB_BITMAP3;		//更换背景图片
				Invalidate(true);					//显示新界面
				UpdateWindow(); 
			}
			c.Init START_END;	//点击结束游戏
			if (FIT)
			{
				OnClose();
			}
			c.Init START_HELP;	//点击帮助
			if (FIT)
			{	
				back.backSwitch=2;
				back.imageSource=IDB_BITMAP2;
				Invalidate(true); 
				UpdateWindow(); 
			}
			c.Init MUSIC;		//点击音频
			if (FIT)
				set_music = 1;
			break;
		case 2:	//帮助界面
			c.Init HELP_BACK;	//点击返回
			if (FIT)
			{
				back.backSwitch=1;
				back.imageSource = IDB_BITMAP1;
				Invalidate(true); 
				UpdateWindow(); 
			}
			c.Init MUSIC;		//点击音频
			if (FIT)
				set_music = 1;
			break;
		case 3:	//游戏界面
			c.Init GAME_HELP;	//点击帮助
			if (FIT)
			{
				back.backSwitch=2;
				back.imageSource = IDB_BITMAP2;
				Invalidate(true); 
				UpdateWindow(); 
			}
			c.Init GAME_BACK;	//点击返回
			if (FIT)
			{
				back.backSwitch=1;
				back.imageSource = IDB_BITMAP1;
				Invalidate(true); 
				UpdateWindow(); 
			}
			c.Init MUSIC;		//点击音乐
			if (FIT)
				set_music = 1;
			break;
			
	}
	if (set_music)
	//打开音频窗口
	{
		set_music = 0; //还原参数
		dlg.DoModal();

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void C连连看Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//指示鼠标指针坐标
	CString str;
	str.Format("%d,%d",point.x,point.y);
	SetWindowText(str);
	//判断鼠标位置
	switch(back.backSwitch)
	{
		case 1:
			c.Init START_GAME;				//开始	
			if (FIT)
			{
				set=1;
				SendMessage(WM_SETCURSOR,NULL,NULL);
			}
			else
			{
				c.Init START_HELP;			//帮助
				if (FIT)
				{
					set=1;
					SendMessage(WM_SETCURSOR,NULL,NULL);
				}
				else
				{
					c.Init START_END;		//结束
					if (FIT)
					{
						set=1;
						SendMessage(WM_SETCURSOR,NULL,NULL);
					}
					else
					{
						c.Init MUSIC;		//音频
						if(FIT)
						{
							set=1;
							SendMessage(WM_SETCURSOR,NULL,NULL);
						}
						else
						{
							set=0;
							SendMessage(WM_SETCURSOR,NULL,NULL);
						}
					}
				}
			}
			break;
		case 2:
			c.Init HELP_BACK;				//返回
			if (FIT)
			{
				set=1;
				SendMessage(WM_SETCURSOR,NULL,NULL);
			}
			else
			{
				c.Init MUSIC;				//音频
				if(FIT)
				{
					set=1;
					SendMessage(WM_SETCURSOR,NULL,NULL);
				}
				else
				{
					set=0;
					SendMessage(WM_SETCURSOR,NULL,NULL);
				}
			}
			break;
		case 3:
			c.Init GAME_HELP;				//帮助
			if (FIT)
			{
				set=1;
				SendMessage(WM_SETCURSOR,NULL,NULL);
			}
			else
			{
				c.Init GAME_BACK;			//返回
				if (FIT)
				{
					set=1;
					SendMessage(WM_SETCURSOR,NULL,NULL);
				}
				else
				{
					c.Init MUSIC;			//音频
					if(FIT)
					{
						set=1;
						SendMessage(WM_SETCURSOR,NULL,NULL);
					}
					else
					{
						set=0;
						SendMessage(WM_SETCURSOR,NULL,NULL);
					}
				}
			}
	}
}





BOOL C连连看Dlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(set)
	{
		//载入手型指针
		SetCursor(LoadCursor(NULL,IDC_HAND)); 
		return true;
	}
	else
		return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
