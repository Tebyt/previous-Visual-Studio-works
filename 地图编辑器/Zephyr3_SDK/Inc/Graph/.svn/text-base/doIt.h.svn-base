#ifndef ZEPHYR_GRAPH_DOIT_H
#define ZEPHYR_GRAPH_DOIT_H

#include <Graph\ZGraph.h>
#include <Graph\ZSprite.h>
#include <Graph\ZRenderEngine.h>

#include <SE_Exception.h>

///////////////////////////////////////////////////////////////////////////////////
// ZRenderEngine

inline LPSPRITE_DATA ZRenderEngine::_createsprite(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag)
{
	return m_Graph->_createsprite(w,h,zcm,flag);
}

inline void ZRenderEngine::ReleaseSprite(LPSPRITE_DATA &lps)
{
	try{
		m_Graph->_releasesprite(lps);
	}
	catch(SE_Exception e)
	{
		Debug("---<<Exception>>---");

		Debug("ZRenderEngine::ReleaseSprite()");

		Debug("--->>Exception<<---");
	}
}

inline HRESULT ZRenderEngine::_clearsprite(LPSPRITE_DATA lps,long x,long y,long r,long b,DWORD color)
{
	return m_Graph->_clearsprite(lps,x,y,r,b,color);
}

inline LPSPRITE_DATA ZRenderEngine::GetBackScreenData()
{
	return m_Graph->GetBackScreenData();
}

inline HRESULT ZRenderEngine::_locksprite(LPSPRITE_DATA lps,void **pvoid,DWORD &pitch,long &w,long &h)
{
	return m_Graph->_locksprite(lps,pvoid,pitch,w,h);
}

inline HRESULT ZRenderEngine::_unlocksprite(LPSPRITE_DATA lps)
{
	return m_Graph->_unlocksprite(lps);
}

inline HRESULT ZRenderEngine::_locksprite_r(LPSPRITE_DATA lps,RECT *rect,void **pvoid,DWORD &pitch,long &w,long &h)
{
	return m_Graph->_locksprite_r(lps,rect,pvoid,pitch,w,h);
}

inline ZGraph* ZRenderEngine::GetGraph()
{
	return m_Graph;
}

inline bool ZRenderEngine::RectInNode(ZRenderEngine::rectlist_node* node,RECT &rect)
{
	if(rect.right<=node->rect.left||rect.bottom<=node->rect.top||
		rect.left>=node->rect.right||rect.top>=node->rect.bottom)
		return false;

	if(rect.left<node->rect.left)
		rect.left=node->rect.left;
	if(rect.right>node->rect.right)
		rect.right=node->rect.right;
	if(rect.top<node->rect.top)
		rect.top=node->rect.top;
	if(rect.bottom>node->rect.bottom)
		rect.bottom=node->rect.bottom;

	return true;
}

inline void ZRenderEngine::ClearState(ZRenderEngine::rectlist_node* node)
{
	node->state=0;
}

inline void ZRenderEngine::SetStateNotDraw(ZRenderEngine::rectlist_node* node)
{
	node->state|=RECTLIST_NODE_NOTDRAW;
}

inline void ZRenderEngine::ClrStateNotDraw(ZRenderEngine::rectlist_node* node)
{
	node->state&=~RECTLIST_NODE_NOTDRAW;
}

inline BOOL ZRenderEngine::IsDrawNode(ZRenderEngine::rectlist_node* node)
{
	return !(node->state&RECTLIST_NODE_NOTDRAW);
}

inline void ZRenderEngine::SetStateNotProcess(ZRenderEngine::rectlist_node* node)
{
	node->state|=RECTLIST_NODE_NOTPROCESS;
}

inline void ZRenderEngine::ClrStateNotProcess(ZRenderEngine::rectlist_node* node)
{
	node->state&=~RECTLIST_NODE_NOTPROCESS;
}

inline BOOL ZRenderEngine::IsNotProcessNode(ZRenderEngine::rectlist_node* node)
{
	return node->state&RECTLIST_NODE_NOTPROCESS;
}

inline void ZRenderEngine::SetCutMode(bool cut)
{
	m_bCut = cut;

	if(!cut)
		m_cutSpr = NULL;
}

inline void ZRenderEngine::SetCutSpr(LPSPRITE_DATA spr)
{
	m_cutSpr=spr;
}

inline ZFont *ZRenderEngine::GetDefaultFont()//(int height)
{
	return m_Graph->GetDefaultFont();//(height);
}

///////////////////////////////////////////////////////////////////////////////////
//	ZGraph

inline void ZGraph::SetHWND(HWND hwnd)
{
	ZASSERT(hwnd);

	m_hWnd=hwnd;
}

inline void ZGraph::SetInstance(HINSTANCE hinst)
{
	ZASSERT(hinst);

	m_hInst=hinst;
}

inline LPSPRITE_DATA ZGraph::GetBackScreenData()
{
	return m_back.m_lps;
}

inline LPZSprite ZGraph::CreateSprite(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag)
{
	LPZSprite tmp=new ZSprite;

	tmp->m_lps=_createsprite(w,h,zcm,flag);
	tmp->SetRenderEngine(m_RenderEngine);

	tmp->SetRect();

	return tmp;
}

inline LPZSprite ZGraph::CreateSprite(LPSPRITE_DATA lps)
{
	LPZSprite tmp=new ZSprite;

	lps->dwTimes++;

	tmp->m_lps=lps;
	tmp->SetRenderEngine(m_RenderEngine);

	tmp->SetRect();

	return tmp;
}

inline ZEPHYR_COLOR_MODE ZGraph::GetDefaultColorMode()
{
	return zcm_default;
}

inline void ZGraph::GetRenderRect()
{
	GetClientRect(m_hWnd, &m_rcViewport);
//   	GetClientRect(m_hWnd, &m_rcScreen);

	GetWindowRect(m_hWnd,&m_rcScreen);
//	ClientToScreen(m_hWnd, (POINT*)&m_rcScreen.left);
//	ClientToScreen(m_hWnd, (POINT*)&m_rcScreen.right);
}

inline void ZGraph::Clear() 
{ 
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Clear(); 
}

inline void ZGraph::ClearBackScreen(long x,long y,long w,long h,DWORD color)
{
	m_back.Clear(x,y,w,h,color);
}

inline void ZGraph::ClearBackScreen(DWORD color)
{
	m_back.Clear(color);
}

inline bool ZGraph::IsInited()
{
	return m_dwState.Has(ZGRAPH_STATE_INITED);
}

// 初始化成功
inline void ZGraph::IAmInit()
{
	ZASSERT(!IsInited());

	m_dwState += ZGRAPH_STATE_INITED;
}

// 释放成功 调用
inline void ZGraph::IAmRelease()
{
	ZASSERT(IsInited());

	m_dwState -= ZGRAPH_STATE_INITED;
}

inline LPZSprite ZGraph::GetBackScreen()
{
	return &m_back;
}

inline long ZGraph::GetScreenW()
{
	return m_lScreenWidth;
}

inline long ZGraph::GetScreenH()
{
	return m_lScreenHeight;
}

inline void ZGraph::SetDefaultFont(ZFont *font)
{
	ZASSERT(font != NULL);

	m_fontDefault = font;
}

inline void ZGraph::ReleaseZFont(ZFont* &font)
{
	if(font != NULL)
		delete font;

	font = NULL;
}
/*
inline HRESULT ZGraph::CreateFontSystem()
{
	if(!m_FontSystem)
		m_FontSystem=new ZFontSystem;

	return m_FontSystem->Init(this);
}

inline void ZGraph::ReleaseFontSystem()
{
	if(m_FontSystem)
	{
		delete m_FontSystem;

		m_FontSystem=NULL;
	}
}
*/
/*
inline ZFont* ZGraph::CreateFont(HFONT hfont,int len /* = ZFontDefaultCacheLen * /)
{
	return NULL;//m_FontSystem->CreateFont(hfont,len);
}

inline ZFont* ZGraph::CreateFont(int fontheight,int len /* = ZFontDefaultCacheLen * /)
{
	return NULL;//m_FontSystem->CreateFont(fontheight,len);
}
*/
/*
inline ZFont* ZGraph::GetFont(int fontheight)
{
	return m_FontSystem->GetFont(fontheight);
}

inline void ZGraph::CreateSprLoad()
{
	if(!m_sprLoad)
		m_sprLoad=new sprLoad;

	m_sprLoad->SetGraph(this);
	m_sprLoad->Init();
}

inline void ZGraph::SetSprLoadWnd(HWND hWnd)
{
	ZASSERT(m_sprLoad);

	m_sprLoad->SetHWND(hWnd);
}

inline void ZGraph::ReleaseSprLoad()
{
	if(m_sprLoad)
		delete m_sprLoad;

	m_sprLoad=NULL;
}

inline void ZGraph::SprLoadRun()
{
	ZASSERT(m_sprLoad);

	m_sprLoad->Work();
}

inline void ZGraph::LoadToCache(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag,long w,long h)
{
	ZASSERT(m_sprLoad);

	m_sprLoad->LoadToCache(filename,zcm,flag,w,h);
}

inline sprLoad *ZGraph::GetSprLoad()
{
	return m_sprLoad;
}
*/
inline void ZGraph::SetCutMode(bool cut)
{
	m_RenderEngine->SetCutMode(cut);
}

inline void ZGraph::SetCutSpr(LPSPRITE_DATA spr)
{
	m_RenderEngine->SetCutSpr(spr);
}

inline void ZGraph::Redraw()
{
	m_RenderEngine->Redraw();
}

inline void ZGraph::ReleaseBackScreen()
{
	m_back.Release();

	DEBUGMESSAGE("Release Back Screen");
}

inline HRESULT ZGraph::Render()
{
	if(m_RenderEngine->Render())
		return _render(m_back.m_lps,m_rcScreen,m_rcViewport);
	
	return S_OK;
}

inline void ZGraph::ReleaseZSprite(LPZSprite &lps)
{
	ZASSERT(lps != NULL);

	delete lps;

	lps = NULL;
}

// R5G6B5 to A1R5G5B5
inline WORD ZGraph::R5G6B5_To_A1R5G5B5(WORD color)
{
	return color == 0 ? 0 : ((color & 0x001f) | ((color & 0xffc0) >> 1) | 0x8000);
}

///////////////////////////////////////////////////////////////////////////////////
//	ZSprite

inline DWORD ZSprite::GetHeight() const
{
	ZASSERT(m_lps);

	return m_lps->dwHeight;
}

inline DWORD ZSprite::GetWidth() const
{
	ZASSERT(m_lps);

	return m_lps->dwWidth;
}

inline void ZSprite::SetRenderEngine(ZRenderEngine *pRenderEngine)
{
	ZASSERT(pRenderEngine);

	m_RenderEngine = pRenderEngine;
}

inline void ZSprite::SetRect(const RECT &r)
{
	memcpy(&m_Rect,&r,sizeof(RECT));
}

inline void ZSprite::SetRect(long l,long t,long r,long b)
{
	m_Rect.left = l;
	m_Rect.top = t;
	m_Rect.right = r;
	m_Rect.bottom = b;
}

inline const LPSPRITE_DATA ZSprite::GetData() const
{	
	return m_lps;	
}

inline void ZSprite::SetRect()
{
	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = m_lps->dwWidth;
	m_Rect.bottom = m_lps->dwHeight;
}

inline void ZSprite::Rect(long x1,long y1,long x2,long y2,DWORD color)
{
	Line(x1,y1,x2,y1,color);
	Line(x1,y1,x1,y2,color);
	Line(x2-1,y1,x2,y2,color);
	Line(x1,y2-1,x2,y2,color);
}

inline bool ZSprite::IsInited() const
{	
	return m_lps != NULL;
}

inline DWORD ZSprite::GetRectWidth() const
{
	return m_Rect.right - m_Rect.left;
}

inline DWORD ZSprite::GetRectHeight() const
{
	return m_Rect.bottom - m_Rect.top;
}

inline void ZSprite::Line(long x1,long y1,long x2,long y2,DWORD color)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Line(m_lps,x1,y1,x2,y2,color);
}

inline void ZSprite::_line(long x1,long y1,long x2,long y2,DWORD color)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->m_Graph->_line(m_lps,x1,y1,x2,y2,color);
}

inline void ZSprite::_rect(long x1,long y1,long x2,long y2,DWORD color)
{
	_line(x1,y1,x2,y1,color);
	_line(x1,y1,x1,y2,color);
	_line(x2-1,y1,x2,y2,color);
	_line(x1,y2-1,x2,y2,color);
}

//Lock & Unlock
inline HRESULT ZSprite::Lock(void **data,DWORD &pitch,long &w,long &h)
{
	return m_RenderEngine->_locksprite(m_lps,data,pitch,w,h);
}

inline void ZSprite::Unlock()
{
	m_RenderEngine->_unlocksprite(m_lps);
}

inline void ZSprite::Save(const char* filename) const
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->GetGraph()->_savebmp(filename,m_lps);
}

inline void ZSprite::SaveBmp(const char* filename) const
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->GetGraph()->_savebmp(filename,m_lps);
}

inline void ZSprite::SaveZpc(const char* filename,const char* jpgfile) const
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->GetGraph()->_savezpc(filename,jpgfile,m_lps,m_pAlpha);
}

inline void ZSprite::SaveZpc(const char* filename,DWORD format) const
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->GetGraph()->_savezpc(filename,format,m_lps,m_pAlpha);
}

inline HRESULT ZSprite::_clear(long x,long y,long w,long h,DWORD color)
{
	ZASSERT(m_RenderEngine);

	return m_RenderEngine->_clearsprite(m_lps,x,y,x+w,y+h,color);
}

inline HRESULT ZSprite::_clear(const RECT &rect,DWORD color)
{
	ZASSERT(m_RenderEngine);

	return m_RenderEngine->_clearsprite(m_lps,rect.left,rect.top,rect.right,rect.bottom,color);
}

inline HRESULT ZSprite::_clear(DWORD color)
{
	ZASSERT(m_RenderEngine);

	return m_RenderEngine->_clearsprite(m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom,color);
}

inline void ZSprite::_blt(long x1,long y1,ZSprite *lpsrc,long x2,long y2,long x3,long y3)
{
	m_RenderEngine->m_Graph->_bltsprite(m_lps,x1,y1,lpsrc->m_lps,x2,y2,x3,y3);
}

inline void ZSprite::_blt_ck(long x1,long y1,ZSprite *src,long x2,long y2,long x3,long y3)
{
	m_RenderEngine->m_Graph->_bltsprite_ck(m_lps,x1,y1,src->m_lps,x2,y2,x3,y3);
}

inline void ZSprite::_blt_zoom(long x1,long y1,long w1,long h1,ZSprite *src,long x2,long y2,long w2,long h2)
{
	m_RenderEngine->m_Graph->_bltsprite_zoom(m_lps,x1,y1,w1,h1,src->m_lps,x2,y2,w2,h2);
}

inline void ZSprite::_blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha)
{
	m_RenderEngine->m_Graph->_bltsprite_alpha(m_lps,x,y,src->m_lps,x0,y0,x1,y1,alpha);
}

inline void ZSprite::_blt_alpha_ck(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha)
{
	m_RenderEngine->m_Graph->_bltsprite_alpha_ck(m_lps,x,y,src->m_lps,x0,y0,x1,y1,alpha);
}

inline void ZSprite::_blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,ZSprite *alpha)
{
	m_RenderEngine->m_Graph->_bltsprite_alpha(m_lps,x,y,src->m_lps,x0,y0,x1,y1,alpha->m_lps,alpha->m_Rect.left,alpha->m_Rect.top);
}

inline void ZSprite::_blt_alpha(long x,long y,DWORD color,long x0,long y0,long x1,long y1,ZSprite *alpha)
{
	m_RenderEngine->m_Graph->_bltsprite_alpha(m_lps,x,y,color,x0,y0,x1,y1,alpha->m_lps,alpha->m_Rect.left,alpha->m_Rect.top);
}

inline void ZSprite::_blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1)
{
	m_RenderEngine->m_Graph->_bltsprite_alpha(m_lps,x,y,src->m_lps,x0,y0,x1,y1,src->m_pAlpha,src->m_Rect.left,src->m_Rect.top);
}

inline void ZSprite::_blt_additive(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha)
{
	m_RenderEngine->m_Graph->_bltsprite_additive(m_lps,x,y,src->m_lps,x0,y0,x1,y1,alpha);
}

inline void ZSprite::Clear(long x,long y,long w,long h,DWORD color)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Clear(m_lps,x,y,x+w,y+h,color);
}

inline void ZSprite::Clear(const RECT &rect,DWORD color)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Clear(m_lps,rect.left,rect.top,rect.right,rect.bottom,color);
}

inline void ZSprite::Clear(DWORD color)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Clear(m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom,color);
}

inline void ZSprite::Updata()
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Update(m_lps,0,0,0,0);
}

inline void ZSprite::Draw(long x,long y)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt(m_RenderEngine->GetBackScreenData(),x,y,m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom);
}

 inline void ZSprite::Draw(long x,long y,DWORD flag)
{
	ZASSERT(m_RenderEngine);

	if(flag & ZEPHYRSPRITE_BLT_COLORKEY)
		m_RenderEngine->Blt_ck(m_RenderEngine->GetBackScreenData(),x,y,m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom);
	else
		m_RenderEngine->Blt(m_RenderEngine->GetBackScreenData(),x,y,m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom);
}

inline void ZSprite::Draw_ck(long x,long y)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_ck(m_RenderEngine->GetBackScreenData(),x,y,m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom);
}

inline void ZSprite::Draw_zoom(long x,long y,long w,long h)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_zoom(m_RenderEngine->GetBackScreenData(),x,y,w,h,m_lps,m_Rect.left,m_Rect.top,m_Rect.right-m_Rect.left,m_Rect.bottom-m_Rect.top);
}

inline void ZSprite::Draw_additive(long x,long y,BYTE alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_additive(m_RenderEngine->GetBackScreenData(),x,y,m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom,alpha);
}

inline void ZSprite::Draw_alpha_ck(long x,long y,BYTE alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_alpha_ck(m_RenderEngine->GetBackScreenData(),x,y,m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom,alpha);
}

inline void ZSprite::Draw_alpha(long x,long y,ZSprite *alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_alpha(m_RenderEngine->GetBackScreenData(),x,y,
		m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom,
		alpha->m_pAlpha == NULL ? alpha->GetData() : alpha->m_pAlpha,alpha->m_Rect.left,alpha->m_Rect.top);
}

inline void ZSprite::Draw_alpha(long x,long y,BYTE alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_alpha(m_RenderEngine->GetBackScreenData(),x,y,
		m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom,
		alpha);
}

inline void ZSprite::Draw_alpha(long x,long y)
{
	if(m_pAlpha != NULL)
		m_RenderEngine->Blt_alpha(m_RenderEngine->GetBackScreenData(),x,y,
			m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom,
			m_pAlpha,m_Rect.left,m_Rect.top);
	else
		m_RenderEngine->Blt(m_RenderEngine->GetBackScreenData(),x,y,
			m_lps,m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom);
}

inline void ZSprite::Blt(long x1,long y1,ZSprite *lpsrc,long x2,long y2,long x3,long y3)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt(m_lps,x1,y1,lpsrc->GetData(),x2,y2,x3,y3);
}

inline void ZSprite::Clear_alpha(long x, long y, long w, long h, DWORD color, BYTE alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Clear_alpha(m_lps, x, y, x + w, y + h, color, alpha);
}

inline void ZSprite::Blt_ck(long x1,long y1,ZSprite *lpsrc,long x2,long y2,long x3,long y3)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_ck(m_lps,x1,y1,lpsrc->GetData(),x2,y2,x3,y3);
}

inline void ZSprite::Blt_zoom(long x1,long y1,long w1,long h1,ZSprite *src,long x2,long y2,long w2,long h2)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_zoom(m_lps,x1,y1,w1,h1,src->GetData(),x2,y2,w2,h2);
}

inline void ZSprite::Blt_zoom_alpha(long x1,long y1,long w1,long h1,ZSprite *src,long x2,long y2,long w2,long h2,BYTE alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_zoom_alpha(m_lps,x1,y1,w1,h1,src->GetData(),x2,y2,w2,h2,alpha);
}

inline void ZSprite::Blt_additive(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_additive(m_lps,x,y,src->GetData(),x0,y0,x1,y1,alpha);
}

inline void ZSprite::Blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_alpha(m_lps,x,y,src->GetData(),x0,y0,x1,y1,alpha);
}

inline void ZSprite::Blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1)
{
	ZASSERT(m_RenderEngine);

	if(src->m_pAlpha != NULL)
		m_RenderEngine->Blt_alpha(m_lps,x,y,src->GetData(),x0,y0,x1,y1,src->m_pAlpha,x,y);
	else
		m_RenderEngine->Blt(m_lps,x,y,src->GetData(),x0,y0,x1,y1);
}

inline void ZSprite::Blt_alpha_ck(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_alpha_ck(m_lps,x,y,src->GetData(),x0,y0,x1,y1,alpha);
}

inline void ZSprite::Blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,ZSprite *alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_alpha(m_lps,x,y,src->GetData(),x0,y0,x1,y1,alpha->m_pAlpha == NULL ? alpha->GetData() : alpha->m_pAlpha,alpha->m_Rect.left,alpha->m_Rect.top);
}

inline void ZSprite::Blt_alpha(long x,long y,DWORD color,long x0,long y0,long x1,long y1,ZSprite *alpha)
{
	ZASSERT(m_RenderEngine);

	m_RenderEngine->Blt_alpha(m_lps,x,y,color,x0,y0,x1,y1,alpha->m_pAlpha == NULL ? alpha->GetData() : alpha->m_pAlpha,alpha->m_Rect.left,alpha->m_Rect.top);
}

#endif //ZEPHYR_GRAPH_DOIT_H