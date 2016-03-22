//ZStack.h
//write by sssxueren 
//		y2k3.3.5

#ifndef ZEPHYR_STACK_H
#define ZEPHYR_STACK_H

#include <Zephyr.h>

//定义了_ZEPHYR_STACK_DEBUG，则会在初始化和释放的时候输出log

#include <zdebug.h>

///////////////////////////////////////////////////////////////////////////////////
//	ZStack

template<class T>
class ZStack{
private:
	T	*m_Data;
	unsigned int m_TP;
	unsigned int m_Size;
public:
	inline ZStack(unsigned int size);
	~ZStack() { Release(); }

	void Release();

	T *Pop() { return m_TP?&(m_Data[--m_TP]):NULL; }
	void Push(T &obj) { m_Data[m_TP++] = obj; }
	inline T *Push() { return &(m_Data[m_TP++]); }

	HRESULT Init(unsigned int size);

	bool IsInit() { return m_Data != NULL;	}
protected:
	T *alloc(unsigned int s);
};

template<class T>
inline ZStack<T>::ZStack(unsigned int size)
{ 
	m_Data = NULL; 

	Init(size); 
}

template<class T>
T *ZStack<T>::alloc(unsigned int s)
{
	if(s == 0)
		return NULL;

	T *tmp = NULL;

	tmp = new T[s];
	if(tmp == NULL)
	{
		Debug("ZStack::alloc(%d) fail!",s);

		return NULL;
	}

	return tmp;
}

template<class T>
void ZStack<T>::Release()
{
	if(m_Data)
	{
		delete[] m_Data;

		m_Data = NULL;

		m_TP = 0;

		m_Size = 0;
	}
}

template<class T>
HRESULT ZStack<T>::Init(unsigned int size)
{
	if(size == 0)
		return E_FAIL;

	if(m_Data)
		Release();

	m_Data = alloc(size);
	if(m_Data == NULL)
		return ZRet(E_FAIL,"ZStack::Init(%d) fail!",size);

	m_Size = size;

	m_TP = 0;

	return S_OK;
}

#endif