#ifndef ZEPHYR_RENDERENGINE_H
#define ZEPHYR_RENDERENGINE_H

#include <windows.h>

#include <ZDebug.h>
#include <Graph\BaseDef.h>

//render operate
const DWORD _zre_operate_null				=	0;		//null
const DWORD _zre_operate_blt				=	1;		//blt
const DWORD	_zre_operate_clear				=	2;		//clear
const DWORD	_zre_operate_update				=	3;		//update
const DWORD _zre_operate_blt_ck				=	4;		//colorkey blt
const DWORD _zre_operate_printf				=	5;		//printf
const DWORD _zre_operate_line				=	6;		//line
const DWORD _zre_operate_blt_zoom			=	7;		//blt zoom
const DWORD _zre_operate_blt_alpha			=	8;		//blt alpha
const DWORD _zre_operate_printf_lim			=	9;		//printf limit width
const DWORD _zre_operate_blt_additive		=	10;		//blt additive
//const DWORD _zre_operate_update				=	11;		//update
const DWORD _zre_operate_blt_alpha_ck		=	12;		//alpha & ck
const DWORD _zre_operate_blt_alphaspr		=	13;		//alpha spr
const DWORD _zre_operate_blt_color_alphaspr	=	15;		//color & alpha spr
const DWORD _zre_operate_blt_zoom_alpha		=	16;		//blt zoom
const DWORD	_zre_operate_clear_alpha		=	17;		//clear alpha

const unsigned _zrenderengine_parambuffsize	=	1024*100;

struct ZRE_PARAMBUFF{
	unsigned long	cur;
	void			*buff;
	ZRE_PARAMBUFF	*next;

	ZRE_PARAMBUFF(){
		cur = 0;
		buff = NULL;
		next = NULL;
	}
};

class ZEPHYR_API ZRenderEngine{
	friend class ZGraph;
	friend class ZSprite;

const DWORD	RECTLIST_NODE_NOTDRAW;
const DWORD	RECTLIST_NODE_NOTPROCESS;

	struct rectlist_node{
		RECT	rect;
		void	*dst;
		RECT	src_rect;
		void	*src;
		DWORD	operate;
		void	*param;
		DWORD	state;

		rectlist_node()
		{
			dst = src = param = NULL;
			state = 0;
		}
	};

	struct rectlist{
		ZLinkEx<rectlist_node,16,16>	link;
		ZRE_PARAMBUFF	*pBuff,*pCur;
		void *_curparam;
		unsigned long size;
	};

private:
//graph
	ZGraph		*m_Graph;

//rect list
	rectlist	*m_rectCur;
	rectlist	*m_rectOld;
	rectlist	*m_rectDraw;
	rectlist	*m_rectCut;

	bool		m_bCut;

	LPSPRITE_DATA	m_cutSpr;

//	bool		m_bRedraw;
public:
	inline ZRenderEngine();
	~ZRenderEngine() { Release(); }

	inline ZGraph* GetGraph();
private:
	//init
	HRESULT Init(ZGraph* graph);
	//Release
	void Release();

//zfont
	inline ZFont* GetDefaultFont();//(int height);

//graph
	void Blt(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1);
	void Blt_ck(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1);
	void Clear_alpha(LPSPRITE_DATA dst, long x0, long y0, long x1, long y1, DWORD color, BYTE alpha);
	void Clear(LPSPRITE_DATA dst,long x0,long y0,long x1,long y1,DWORD color);
	void Printf(LPSPRITE_DATA dst,int fontheight,long x,long y,DWORD color,const char* text);
	void Printf(LPSPRITE_DATA dst,ZFont* zfont,long x,long y,DWORD color,const char* text);
	void Line(LPSPRITE_DATA dst,long x1,long y1,long x2,long y2,DWORD color);
	void Blt_zoom(LPSPRITE_DATA dst,long x,long y,long w,long h,LPSPRITE_DATA src,long x0,long y0,long w0,long h0);
	void Blt_zoom_alpha(LPSPRITE_DATA dst,long x,long y,long w,long h,LPSPRITE_DATA src,long x0,long y0,long w0,long h0,BYTE alpha);
	void Blt_alpha(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha);
	void Blt_alpha_ck(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha);
	void Blt_alpha(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,LPSPRITE_DATA alpha,long x2,long y2);
	void Blt_alpha(LPSPRITE_DATA dst,long x,long y,DWORD color,long x0,long y0,long x1,long y1,LPSPRITE_DATA alpha,long x2,long y2);
	void Blt_additive(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha);
	void Printf(LPSPRITE_DATA dst,int fontheight,long x,long y,DWORD color,const char* text,long max_x);
	void Printf(LPSPRITE_DATA dst,ZFont* zfont,long x,long y,DWORD color,const char* text,long max_x);
	void Update(LPSPRITE_DATA dst,long x,long y,long x1,long y1);

	inline LPSPRITE_DATA _createsprite(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	inline void ReleaseSprite(LPSPRITE_DATA &lps);

	inline HRESULT _clearsprite(LPSPRITE_DATA lps,long x,long y,long r,long b,DWORD color);

	inline LPSPRITE_DATA GetBackScreenData();

	inline HRESULT _locksprite(LPSPRITE_DATA lps,void **pvoid,DWORD &pitch,long &w,long &h);
	inline HRESULT _unlocksprite(LPSPRITE_DATA lps);
	inline HRESULT _locksprite_r(LPSPRITE_DATA lps,RECT *rect,void **pvoid,DWORD &pitch,long &w,long &h);

//render
	//! 渲染增强版，可以根据参数决定是否渲染，主要用于跳帧
	int RenderEx(bool bRealRender);
	int Render();
	int RenderCut();

	void Redraw();
//	int RenderBackCut();

	inline void SetCutMode(bool cut);
	inline void SetCutSpr(LPSPRITE_DATA spr);

	void Clear();
private:
//param
	ZRE_PARAMBUFF* CreateParamBuff();
	void ReleaseParamBuff(rectlist* list);
	inline void ClearParamBuff(rectlist* list);
	inline void SaveParam(rectlist* list,DWORD dwparam);
	inline void SaveParam(rectlist* list,WORD wparam);
	inline void SaveParam(rectlist* list,BYTE bparam);
	void SaveParam(rectlist* list,const void *param,unsigned size);
	void *RequestParamSize(rectlist* list,unsigned size);
//node
	inline void ClearState(rectlist_node* node);
	inline void SetStateNotDraw(rectlist_node* node);
	inline void ClrStateNotDraw(rectlist_node* node);
	inline BOOL IsDrawNode(rectlist_node* node);
	inline void SetStateNotProcess(rectlist_node* node);
	inline void ClrStateNotProcess(rectlist_node* node);
	inline BOOL IsNotProcessNode(rectlist_node* node);
//list
	void CutList(rectlist* list,RECT &rect);
	int CutNode(rectlist_node* node,RECT &rect,rectlist_node* newnode);
	inline bool RectInNode(rectlist_node* node,RECT &rect);

	bool IsInList(rectlist* list,rectlist_node* node);
	bool EquNode(rectlist_node* dst,rectlist_node* src);

	void AddToList(rectlist* list,rectlist_node* node,bool draw);

	void BuildingFrame();

	void ThisFrame(rectlist* list,void* index,RECT& rect);
	void PreFrame(rectlist* list,RECT& rect);
};

inline ZRenderEngine::ZRenderEngine() : RECTLIST_NODE_NOTDRAW(0x01),RECTLIST_NODE_NOTPROCESS(0x02)
{
	m_rectCur=m_rectOld=NULL;
	m_rectDraw=NULL;

//	m_bRedraw=false;

	Init(NULL);
}

#endif	//ZEPHYR_RENDERENGINE_H