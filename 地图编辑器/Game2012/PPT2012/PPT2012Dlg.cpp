// PPT2012Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PPT2012.h"
#include "PPT2012Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum{
	HEIGHT = 10,WIDTH = 10  //定义长宽
};
int background[HEIGHT][WIDTH];
int stuff[HEIGHT][WIDTH];
bool changeBackground = true;
int changeIndex = 0;

//绘制坐标
int x_default = 40;
int y_default = 40; //xy偏移量
int x_edit = 500;  
int y_background = y_default;
int y_stuff = y_background + 50;
int y_fengche = y_stuff + 100;//编辑区域
int x_view = x_edit + 200;
int y_view = y_fengche; //预览区域

void CPPT2012Dlg::Init()
{
	for (int i =0;i<HEIGHT;i++)
		for (int j=0;j<WIDTH;j++){
			background[i][j]=0;
			stuff[i][j]=0;
		}
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPPT2012Dlg 对话框




CPPT2012Dlg::CPPT2012Dlg(CWnd* pParent /*=NULL*/)
	: CZDialog(CPPT2012Dlg::IDD, pParent, AfxGetApp()->m_hInstance)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPPT2012Dlg::DoDataExchange(CDataExchange* pDX)
{
	CZDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPPT2012Dlg, CZDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPPT2012Dlg 消息处理程序

BOOL CPPT2012Dlg::OnInitDialog()
{
	CZDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	SetTimer(10, 33, NULL);
	SetTimer(11, 500, NULL);
	Load();

	Init();

	FILE *file = fopen("ppt.map","r");
	fread(background,4,HEIGHT*WIDTH,file);
	fread(stuff,4,HEIGHT*WIDTH,file);
	fclose(file);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPPT2012Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CZDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPPT2012Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CZDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CPPT2012Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//！ 窗口绘制函数
void CPPT2012Dlg::Draw(RECT* rect)
{
	static int act = 0; 
	if(act < 19)	act++;
	else	act = 0;   //控制动画

	//设置背景颜色
	m_Graph->GetBackScreen()->Clear(_color16b_565(174, 239, 234));

	//绘制地图
	for (int i =0;i<HEIGHT;i++)
		for (int j=0;j<WIDTH;j++){
			int m = background[i][j];
			m_background->SetRect(m*40, 0, (m+1)*40, 40);
			m_background->Draw(x_default+i*40, y_default+j*40);
		}

	for (int i =0;i<HEIGHT;i++)
		for (int j=0;j<WIDTH;j++){
			int m = stuff[i][j];
			if (m>=1 && m!=9){
				m_stuff->SetRect((m-1)*40, 0, m*40, 67);
				m_stuff->Draw_ck(x_default+i*40, y_default+j*40-27);
			}
			else if (m==9){
				m_fengche->SetRect(120 * (act / 10), 0, 120 * (act / 10 + 1), 180);
				m_fengche->Draw_ck(x_default+i*40, y_default+j*40 - 140);
			}
		}

	//绘制编辑区域
	m_background->SetRect(0,0,280,40);
	m_background->Draw(x_edit,y_background);
	m_stuff->SetRect(0,0,320,67);
	m_stuff->Draw_ck(x_edit,y_stuff);
	m_fengche->SetRect(120 * (act / 10), 0, 120 * (act / 10 + 1), 180);
	m_fengche->Draw_ck(x_edit,y_fengche);

	//绘制预览区域
	if (changeBackground){
			m_background->SetRect(changeIndex*40,0,(changeIndex+1)*40,40);
			m_background->Draw(x_view,y_view);
	}
	else{
		if (changeIndex <= 7){
			m_stuff->SetRect(changeIndex*40,0,(changeIndex+1)*40,67);
			m_stuff->Draw_ck(x_view,y_view-27);
			}
		else {
			m_fengche->SetRect(120 * (act / 10), 0, 120 * (act / 10 + 1), 180);
			m_fengche->Draw_ck(x_view,y_view);
		}
	}

	/*m_sprBoy->SetRect(0, 64, 48, 128);
	m_sprBoy->Draw(0, 0);

	m_sprBoy->SetRect(0, 0, 48, 64);
	m_sprBoy->Draw_ck(100, 0);

	static int i = 0;

	m_sprBoy->SetRect(0, 128, 48, 192);
	m_sprBoy->Draw_alpha_ck(200, 0, i);

	if(i < 255)
		i++;
	else
		i = 0;

	static int j = 0;
	static int y = 0;

	m_sprBoy->SetRect(48 * (j / 10), 64, 48 * (j / 10 + 1), 128);
	m_sprBoy->Draw_ck(300, y);

	if(j < 59)
		j++;
	else
		j = 0;

	y++;*/

	Render(*rect);
}

void CPPT2012Dlg::Load()
{
	//! 载入图片，改变Load后面的第一个参数，参数为图片的路径及名字
	m_background = m_Graph->Load("pic\\TownGround.bmp", ZEPHYRSPRITE_3DDEVICE7);
	//! 载入图片，改变Load后面的第一个参数，参数为图片的路径及名字
	m_stuff = m_Graph->Load("pic\\new.bmp", ZEPHYRSPRITE_3DDEVICE7);
	//！ 设置图片特定位置的颜色为透明色
	m_stuff->SetColorKey(0, 0);
	//! 载入图片，改变Load后面的第一个参数，参数为图片的路径及名字
	m_fengche = m_Graph->Load("pic\\fengche.bmp", ZEPHYRSPRITE_3DDEVICE7);
	//！ 设置图片特定位置的颜色为透明色
	m_fengche->SetColorKey(0, 0);


	//! 载入图片，改变Load后面的第一个参数，参数为图片的路径及名字
	//m_sprBoy = m_Graph->Load("pic\\Role1.bmp", ZEPHYRSPRITE_3DDEVICE7);
	//！ 设置图片特定位置的颜色为透明色
	//m_sprBoy->SetColorKey(0, 0);
//
//	m_sprGround = m_Graph->Load("pic\\TownGround.bmp", ZEPHYRSPRITE_3DDEVICE7);
//	
//	m_sprBuild = m_Graph->Load("pic\\new.bmp", ZEPHYRSPRITE_3DDEVICE7);
//	m_sprBuild->SetColorKey(0, 0);
//
//	m_sprFC = m_Graph->Load("pic\\fengche.bmp", ZEPHYRSPRITE_3DDEVICE7);
//	m_sprFC->SetColorKey(0, 0);
//
//	m_sprBG = m_Graph->Load("pic\\BG.bmp", ZEPHYRSPRITE_3DDEVICE7);
}

void CPPT2012Dlg::Release()
{
	//m_sprBoy->Release();
	m_background->Release();
	m_stuff->Release();
	m_fengche->Release();
}


void CPPT2012Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 10)
	{
		RECT rect;

		GetClientRect(&rect);

		Draw(&rect);
	}
	else if(nIDEvent == 11)
	{
	}

	CZDialog::OnTimer(nIDEvent);
}

void CPPT2012Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//编辑区域地板
	if (point.x >=x_edit && point.x <=x_edit+280 && point.y>=y_background && point.y <=y_background +40){
		changeBackground = true;
		changeIndex = (point.x - x_edit)/40;
	}
	//编辑区域物品
	else if (point.x >=x_edit && point.x <=x_edit+320 && point.y>=y_stuff && point.y <=y_stuff +67){
		changeBackground = false;
		changeIndex = (point.x - x_edit)/40;
	}
	//编辑区域风车
	else if (point.x >=x_edit && point.x <=x_edit+120 && point.y>=y_fengche && point.y <=y_fengche + 180){
		changeBackground = false;
		changeIndex = 8;
	}
	//地图区域
	else if (point.x >=x_default && point.x <=x_default+40*WIDTH && point.y>=y_default && point.y <=y_default +40*HEIGHT){
		if (changeBackground == true){
			int i = (point.x-x_default)/40;
			int j = (point.y-y_default)/40;
			stuff[i][j] = 0;
			background[i][j] = changeIndex;
		}
		else 
			stuff[(point.x-x_default)/40][(point.y-y_default)/40] = changeIndex+1;
	}	
	CZDialog::OnLButtonDown(nFlags, point);
}


void CPPT2012Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CZDialog::OnMouseMove(nFlags, point);
}

void CPPT2012Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//// TODO: 在此添加消息处理程序代码和/或调用默认值

	CZDialog::OnLButtonUp(nFlags, point);
}

void CPPT2012Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//// TODO: 在此添加消息处理程序代码和/或调用默认值



	CZDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPPT2012Dlg::OnDestroy()
{
	FILE *file = fopen("ppt.map","w");
	fwrite(background,4,HEIGHT*WIDTH,file);
	fwrite(stuff,4,HEIGHT*WIDTH,file);
	fclose(file);
	CZDialog::OnDestroy();

	//// TODO: 在此处添加消息处理程序代码
}
