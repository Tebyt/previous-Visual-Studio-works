/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	CZWnd.h

							Describe:	MFC CWnd µƒ¿©’π÷ß≥÷

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2003.08.20
							UpdateTime:
*/

#ifndef _ZEPHYR_CZWND_H
#define _ZEPHYR_CZWND_H

#include <Graph\BaseDef.h>
#include <Windows\ZWnd.h>

#include <Graph\ZArea.h>

#include <MFC\BaseDef.h>

////////////////////////////////////////////////////////////////////////////////////////////////
// CZWnd

class ZEPHYR_MFC_API CZWnd : public CWnd
{
protected:
	RECT				m_localRect;

	ZGraph				*m_Graph;

	HINSTANCE			m_hInst;

	bool				m_bReleaseGraph;

	VirtualZephyrWnd	m_zWnd;

	HFONT				m_hFont12;
	ZFont				*m_Font12;

	ZArea				m_Area;

	bool				m_bInit;

	long				m_screenX, m_screenY;
private:
	DECLARE_DYNAMIC(CZWnd)
public:
	CZWnd(HINSTANCE	hInst, ZGraph *pGraph);
	virtual ~CZWnd();

	void Release();

	void SetInstance(HINSTANCE hInst) { m_hInst = hInst; }

	inline void SetRect(long x,long y ,long w,long h);

	virtual void Draw(RECT *rect);

	RECT *GetRect() { return &m_localRect; }

	void Render(RECT &rect);

	void DrawSpr(LPZSprite spr,int x,int y,bool bColorKey);

	void DrawSprAlpha(LPZSprite spr,int x,int y,BYTE alpha);

	void DrawString(DWORD fontHeight,int x,int y,DWORD color,const char* str);

	ZArea& GetArea() { return m_Area; }
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
};

inline void CZWnd::SetRect(long x,long y ,long w,long h) 
{ 
	m_localRect.left = x;
	m_localRect.top = y;
	m_localRect.right = x + w;
	m_localRect.bottom = y + h;
}

#endif//_ZEPHYR_CZWND_H