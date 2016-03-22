#ifndef ZEPHYR_WND_CTRL_H
#define ZEPHYR_WND_CTRL_H

#include <Zephyr.h>

#include <Windows\ZWnd.h>
#include <ZTimer.h>

#include <TextList.h>
#include <string>

//////////////////////////////////////////////////////////////////////
//	ZWndButton

//ZWndButton 的消息，WM_COMMAND 里面的 lParam
const int	ZWND_BUTTON_LBUTTONDOWN		=	0x80000001;
const int	ZWND_BUTTON_RBUTTONDOWN		=	0x80000002;
const int	ZWND_BUTTON_LRBUTTONDOWN	=	0x80000003;
const int	ZWND_BUTTON_LBUTTONUP		=	0x80000010;
const int	ZWND_BUTTON_RBUTTONUP		=	0x80000020;
const int	ZWND_BUTTON_LRBUTTONUP		=	0x80000030;

const int	ZWND_BUTTON_LBUTTONDBCLK	=	0x80000100;//DblClk

//ZWndButton Sprite
const int ZWND_BUTTON_NORMAL		=	0;
const int ZWND_BUTTON_SELECT		=	1;
const int ZWND_BUTTON_DISABLE		=	2;
const int ZWND_BUTTON_PUSH			=	3;

//state
const DWORD ZWNDBUTTON_STATE_COLORKEY	=	0x01;
const DWORD ZWNDBUTTON_STATE_SHOWFONT	=	0x02;
const DWORD ZWNDBUTTON_STATE_DRAWBMP	=	0x04;
const DWORD ZWNDBUTTON_STATE_SHOWINFO	=	0x08;

//const DWORD ZWNDBUTTON_STATE_PUSH		=	0x80;

const DWORD ZWNDBUTTON_STATE_FOCUS		=	0x0800;
const DWORD ZWNDBUTTON_STATE_DOWN		=	0x0400;
const DWORD ZWNDBUTTON_STATE_DISABLE	=	ZWND_STATE_DISABLE;

const DWORD ZWNDBUTTON_STATE_LDOWN		=	0x1000;
const DWORD ZWNDBUTTON_STATE_RDOWN		=	0x2000;

const DWORD	ZWNDBUTTON_SHOWTIME			=	1 * 1000;


class ZEPHYR_API ZWndButton : public ZephyrWnd{
private:
	LPZSprite	m_Sprite[4];

	DWORD		m_dwTextColor;

	DWORD		m_Msg;

	DWORD		m_dwShowTime;

	std::string	m_strInfo;
public:
	inline ZWndButton();
	virtual ~ZWndButton();

	//创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,int w,int h,ZephyrWnd *parent,UINT nID);
	//创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,int w,int h,HWND parent,UINT nID);

	//load bmp
	//一幅bmp，4个状态，竖着排列
	HRESULT LoadBitmap(char *filename,bool bColorkey,long x,long y);

	void SetSprite(LPZSprite lps,int index,RECT &rect,bool bColorKey);

	inline long GetWidth() const;
	inline long GetHeight()	const;

	void SetTextColor(DWORD TextColor) { m_dwTextColor = TextColor; }

	void Release();

	void Load(const char *name);
//virtual from ZephyrWnd
	virtual void DrawWndItem(RECT* pRect = NULL);
	virtual bool IsIn(long x,long y);

	void SetMessage(DWORD msg) { m_Msg = msg; }

	void SetHelpInfo(const char* str){
			m_strInfo = str;
		}
protected:
//message
	int OnLButtonDown(DWORD wParam,DWORD lParam);
	int OnLButtonUp(DWORD wParam,DWORD lParam);
	int OnRButtonDown(DWORD wParam,DWORD lParam);
	int OnRButtonUp(DWORD wParam,DWORD lParam);
	int OnLButtonDblClk(DWORD wParam,DWORD lParam);
	int OnMouseMove(DWORD wParam,DWORD lParam);
	int OnMouseLeave(DWORD wParam,DWORD lParam);
	int OnTimer(DWORD wParam,DWORD lParam);
	int OnDestroy(DWORD wParam,DWORD lParam);

	ZDECLARE_MESSAGE_MAP()
};

inline ZWndButton::ZWndButton()
{
	m_Sprite[0] = m_Sprite[1] = m_Sprite[2] = m_Sprite[3] = NULL;

	m_dwTextColor = 0x0;

	m_Msg = WM_COMMAND;
}

inline long ZWndButton::GetWidth() const
{
	if(m_Sprite[0])
		return m_Sprite[0]->GetRectWidth();
	else
		return m_Rect.right-m_Rect.left;
}

inline long ZWndButton::GetHeight() const
{
	if(m_Sprite[0])
		return m_Sprite[0]->GetRectHeight();
	else
		return m_Rect.bottom-m_Rect.top;
}

//////////////////////////////////////////////////////////////////////
//	ZWndEdit

const DWORD  ZWNDEDIT_TIMER_ID	=	1;

//string len
const DWORD ZWNDEDIT_STRLEN		=	256;

const DWORD ZWNDEDIT_KEY_TAB	=	0x01;

//state
const DWORD ZWNDEDIT_STATE_COLORKEY		=	0x01;

const DWORD ZWNDEDIT_STATE_DRAWBMP		=	0x08;

const DWORD ZWNDEDIT_STATE_PASSWORD		=	0x0800;
const DWORD	ZWNDEDIT_STATE_READONLY		=	0x0400;

class ZEPHYR_API ZWndEdit : public ZephyrWnd{
private:
	static HWND	_editWnd;
	static HWND	_focusWnd;

	bool		m_bShowCursor;

	int			m_selStart,m_selEnd;
	int			m_strStart;
	int			m_selClk;
	char		m_String[ZWNDEDIT_STRLEN];

	int			m_MaxLength;

	DWORD		m_BackColor;
	DWORD		m_SelectColor;
	DWORD		m_TextColor;
	DWORD		m_Color;

	LPZSprite	m_Sprite;

	UINT		m_dstID;
public:
	inline ZWndEdit();

	virtual ~ZWndEdit();

	// 创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,
		int w,int h,ZephyrWnd *parent,UINT nID);

	// 创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,
		int w,int h,HWND parent,UINT nID);

	inline void LimitText(int len);

	inline void SetColor(DWORD BackColor,DWORD TextColor,DWORD SelectColor,DWORD Color);

	inline void SetSprite(LPZSprite lps);

	HRESULT LoadBitmap(char *filename,bool bColorkey,long x,long y);

	inline long GetDefaultHeight();

	inline const char* GetText();
	inline void SetText(const char *str);

	inline void ClearText();

	inline void SetDstWndID(UINT id);

	void Active(long x);

//virtual from ZephyrWnd
	void Release();
	virtual void DrawWndItem(RECT* pRect = NULL);

protected:
//message
	int OnSetFoucs(DWORD wParam,DWORD lParam);
	int OnTimer(DWORD wParam,DWORD lParam);
	int OnChar(DWORD wParam,DWORD lParam);
	int OnLButtonClk(DWORD wParam,DWORD lParam);
	int OnKeyDown(DWORD wParam,DWORD lParam);
	int OnImeChar(DWORD wParam,DWORD lParam);
	int OnMouseMove(DWORD wParam,DWORD lParam);
	int OnLButtonDblClk(DWORD wParam,DWORD lParam);

	ZDECLARE_MESSAGE_MAP()
};

inline ZWndEdit::ZWndEdit()	
{	
	m_String[0] = '\0';	
	m_BackColor = 0xffffffff;
	m_SelectColor = 0xf7f7f7f7;
	m_TextColor = 0;
	m_Sprite = NULL;
	m_Color = 0;

	m_strStart = 0;

	m_dstID = 0;
}

inline void ZWndEdit::LimitText(int len)
{
	m_MaxLength = len - 1;
}

inline void ZWndEdit::SetColor(DWORD BackColor,DWORD TextColor,DWORD SelectColor,DWORD Color)
{
	m_BackColor = BackColor;
	m_TextColor = TextColor;
	m_Color = Color;
	m_SelectColor = SelectColor;
}

inline void ZWndEdit::SetSprite(LPZSprite lps)
{
	m_Sprite = lps;

	m_dwState.Add(ZWNDEDIT_STATE_DRAWBMP);
}

inline long ZWndEdit::GetDefaultHeight()
{
	return m_ZFont->GetHeight() + 2;
}

inline const char* ZWndEdit::GetText()
{
	return m_String;
}

inline void ZWndEdit::SetText(const char *str)
{
	ZASSERT(str && *str);

	strcpy(m_String,str);

	if(_focusWnd == m_hWnd)
		SetWindowText(_editWnd,m_String);
}

inline void ZWndEdit::ClearText()
{
	m_String[0] = '\0';

	SetWindowText(_editWnd,m_String);
}

inline void ZWndEdit::SetDstWndID(UINT id)
{
	m_dstID = id;
}

//////////////////////////////////////////////////////////////////////
//	ZWndScroll

#define ZWNDSCROLL_TIMER_ID			1

//sprite
#define ZWND_SCROLL_BACK			0
#define ZWND_SCROLL_CURSOR			1
#define ZWND_SCROLL_SUBBLOCKUP		2
#define ZWND_SCROLL_SUBBLOCKDOWN	3
#define ZWND_SCROLL_ADDBLOCKUP		4
#define ZWND_SCROLL_ADDBLOCKDOWN	5

//scroll state
const DWORD ZWNDSCROLL_STATE_COLORKEY		=0x01;
const DWORD ZWNDSCROLL_STATE_SHOWFONT		=0x02;
const DWORD ZWNDSCROLL_STATE_DRAWFRAME		=0x04;
const DWORD ZWNDSCROLL_STATE_DRAWBMP		=0x08;
const DWORD ZWNDSCROLL_STATE_FILLCOLOR		=0x10;

const DWORD ZWNDSCROLL_STATE_ADDBLOCKDOWN	=0x0080;
const DWORD ZWNDSCROLL_STATE_SUBBLOCKDOWN	=0x0040;
const DWORD ZWNDSCROLL_STATE_MOVBLOCKDOWN	=0x0020;

const DWORD ZWNDSCROLL_STATE_VERT			=0x0800;

const DWORD ZWNDSCROLL_STATE_RELEASESPR		=0x8000;

class ZEPHYR_API ZWndScroll : public ZephyrWnd{
protected:
	DWORD	m_BlockSize;		//按钮大小
	DWORD	m_MovBlockSize;		//滑块大小

	DWORD	m_BackColor;
	DWORD	m_Color;

	LPZSprite	m_Sprite[6];

	long	m_lMovPos;			//每次移动的大小
	long	m_lCurPos;			//滑块当前位移
	long	m_lMaxPos;			//滑块最大的位移
	long	m_lMaxLines;		//目标最大位移
public:
	inline ZWndScroll();
	virtual ~ZWndScroll();

	// 创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,
		int w,int h,ZephyrWnd *parent,UINT nID);

	// 创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,
		int w,int h,HWND parent,UINT nID);

	HRESULT LoadBitmap(char *filename,bool bColorkey,long x,long y);

	void SetSprite(LPZSprite lps,int index,bool bColorKey);
	void SetSprite(LPZSprite lps,int index,RECT &rect,bool bColorKey);

	inline void SetColor(DWORD backColor,DWORD Color);

	inline void SetArea(long maxLines);
	inline void SetPos(long pos);

	inline void SetBlockSize(DWORD Size,DWORD movSize);

	inline void SetDefault();

	inline void Down();

	DWORD GetBlockSize() { return m_BlockSize; }

//virtual from ZephyrWnd
	virtual void Draw(RECT* pRect = NULL);
	void Release();

protected:
	inline void UpAll();

//message
	int OnLButtonDown(DWORD wParam,DWORD lParam);
	int OnLButtonUp(DWORD wParam,DWORD lParam);
	int OnMouseMove(DWORD wParam,DWORD lParam);
	int OnTimer(DWORD wParam,DWORD lParam);

	ZDECLARE_MESSAGE_MAP()
};

inline ZWndScroll::ZWndScroll()
{
	m_BackColor = 0xffffffff;
	m_Color = 0;
	m_Sprite[0] = m_Sprite[1] = m_Sprite[2] = m_Sprite[3] = m_Sprite[4] = m_Sprite[5] = NULL;

	m_lMovPos = 1;
	m_lCurPos = 0;
	m_lMaxPos = 0;
	m_lMaxLines = 0;

	m_BlockSize = 0;
	m_MovBlockSize = 0;
}

inline void ZWndScroll::SetColor(DWORD backColor,DWORD Color)
{
	m_BackColor = backColor;
	m_Color = Color;
}

inline void ZWndScroll::SetArea(long maxLines)
{
	if(maxLines <= 0)
		return ;

	if(maxLines > m_lMaxLines)
		m_lCurPos--;
//	m_lCurPos=m_lCurPos*maxLines/m_lMaxLines;

	m_lMaxLines = maxLines;

	m_lMovPos = maxLines > m_lMaxPos ? 1 : (m_lMaxPos/maxLines);
}

inline void ZWndScroll::SetPos(long pos)
{
	if(pos <= m_lMaxPos)
		m_lCurPos = pos;
}

inline void ZWndScroll::SetBlockSize(DWORD Size,DWORD movSize)
{
	m_BlockSize = Size;
	m_MovBlockSize = movSize;
}

inline void ZWndScroll::SetDefault()
{
	m_dwState.Add(ZWNDSCROLL_STATE_DRAWFRAME|ZWNDSCROLL_STATE_FILLCOLOR|ZWNDSCROLL_STATE_SHOWFONT);

	if(m_dwState.Has(ZWNDSCROLL_STATE_VERT))
	{
		m_BlockSize = m_Rect.right - m_Rect.left;
		m_MovBlockSize = m_BlockSize/2;

		m_lMaxPos = m_Rect.bottom - m_Rect.top - m_BlockSize * 2 - m_MovBlockSize;
	}
	else
	{
		m_BlockSize = m_Rect.bottom - m_Rect.top;
		m_MovBlockSize = m_BlockSize/2;

		m_lMaxPos = m_Rect.right - m_Rect.left - m_BlockSize * 2 - m_MovBlockSize;
	}
}

inline void ZWndScroll::UpAll()
{
	m_dwState.Sub(ZWNDSCROLL_STATE_ADDBLOCKDOWN|ZWNDSCROLL_STATE_SUBBLOCKDOWN|ZWNDSCROLL_STATE_MOVBLOCKDOWN);
}

inline void ZWndScroll::Down()
{
	if(m_lCurPos < m_lMaxPos)
	{
		m_lCurPos += m_lMovPos;
		if(m_lCurPos > m_lMaxPos)
			m_lCurPos = m_lMaxPos;

		SendMessage(::GetParent(m_hWnd),WM_VSCROLL,SB_LINEDOWN,1);
	}
}

//////////////////////////////////////////////////////////////////////
//	_ZWndListBox

const int	ZWND_LISTBOX_LBUTTONDOWN		=	0x80000001;
const int	ZWND_LISTBOX_RBUTTONDOWN		=	0x80000002;
const int	ZWND_LISTBOX_LRBUTTONDOWN		=	0x80000003;
const int	ZWND_LISTBOX_LBUTTONUP			=	0x80000010;
const int	ZWND_LISTBOX_RBUTTONUP			=	0x80000020;
const int	ZWND_LISTBOX_LRBUTTONUP			=	0x80000030;

const int	ZWND_LISTBOX_LBUTTONDBLCLK		=	0x80000004;

//state
const DWORD ZWNDLISTBOX_STATE_COVER			=	0x01;

const DWORD ZWNDLISTBOX_STATE_SHOWFONT		=	0x02;

const DWORD ZWNDLISTBOX_STATE_VSCROLL		=	0x0800;
const DWORD ZWNDLISTBOX_STATE_HSCROLL		=	0x0400;
const DWORD ZWNDLISTBOX_STATE_NEWLINE		=	0x0200;		//自动换行

const DWORD ZWNDLISTBOX_STATE_SELECT		=	0x1000;		//选择，缺省为单击选择
const DWORD ZWNDLISTBOX_STATE_SELECT_MOUSE	=	0x1001;		//选择，鼠标移动选择

const DWORD ZWNDLISTBOX_STATE_RELEASESPR	=	0x8000;

class ZEPHYR_API _ZWndListBox : public ZephyrWnd{
protected:
	DWORD		m_SelectColor;
	DWORD		m_TextColor;

	int		m_iMaxLines;		//list可显示的最大行数
	int		m_iBegin;

	ZWndScroll *m_vScroll;
	ZWndScroll *m_hScroll;

	int			m_iCurSelect;
public:
	inline _ZWndListBox();
	virtual ~_ZWndListBox() { Release(); }

	// 创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,
		int w,int h,ZephyrWnd *parent,UINT nID);

	inline void SetColor(DWORD textColor,DWORD selectColor);

	inline void SetList(void *list);
	inline void *GetList();

	virtual void ChangeSize(long w,long h);

	inline void Clear();

	void CreateHScroll(long h);
	void CreateVScroll(long w);

	inline void SetVScrollSprite(LPZSprite lps,int index,RECT &rect,bool bColorKey);

	long SetHeight(long height);

	void SetDefault();

	inline int GetCur() const { return m_iCurSelect; }

//virtual from ZephyrWnd
	virtual void DrawWndItem(RECT* pRect = NULL);

	void Release();

protected:
	virtual void DrawList() = 0;

	virtual int GetUsed() = 0;

//message
	int OnLButtonDown(DWORD wParam,DWORD lParam);
	int OnLButtonDblClk(DWORD wParam,DWORD lParam);
	int OnVScroll(DWORD wParam,DWORD lParam);
	int OnHScroll(DWORD wParam,DWORD lParam);
	int OnMouseMove(DWORD wParam,DWORD lParam);

	ZDECLARE_MESSAGE_MAP()
};

inline _ZWndListBox::_ZWndListBox()
{
	m_SelectColor = 0xf0f0f0f0;
	m_TextColor = 0;

	m_iMaxLines = 0;
	m_iBegin = 0;

	m_vScroll = m_hScroll = NULL;

	m_iCurSelect = -1;
}

inline void _ZWndListBox::SetColor(DWORD textColor,DWORD selectColor)
{
	m_TextColor = textColor;
	m_SelectColor = selectColor;
}

inline void _ZWndListBox::SetVScrollSprite(LPZSprite lps,int index,RECT &rect,bool bColorKey)
{
	if(m_vScroll)
		m_vScroll->SetSprite(lps,index,rect,bColorKey);
}

//////////////////////////////////////////////////////////////////////
//	ZWndListBox_Simple

class ZEPHYR_API ZWndListBox_Simple : public _ZWndListBox{
protected:
	int		m_StrLen;
	int		m_LstLen;

	char	**m_List;
public:
	inline ZWndListBox_Simple();
	virtual ~ZWndListBox_Simple() { Release(); }

	void CreateList(int iSize,int iLength);

	void AddString(int index,const char *string,bool bCover,bool bMove);
	void DelString(int index);
	void DelString(const char *string);

	void Clear();

	void Release();

	inline const char *GetCurString();
protected:
	virtual void DrawList();

	virtual int GetUsed();
};

inline ZWndListBox_Simple::ZWndListBox_Simple()
{
	m_List = NULL;
	m_StrLen = 0;
	m_LstLen = 0;
}

inline const char *ZWndListBox_Simple::GetCurString() 
{ 
	ZASSERT(m_iCurSelect != -1);

	return m_List[m_iCurSelect];
}

//////////////////////////////////////////////////////////////////////
//	ZWndListBox

//state
const DWORD ZWNDLISTBOX_STATE_RELEASELIST	=	0x4000;

class ZEPHYR_API ZWndListBox : public _ZWndListBox{
protected:
	ZTextList	*m_List;
public:
	inline ZWndListBox();
	virtual ~ZWndListBox() { Release(); }

	inline void SetList(void *list);
	inline void *GetList();

	void CreateList(int iSize,int iLength);

	void AddString(const char *string);
	void DelString(const char *string);

	inline void Clear();

	void Release();

	inline const char *GetCurString();
protected:
	virtual void DrawList();

	virtual int GetUsed();
};

inline ZWndListBox::ZWndListBox()
{
	m_List = NULL;
}

inline void ZWndListBox::SetList(void *list)
{
	m_List = (ZTextList *)list;
}

inline void *ZWndListBox::GetList()
{
	return m_List;
}

inline void ZWndListBox::Clear()
{
	if(m_List)
		m_List->Clear();
}

inline const char *ZWndListBox::GetCurString()
{
	if(m_List != NULL)
		return m_List->GetData(m_iCurSelect);

	return NULL;
}

//////////////////////////////////////////////////////////////////////
//	ZWndImageBox

//ZWndImageBox 的消息，WM_COMMAND 里面的 lParam
const int	ZWND_IMAGEBOX_LBUTTONDOWN		=	0x80000001;
const int	ZWND_IMAGEBOX_RBUTTONDOWN		=	0x80000002;
const int	ZWND_IMAGEBOX_LRBUTTONDOWN		=	0x80000003;
const int	ZWND_IMAGEBOX_LBUTTONUP			=	0x80000010;
const int	ZWND_IMAGEBOX_RBUTTONUP			=	0x80000020;
const int	ZWND_IMAGEBOX_LRBUTTONUP		=	0x80000030;
const int	ZWND_IMAGEBOX_MOUSEIN			=	0x80000005;

const DWORD URL_MAX_LEN	=	256;

//State
const DWORD ZWNDIMAGEBOX_STATE_COLORKEY	=	0x01;

const DWORD ZWNDIMAGEBOX_STATE_SIZE		=	0x02;

const DWORD ZWNDIMAGEBOX_STATE_CLICK	=	0x04;

class ZEPHYR_API ZWndImageBox : public ZephyrWnd{
private:
	LPZSprite	m_sprData;
	LPZSprite	m_sprSrc;

	char		m_dstURL[URL_MAX_LEN];
public:
	inline ZWndImageBox();
	virtual ~ZWndImageBox() { Release(); }

	//创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,int w,int h,ZephyrWnd *parent,UINT nID);
	//创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,int w,int h,HWND parent,UINT nID);

	//load bmp
	HRESULT LoadBitmap(char *filename,bool bColorkey);

	inline long GetSprWidth();
	inline long GetSprHeight();

	void SetSprite(LPZSprite lps,RECT &rect,bool bColorKey);

	inline void SetURL(const char *url);

	void Release();
//virtual from ZephyrWnd
	virtual void DrawWndItem(RECT* pRect = NULL);
	virtual bool IsIn(long x,long y);

	//改变窗口大小
	virtual void ChangeSize(long w,long h);

protected:
//message
	int OnLButtonDown(DWORD wParam,DWORD lParam);
	int OnMouseMove(DWORD wParam,DWORD lParam);
	int OnMouseLeave(DWORD wParam,DWORD lParam);
	int OnSetCursor(DWORD wPAram,DWORD lParam);

	ZDECLARE_MESSAGE_MAP()
};

inline ZWndImageBox::ZWndImageBox() 
{ 
	m_sprData = NULL;
	m_sprSrc = NULL;

	m_dstURL[0] = '\0';
}

inline long ZWndImageBox::GetSprWidth()
{
	if(m_sprData != NULL)
		return m_sprData->GetRectWidth();
	else if(m_sprSrc != NULL)
		return m_sprSrc->GetRectWidth();

	return 0;
}

inline long ZWndImageBox::GetSprHeight()
{
	if(m_sprData != NULL)
		return m_sprData->GetRectHeight();
	else if(m_sprSrc != NULL)
		return m_sprSrc->GetRectHeight();

	return 0;
}

inline void ZWndImageBox::SetURL(const char *url)
{
	ZASSERT(url != NULL);

	strcpy(m_dstURL,url);
}

//////////////////////////////////////////////////////////////////////
//	ZWndAniImageBox

const DWORD ZWNDANIIMAGE_STATE_RELEASEANI	=	0x01;

#include <Graph\Ani.h>

class ZEPHYR_API ZWndAniImageBox : public ZWndImageBox{
private:
	ZAni		*m_aniData;
public:
	ZWndAniImageBox() { m_aniData = NULL; }
	virtual ~ZWndAniImageBox() { Release(); }

	//load ani
	inline HRESULT LoadAni(char *filename);

	inline void SetAni(ZAni *pAni);

	inline long GetSprWidth();
	inline long GetSprHeight();

	void Release();
//virtual from ZephyrWnd
	virtual void DrawWndItem(RECT *pRect = NULL);
	virtual bool IsIn(long x,long y);
};

//load ani
inline HRESULT ZWndAniImageBox::LoadAni(char *filename)
{
	ZASSERT(m_Graph != NULL);
	ZASSERT(filename != NULL);
	ZASSERT(m_aniData == NULL);

	m_aniData = new ZAni;
	assert(m_aniData != NULL);

	AddState(ZWNDANIIMAGE_STATE_RELEASEANI);

	return m_aniData->Load(filename,m_Graph);
}

inline long ZWndAniImageBox::GetSprWidth()
{
	if(m_aniData != NULL)
		return m_aniData->GetWidth();
	else
		return 0;
}

inline long ZWndAniImageBox::GetSprHeight()
{
	if(m_aniData != NULL)
		return m_aniData->GetHeight();
	else
		return 0;
}

inline void ZWndAniImageBox::SetAni(ZAni *pAni)
{
	ZASSERT(pAni != NULL);

	m_aniData = pAni;
}

//////////////////////////////////////////////////////////////////////
//	ZWndComboBox

const DWORD ZWNDCOMBOBOX_STRLEN		=	256;

const DWORD	ZWNDCOMBOBOX_LIST_ID	=	100;

class ZEPHYR_API ZWndComboBox : public ZephyrWnd{
	ZWndListBox_Simple		m_List;
	char					m_String[ZWNDCOMBOBOX_STRLEN];
	bool					m_bShowList;
	int						m_iDefaultIndex;
	DWORD					m_TextColor;
public:
	inline ZWndComboBox();
	virtual ~ZWndComboBox() { Release(); }

	// 创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,
		int w,int h,ZephyrWnd *parent,UINT nID,int w2,int h2,bool bUp);

	// 创建窗口
	HRESULT Create(const char *name,DWORD style,int x,int y,
		int w,int h,HWND parent,UINT nID,int w2,int h2,bool bUp);

	void CreateList(int iSize,int iLength) { m_List.CreateList(iSize,iLength); }

	void Release();

	const char *GetString() { return m_String; }

	void SetDefaultIndex(int index) { m_iDefaultIndex = index; }

	ZWndListBox_Simple *GetList() { return &m_List; }

	void AddString(const char *str);
	void DelString(const char *str);

	void setColor(DWORD textColor) { m_TextColor = textColor; }

//virtual from ZephyrWnd
	virtual void DrawWndItem(RECT *pRect = NULL);
	virtual bool IsIn(long x,long y);
protected:
//message
	int OnLButtonDown(DWORD wParam,DWORD lParam);
	int OnCommand(DWORD wPAram,DWORD lParam);

	ZDECLARE_MESSAGE_MAP()
};

inline ZWndComboBox::ZWndComboBox()
{
	m_bShowList = false;
	m_iDefaultIndex = 0;
	m_String[0] = '\0';
	m_TextColor = 0xffffffff;
}

#endif