/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	WTL\DlgGraph.h

							Describe:	WTL �� DlgGraph ֧��

							Author:		�Ժ���(xueren)

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
		// ���캯��
		DlgGraph() {
			m_hInst = NULL;
			m_pGraph = NULL;
			m_hWnd = NULL;
		}

		// ��ʼ��
		HRESULT Init(HINSTANCE hInst,HWND hWnd);

		// �ͷ���Դ
		void Release();

		// ��ð�ȫ��ZGraph
		const ZGraph* GetSafeGraph() const { return m_pGraph; }

		// ���ZGraph
		ZGraph* GetGraph() { return m_pGraph; }
	protected:
		ZGraph*		m_pGraph;
	private:
		HINSTANCE	m_hInst;
		HWND		m_hWnd;
	};
};

#endif // _ZEPHYR_3_WTL_DLGGRAPH_H