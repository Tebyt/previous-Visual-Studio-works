#ifndef ZEPHYR_GRAPH_H
#define ZEPHYR_GRAPH_H

//#include <ddraw.h>
//#include <d3d.h>

#include <ZDebug.h>
#include <ZState.h>
#include <Graph\BaseDef.h>
#include <Graph\ZFont_2.h>
#include <Graph\SprLoad.h>
#include <Graph\ZSpriteManager.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZGraph 基类
//带下划线的，如无必要，最好不要使用

const DWORD	ZGRAPH_STATE_INITED		=	0x01;
const DWORD	ZGRAPH_STATE_FULLSCREEN	=	0x02;

class ZEPHYR_API ZGraph{
	friend class sprLoad;
	friend class ZRenderEngine;
	friend class ZSprite;
	friend class ZFont;
	friend class ZSmoothVectorFont;
	friend class ZVectorFont;
	friend class ZSpriteManager;
public:
	// 构造函数
	inline ZGraph();
	// 构造函数
	inline ZGraph(HWND hWnd,HINSTANCE hInst);
	// 析构函数
	virtual ~ZGraph() { ; }

	// 设置窗口句柄
	inline void SetHWND(HWND hWnd);
	// 设置实例
	inline void SetInstance(HINSTANCE hInst);

	// 是否已经初始化
	inline bool IsInited();

	// 获得缺省 颜色模式
	inline ZEPHYR_COLOR_MODE GetDefaultColorMode();
	// 获得 渲染矩形区
	inline void GetRenderRect();

	// 获得 屏幕宽度
	inline long GetScreenW();
	// 获得 屏幕高度
	inline long GetScreenH();

	// R5G6B5 to A1R5G5B5
	inline WORD R5G6B5_To_A1R5G5B5(WORD color);

//ZRenderEngine Cut State
	inline void SetCutMode(bool cut);
	inline void SetCutSpr(LPSPRITE_DATA spr);

//ZRenderEngine Redraw Screen
	inline void Redraw();

//sprLoad
	inline void CreateSprLoad();
	inline void SetSprLoadWnd(HWND hWnd);
	inline void ReleaseSprLoad();
	inline void SprLoadRun();
	inline void LoadToCache(const char *filename,ZEPHYR_COLOR_MODE zcm,DWORD flag,long w,long h);
	inline sprLoad *GetSprLoad();

//font
	inline void SetDefaultFont(ZFont *font);
	inline void ReleaseZFont(ZFont* &font);
	ZFont *GetDefaultFont() { return m_fontDefault; }

//render
	HRESULT RenderEx(RECT &screen, bool bRealRender);			//render
	HRESULT Render(ZSprite &backscreen);	//render
	inline HRESULT Render();				//render
	HRESULT Render(RECT &screen);			//render

	// render to screen
	void RenderToScreen(RECT &screen);
	// render to backscreen
	void RenderToBack();
	// render to backscreen
	void RenderToBackEx(bool bRealRender);

	// clear renderlist
	inline void Clear();

//sprite
	inline LPZSprite CreateSprite(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	inline LPZSprite CreateSprite(LPSPRITE_DATA lps);

//backscreen
	// return back screen data
	inline LPSPRITE_DATA GetBackScreenData();
	// Clear back screen with color
	inline void ClearBackScreen(long x,long y,long w,long h,DWORD color);
	// Clear back screen with color
	inline void ClearBackScreen(DWORD color);
	// return back with LPZSprite
	inline LPZSprite GetBackScreen();

	// release backscreen
	inline void ReleaseBackScreen();
//render engine
	HRESULT CreateRenderEngine();
	void ReleaseRenderEngine();
	ZRenderEngine* GetRenderEngine() { return m_RenderEngine;}

//文件操作 Load 到 ZSprite
//graph file
	// load file *.bmp *.tga *.zpc *.jpg ......
	LPZSprite Load(const char* filename,DWORD flag);

	inline void ReleaseZSprite(LPZSprite &lps);

	bool IsPNG(const char* name);
protected:
	// 初始化成功 调用
	inline void IAmInit();
	// 释放成功 调用
	inline void IAmRelease();

//bmp file
protected:
	void _savebmp(const char* filename,LPSPRITE_DATA lps);
	LPSPRITE_DATA _loadbmp(LPSPRITE_DATA& pAlpha,const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	LPSPRITE_DATA _loadtga(LPSPRITE_DATA& pAlpha,const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	LPSPRITE_DATA _loadpng(LPSPRITE_DATA& pAlpha,const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	LPSPRITE_DATA _loadgif(LPSPRITE_DATA& pAlpha,const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);
public:
	LPZSprite LoadBmp(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	LPZSprite LoadTga(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	LPZSprite LoadPng(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	LPZSprite LoadGif(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);
//zpc file
protected:
	HRESULT _set_spritecolorkey_maskrle(LPSPRITE_DATA lps,BYTE *data,ULONG len);
	BYTE *_get_spritecolorkey_maskrle(LPSPRITE_DATA lps,ULONG &len);
	LPSPRITE_DATA _loadzpc(LPSPRITE_DATA& pAlpha,const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	HRESULT _savezpc(const char* filename,const char* jpgfile,LPSPRITE_DATA lps, LPSPRITE_DATA pAlpha = NULL);
	HRESULT _savezpc(const char* filename,DWORD Format,LPSPRITE_DATA lps, LPSPRITE_DATA pAlpha = NULL);
public:
	LPZSprite LoadZpc(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

//jpeg file
protected:
	LPSPRITE_DATA _loadjpg(LPSPRITE_DATA& pAlpha,const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	LPSPRITE_DATA _loadjpg(void *data,DWORD len,ZEPHYR_COLOR_MODE zcm,DWORD flag);
public:
	LPZSprite LoadJpg(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	LPZSprite LoadJpg(void *data,DWORD len,ZEPHYR_COLOR_MODE zcm,DWORD flag);

//////////////////////////////////////////////////////////////////////
//virtual
	virtual void Release() = 0;

	virtual HRESULT Init(bool bWindow,DWORD W,DWORD H,ZEPHYR_COLOR_MODE zcm,bool bUsevm = true) = 0;

	virtual ZFont *CreateSmoothFont(HFONT hFont) = 0;
	virtual ZFont *CreateFont(HFONT hFont) = 0;

	virtual void ReSizeBackScreen(long w,long h,ZEPHYR_COLOR_MODE zcm,bool bUsevm = true) = 0;

public:
	// 创建 spr 管理器
	virtual HRESULT CreateSpriteManager() = 0;
//render
	virtual void _beginrender() = 0;
	virtual void _endrender() = 0;
	virtual HRESULT _render(LPSPRITE_DATA backscreen,RECT &screen,RECT &viewport) = 0;

//sprite
	virtual LPSPRITE_DATA _createsprite(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag) = 0;
	virtual void _releasesprite(LPSPRITE_DATA &lps) = 0;

	virtual HRESULT _clearsprite_alpha(LPSPRITE_DATA lps, long x, long y, long r, long b, DWORD color, BYTE alpha) = 0;
	virtual HRESULT _clearsprite(LPSPRITE_DATA lps,long x,long y,long r,long b,DWORD color) = 0;
	virtual HRESULT _bltsprite(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1) = 0;
	virtual HRESULT _bltsprite_ck(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1) = 0;
	virtual HRESULT _bltsprite_zoom(LPSPRITE_DATA dst,long x,long y,long w,long h,LPSPRITE_DATA src,long x0,long y0,long w0,long h0) = 0;
	virtual HRESULT _bltsprite_zoom_alpha(LPSPRITE_DATA dst,long x,long y,long w,long h,LPSPRITE_DATA src,long x0,long y0,long w0,long h0,BYTE alpha) = 0;
	virtual HRESULT _bltsprite_alpha(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha) = 0;
	virtual HRESULT _bltsprite_alpha_ck(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha) = 0;
	virtual HRESULT _bltsprite_alpha(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,LPSPRITE_DATA alpha,long x2,long y2) = 0;
	virtual HRESULT _bltsprite_alpha(LPSPRITE_DATA dst,long x,long y,DWORD color,long x0,long y0,long x1,long y1,LPSPRITE_DATA alpha,long x2,long y2) = 0;
	virtual HRESULT _bltsprite_additive(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha) = 0;

	virtual HRESULT _locksprite(LPSPRITE_DATA lps,void **pvoid,DWORD &pitch,long &w,long &h) = 0;
	virtual HRESULT _unlocksprite(LPSPRITE_DATA lps) = 0;
	virtual HRESULT _locksprite_r(LPSPRITE_DATA lps,RECT *rect,void **pvoid,DWORD &pitch,long &w,long &h) = 0;

	virtual void _setcolorkey(void *lpds) = 0;

//	virtual void _drawchar(LPSPRITE_DATA lps,long x,long y,DWORD color,LPZFONT_DATA dat) = 0;

//图形函数
	virtual void _line(LPSPRITE_DATA lps,long x1,long y1,long x2,long y2,DWORD color) = 0;

//other
	virtual void _printanything() = 0;

	virtual LPSPRITE_DATA Clone(LPSPRITE_DATA pSrc) = 0;

protected:
	ZEPHYR_RENDER_MODE	m_zrm;				//render mode
	HWND				m_hWnd;				//hwnd
	HINSTANCE			m_hInst;
	bool				m_bWindow;			//window?
	long				m_lScreenWidth;
	long				m_lScreenHeight;	//screen's w/h
	ZEPHYR_COLOR_MODE	m_zcm;				//color mode
	RECT				m_rcScreen;
	RECT				m_rcViewport;		//render screen RECT
	ZSprite				m_back;				//backscreen

	bool				m_bIs555;

	ZEPHYR_COLOR_MODE	zcm_default;		//缺省的sprite用zcm

	ZRenderEngine		*m_RenderEngine;

	ZFont				*m_fontDefault;

	sprLoad				*m_sprLoad;

	ZSpriteManager		*m_sprManager;

	ZState_DWord		m_dwState;
};

// 构造函数
inline ZGraph::ZGraph()
{
	m_hWnd = NULL;
	m_zrm = ZRM_D3D7;
	m_hInst = 0;
	m_RenderEngine = NULL;
	m_fontDefault = NULL;
	m_sprLoad = NULL;
	m_sprManager = NULL;
};

// 构造函数
inline ZGraph::ZGraph(HWND hWnd,HINSTANCE hInst)
{
	m_hWnd = hWnd;
	m_hInst = hInst;

	m_zrm = ZRM_D3D7;
	m_RenderEngine = NULL;
	m_fontDefault = NULL;
	m_sprLoad = NULL;
	m_sprManager = NULL;
}

typedef ZGraph* LPZGraph;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZGraph 基本函数

//创建 ZGraph
//zrm为渲染模式，可以为	ZRM_GDI、ZRM_DD7、ZRM_D3D7
//bWindow为真则表示窗口模式
//w、h为初始化窗口大小
//zcm为颜色模式，2D程序建议为ZCM_R5G6B5
//bUseVM为真，表示背景缓冲使用显存，GDI模式该参数被忽略
//bChange为真，则表示如果无法创建zrm模式的ZGraph，可以创建低一级的ZGraph
LPZGraph ZEPHYR_API CreateZGraph(ZEPHYR_RENDER_MODE zrm,bool bWindow,DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,bool bUseVM = true,bool bChange = false);

//释放ZGraph
//pGraph 必须为非空值
void ZEPHYR_API ReleaseZGraph(ZGraph* &pGraph);

#endif