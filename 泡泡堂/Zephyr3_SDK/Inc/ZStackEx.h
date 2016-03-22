/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZStackEx.h

							Describe:	∂—’ª

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2004.03.17
							UpdateTime:
*/

#ifndef _ZEPHYR_3_STACK_EX_H
#define _ZEPHYR_3_STACK_EX_H

#include <Zephyr.h>

#include <ZDebug.h>

namespace Zephyr3{

	/////////////////////////////////////////////////////////////////////////////////
	// Stack

	template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
	class Stack{
	public:
		Stack() {

			m_pDat = NULL;

			Init();
		}

		T& Pop() {

			ZASSERT(m_uiCur > 0);

			return m_pDat[--m_uiCur];
		}

		void Push(T& obj) {
			ZASSERT(m_pDat != NULL);

			if(m_uiCur >= m_uiTotal)
			{
				Realloc();

				ZASSERT(m_uiCur < m_uiTotal);
			}

			m_pDat[m_uiCur++] = obj;
		}

		unsigned int GetUsed() const { return m_uiCur; }
	private:
		void Init() {
			ZASSERT(m_pDat == NULL);

			m_pDat = (T*)malloc(sizeof(T) * SIZE);
			ZASSERT_R(m_pDat != NULL);

			m_uiTotal = SIZE;
			m_uiCur = 0;
		}

		void Realloc() {
			ZASSERT(m_pDat != NULL);

			m_pDat = (T*)realloc(m_pDat,sizeof(T) * (m_uiTotal + ADD_SIZE));
			ZASSERT_R(m_pDat != NULL);

			m_uiTotal += ADD_SIZE;
		}
	private:
		T*				m_pDat;
		unsigned int	m_uiTotal;
		unsigned int	m_uiCur;
	};
};

#endif	// _ZEPHYR_3_STACK_EX_H