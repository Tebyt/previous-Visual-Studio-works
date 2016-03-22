
// 贪吃蛇Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "贪吃蛇.h"
#include "贪吃蛇Dlg.h"
#include "afxdialogex.h"
#include "Logic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int WIDTH=20; //棋盘格子宽度
const int ORIGIN_X=30; 
const int ORIGIN_Y=30; //棋盘起点
bool timerGo = true; //计时器状态
Logic l;
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


// C贪吃蛇Dlg 对话框




C贪吃蛇Dlg::C贪吃蛇Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C贪吃蛇Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C贪吃蛇Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C贪吃蛇Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// C贪吃蛇Dlg 消息处理程序

BOOL C贪吃蛇Dlg::OnInitDialog()
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
	SetTimer(1,100,NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C贪吃蛇Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C贪吃蛇Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		POINT point [2];
		for(int i=0;i<Logic::SCALE;i++)   //绘制列
		{
			point[0].x=ORIGIN_X+i*WIDTH;
			point[0].y=ORIGIN_Y;
			point[1].x=ORIGIN_X+i*WIDTH;
			point[1].y=ORIGIN_Y+WIDTH*(Logic::SCALE-1);
			dc.Polyline(point,2);
		}
		for(int j=0;j<Logic::SCALE;j++)  //绘制行
		{
			point[0].x=ORIGIN_X;
			point[0].y=ORIGIN_Y+WIDTH*j;
			point[1].x=ORIGIN_X+WIDTH*(Logic::SCALE-1);
			point[1].y=ORIGIN_Y+WIDTH*j;
			dc.Polyline(point,2);
		}
		for (int i=0;i<Logic::SCALE;i++){
			for (int j=0;j<Logic::SCALE;j++){
				if (l.GetStatus(i,j)==Logic::SNACK){
					dc.SelectStockObject(BLACK_BRUSH);  //绘制蛇
					dc.Ellipse(ORIGIN_X+WIDTH*(i-0.5),ORIGIN_Y+WIDTH*(j-0.5),ORIGIN_X+WIDTH*(i+0.5),ORIGIN_X+WIDTH*(j+0.5));
				}
				else if (l.GetStatus(i,j)==Logic::FOOD){
					dc.SelectStockObject(WHITE_BRUSH);  //绘制食物
					dc.Ellipse(ORIGIN_X+WIDTH*(i-0.5),ORIGIN_Y+WIDTH*(j-0.5),ORIGIN_X+WIDTH*(i+0.5),ORIGIN_X+WIDTH*(j+0.5));
				}

			}
		}
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C贪吃蛇Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C贪吃蛇Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar){
	case'W':
	case'w':
		l.ChangeDirection(Logic::UP);
		break;
	case'S':
	case's':
		l.ChangeDirection(Logic::DOWN);
		break;
	case'A':
	case'a':
		l.ChangeDirection(Logic::LEFT);
		break;
	case'D':
	case'd':
		l.ChangeDirection(Logic::RIGHT);
		break;
	}
	Invalidate();
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void C贪吃蛇Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent){
	case 1:
		if (timerGo){
			if (!l.Move()){
				timerGo = false;
				MessageBox(_T("You Die!"),_T("GAME OVER"),MB_OK);
				l.Init();
				timerGo=true;
			}
			Invalidate();
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
