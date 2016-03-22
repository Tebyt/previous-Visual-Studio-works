/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\RenderEngine.h

							Describe:	��Ⱦ����

							Author:		�Ժ���(xueren)

							CreateTime: 2004.04.24
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_2_RENDERENGINE_H
#define _ZEPHYR_GRAPH_2_RENDERENGINE_H

#include <Graph2\BaseDef.h>
#include <Graph2\GraphImp.h>

namespace ZGraph2{

	///////////////////////////////////////////////////////////////////////////////////////////
	// RenderEngine
	// ��ͨ����Ⱦ���棬ֻ�Ǽ򵥵�ʵ���첽��Ⱦ���ѣ������κε��Ż�

	class RenderEngine{
	public:
		RenderEngine(GraphImp* ptr) {

			ZASSERT(ptr != NULL);

			m_pGraphImp = ptr;
		}

		virtual ~RenderEngine() {}

		virtual void Render();

		virtual void Render(RECT rect);
	protected:
		GraphImp*		m_pGraphImp;
	};
};

#endif // _ZEPHYR_GRAPH_2_RENDERENGINE_H