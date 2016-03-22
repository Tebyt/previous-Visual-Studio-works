/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\RenderEngine.h

							Describe:	渲染引擎

							Author:		赵洪松(xueren)

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
	// 普通的渲染引擎，只是简单的实现异步渲染而已，不做任何的优化

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