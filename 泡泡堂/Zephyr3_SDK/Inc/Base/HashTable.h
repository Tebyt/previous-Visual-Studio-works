/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\HashTable.h

							Describe:	HASH±Ì

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2004.04.28
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_HASHTABLE_H
#define _ZEPHYR_3_BASE_HASHTABLE_H

#include <Base\List.h>

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////////////
	// HashTable

	template<typename T,unsigned int W,unsigned int H,unsigned int W_ADD,unsigned int H_ADD>
	class HashTable{
	public:
		typedef Link<T,W,W_ADD>	_WLink;
		typedef Link<_WLink,H,H_ADD> _HLink;
	public:
		// ππ‘Ï∫Ø ˝
		HashTable() {}
	private:
		_HLink	m_link;
	};
};

#endif // _ZEPHYR_3_BASE_HASHTABLE_H