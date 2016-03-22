//Graph\ZFont_2.h
//ZFont 2.0 版本
//Write by zhs007			y2k3.7.14

#ifndef ZEPHYR_GRAPH_FONT_2_H
#define ZEPHYR_GRAPH_FONT_2_H

#include <windows.h>

#include <ZLink.h>
#include <ZState.h>
#include <Graph\BaseDef.h>

#include <ZStack.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ZFont

const DWORD ZFONT_STATE_INIT		=	0x01;			//zfont已经初始化

class ZEPHYR_API ZFont{
protected:
	int				m_iHeight;

	ZState_DWord	m_dwState;

	ZGraph			*m_Graph;
public:
	inline ZFont();
	virtual ~ZFont()	{ }

	HRESULT Printf(void *dst,long x,long y,DWORD color,char *s,...);

	HRESULT	DrawString(void *dst,long x,long y,DWORD color,char *s);
	HRESULT	DrawString(void *dst,long x,long y,DWORD color,char *s,long max_x,bool newline = false);

	int	GetStringWidth(char *s);
	int	GetStringWidth(char *s,unsigned len);

	int	GetStringBegin(char *s,long str_len);
	int	GetStringEnd(char *s,long str_len);

	void SetHeight(int h) { m_iHeight = h; }
	int GetHeight() const { return m_iHeight; }

	virtual int GetWidth(unsigned int c) = 0;

	inline void SetGraph(ZGraph *graph);
protected:
	virtual int DrawChar(void *dst,long x,long y,DWORD color,unsigned int c) = 0;
};

inline ZFont::ZFont()
{
	m_iHeight = 0;
	m_Graph = NULL;
}

inline void ZFont::SetGraph(ZGraph *graph)
{
	ZASSERT(graph != NULL);

	m_Graph = graph;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ZVectorFont

class ZEPHYR_API ZVectorFont : public ZFont{
public:
	struct _node{
		BYTE			*pData;
		DWORD			dwSize;
		int				w,h,width,kx,ky;
		unsigned int	c;

		_node			*next;

		_node() {
			pData = NULL;

			next = NULL;

			dwSize = 0;
		}
	};
protected:
	DWORD		m_dwCacheSize;
	HDC			m_fontDC;
	HFONT		m_hFont;
	int			m_Ascent;

	_node		*m_lpZFontData,*m_lpEndZFontData;
	_node		*m_pHead;
public:
	ZVectorFont(ZGraph *pGraph,HFONT hFont,DWORD dwCacheSize);
	virtual ~ZVectorFont() { Release(); }

	void Release();

	//virtual from ZFont
	virtual int GetWidth(unsigned int c);
protected:
	//virtual from ZFont
	virtual int DrawChar(void *dst,long x,long y,DWORD color,unsigned int c);

	virtual ZVectorFont::_node *GetData(unsigned int c);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ZSmoothVectorFont

class ZEPHYR_API ZSmoothVectorFont :public ZVectorFont{
public:
	struct _node : public ZVectorFont::_node{
		int	x,y;

		_node() : ZVectorFont::_node() {
			x = y = -1;
		}
	};
protected:
	LPZSprite			m_sprCache;

	int					m_tileWidth;
public:
	ZSmoothVectorFont(ZGraph *pGraph,HFONT hFont,long CacheSprWidth,long CacheSprHeight);
	virtual ~ZSmoothVectorFont() { Release(); }

	void Release();
	//virtual from ZFont
	virtual int GetWidth(unsigned int c);
protected:
	void DrawCache(ZSmoothVectorFont::_node *dat);

	//virtual from ZFont
	virtual int DrawChar(void *dst,long x,long y,DWORD color,unsigned int c);
	//virtual from ZVectorFont
	virtual ZVectorFont::_node *GetData(unsigned int c);
};

#endif//ZEPHYR_GRAPH_FONT_2_H