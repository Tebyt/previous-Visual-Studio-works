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
//	消息映射

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

const DWORD	ZWND_STATE_BACK				=	0x01000000;		//整图的窗口背景
const DWORD	ZWND_STATE_BACK_EX			=	0x03000000;		//9块图拼成一个窗口
const DWORD	ZWND_STATE_BACK_EX2			=	0x05000000;		//1张完整低图

const DWORD ZWND_STATE_BACK_COLORKEY	=	0x08000000;		//透明色的方式画背景
const DWORD ZWND_STATE_BACK_ALPHA50		=	0x10000000;		//半透明的方式画背景

const DWORD ZWND_STATE_BACK_ALPHA_CK	=	0x0c000000;		//带透明色的半透明方式画背景

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
	RECT				m_Rect;					//窗口大小
	RECT				m_ClientRect;			//实际窗口大小
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

	//创建窗口
	HRESULT Create(const char *classname,const char *name,DWORD style,int x,int y,int w,int h,ZephyrWnd *parent,UINT nID);
	//创建窗口
	HRESULT Create(const char *classname,const char *name,DWORD style,int x,int y,int w,int h,HWND parent,UINT nID);
	//创建窗口
	HRESULT CreateEx(DWORD exstyle,const char *classname,const char *name,DWORD style,int x,int y,int w,int h,ZephyrWnd *parent,UINT nID);
	//创建窗口
	HRESULT CreateEx(DWORD exstyle,const char *classname,const char *name,DWORD style,int x,int y,int w,int h,HWND parent,UINT nID);

	//初始化窗口
	static void Init(HINSTANCE hInstance);
	//注册窗口类
	static ATOM RegisterWndClass(const char *classname,DWORD style,HICON icon,HCURSOR cursor,HBRUSH brush,const char *menuname);

	//画整个窗口
	virtual void Draw(RECT *pRect = NULL);
	//画窗口背景部分
	virtual void DrawWndBack(RECT *pRect = NULL);
	//画窗口部件
	virtual void DrawWndItem(RECT *pRect = NULL);

	LPZSprite GetBackSpr() const { return m_sprWndBack; }

	//判断当前点是否在窗口内（可以在这里通过透明色来处理非矩形窗口）
	virtual bool IsIn(long x,long y);

	//生成Ex窗口的背景，必须要 m_sprBackEx 可用
	virtual void DrawBackEx();
	//生成Ex2窗口的背景，必须要 m_sprBackEx 可用
	virtual void DrawBackEx2();

	//资源释放
	void Release();

	// 鼠标离开窗口
	void MouseLeave();

//Set
	//设置ZGraph，必须在初始化以前设置！
	inline void SetGraph(ZGraph *graph);
	//设置ZFont，如果不设置的话，将会使用Graph缺省的文字显示
	inline void SetZFont(ZFont *zfont);

//Get
	//获得窗口句柄
	HWND GetHandle() const { return m_hWnd; }
	//获得当前的ZFont
	ZFont *GetZFont() const { return m_ZFont; }
	//获得Graph
	ZGraph *GetGraph() const { return m_Graph; }

	const char *GetClassName() { return m_ClassName; }

//rect
	//设置Rect，一般情况下，在Create函数内会自己调用该函数
	inline void SetRect(int x,int y,int w,int h);
	//获得RECT
	RECT *GetRect() { return &m_Rect; }
	//获得RECT宽度
	long GetWidth() { return m_Rect.right - m_Rect.left; }
	//获得RECT高度
	long GetHeight() { return m_Rect.bottom - m_Rect.top; }
	//设置窗口可用区域
	inline void SetClientArea(int x,int y,int w,int h);
	//获取窗口可用区域
	RECT *GetClientArea() { return &m_ClientRect; }

	// 是否在子窗口内
	bool IsInChild(long x,long y);

	ZephyrWnd* GetParent() { return m_Parent; }
//Sprite
	//设置BACKEX状态下的9个Spr
	void SetBackExSprite(LPZSprite lps,int index,RECT &rect,bool bColorKey);
	//设置BACKEX2状态下的Spr
	void SetBackEx2Sprite(LPZSprite lps,RECT &rect,bool bColorKey);
	//设置BACK状态下的Spr
	void SetBackSprite(LPZSprite lps,RECT &rect,bool bColorKey);
	//创建背景Spr
	void CreateWndBackSpr(long w,long h,DWORD flag);

	//改变窗口大小
	virtual void ChangeSize(long w,long h);

//State
	//设置State
	void SetState(DWORD state) { m_dwState = state; }
	//增加State
	void AddState(DWORD state) { m_dwState.Add(state); }
	//取消State
	void SubState(DWORD state) { m_dwState.Sub(state); }
	//获取State
	DWORD GetState() { return m_dwState.Get(); }

	//设置当前窗口为顶层窗口
	void SetTopWnd();
	//设置child为顶层窗口
	void SetTopChild(ZephyrWnd *child) { m_Top_Child = child; }

	//是否活动状态
	bool IsActive() { return m_dwState.Has(ZWND_STATE_ACTIVE); }
	//是否不可见状态
	bool IsHide() { return m_dwState.Has(ZWND_STATE_HIDE); }

//show/draw
	//隐藏窗口
	void HideWindow();
	//显示窗口
	void ShowWindow() { m_dwState.Sub(ZWND_STATE_HIDE); }
	//隐藏子窗口
	void HideChild(ZephyrWnd *child);

	//移动，参数为偏移
	void Move(long xOff,long yOff);
	//移动到坐标(x,y)
	void MoveTo(long x,long y) { Move(x-m_Rect.left,y-m_Rect.top); }

	//是否在RECT内
	inline bool IsInClient(long x,long y);

	//不可以使用窗口
	void Disable() { m_dwState += ZWND_STATE_DISABLE; }
	//可以使用
	void Enable() { m_dwState -= ZWND_STATE_DISABLE; }

//child wnd
	//添加child
	void AddToChild(ZephyrWnd* parent);
	//删除child
	void DelToChild(ZephyrWnd* parent);

	//添加子窗口
	void AddChild(ZephyrWnd* child);
	//删除子窗口
	void DelChild(ZephyrWnd* child);

	//捉住窗口
	void CatchChild(ZephyrWnd* child) { m_Catch_Child = child; }
	//焦点窗口
	void FocusChild(ZephyrWnd* child) { m_Focus_Child = child; }

	//是否存在子窗口
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

	// 初始化
	void Init(ZGraph *pGraph,HINSTANCE hInst,long x,long y,long w,long h,HWND hWnd);
	// 释放资源
	void Release();
};

#endif	//#ifndef ZEPHYR_WND_H