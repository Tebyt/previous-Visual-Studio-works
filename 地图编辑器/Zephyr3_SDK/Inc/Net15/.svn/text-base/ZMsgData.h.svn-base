#ifndef ZEPHYR_NETMSGDATA_H
#define ZEPHYR_NETMSGDATA_H

#include <ZStream.h>
#include <ZLink.h>
#include <ZLock.h>
/*
#pragma pack (push)
#pragma pack (1)

//////////////////////////////////////////////////////////////////////////////////
//	消息头

const BYTE	ZNETMSG_STATE_REQUEST		=	0x01;	//请求
const BYTE	ZNETMSG_STATE_RESPOND		=	0x02;	//响应请求

const BYTE	ZNETMSG_STATE_NOTMSGHEAD	=	0x80;	//不是消息头

struct _MsgHead{
	WORD	wSize;			//消息大小
	BYTE	bState;			//消息属性
	BYTE	bVer;			//消息版本
	DWORD	dwID;			//消息ID
	BYTE	bMainID;		//主消息ID
	BYTE	bAssistantID;	//辅助消息ID
	WORD	wReserve;		//保留
};

//消息头 长度
const int ZNETMSGHEAD_LEN	=	sizeof(_MsgHead);

inline void SetMsgHead(_MsgHead &Head,WORD Size,BYTE State,DWORD ID,BYTE MainID,BYTE AssistantID,BYTE Ver)
{
	Head.wSize = Size;
	Head.bState = State;
	Head.dwID = ID;
	Head.bMainID = MainID;
	Head.bAssistantID = AssistantID;
	Head.bVer = Ver;
	Head.wReserve = 0;
}
*/
//////////////////////////////////////////////////////////////////////////////////
//	ZNetStream 网络流数据 可能包括多个消息包
//	可操作的最小元素为消息包

//网络数据包 大小属性
const WORD	ZNETPACK_SIZE_STATE_MULPACK	=	0x8000;	//是否进行了包分割
const WORD	ZNETPACK_SIZE_STATE_RLE		=	0x4000;	//是否进行了RLE压缩
//网络数据包 大小掩码
const WORD	ZNETPACK_SIZE_MASK			=	0x07ff;		//2048

//网络数据包 最大的长度
const int ZNETPACK_LEN	=	1400;

//网络数据包 标识
const BYTE	ZNETPACKHEAD_STATE_ID		=	0x80;
const BYTE	ZNETPACKHEAD_STATE_RLE		=	0x40;

//分割后的包 顺序
const BYTE	ZNETPACKHEAD_STATE_NUMS_MASK	=	0x0f;

struct _PackHead{
	WORD	wSize;			//大小
	BYTE	bState;			//属性
	BYTE	dwID;			//标识码
};

class ZEPHYR_NET_API ZNetStream{
private:
	ZStream<BYTE,ZNETPACK_LEN*2>	m_Stream;
public:
	ZNetStream() { ; }
	ZNetStream(void *data,unsigned int Size) : m_Stream(data,Size) { ; }

	void _init() { m_Stream._init(); }

	//分配足够的空间
	void Alloc(unsigned int Size) { m_Stream.Alloc(Size); }

	void *GetEnd() { return m_Stream.GetEnd(); }

	void *GetData() { return m_Stream.GetBase(); }
	unsigned int GetTotal() { return m_Stream.GetSize(); }
	unsigned int GetFree() { return m_Stream.GetFree(); }
	WORD GetSize() { return m_Stream.GetUsed(); }

	void *AddData(void *Data,unsigned int Size) { return m_Stream.Add(Data,Size); }

	void Clear() { m_Stream.Clear(); }

//TCP 客户端用
	//接收消息
	DWORD RecvMsg(SOCKET sock,BYTE* &buf);

//TCP 服务器模型用
	//已经接收到 recv_len 长的消息
	//返回 S_OK 则表示至少接收到1条完整的消息
	//返回 E_FAIL 则表示没有接收到完整的消息，want_len 用来填充还需要接收的
	//消息字节数
	HRESULT _RecvData(DWORD recv_len,DWORD &want_len);
	//得到消息
	//如果 _RecvData() 返回 S_OK 则调用本函数获得消息
	//如果成功，返回得到的消息长度
	//如果当前消息不完整，返回 0，且填充 want_len 为还需要接收的消息字节数
	DWORD _RecvMsg(BYTE* &buf,DWORD &want_len);
};
/*
//////////////////////////////////////////////////////////////////////////////////
//	普通消息

typedef struct {} null_type;

template<class T>
class ZNetMsg{
	_MsgHead	m_Head;
	T			m_Data;
public:
	inline void SetHead(_MsgHead &Head) { memcpy(&m_Head,&Head,ZNETMSGHEAD_LEN); }
	inline void SetHead(WORD Size,BYTE State,BYTE ID,BYTE MainID,BYTE AssistantID,BYTE Ver);
	inline _MsgHead *GetHead() { return &m_Head; }

	inline void SetData(T &Data) { memcpy(&m_Data,&Data,sizeof(T)); }
	inline T *GetData() { return &m_Data; }
};

template<class T>
inline void ZNetMsg<T>::SetHead(WORD Size,BYTE State,BYTE ID,BYTE MainID,BYTE AssistantID,BYTE Ver)
{
	::SetMsgHead(m_Head,Size,State,ID,MainID,AssistantID,Ver);
}

template<>
class ZNetMsg<null_type>{
   _MsgHead	m_Head;
public:
	inline void SetHead(_MsgHead &Head) { memcpy(&m_Head,&Head,ZNETMSGHEAD_LEN); }

	inline void SetHead(WORD Size,BYTE State,BYTE ID,BYTE MainID,BYTE AssistantID,BYTE Ver)
	{
		::SetMsgHead(m_Head,Size,State,ID,MainID,AssistantID,Ver);
	}

	inline _MsgHead *GetHead() { return &m_Head; }
};


///////////////////////////////////////////////////////////////////////////////////
//	多数据消息

template<class T>
class ZNetMsg_MulData{
private:
	ZStream<BYTE,ZNETMSGHEAD_LEN+sizeof(T),sizeof(T)>	m_Stream;

	_MsgHead	*m_pHead;
	T			*m_Data;

	WORD		m_Size;
public:
	inline ZNetMsg_MulData();
	inline ZNetMsg_MulData(void *buf,unsigned int Size);

	inline T *AddNewData();

	void *GetData() { return m_Stream.GetData(); }
	T *GetData(int Index) { return &m_Data[Index]; }

	_MsgHead *GetHead() { return m_pHead; }

	void *GetMsgData() { return m_pHead; }

	DWORD GetSize() { return m_Size; }

	void End() { m_pHead->wSize = m_Size; }

	int GetMsgNums() { return (m_Size - ZNETMSGHEAD_LEN)/sizeof(T); }

	bool Check() { return (m_Size - ZNETMSGHEAD_LEN)%sizeof(T) == 0; }
};

template<class T>
inline ZNetMsg_MulData<T>::ZNetMsg_MulData()
{
	m_Size = ZNETMSGHEAD_LEN;

	m_pHead = (_MsgHead	*)m_Stream.Add(NULL,ZNETMSGHEAD_LEN);
	m_Data = AddNewData();
}

template<class T>
inline ZNetMsg_MulData<T>::ZNetMsg_MulData(void *buf,unsigned int Size) : m_Stream(buf,Size)
{
	m_Size = Size;

	m_pHead = (_MsgHead	*)buf;
	m_Data = (T *)((BYTE *)buf + ZNETMSGHEAD_LEN);
}

template<class T>
inline T *ZNetMsg_MulData<T>::AddNewData() 
{ 
	m_Size += sizeof(T);

	return (T *)m_Stream.Add(NULL,sizeof(T));
}

#pragma pack (pop)

/////////////////////////////////////////////////////////////////////
//	RequestMsg

template<class T,unsigned int SIZE>
class RequestMsg{
	struct _Object{
		T				Msg;
		unsigned long	Time; 
		void			*Data;
	};
private:
	ZLinkEx<_Object,SIZE,SIZE>	m_MsgList;
	ZCriticalSection			m_Lock;
	unsigned long				m_MaxTime;
public:
	RequestMsg() { ; }

	inline T *Add(unsigned long time,void *data);

	inline T *Find(DWORD ID,void* &data,void* &index);

	inline void Del(void *index);

	inline HRESULT Timer(unsigned long curTime,T* &Msg,void* &Index);
};

template<class T,unsigned int SIZE>
inline T *RequestMsg<T,SIZE>::Add(unsigned long time,void *data)
{
	m_Lock.Lock();
	_Object *Obj = m_MsgList.GetEndObjPoint();
	m_MsgList.Add();
	m_Lock.Unlock();

	Obj->Time = time;
	Obj->Data = data;

	return &(Obj->Msg);
}

template<class T,unsigned int SIZE>
inline HRESULT RequestMsg<T,SIZE>::Timer(unsigned long curTime,T* &Msg,void* &Index)
{
	m_Lock.Lock();

	if(m_MsgList.GetUsed())
	{
		_Object *obj = NULL;
		unsigned long time;

		do{
			m_MsgList.GetData(obj,Index);
			if(obj)
			{
				time = curTime - obj->Time;
				if(time > m_MaxTime)
				{
					Msg = &(obj->Msg);

					m_Lock.Unlock();

					return E_FAIL;
				}
			}
		}while(Index);
	}

	m_Lock.Unlock();

	return S_OK;
}

template<class T,unsigned int SIZE>
inline void RequestMsg<T,SIZE>::Del(void *index)
{
	ZASSERT(m_MsgList.GetUsed());
	ZASSERT(index);

	m_Lock.Lock();
	m_MsgList.Del((_Object *)index);
	m_Lock.Unlock();
}

template<class T,unsigned int SIZE>
inline T *RequestMsg<T,SIZE>::Find(DWORD ID,void* &data,void* &Obj)
{
	ZASSERT(m_MsgList.GetUsed());

	void *index = NULL;
	_Object *obj = NULL;

	m_Lock.Lock();

	do{
		m_MsgList.GetData(obj,index);
		if(obj)
		{
			if(((_MsgHead *)&(obj->Msg))->dwID == ID)
			{
				data = obj->Data;

				Obj = obj;

				m_Lock.Unlock();

				return &(obj->Msg);
			}
		}
	}while(index);

	m_Lock.Unlock();

	return NULL;
}
*/
#endif