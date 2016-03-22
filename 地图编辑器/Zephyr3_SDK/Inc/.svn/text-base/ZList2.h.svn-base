/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZList2.h

							Describe:	列表

							Author:		赵洪松(xueren)

							CreateTime: 2003.12.24
							UpdateTime:
*/

#ifndef _ZEPHYR_3_LIST_2_H
#define _ZEPHYR_3_LIST_2_H

#include <Zephyr.h>

#include <ZArray2.h>

namespace Zephyr3{

	//////////////////////////////////////////////////////////////////////////////
	// ZList2
	// 说明：列表

	template<class T,unsigned int SIZE,unsigned int ADD_SIZE = SIZE>
	class ZList{
	public:
		// 缺省构造函数
		ZList() { m_Used = 0; }

		// 构造函数，使用现有内存空间
		ZList(T *dat,unsigned int size,unsigned int used) : m_List(dat,size) { m_Used = used; }

		// 在尾部增加列表单元
		HRESULT Add(T& obj) {

			if(m_Used >= m_List.GetTotalSize())
			{
				if(m_List.Realloc(m_List.GetTotalSize() + ADD_SIZE) != S_OK)
					return ZRet(E_FAIL,"ZList::Add() fail!");
			}
			
			m_List[m_Used++] = obj;

			return S_OK;
		}

		// 获得尾部可用单元指针
		// 注意：该单元没有被使用，该函数一般和 Add 函数配合直接增加新结点，省却一个 memcpy 的工作
		T* GetEndObjPoint() {
			if(m_Used >= m_List.GetTotalSize())
			{
				if(m_List.Realloc(m_List.GetTotalSize()+ADD_SIZE) != S_OK)
					return NULL;
			}

			return &m_List[m_Used];
		}

		// 增加一个单元
		// 注意：该函数一般和 GetEndObjPoint 配合使用
		void Add() { m_Used++; }

		// 删除对象
		// 注意：必须保证 index 已经被使用
		void Del(unsigned int index) {
			ZASSERT(index < m_Used);

			for(;index<m_Used-1;index++)
				m_List[index] = m_List[index+1];

			m_Used--;
		}

		// dst <---> src
		// 注意：必须保证 dst 、src 都可用
		void Change(unsigned int dst,unsigned int src) {
			ZASSERT(dst < m_Used && src < m_Used);

			T t = m_List[dst];
			m_List[dst] = m_List[src];
			m_List[src] = t;
		}

		// 删除最后一个结点，且将删除结点指针返回
		// 注意：必须保证有结点
		// 注意：如果需要使用返回的指针，必须保证使用以前，都没有继续添加结点，就是保证没有调用任何 Add 函数
		T* DelLastObj() {

			ZASSERT(m_Used > 0);

			return &m_List[--m_Used];
		}

		//清空
		void Clear() { m_Used = 0; }

		//获得已经使用到的个数
		unsigned int GetUsed() const { return m_Used; }

		T& operator[](const unsigned int index) { return m_List[index]; }

		T* GetData() { return m_List.GetData(); }

		unsigned int GetTotalSize()	const { return m_List.GetTotalSize(); }

	private:
		ZArray<T,SIZE>	m_List;
		unsigned int	m_Used;
	};
};

#endif	// _ZEPHYR_3_LIST_2_H