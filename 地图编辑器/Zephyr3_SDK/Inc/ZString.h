/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZString.h

							Describe:	�ַ���

							Author:		�Ժ���(xueren)

							CreateTime: 2004.03.10
							UpdateTime:
*/

#ifndef _ZEPHYR_3_STRING_H
#define _ZEPHYR_3_STRING_H

#include <Zephyr.h>

namespace Zephyr3{

	/////////////////////////////////////////////////////////////////////////
	// String

	class ZEPHYR_API String{
	public:
	private:
		char*	m_pStr;
	};

	/////////////////////////////////////////////////////////////////////////
	// StringEx
	// ��̬�����ڴ�ռ�

	template<unsigned int SIZE>
	class StringEx{
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
		unsigned int GetLength() const { return strlen(m_str); }
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
/*
		template<unsigned int SIZE>
		friend const char* operator =(char* buf,const StringEx<SIZE>& string) {

			buf = string.GetData();

			return buf;
		};
*/
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
/*
	template<unsigned int SIZE>
	const char* operator =(char* buf,const StringEx<SIZE>& string) {

		buf = string.Val();

		return buf;
	};
*/
};

#endif	// _ZEPHYR_3_STRING_H