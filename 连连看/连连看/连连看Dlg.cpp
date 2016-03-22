
// ������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������.h"
#include "������Dlg.h"
#include "afxdialogex.h"
#include "MusicDlg.h"
#include "mmsystem.h"				//��������ͷ�ļ�
#pragma comment(lib,"winmm.lib")	//��������ͷ�ļ���


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
	set = 0; //�ж�����Ƿ���Ҫ�������
	back.imageSource=IDB_BITMAP1; //��ʼ������ͼƬΪ��ʼͼƬ
	back.backSwitch=1;
	MusicSelection::music_type = _IDR_WAVE1;//��ʼ������
	PlaySound(MusicSelection::music_type,AfxGetInstanceHandle(),SND_RESOURCE | SND_ASYNC | SND_LOOP);//����Ĭ�ϱ�������

}

void C������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
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
	//���뱳��ͼƬ
	CPaintDC   dc(this);   
    CRect   rect;   
    GetClientRect(&rect);   
    CDC   dcMem;   
    dcMem.CreateCompatibleDC(&dc);   
    CBitmap   bmpBackground;   
    bmpBackground.LoadBitmap(back.imageSource);   //IDB_BITMAP1��ͼ��Ӧ��ID
                  
    BITMAP   bitmap;   
    bmpBackground.GetBitmap(&bitmap);   
    CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
    dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
    bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
//HCURSOR C������Dlg::OnQueryDragIcon()
//{
//	return static_cast<HCURSOR>(m_hIcon);
//}


void C������Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(::MessageBox(this->m_hWnd, "ȷ��Ҫ�˳���","�����˳�",MB_YESNO) == IDYES)
	{
		back.imageSource = IDB_BITMAP4;
		Invalidate(true); 
		UpdateWindow(); 
		Sleep (500);
		PostQuitMessage(0);
	}

	
}



void C������Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	bool set_music = 0; //�ж��Ƿ����Ƶ����
	switch(back.backSwitch)	// �л�����
	{
		case 1:	//��ʼ����
			c.Init START_GAME;	//�����ʼ��Ϸ
			if (FIT)
			{
				back.backSwitch=3;					//���Ľ����ж�����
				back.imageSource=IDB_BITMAP3;		//��������ͼƬ
				Invalidate(true);					//��ʾ�½���
				UpdateWindow(); 
			}
			c.Init START_END;	//���������Ϸ
			if (FIT)
			{
				OnClose();
			}
			c.Init START_HELP;	//�������
			if (FIT)
			{	
				back.backSwitch=2;
				back.imageSource=IDB_BITMAP2;
				Invalidate(true); 
				UpdateWindow(); 
			}
			c.Init MUSIC;		//�����Ƶ
			if (FIT)
				set_music = 1;
			break;
		case 2:	//��������
			c.Init HELP_BACK;	//�������
			if (FIT)
			{
				back.backSwitch=1;
				back.imageSource = IDB_BITMAP1;
				Invalidate(true); 
				UpdateWindow(); 
			}
			c.Init MUSIC;		//�����Ƶ
			if (FIT)
				set_music = 1;
			break;
		case 3:	//��Ϸ����
			c.Init GAME_HELP;	//�������
			if (FIT)
			{
				back.backSwitch=2;
				back.imageSource = IDB_BITMAP2;
				Invalidate(true); 
				UpdateWindow(); 
			}
			c.Init GAME_BACK;	//�������
			if (FIT)
			{
				back.backSwitch=1;
				back.imageSource = IDB_BITMAP1;
				Invalidate(true); 
				UpdateWindow(); 
			}
			c.Init MUSIC;		//�������
			if (FIT)
				set_music = 1;
			break;
			
	}
	if (set_music)
	//����Ƶ����
	{
		set_music = 0; //��ԭ����
		dlg.DoModal();

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void C������Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//ָʾ���ָ������
	CString str;
	str.Format("%d,%d",point.x,point.y);
	SetWindowText(str);
	//�ж����λ��
	switch(back.backSwitch)
	{
		case 1:
			c.Init START_GAME;				//��ʼ	
			if (FIT)
			{
				set=1;
				SendMessage(WM_SETCURSOR,NULL,NULL);
			}
			else
			{
				c.Init START_HELP;			//����
				if (FIT)
				{
					set=1;
					SendMessage(WM_SETCURSOR,NULL,NULL);
				}
				else
				{
					c.Init START_END;		//����
					if (FIT)
					{
						set=1;
						SendMessage(WM_SETCURSOR,NULL,NULL);
					}
					else
					{
						c.Init MUSIC;		//��Ƶ
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
			c.Init HELP_BACK;				//����
			if (FIT)
			{
				set=1;
				SendMessage(WM_SETCURSOR,NULL,NULL);
			}
			else
			{
				c.Init MUSIC;				//��Ƶ
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
			c.Init GAME_HELP;				//����
			if (FIT)
			{
				set=1;
				SendMessage(WM_SETCURSOR,NULL,NULL);
			}
			else
			{
				c.Init GAME_BACK;			//����
				if (FIT)
				{
					set=1;
					SendMessage(WM_SETCURSOR,NULL,NULL);
				}
				else
				{
					c.Init MUSIC;			//��Ƶ
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





BOOL C������Dlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(set)
	{
		//��������ָ��
		SetCursor(LoadCursor(NULL,IDC_HAND)); 
		return true;
	}
	else
		return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
