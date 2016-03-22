/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\Graph.h

							Describe:	Graph

							Author:		�Ժ���(xueren)

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
		// ���캯��
		Graph(DWORD mode,HWND hWnd,DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,DWORD flag) {

			ZASSERT_R(InitGraphImp(mode,hWnd,w,h,zcm,flag) == S_OK);

			ZASSERT_R(Init() == S_OK);
		}
		// ��������
		~Graph() {}

		// ��Ⱦ
		void RenderToScreen(RECT rect) {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->RenderToScreen(rect);
		}

		// ��Ⱦ
		void RenderToScreen() {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->RenderToScreen();
		}

		// ��Ⱦ����������
		void RenderToBackScreen(RECT rect) {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->RenderToBackScreen(rect);
		}

		// ��Ⱦ����������
		void RenderToBackScreen() {
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->RenderToBackScreen();
		}

		// �����ĻWidth
		DWORD GetScreenWidth() const { 
			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			return m_pGraphImp->GetScreenWidth();
		}
		// �����ĻHeight
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
		// ��ʼ��ͼ��ʵ��ģ��
		HRESULT InitGraphImp(DWORD mode,HWND hWnd,DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,DWORD flag);
		// ��ʼ��
		HRESULT Init();
	private:
		GraphImpPtr			m_pGraphImp;
		BitmapManagerPtr	m_pBitmapManager;
	};

	typedef Zephyr3::AutoPtr<Graph>	GraphPtr;
};

#endif // _ZEPHYR_GRAPH_2_GRAPH_H