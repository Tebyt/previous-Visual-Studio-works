/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\AutoPtr.h

							Describe:	智能指针

							Author:		赵洪松(xueren)

							CreateTime: 2003.04.16
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_AUTO_PTR_H
#define _ZEPHYR_3_BASE_AUTO_PTR_H

#include <Base\Assert.h>

namespace Zephyr3{

	////////////////////////////////////////////////////////////////////
	// 智能指针

	template<typename T>
	class AutoPtr{
	public:
		struct Data{
			long	lNums;
			T*		ptr;
		};

		typedef Data*	LPData;

		template<typename T>
			friend void _New(AutoPtr<T>& ptr, T* dat);

		template<typename T>
			friend void _Release(AutoPtr<T>& ptr);

		template<typename T>
			friend bool _IsInited(const AutoPtr<T>& ptr);

		template<typename T>
			friend bool _IsNull(const AutoPtr<T>& ptr);

		template<typename T>
			friend T* _GetPtr(AutoPtr<T>& ptr);
	public:
		// 构造函数
		AutoPtr() {
			m_pDat = NULL;
		}

		// 构造函数
		AutoPtr(T* ptr) {
			m_pDat = NULL;

			_New<T>(*this,ptr);
		}

		// 构造函数
		template<typename T>
		AutoPtr(AutoPtr<T>& autoPtr) {

			m_pDat = autoPtr.m_pDat;

			m_pDat->lNums++;
		}

		// 析构函数
		~AutoPtr() {
			if(m_pDat != NULL)
				_Release(*this);
		}

		T& operator*() const { 

			ZASSERT(_IsInited(*this));

			return *m_pDat->ptr; 
		}

		T* operator->() const { 

			ZASSERT(_IsInited(*this));

			return m_pDat->ptr; 
		}

		AutoPtr<T>& operator=(T* ptr) {

			if(m_pDat != NULL)
				_Release<T>(*this);

			_New<T>(*this,ptr);

			return *this;
		}

		template<typename T>
		AutoPtr<T>& operator=(AutoPtr<T>& autoPtr) {

			if(m_pDat != NULL)
				_Release<T>(*this);

			m_pDat = autoPtr.m_pDat;

			return *this;
		}
	private:
		LPData	m_pDat;
	};

	template<typename T>
		inline bool _IsInited(const AutoPtr<T>& ptr) {
			return ptr.m_pDat != NULL;
		}

	template<typename T>
		inline bool _IsNull(const AutoPtr<T>& ptr) {

			return !_IsInited<T>(ptr) || ptr.m_pDat->ptr == NULL;
		}

	template<typename T>
		inline void _New(AutoPtr<T>& ptr, T* dat) {
			ptr.m_pDat = new AutoPtr<T>::Data;
			ZASSERT_R(ptr.m_pDat != NULL);

			ptr.m_pDat->ptr = dat;
			ptr.m_pDat->lNums = 1;
		}

	template<typename T>
		inline void _Release(AutoPtr<T>& ptr) {

			ZASSERT(_IsInited(ptr));

			if(ptr.m_pDat->lNums == 1)
			{
				if(ptr.m_pDat->ptr != NULL)
					delete ptr.m_pDat->ptr;

				delete ptr.m_pDat;

				ptr.m_pDat = NULL;
			}
			else if(ptr.m_pDat->lNums > 1)
				ptr.m_pDat->lNums--;
		}

	template<typename T>
		inline T* _GetPtr(AutoPtr<T>& ptr) {
			return _IsNull(ptr) ? NULL : ptr.m_pDat->ptr;
		}
};

#endif // _ZEPHYR_3_BASE_AUTO_PTR_H