/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	WTL\DlgGraph.h

							Describe:	WTL 的 DlgGraph 支持

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.15
							UpdateTime:
*/

#ifndef _ZEPHYR_3_WTL_DLGGRAPH_H
#define _ZEPHYR_3_WTL_DLGGRAPH_H

#include <Graph\ZGraph_GDI.h>

namespace ZephyrWTL{

	//////////////////////////////////////////////////////////////////////////
	// DlgGraph

	class ZEPHYRWTL_API DlgGraph{
	public:
		// 构造函数
		DlgGraph() {
			m_hInst = NULL;
			m_pGraph = NULL;
			m_hWnd = NULL;
		}

		// 初始化
		HRESULT Init(HINSTANCE hInst,HWND hWnd);

		// 释放资源
		void Release();

		// 获得安全的ZGraph
		const ZGraph* GetSafeGraph() const { return m_pGraph; }

		// 获得ZGraph
		ZGraph* GetGraph() { return m_pGraph; }
	protected:
		ZGraph*		m_pGraph;
	private:
		HINSTANCE	m_hInst;
		HWND		m_hWnd;
	};
};

#endif // _ZEPHYR_3_WTL_DLGGRAPH_H