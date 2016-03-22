/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\Graph.h

							Describe:	Graph

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.24
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_2_GRAPH_H
#define _ZEPHYR_GRAPH_2_GRAPH_H

#include <Graph2\BaseDef.h>
#include <Graph2\GraphImp.h>
#include <Graph2\BitmapManager.h>

namespace ZGraph2{

	///////////////////////////////////////////////////////////////////////////////////////////
	// Graph

	class ZEPHYR_GRAPH_2_API Graph{
	public:
		enum{
			_MODE_GDI = 1,
			_MODE_D3D = 2
		};
	public:
		// 构造函数
		Graph(DWORD mode,HWND hWnd,DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,DWORD flag) {

			ZASSERT_R(InitGraphImp(mode,hWnd,w,h,zcm,flag) == S_OK);

			ZASSERT_R(Init() == S_OK);
		}
		// 析构函数
		~Graph() {}

		// 渲染
		void RenderToScreen(RECT rect) {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->RenderToScreen(rect);
		}

		// 渲染
		void RenderToScreen() {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->RenderToScreen();
		}

		// 渲染到背景缓冲
		void RenderToBackScreen(RECT rect) {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->RenderToBackScreen(rect);
		}

		// 渲染到背景缓冲
		void RenderToBackScreen() {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->RenderToBackScreen();
		}

		// 获得屏幕Width
		DWORD GetScreenWidth() const { 
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			return m_pGraphImp->GetScreenWidth();
		}
		// 获得屏幕Height
		DWORD GetScreenHeight() const { 
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			return m_pGraphImp->GetScreenHeight();
		}

		// Clear BackScreen
		void ClearBackScreen(int x,int y,int w,int h,DWORD color) {

			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->ClearBackScreen(x,y,w,h,color);
		}

		// Clear BackScreen
		void _ClearBackScreen(int x,int y,int w,int h,DWORD color) {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->_ClearBackScreen(x,y,w,h,color);
		}

		// Clear Command
		void ClearCmd() {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->ClearCmd();
		}
	protected:
		// 初始化图形实现模块
		HRESULT InitGraphImp(DWORD mode,HWND hWnd,DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,DWORD flag);
		// 初始化
		HRESULT Init();
	private:
		GraphImpPtr			m_pGraphImp;
		BitmapManagerPtr	m_pBitmapManager;
	};

	typedef Zephyr3::AutoPtr<Graph>	GraphPtr;
};

#endif // _ZEPHYR_GRAPH_2_GRAPH_H