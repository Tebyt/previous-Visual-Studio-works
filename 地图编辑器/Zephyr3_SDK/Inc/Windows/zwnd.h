#ifndef ZEPHYR_WND_H
#define ZEPHYR_WND_H

#include <Zephyr.h>

#include <ZDebug.h>
#include <ZLink.h>
#include <ZTimer.h>
#include <ZState.h>
#include <Graph\ZGraphDef.h>

class ZephyrWnd;
//	+
	 class ZWndButton;
//	+
	 class ZWndEdit;
//	+
	 class ZWndComboBox;
//	+
//	 class ZWndListBox;
//	+
	 class ZWndScroll;

//////////////////////////////////////////////////////////////////////
//	��Ϣӳ��

typedef int (ZephyrWnd::*ZWndFunc)(DWORD,DWORD);

struct ZMessageFunc {
	DWORD id;
	ZWndFunc func;
};

#define ZDECLARE_MESSAGE_MAP()		\
public:		\
virtual const ZMessageFunc* GetMessageEntries() \
{ return messageEntries; }	\
static const ZMessageFunc messageEntries[];


#define ZBEGIN_MAP_MESSAGE_BASECLASS(thisclass)	\
const ZMessageFunc thisclass::messageEntries[]={	\
	{0,0},

#define ZBEGIN_MAP_MESSAGE(thisclass,baseclass)	\
const ZMessageFunc thisclass::messageEntries[]={	\
	{(DWORD)(baseclass::messageEntries),0},

#define ZMAP_MESSAGE(id,func) {id,(ZWndFunc)&func},

#define ZEND_MAP_MESSAGE() {0,0}};

//////////////////////////////////////////////////////////////////////
//	ZephyrWnd

const DWORD ZWND_STATE_HIDE				=	0x80000000;
const DWORD ZWND_STATE_ACTIVE			=	0x40000000;
const DWORD ZWND_STATE_DISABLE			=	0x20000000;

const DWORD	ZWND_STATE_BACK				=	0x01000000;		//��ͼ�Ĵ��ڱ���
const DWORD	ZWND_STATE_BACK_EX			=	0x03000000;		//9��ͼƴ��һ������
const DWORD	ZWND_STATE_BACK_EX2			=	0x05000000;		//1��������ͼ

const DWORD ZWND_STATE_BACK_COLORKEY	=	0x08000000;		//͸��ɫ�ķ�ʽ������
const DWORD ZWND_STATE_BACK_ALPHA50		=	0x10000000;		//��͸���ķ�ʽ������

const DWORD ZWND_STATE_BACK_ALPHA_CK	=	0x0c000000;		//��͸��ɫ�İ�͸����ʽ������

const DWORD	ZWND_STATE_INIT				=	0x00800000;


//------------------------------------------------------------------
//wnd spr
const int ZWND_SPR_NUMS				=	9;

const int ZWND_SPR_CORNER_TL		=	0;
const int ZWND_SPR_CORNER_TR		=	2;
const int ZWND_SPR_CORNER_BR		=	4;
const int ZWND_SPR_CORNER_BL		=	6;

const int ZWND_SPR_BORDER_T			=	1;
const int ZWND_SPR_BORDER_R			=	3;
const int ZWND_SPR_BORDER_B			=	5;
const int ZWND_SPR_BORDER_L			=	7;

const int ZWND_SPR_BODY				=	8;

class ZEPHYR_API ZephyrWnd{
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ZWndProc(ZephyrWnd *wnd,UINT message,WPARAM wParam, LPARAM lParam);

	typedef ZLink<ZephyrWnd,16,4> ChildLink;
protected:
	static HINSTANCE	m_hInst;
	static char			m_ClassName[];

	ZephyrWnd			*m_Parent;

	HWND				m_hWnd;					//HWND
	UINT				m_uID;					//ID

	ZGraph				*m_Graph;				//Graph
	RECT				m_Rect;					//���ڴ�С
	RECT				m_ClientRect;			//ʵ�ʴ��ڴ�С
	ZFont				*m_ZFont;				//ZFont

	ChildLink			*m_Child;				//Child List
	ZephyrWnd			*m_MouseIn_Child;		//Mouse In
	ZephyrWnd			*m_Catch_Child;			//Catch
	ZephyrWnd			*m_Focus_Child;
	ZephyrWnd			*m_Top_Child;

	ZState_DWord		m_dwState;				//State

	long				m_MouseX,m_MouseY;		//MouseX/Y

	LPZSprite			m_sprBackEx[ZWND_SPR_NUMS];
	LPZSprite			m_sprBackEx2;
	LPZSprite			m_sprWndBack;

	DWORD				m_dwLButtonDownTime;
public:
	ZephyrWnd();
	virtual ~ZephyrWnd() { Release(); }

	//��������
	HRESULT Create(const char *classname,const char *name,DWORD style,int x,int y,int w,int h,ZephyrWnd *parent,UINT nID);
	//��������
	HRESULT Create(const char *classname,const char *name,DWORD style,int x,int y,int w,int h,HWND parent,UINT nID);
	//��������
	HRESULT CreateEx(DWORD exstyle,const char *classname,const char *name,DWORD style,int x,int y,int w,int h,ZephyrWnd *parent,UINT nID);
	//��������
	HRESULT CreateEx(DWORD exstyle,const char *classname,const char *name,DWORD style,int x,int y,int w,int h,HWND parent,UINT nID);

	//��ʼ������
	static void Init(HINSTANCE hInstance);
	//ע�ᴰ����
	static ATOM RegisterWndClass(const char *classname,DWORD style,HICON icon,HCURSOR cursor,HBRUSH brush,const char *menuname);

	//����������
	virtual void Draw(RECT *pRect = NULL);
	//�����ڱ�������
	virtual void DrawWndBack(RECT *pRect = NULL);
	//�����ڲ���
	virtual void DrawWndItem(RECT *pRect = NULL);

	LPZSprite GetBackSpr() const { return m_sprWndBack; }

	//�жϵ�ǰ���Ƿ��ڴ����ڣ�����������ͨ��͸��ɫ������Ǿ��δ��ڣ�
	virtual bool IsIn(long x,long y);

	//����Ex���ڵı���������Ҫ m_sprBackEx ����
	virtual void DrawBackEx();
	//����Ex2���ڵı���������Ҫ m_sprBackEx ����
	virtual void DrawBackEx2();

	//��Դ�ͷ�
	void Release();

	// ����뿪����
	void MouseLeave();

//Set
	//����ZGraph�������ڳ�ʼ����ǰ���ã�
	inline void SetGraph(ZGraph *graph);
	//����ZFont����������õĻ�������ʹ��Graphȱʡ��������ʾ
	inline void SetZFont(ZFont *zfont);

//Get
	//��ô��ھ��
	HWND GetHandle() const { return m_hWnd; }
	//��õ�ǰ��ZFont
	ZFont *GetZFont() const { return m_ZFont; }
	//���Graph
	ZGraph *GetGraph() const { return m_Graph; }

	const char *GetClassName() { return m_ClassName; }

//rect
	//����Rect��һ������£���Create�����ڻ��Լ����øú���
	inline void SetRect(int x,int y,int w,int h);
	//���RECT
	RECT *GetRect() { return &m_Rect; }
	//���RECT���
	long GetWidth() { return m_Rect.right - m_Rect.left; }
	//���RECT�߶�
	long GetHeight() { return m_Rect.bottom - m_Rect.top; }
	//���ô��ڿ�������
	inline void SetClientArea(int x,int y,int w,int h);
	//��ȡ���ڿ�������
	RECT *GetClientArea() { return &m_ClientRect; }

	// �Ƿ����Ӵ�����
	bool IsInChild(long x,long y);

	ZephyrWnd* GetParent() { return m_Parent; }
//Sprite
	//����BACKEX״̬�µ�9��Spr
	void SetBackExSprite(LPZSprite lps,int index,RECT &rect,bool bColorKey);
	//����BACKEX2״̬�µ�Spr
	void SetBackEx2Sprite(LPZSprite lps,RECT &rect,bool bColorKey);
	//����BACK״̬�µ�Spr
	void SetBackSprite(LPZSprite lps,RECT &rect,bool bColorKey);
	//��������Spr
	void CreateWndBackSpr(long w,long h,DWORD flag);

	//�ı䴰�ڴ�С
	virtual void ChangeSize(long w,long h);

//State
	//����State
	void SetState(DWORD state) { m_dwState = state; }
	//����State
	void AddState(DWORD state) { m_dwState.Add(state); }
	//ȡ��State
	void SubState(DWORD state) { m_dwState.Sub(state); }
	//��ȡState
	DWORD GetState() { return m_dwState.Get(); }

	//���õ�ǰ����Ϊ���㴰��
	void SetTopWnd();
	//����childΪ���㴰��
	void SetTopChild(ZephyrWnd *child) { m_Top_Child = child; }

	//�Ƿ�״̬
	bool IsActive() { return m_dwState.Has(ZWND_STATE_ACTIVE); }
	//�Ƿ񲻿ɼ�״̬
	bool IsHide() { return m_dwState.Has(ZWND_STATE_HIDE); }

//show/draw
	//���ش���
	void HideWindow();
	//��ʾ����
	void ShowWindow() { m_dwState.Sub(ZWND_STATE_HIDE); }
	//�����Ӵ���
	void HideChild(ZephyrWnd *child);

	//�ƶ�������Ϊƫ��
	void Move(long xOff,long yOff);
	//�ƶ�������(x,y)
	void MoveTo(long x,long y) { Move(x-m_Rect.left,y-m_Rect.top); }

	//�Ƿ���RECT��
	inline bool IsInClient(long x,long y);

	//������ʹ�ô���
	void Disable() { m_dwState += ZWND_STATE_DISABLE; }
	//����ʹ��
	void Enable() { m_dwState -= ZWND_STATE_DISABLE; }

//child wnd
	//���child
	void AddToChild(ZephyrWnd* parent);
	//ɾ��child
	void DelToChild(ZephyrWnd* parent);

	//����Ӵ���
	void AddChild(ZephyrWnd* child);
	//ɾ���Ӵ���
	void DelChild(ZephyrWnd* child);

	//׽ס����
	void CatchChild(ZephyrWnd* child) { m_Catch_Child = child; }
	//���㴰��
	void FocusChild(ZephyrWnd* child) { m_Focus_Child = child; }

	//�Ƿ�����Ӵ���
	bool HasChild() const { return m_Child != NULL; }

//timer
	inline _zwndTimer* SetZTimer(ZThreadSystem *pThreadSystem,DWORD timerID,DWORD timer);
	inline void KillZTimer(_zwndTimer* &timer);

//protected:
	//message
	int OnDestroy(DWORD wParam,DWORD lParam);
	int OnMove(DWORD wParam,DWORD lParam);
	int OnSize(DWORD wParam,DWORD lParam);
	int OnPaint(DWORD wParam,DWORD lParam);
	int OnLButtonUp(DWORD wParam,DWORD lParam);
	int OnLButtonDown(DWORD wParam,DWORD lParam);
	int OnLButtonDblClk(DWORD wParam,DWORD lParam);
	int OnRButtonUp(DWORD wParam,DWORD lParam);
	int OnRButtonDown(DWORD wParam,DWORD lParam);
	int OnRButtonDblClk(DWORD wParam,DWORD lParam);
	int OnMouseMove(DWORD wParam,DWORD lParam);
	int OnActive(DWORD wParam,DWORD lParam);

protected:
	ZDECLARE_MESSAGE_MAP()
};

inline void ZephyrWnd::SetGraph(ZGraph *graph)
{
	ZASSERT(graph != NULL);

	m_Graph = graph;

	m_ZFont = m_Graph->GetDefaultFont();
}

inline void ZephyrWnd::SetRect(int x,int y,int w,int h)
{
	if(w == 0 || h == 0)
		return ;

	ZASSERT(w > 0 && h > 0);

	m_Rect.left = x;
	m_Rect.top = y;
	m_Rect.right = x + w;
	m_Rect.bottom = y + h;

//	MoveWindow(m_hWnd, x, y, w, h, true);
}

inline void ZephyrWnd::SetClientArea(int x,int y,int w,int h)
{
	ZASSERT(w > 0 && h > 0);

	m_ClientRect.left = x;
	m_ClientRect.top = y;
	m_ClientRect.right = x + w;
	m_ClientRect.bottom = y + h;
}

inline void ZephyrWnd::SetZFont(ZFont *zfont)
{
	ZASSERT(zfont != NULL);

	m_ZFont = zfont;
}

inline _zwndTimer* ZephyrWnd::SetZTimer(ZThreadSystem *pThreadSystem,DWORD timerID,DWORD timer)
{
	return ::SetZTimer(pThreadSystem,m_hWnd,timerID,timer);
}

inline void ZephyrWnd::KillZTimer(_zwndTimer* &timer)
{
	::KillZTimer(timer);
}

inline bool ZephyrWnd::IsInClient(long x,long y)
{
	return IsInRect(x,y,m_Rect);
}

//////////////////////////////////////////////////////////////////////
//	ZephyrMainWnd

class ZEPHYR_API ZephyrMainWnd : public ZephyrWnd{
protected:
	ZephyrWnd	*m_pActiveWnd;

	bool		m_bActive;
public:
	inline ZephyrMainWnd();
	virtual ~ZephyrMainWnd();

	//idle
	virtual int	OnIdle();

	void Release();

	HRESULT Render(RECT *pRect=NULL);
//run
	HRESULT MessageRun();
	HRESULT MessageRunIdle();

//message
	int OnPaint(DWORD wParam,DWORD lParam);
	int OnMove(DWORD wParam,DWORD lParam);
	int OnActivate(DWORD wParam,DWORD lParam);

protected:
	ZDECLARE_MESSAGE_MAP()
};

inline ZephyrMainWnd::ZephyrMainWnd()
{
	m_pActiveWnd = NULL;
}

#ifndef ZEPHYRFRAME_API
//////////////////////////////////////////////////////////////////////
//	ZephyrFrame

class ZEPHYR_API ZephyrFrame{
protected:
	ZGraph		*m_Graph;
	ZephyrWnd	*m_zWnd;
public:
	inline ZephyrFrame();
	virtual ~ZephyrFrame();

	inline void SetGraph(ZGraph* pGraph);

	virtual HRESULT Init(ZephyrWnd* pzWnd) = 0;

	virtual void Load() = 0;

	virtual void Draw(RECT* pRect=NULL) = 0;

	virtual void Run() = 0;

	virtual void Exit() = 0;
};

inline ZephyrFrame::ZephyrFrame()
{
	m_Graph = NULL;
	m_zWnd = NULL;
}

inline void ZephyrFrame::SetGraph(ZGraph* pGraph)
{
	ZASSERT(pGraph != NULL);

	m_Graph = pGraph;
}
#endif // ZEPHYRFRAME_API
//////////////////////////////////////////////////////////////////////
//	VirtualZephyrWnd

class ZEPHYR_API VirtualZephyrWnd : public ZephyrWnd{
public:
	VirtualZephyrWnd() {}
	virtual ~VirtualZephyrWnd() { Release(); }

	// ��ʼ��
	void Init(ZGraph *pGraph,HINSTANCE hInst,long x,long y,long w,long h,HWND hWnd);
	// �ͷ���Դ
	void Release();
};

#endif	//#ifndef ZEPHYR_WND_H