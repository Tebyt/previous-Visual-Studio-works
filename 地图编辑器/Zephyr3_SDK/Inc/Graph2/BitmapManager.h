/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\BitmapManager.h

							Describe:	BitmapManager

							Author:		�Ժ���(xueren)

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
		// ���캯��
		BitmapManager(GraphImpPtr ptr) {
			ZASSERT(!Zephyr3::_IsNull(ptr));

			m_GraphImpPtr = ptr;
		}

		// ��ȡbmpͼƬ
		LPBitmap LoadBmp(const char* name,WORD zcm,WORD flag);

		// ��ȡzpcͼƬ
		LPBitmap LoadZpc(const char* name,WORD zcm,WORD flag);

		// ��ȡjpgͼƬ
		LPBitmap LoadJpg(const char* name,WORD zcm,WORD flag);
	protected:
		// ���ڴ��ж�ȡjpgͼƬ
		LPBitmap _LoadJpg(void* data,DWORD len,WORD zcm,WORD flag);

		// ����λͼ
		LPBitmap CreateBitmap(DWORD w,DWORD h,WORD zcm,WORD flag);

		// ���ӽ��
		void AddNode(const char* name,Bitmap::_Ptr ptr) {
			m_map[name] = ptr;
		}

		// �������
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