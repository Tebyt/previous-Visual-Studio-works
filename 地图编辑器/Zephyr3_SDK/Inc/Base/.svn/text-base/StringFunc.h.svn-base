/*
							Zephyr Engine v3.0

								by ÕÔºéËÉ(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\StringFunc.h

							Describe:	×Ö·û´®º¯Êý

							Author:		ÕÔºéËÉ(xueren)

							CreateTime: 2004.09.11
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_STRINGFUNC_H
#define _ZEPHYR_3_BASE_STRINGFUNC_H

namespace Zephyr3{

	// ¸Ä±ä×Ö·û´®Îª´óÐ´
	void ZEPHYR_3_API Chg2Capital(char* str);

	// ¸Ä±ä×Ö·û´®ÎªÐ¡Ð´
	void ZEPHYR_3_API Chg2Lowercase(char* str);

	inline bool IsCapital(char c) { return c >= 'A' && c <= 'Z'; }

	inline bool IsLowercase(char c) { return c >='a' && c <= 'z'; }

	inline char Capital(char c) { return IsLowercase(c) ? c - 'a' + 'A' : c; }

	inline char Lowercase(char c) { return IsCapital(c) ? c + 'a' - 'A' : c; }

	template<class T>
	unsigned int StrLen(const T* str);

	template<class T>
	T* StrCpy(T* dst,const T* src);

	template<>
	inline unsigned int StrLen<char>(const char* str)
	{
		return static_cast<unsigned int>(strlen(str));
	}
/*
	template<>
	inline unsigned int StrLen<wchat_t>(const wchat_t* str)
	{
		return wcslen(str);
	}
*/
	template<>
	inline char* StrCpy<char>(char* dst,const char* src)
	{
		return strcpy(dst,src);
	}
/*
	template<>
	inline wchat_t* StrCpy<WORD>(wchat_t* dst,const WORD* src)
	{
		return wcscpy(dst,src);
	}
*/
};

#endif // _ZEPHYR_3_BASE_STRINGFUNC_H