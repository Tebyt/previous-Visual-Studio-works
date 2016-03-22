#ifndef ZEPHYR_WND_DIALOG_H
#define ZEPHYR_WND_DIALOG_H

#include <Windows\ZWnd.h>

///////////////////////////////////////////////////////////////////////////////////
//	ZWndDlg

const DWORD ZWNDDLG_STATE_COLORKEY		=	0x01;
const DWORD ZWNDDLG_STATE_DRAWBMP		=	0x08;

const DWORD ZWNDDLG_STATE_CANMOVE		=	0x80;

const DWORD ZWNDDLG_STATE_FOCUS			=	0x0800;
const DWORD ZWNDDLG_STATE_CATCH			=	0x0400;

class ZEPHYR_API ZWndDlg : public ZephyrWnd{
protected:
//	LPZSprite	m_sprBack;
	long		m_xBegin,m_yBegin;
public:
	inline ZWndDlg();
	virtual ~ZWndDlg() { Release(); }

	// ´´½¨´°¿Ú
	HRESULT Create(const char *name,DWORD style,int x,int y,
		int w,int h,ZephyrWnd *parent,UINT nID);

	void Release();

	//load bmp
	HRESULT LoadBitmap(char *filename,bool bColorkey,long x,long y);

	void SetSprite(LPZSprite lps,bool bColorKey);
	void SetSprite(LPZSprite lps,RECT &rect,bool bColorKey);

	inline long GetWidth() const;
	inline long GetHeight()	const;

	virtual void Active(bool bActive = true) { ; }

	//virtual from ZephyrWnd
	virtual void DrawWndItem(RECT* pRect = NULL);
	virtual bool IsIn(long x,long y);
protected:
	int OnLButtonDown(DWORD wParam,DWORD lParam);
	int OnLButtonUp(DWORD wParam,DWORD lParam);
	int OnMouseMove(DWORD wParam,DWORD lParam);
	int OnMouseLeave(DWORD wParam,DWORD lParam);

	ZDECLARE_MESSAGE_MAP()
};

inline ZWndDlg::ZWndDlg()
{
//	m_sprBack = NULL;
	m_xBegin = m_yBegin = 0;
}

inline long ZWndDlg::GetWidth() const
{
	if(m_sprWndBack)
		return m_sprWndBack->GetRectWidth();

	return m_Rect.right - m_Rect.left;
}

inline long ZWndDlg::GetHeight() const
{
	if(m_sprWndBack)
		return m_sprWndBack->GetRectHeight();

	return m_Rect.bottom - m_Rect.top;
}
/*
///////////////////////////////////////////////////////////////////////////////////
//	ZWndInfoDlg

const int ZWNDINFODLG_STRING_MAX	=	256;

class ZEPHYR_API ZWndInfoDlg : public ZWndDlg{
private:
	char	m_String[ZWNDINFODLG_STRING_MAX];
	DWORD	m_TextColor;
public:
	inline ZWndInfoDlg() { m_String[0] = '\0',m_TextColor = 0; }
	virtual ~ZWndInfoDlg() { ; }

	//CreateBack
	void CreateBack(long w,long h,DWORD color);

	//virtual from ZephyrWnd
	virtual void Draw(RECT* pRect = NULL);

	inline void SetString(const char *str);
};

inline void ZWndInfoDlg::SetString(const char *str)
{
	if(str == NULL || str[0] == '\0')
		m_String[0] = '\0';
	else
		strcpy(m_String,str); 
}
*/
#endif