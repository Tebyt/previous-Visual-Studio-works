/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZLinkEx.h

							Describe:	链表

							Author:		赵洪松(xueren)

							CreateTime: 2004.03.16
							UpdateTime:
*/

#ifndef _ZEPHYR_3_LINK_EX_H
#define _ZEPHYR_3_LINK_EX_H

#include <Zephyr.h>

#include <vector>

#if _MSC_VER <= 1020
# define TYPENAME
#else
# define TYPENAME typename
#endif

//#define _ZEPHYR_3_LINK_EX_SAFE_

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////////////////////////
	// Link

	template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
	class Link{
	public:
		struct Node{
			T		obj;
			Node*	pNext;

			// 构造函数
			Node() { pNext = NULL; }
		};

		typedef Node*	LPNode;

		typedef std::vector<LPNode> Array;
	public:
		// 构造函数
		Link() { 
			m_pHead = m_pEnd = m_pLast = NULL;
			m_uiTotal = m_uiUsed = 0;

			m_pHead = Alloc(SIZE);
			ZASSERT_R(m_pHead != NULL);

			m_pEnd = NULL;
		}
		// 析构函数
		~Link() { Release(); }

		// 资源释放
		void Release() {

			Clear();

			for(Array::size_type i = 0; i < m_memory.size(); i++)
			{
				if(m_memory[i] != NULL)
					delete[] m_memory[i];
			}

			m_memory.clear();
		}

		// 获得使用的长度
		unsigned int GetUsed() const { return m_uiUsed; }
		// 获得总长度
		unsigned int GetTotal() const { return m_uiTotal; }

		// 获得首结点数据指针
		const T* GetHeadObjPoint() const { return m_uiUsed == 0 ? NULL : &(m_pHead->obj); }
		// 获得尾结点数据指针
		const T* GetEndObjPoint() const { return m_uiUsed == 0 ? NULL : &(m_pEnd->obj); }
/*
		// 获得首结点数据
		const T& GetHeadObj() const { return m_uiUsed == 0 ? NULL : m_pHead->obj; }
		// 获得尾结点数据
		const T& GetEndObj() const { return m_uiUsed == 0 ? NULL : m_pEnd->obj; }
*/
		// 获得尾结点指针
		TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode GetHeadNode() const { return m_uiUsed == 0 ? NULL : m_pHead; }
		// 获得首结点指针
		TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode GetEndNode() const { return m_uiUsed == 0 ? NULL : m_pEnd; }

		// 增加尾部结点
		T* Add() {

			if(m_pEnd == NULL)
			{
				m_pEnd = m_pHead;

				m_uiUsed++;

				return &(m_pEnd->obj);
			}

			if(m_pEnd->pNext == NULL)
			{
				m_pEnd->pNext = Alloc(ADD_SIZE);
				ZASSERT_R(m_pEnd->pNext != NULL);
			}

//			T* tmp = &(m_pEnd->pNext->obj);

			m_pEnd = m_pEnd->pNext;

			m_uiUsed++;

			return &(m_pEnd->obj);
		}

		// 增加新结点
		void Add(T& obj) {

			if(m_pEnd == NULL)
			{
#ifdef _ZEPHYR_3_LINK_EX_SAFE_
//				ZASSERT(m_uiUsed == 0);
				if(m_uiUsed != 0)
					Debug("Zephyr3::Link Add fail! End == NULL && used != 0");
#endif // _ZEPHYR_3_LINK_EX_SAFE_

				m_pEnd = m_pHead;

				m_uiUsed++;

				m_pEnd->obj = obj;

				return ;
			}

			if(m_pEnd->pNext == NULL)
			{
				m_pEnd->pNext = Alloc(ADD_SIZE);
				ZASSERT_R(m_pEnd->pNext != NULL);
			}

			m_pEnd = m_pEnd->pNext;

			m_pEnd->obj = obj;

			m_uiUsed++;
		}

		void Del_point(const T* pDat) {

			switch(GetUsed())
			{
			case 0:
				return ;
			case 1:

#ifdef _ZEPHYR_3_LINK_EX_SAFE_
				if(pDat != &(m_pHead->obj))
				{
					Debug("Zephyr3::Link Del_point fail! (pDat != &(m_pHead->obj))");

					return ;
				}

//				ZASSERT_R(pDat == &(m_pHead->obj));
				DelNode(NULL,m_pHead);
				return ;
#else	// _ZEPHYR_3_LINK_EX_SAFE_
				if(pDat != &(m_pHead->obj))
				{
					Debug("Zephyr3::Link Del_point fail! (pDat != &(m_pHead->obj))");

					return ;
				}

//				ZASSERT_RET(pDat == &(m_pHead->obj));
				DelNode(NULL,m_pHead);
				return ;
#endif	// _ZEPHYR_3_LINK_EX_SAFE_

			default:
				{
					LPNode tmp = m_pHead;
					LPNode pre = NULL;

					do{
						if(pDat == &(tmp->obj))
						{
							DelNode(pre,tmp);

							return ;
						}

						pre = tmp;
						tmp = tmp->pNext;

					}while(tmp != m_pEnd->pNext);

#ifdef _ZEPHYR_3_LINK_EX_SAFE_
//					ZASSERT_R(false);
					Debug("Zephyr3::Link Del_point fail! not find!");
#endif	// _ZEPHYR_3_LINK_EX_SAFE_
				}
			}
		}

		void Del(const T& dat) {

			switch(GetUsed())
			{
			case 0:
				return ;
			case 1:

#ifdef _ZEPHYR_3_LINK_EX_SAFE_
				if(dat != (m_pHead->obj))
				{
					Debug("Zephyr3::Link Del fail! (pDat != &(m_pHead->obj))");

					return ;
				}

//				ZASSERT_R(dat == m_pHead->obj);
				DelNode(NULL,m_pHead);
				return ;
#else	// _ZEPHYR_3_LINK_EX_SAFE_
				if(dat != (m_pHead->obj))
				{
					Debug("Zephyr3::Link Del fail! (pDat != &(m_pHead->obj))");

					return ;
				}
//				ZASSERT_RET(dat == m_pHead->obj);
				DelNode(NULL,m_pHead);
				return ;
#endif	// _ZEPHYR_3_LINK_EX_SAFE_

			default:
				{
					LPNode tmp = m_pHead;
					LPNode pre = NULL;

					do{
						if(dat == tmp->obj)
						{
							DelNode(pre,tmp);

							return ;
						}

						pre = tmp;
						tmp = tmp->pNext;

					}while(tmp != m_pEnd->pNext);

#ifdef _ZEPHYR_3_LINK_EX_SAFE_
//					ZASSERT_R(false);
					Debug("Zephyr3::Link Del fail! not find!");
#endif	// _ZEPHYR_3_LINK_EX_SAFE_
				}
			}
		}

		// 删除结点
		void DelNext(TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode pNode) {

			if(GetUsed() <= 0)
				return ;

			if(pNode == m_pEnd)
				return ;

			if(pNode != NULL)
				DelNode(pNode,pNode->pNext);
			else
				DelNode(NULL,NULL);

		}

		// 获得数据
		void GetData(T* &pObj,TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode& pNode) {

			if(m_uiUsed == 0 || pNode == m_pEnd)
			{
				pNode = NULL;
				pObj = NULL;
			}
			else if(pNode == NULL)
			{
				pObj = &(m_pHead->obj);
				pNode = m_pHead;
			}
			else
			{
				pNode = pNode->pNext;
				pObj = &(pNode->obj);
			}
		}

		// 是否是尾结点
		bool IsEndNode(TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode pNode) const { return m_uiUsed == 0 ? true : pNode == m_pEnd; }

		// 清空链表
		void Clear() {

			m_uiUsed = 0;

			m_pEnd = NULL;
		}

		// 是否再链表中
		bool IsIn(TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode pNode) {

			ZASSERT(pNode != NULL);

			switch(GetUsed())
			{
			case 0:
				return false;
			case 1:
				if(pNode == m_pHead)
					return true;

				break;
			default:
				{
					LPNode tmp = m_pHead;

					do{
						if(tmp == pNode)
							return true;

						tmp = tmp->pNext;

					}while(tmp != m_pEnd->pNext);
				}

				break;
			}

			return false;
		}
	private:
		// 分配空间
		TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode Alloc(unsigned int size) {

			ZASSERT(size > 0);

			LPNode tmp = NULL;

			tmp = new Node[size];
			ZASSERT_R(tmp != NULL);

			LPNode tmp1 = tmp;

			unsigned int i = 1;

			while(i < size)
			{
				tmp1->pNext = &tmp[i++];
				tmp1 = tmp1->pNext;
			}

			m_pLast = tmp1;

			m_uiTotal += size;

			m_memory.push_back(tmp);

			return tmp;
		}

		// 释放结点
		void DelNode(TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode pPre,TYPENAME Link<T,SIZE,ADD_SIZE>::LPNode pNode) {

			if(pPre == NULL || pNode == m_pHead)	// if del head
			{
				if(m_pEnd == m_pHead)	// if only a node
					m_pEnd = NULL;
				else
				{
					// move head to last
					m_pLast->pNext = m_pHead;
					m_pLast = m_pLast->pNext;

					m_pHead = m_pHead->pNext;
					m_pLast->pNext = NULL;
				}
			}
			else if(pNode == m_pEnd) // if del end
			{
				m_pEnd = pPre;
			}
			else // others
			{

#ifdef _ZEPHYR_3_LINK_EX_SAFE_
//				ZASSERT_R(IsIn(pNode));
				if(!IsIn(pNode))
				{
					Debug("Zephyr3::Link DelNode IsIn(pNode) fail!");

					return ;
				}
#endif	// _ZEPHYR_3_LINK_EX_SAFE_

				pPre->pNext = pNode->pNext;

				m_pLast->pNext = pNode;
				pNode->pNext = NULL;

				m_pLast = m_pLast->pNext;
			}

			m_uiUsed--;
		}
	private:
		LPNode			m_pHead;
		LPNode			m_pEnd;
		LPNode			m_pLast;
		unsigned int	m_uiTotal;
		unsigned int	m_uiUsed;
		Array			m_memory;
	};

	///////////////////////////////////////////////////////////////////////////////////////////
	// Link

	template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
	class Link_SafePtr{
	public:
		typedef Link<T,SIZE,ADD_SIZE>	DataLink;
//		typedef Link<T*,SIZE,ADD_SIZE>	PtrLink;
	public:
	private:
		DataLink	m_dataLink;
//		PrtLink		m_ptrLink;
	};
};

#endif	// _ZEPHYR_3_LINK_EX_H