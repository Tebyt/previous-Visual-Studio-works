
// ������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������.h"
#include "������Dlg.h"
#include "afxdialogex.h"
#include "Logic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int WIDTH=30; //���̿��
const int SCALE=10;
const int ORIGIN_X=30; 
const int ORIGIN_Y=30; //�������
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


// C������Dlg �Ի���




C������Dlg::C������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C������Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// C������Dlg ��Ϣ�������

BOOL C������Dlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C������Dlg::OnPaint()
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
		for(int i=0;i<10;i++)   //������
		{
			point[0].x=ORIGIN_X+i*WIDTH;
			point[0].y=ORIGIN_Y;
			point[1].x=ORIGIN_X+i*WIDTH;
			point[1].y=WIDTH*SCALE;
			dc.Polyline(point,2);
		}
		for(int j=0;j<10;j++)  //������
		{
			point[0].x=ORIGIN_X;
			point[0].y=ORIGIN_Y+WIDTH*j;
			point[1].x=WIDTH*SCALE;
			point[1].y=ORIGIN_Y+WIDTH*j;
			dc.Polyline(point,2);
		}
		for (int i=0;i<10;i++){
			for (int j=0;j<10;j++){
				if (l.GetStatus(i,j)==1)
					dc.SelectStockObject(WHITE_BRUSH);
				if (l.GetStatus(i,j)==2)
					dc.SelectStockObject(BLACK_BRUSH);
				if (l.GetStatus(i,j)==0)
					continue;
				dc.Ellipse(ORIGIN_X+WIDTH*(i-0.5),ORIGIN_Y+WIDTH*(j-0.5),ORIGIN_X+WIDTH*(i+0.5),ORIGIN_X+WIDTH*(j+0.5));
			}
		}
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C������Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	int x = (point.x-ORIGIN_X+WIDTH/2)/WIDTH;
	int y = (point.y-ORIGIN_Y+WIDTH/2)/WIDTH;
	if (l.Go(x,y)){
		Invalidate();
		UpdateWindow();
	}
	if (l.IsWin(x,y)){
		if ((l.total)%2==0)
			MessageBox(_T("White wins"),_T("WIN"),MB_OK);
		else
			MessageBox(_T("Black wins"),_T("WIN"),MB_OK);
		l.Init();
		Invalidate();
		UpdateWindow();
	}
	if (l.IsDraw()){
		MessageBox(_T("No one win"),_T("DRAW"),MB_OK);
		Invalidate();
		UpdateWindow();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
