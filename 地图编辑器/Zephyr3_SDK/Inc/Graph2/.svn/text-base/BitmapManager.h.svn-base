/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\BitmapManager.h

							Describe:	BitmapManager

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.27
							UpdateTime:
*/

#ifndef _ZEPHYR_3_GRAPH_2_BITMAPMANAGER_H
#define _ZEPHYR_3_GRAPH_2_BITMAPMANAGER_H

#include <string>
#include <map>

#include <Graph2\Bitmap.h>
#include <Graph2\GraphImp.h>

namespace ZGraph2{

	//////////////////////////////////////////////////////////////////////////////////////////////
	// BitmapManager

	class ZEPHYR_GRAPH_2_API BitmapManager{
	public:
		typedef std::map<std::string, Bitmap::_Ptr> _Map;
	public:
		// 构造函数
		BitmapManager(GraphImpPtr ptr) {
			ZASSERT(!Zephyr3::_IsNull(ptr));

			m_GraphImpPtr = ptr;
		}

		// 读取bmp图片
		LPBitmap LoadBmp(const char* name,WORD zcm,WORD flag);

		// 读取zpc图片
		LPBitmap LoadZpc(const char* name,WORD zcm,WORD flag);

		// 读取jpg图片
		LPBitmap LoadJpg(const char* name,WORD zcm,WORD flag);
	protected:
		// 从内存中读取jpg图片
		LPBitmap _LoadJpg(void* data,DWORD len,WORD zcm,WORD flag);

		// 创建位图
		LPBitmap CreateBitmap(DWORD w,DWORD h,WORD zcm,WORD flag);

		// 增加结点
		void AddNode(const char* name,Bitmap::_Ptr ptr) {
			m_map[name] = ptr;
		}

		// 搜索结点
		HRESULT FindNode(Bitmap::_Ptr& ptr,const char* name) {

			_Map::iterator it = m_map.find(name);

			if(it == m_map.end())
				return E_FAIL;

			ptr = it->second;

			return S_OK;
		}
	protected:
		_Map		m_map;
		GraphImpPtr	m_GraphImpPtr;
	};

	typedef Zephyr3::AutoPtr<BitmapManager>	BitmapManagerPtr;
};

#endif // _ZEPHYR_3_GRAPH_2_BITMAPMANAGER_H