/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\String.h

							Describe:	�ַ���

							Author:		�Ժ���(xueren)

							CreateTime: 2004.03.10
							UpdateTime: 2004.04.16
*/

#ifndef _ZEPHYR_3_BASE_STRING_H
#define _ZEPHYR_3_BASE_STRING_H

#include <stdio.h>

#include <Base\Assert.h>
#include <Base\StringFunc.h>
#include <Base\Allocator.h>

namespace Zephyr3{

	/////////////////////////////////////////////////////////////////////////
	// String

	template<class T>
	class String{
	public:
		typedef T*	_LPItem;

		enum { _ITEM_SIZE = sizeof(T) };
	public:
		// ���캯��
		String() {
			m_pItem = NULL;
			m_size = 0;
		}
		// ���캯��
		String(const _LPItem str) {
			ZASSERT(str != NULL);
			ZASSERT(StrLen<T>(str) > 0);

			SetData(str);
		}

		// ���
		void Empty() {
			if(m_pItem != NULL)
				m_pItem[0] = 0;
		}

		void Release() {
			if(m_pItem != NULL)
				_SafeFree(m_pItem);

			m_size = 0;
		}

		// ���������
		unsigned int GetTotalSize() const { return ; }
		// ����ַ�������
		unsigned int GetLength() const { return StrLen<T>(m_pItem); }


		unsigned int GetItemSize() const { return _ITEM_SIZE; }

		operator const _LPItem() const { return m_pItem; }

		const _LPItem Val() const { return GetData(); }
	private:
		void SetData(const _LPItem str) {

			ZASSERT(str != NULL);

			unsigned int len = StrLen<T>(str) + 1;

			if(m_pItem == NULL)
			{
				m_pItem = _AllocObject<T>(len);

				m_size = len;
			}
			else
			{
			}

			StrCpy<T>(m_pItem, str);
		}

		const _LPItem GetData() const { return m_pItem; }
	private:
		_LPItem			m_pItem;
		unsigned int	m_size;
	};

	/////////////////////////////////////////////////////////////////////////
	// StringEx
	// ��̬�����ڴ�ռ�

	template<unsigned int SIZE>
	class StringEx{
	public:
	public:
		// ���캯��
		StringEx() { Empty(); }
		// ���캯��
		StringEx(const char* str) {
			ZASSERT(str != NULL);
			ZASSERT(strlen(str) < SIZE);

			SetData(str);
		}

		// ���
		void Empty() {

			m_str[0] = '\0';
		}

		// ���������
		unsigned int GetTotalSize() const { return SIZE; }
		// ����ַ�������
		unsigned int GetLength() const { return (unsigned int)strlen(m_str); }
		// �Ƿ�Ϊ��
		bool IsEmpty() const { return m_str[0] == '\0'; }

		// +=
		StringEx& operator +=(const char* str) {

			ZASSERT(strlen(m_str) + strlen(str) < SIZE);

			strcat(m_str,str);

			return *this;
		}

		// +=
		StringEx& operator +=(const StringEx& string) {
			return operator +=(string.GetData());
		}

		// <<
		StringEx& operator <<(const char* str) {

			return operator +=(str);
		}

		// <<
		StringEx& operator <<(const StringEx& string) {

			return operator +=(string.GetData());
		}

		// <<
		StringEx& operator <<(const int iNums) {

			unsigned int len = GetLength();

			sprintf(m_str + len,"%d",iNums);

			return *this;
		}

		// <<
		StringEx& operator <<(const unsigned int uiNums) {

			unsigned int len = GetLength();

			sprintf(m_str + len,"%u",uiNums);

			return *this;
		}

		// =
		StringEx& operator =(const char* str) {

			SetData(str);

			return *this;
		}

		// =
		StringEx& operator =(const StringEx& string) {

			SetData(string.GetData());

			return *this;
		}

		operator const char*() const { return m_str; }

		const char* Val() const { return GetData(); }
	private:
		void SetData(const char* str) {

			ZASSERT(str != NULL);
			ZASSERT(strlen(str) < SIZE);

			strcpy(m_str,str);
		}

		const char* GetData() const { return m_str; }
	private:
		char	m_str[SIZE];
	};
};

#endif	// _ZEPHYR_3_BASE_STRING_H