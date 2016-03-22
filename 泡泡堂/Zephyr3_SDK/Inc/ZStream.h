#ifndef ZEPHYR_STREAM_H
#define ZEPHYR_STREAM_H

#include <Zephyr.h>

#include <ZDebug.h>
#include <ZState.h>

///////////////////////////////////////////////////////////////////////////////////
//	ZStream

//流属性
const DWORD	ZSTREAM_STATE_EXTERNMEM	=	0x01;	//外部分派的内存

template<class T,unsigned int SIZE = 1024,unsigned int ADD_SIZE = SIZE>
class ZStream{
protected:
	T *m_Data;
	unsigned int m_Size;
	unsigned int m_Head;
	unsigned int m_End;
	ZState_DWord m_State;
public:
	inline ZStream() { _init(); }
	inline ZStream(void *buf,unsigned int Size);

	inline ~ZStream() { Release(); }

	inline void Release();

	inline void _init();

	//分配空间
	inline HRESULT Alloc(unsigned int Size);

	inline T *Add(T &data);
	inline T *AddValue(T data);
	//t_len是T的数量，如果data为空，只移动指针
	inline T *Add(void *data,unsigned int t_len);

	inline T *Get(unsigned int &t_len);
	inline T *Get();

	inline T *GetBase() { return m_Data; }
	inline T *GetEnd() { return &m_Data[m_End]; }
	inline T *GetHead() { return &m_Data[m_Head]; }

	inline bool IsFull() { return m_Head == m_End; }

	inline unsigned int GetSize() { return m_Size; }
	inline unsigned int GetFree() { return m_Size-m_End; }
	inline unsigned int GetUsed() { return m_End-m_Head; }

	inline void Clear()	{ m_Head = m_End = 0; }
protected:
	inline typename T *alloc(unsigned int s) { return (typename T *)malloc(s); }
	inline typename T *realloc(unsigned int s) { return (typename T *)::realloc(m_Data,s); }
};

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline void ZStream<T,SIZE,ADD_SIZE>::_init()
{
	m_Data = alloc(SIZE);
	m_Size = SIZE;
	m_Head = m_End = 0;
}

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline ZStream<T,SIZE,ADD_SIZE>::ZStream(void *buf,unsigned int Size)
{
	if(buf)
	{
		m_Data = (T *)buf;
		m_Size = Size;
		m_Head = m_End = 0;

		m_State.Add(ZSTREAM_STATE_EXTERNMEM);
	}
	else
		ZStream();
}

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline void ZStream<T,SIZE,ADD_SIZE>::Release()
{
	if(m_Data && !m_State.Has(ZSTREAM_STATE_EXTERNMEM))
	{
		free(m_Data);

		m_Data = NULL;
	}
}

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline T *ZStream<T,SIZE,ADD_SIZE>::Add(T &data)
{
	T *tmp = &m_Data[m_End];

	if(m_State.Has(ZSTREAM_STATE_EXTERNMEM))
	{
		if(m_End >= m_Size)
			return NULL;

		m_Data[m_End++] = data;

		return tmp;
	}
	else
	{
		if(m_End >= m_Size)
		{
			m_Size += ADD_SIZE;

			m_Data = realloc(m_Size);
		}

		m_Data[m_End++] = data;

		return tmp;
	}
}

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline T *ZStream<T,SIZE,ADD_SIZE>::AddValue(T data)
{
T *tmp = &m_Data[m_End];

	if(m_State.Has(ZSTREAM_STATE_EXTERNMEM))
	{
		if(m_End >= m_Size)
			return NULL;

		m_Data[m_End++] = data;

		return tmp;
	}
	else
	{
		if(m_End >= m_Size)
		{
			m_Size += ADD_SIZE;

			m_Data = realloc(m_Size);
		}

		m_Data[m_End++] = data;

		return tmp;
	}
}

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline T *ZStream<T,SIZE,ADD_SIZE>::Add(void *data,unsigned int t_len)
{
	T *tmp = &m_Data[m_End];

	if(m_State.Has(ZSTREAM_STATE_EXTERNMEM))
	{
		if(m_End+t_len >= m_Size)
			return NULL;

		if(m_Data)
			memcpy(((char *)m_Data)+m_End*sizeof(T),data,t_len*sizeof(T));

		m_End += t_len;

		return tmp;
	}
	else
	{
		if(m_End+t_len >= m_Size)
		{
			do{
				m_Size += ADD_SIZE;
			}while(m_End+t_len >= m_Size);

			m_Data = realloc(m_Size);
		}

		if(data)
			memcpy(((char *)m_Data)+m_End*sizeof(T),data,t_len*sizeof(T));

		m_End += t_len;

		return tmp;
	}
}

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline T *ZStream<T,SIZE,ADD_SIZE>::Get(unsigned int &t_len)
{
	if(m_Head+t_len > m_End)
	{
		t_len = m_Head+t_len-m_End;

		return NULL;
	}

	T *tmp = &m_Data[m_Head];

	m_Head += t_len;

	return tmp;
}

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline T *ZStream<T,SIZE,ADD_SIZE>::Get()
{
	if(m_Head < m_End)
		return &m_Data[m_Head++];

	return NULL;
}

//分配空间
template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline HRESULT ZStream<T,SIZE,ADD_SIZE>::Alloc(unsigned int Size)
{
	if(m_End+Size >= m_Size)
	{
		do{
			m_Size += ADD_SIZE;
		}while(m_End+Size >= m_Size);

		m_Data = realloc(m_Size);

		return m_Data?S_OK:E_FAIL;
	}

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
//	Func

#include <windows.h>

DWORD _RlePack(void *Dst,void *Src,DWORD Size);
DWORD _RleUnpack(void *Dst,DWORD DstSize,void *Src,DWORD Size);

#endif