// ZRandom.h
// 随机数 头文件
// write by zhs007			y2k3.6.5

#ifndef __ZEPHYR_RANDOM_H
#define __ZEPHYR_RANDOM_H

#include <Zephyr.h>

////////////////////////////////////////////////////////////////////////
//	ZRand

class ZEPHYR_API ZRandom{
	static DWORD MCoef_32[2];
public:
	DWORD Random(DWORD dwMset,DWORD dwKey,int nNumber,DWORD *pdwRandom);
	void RandomGenerator(void *pBuffer, int nLength);

	DWORD Random(DWORD max);
};

////////////////////////////////////////////////////////////////////////
//	ZRandom_List

class ZEPHYR_API ZRandom_List : public ZRandom{
private:
	DWORD	*m_pBuff;
	DWORD	m_dwSize;
public:
	inline ZRandom_List();
	~ZRandom_List() { Release(); }

	bool IsInit() const { return m_pBuff != NULL; }
	DWORD GetSize() const { return m_dwSize; }
	DWORD *GetBuff() { return m_pBuff; }

	HRESULT Init(DWORD size);

	void Release();

	void Random(DWORD nums,DWORD max);
};

inline ZRandom_List::ZRandom_List() 
{ 
	m_pBuff = NULL; 
	m_dwSize = 0;
}

#endif//__ZEPHYR_RANDOM_H