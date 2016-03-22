
// ̰����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "̰����.h"
#include "̰����Dlg.h"
#include "afxdialogex.h"
#include "Logic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int WIDTH=20; //���̸��ӿ��
const int ORIGIN_X=30; 
const int ORIGIN_Y=30; //�������
bool timerGo = true; //��ʱ��״̬
Logic l;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// C̰����Dlg �Ի���




C̰����Dlg::C̰����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C̰����Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C̰����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C̰����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// C̰����Dlg ��Ϣ�������

BOOL C̰����Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(1,100,NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C̰����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C̰����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		POINT point [2];
		for(int i=0;i<Logic::SCALE;i++)   //������
		{
			point[0].x=ORIGIN_X+i*WIDTH;
			point[0].y=ORIGIN_Y;
			point[1].x=ORIGIN_X+i*WIDTH;
			point[1].y=ORIGIN_Y+WIDTH*(Logic::SCALE-1);
			dc.Polyline(point,2);
		}
		for(int j=0;j<Logic::SCALE;j++)  //������
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
					dc.SelectStockObject(BLACK_BRUSH);  //������
					dc.Ellipse(ORIGIN_X+WIDTH*(i-0.5),ORIGIN_Y+WIDTH*(j-0.5),ORIGIN_X+WIDTH*(i+0.5),ORIGIN_X+WIDTH*(j+0.5));
				}
				else if (l.GetStatus(i,j)==Logic::FOOD){
					dc.SelectStockObject(WHITE_BRUSH);  //����ʳ��
					dc.Ellipse(ORIGIN_X+WIDTH*(i-0.5),ORIGIN_Y+WIDTH*(j-0.5),ORIGIN_X+WIDTH*(i+0.5),ORIGIN_X+WIDTH*(j+0.5));
				}

			}
		}
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C̰����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C̰����Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void C̰����Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
