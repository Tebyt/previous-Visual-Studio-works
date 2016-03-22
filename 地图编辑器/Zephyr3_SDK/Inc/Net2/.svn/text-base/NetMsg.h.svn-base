/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\NetMsg.h

							Describe:	网络消息

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.5
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_NETMSG_H
#define _ZEPHYR_NET_2_NETMSG_H

#include <ZDebug.h>
#include <ZLink.h>
#include <Net2\BaseDef.h>

////////////////////////////////////////////////////////////////////////////////
// ZNet2

namespace ZNet2{

#pragma pack (push)
#pragma pack (1)

	////////////////////////////////////////////////////////////////////////////
	// 统一消息头
	// ZNetMsgHead

	class ZEPHYR_NET_API ZNetMsgHead{
	public:

	// ------------------------------------------------------------------------
	// 操作
#if _ZEPHYR_NET_VER >= 2200
		// 设置消息头
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true, bool bToOther = false) {

			SetSize(wSize);
			SetMainID(mainID);
			SetAssistantID(assID);

			m_bRequestMsg = bRequest;
			m_bRespondMsg = bRespond;
			m_bOrdinalMsg = bOrdinal;
			m_bToOther = bToOther;
		}
#else
		// 设置消息头
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {

			SetSize(wSize);
			SetMainID(mainID);
			SetAssistantID(assID);
#ifndef __ZEPHYR3_USE_ZEPHYRNET3__
			m_bRequestMsg = bRequest;
			m_bRespondMsg = bRespond;
			m_bOrdinalMsg = bOrdinal;
#endif // __ZEPHYR3_USE_ZEPHYRNET3__
		}
#endif

		// 置 0
		void Clear() { memset(this, 0, sizeof(ZNetMsgHead)); }

	// ------------------------------------------------------------------------
	// 属性

		// 获得消息长度
		int GetSize() const { return m_wSize; }
		// 设置消息长度
		void SetSize(WORD size) { 

			ZASSERT(size <= MAX_PKG_SIZE);

			m_wSize = size; 
		}

		// 获得主消息ID
		BYTE GetMainID() const { return m_bMainID; }
		// 设置主消息ID
		void SetMainID(BYTE mainID) { 

			ZASSERT(mainID <= 0x4f);

			m_bMainID = mainID; 
		}

		// 获得辅助消息ID
		BYTE GetAssistantID() const { return m_bAssistantID; }
		// 获得辅助消息ID
		BYTE GetAssID() const { return m_bAssistantID; }
		// 设置辅助消息ID
		void SetAssistantID(BYTE assID) { m_bAssistantID = assID; }
#ifndef __ZEPHYR3_USE_ZEPHYRNET3__
		// 是否是请求消息
		bool IsRequestMsg() const { return m_bRequestMsg; }
		// 请求
		void Request() { m_bRequestMsg = true; }

		// 是否相应请求消息
		bool IsRespondMsg() const { return m_bRespondMsg; }
		// 响应
		void Respond() { m_bRespondMsg = true; }

		// 是否有序
		bool IsOrdinal() const { return m_bOrdinalMsg; }
		// 有序
		void Ordinal() { m_bOrdinalMsg = true; }
#else // __ZEPHYR3_USE_ZEPHYRNET3__
		// 是否是请求消息
		bool IsRequestMsg() const { return false; }
		// 请求
		void Request() {}

		// 是否相应请求消息
		bool IsRespondMsg() const { return false; }
		// 响应
		void Respond() {}

		// 是否有序
		bool IsOrdinal() const { return true; }
		// 有序
		void Ordinal() {}
#endif // __ZEPHYR3_USE_ZEPHYRNET3__
		// 是否是断开连接消息
		bool IsEndConnect() {
			return m_bMainID == 0;
		}
#if _ZEPHYR_NET_VER >= 2200
		bool IsToOther() const { return m_bToOther; }

		void ToOther() {
			m_bToOther = 1;
		}
#endif
	private:
#ifndef __ZEPHYR3_USE_ZEPHYRNET3__
		WORD	m_wSize:15;			//消息大小
		WORD	m_bOrdinalMsg:1;	//消息是否是有序的
		BYTE	m_bRequestMsg:1;	//是否为请求消息
		BYTE	m_bRespondMsg:1;	//是否为相应请求消息
		BYTE	m_bMainID:6;		//主消息ID
#else // __ZEPHYR3_USE_ZEPHYRNET3__
		WORD	m_wSize;			//消息大小
		BYTE	m_bMainID;			//主消息ID
#endif // __ZEPHYR3_USE_ZEPHYRNET3__
#if _ZEPHYR_NET_VER >= 2200
		BYTE	m_bToOther:1;		// 是否为转发消息
		BYTE	m_bAssistantID:7;	// 辅助消息ID
#else
		BYTE	m_bAssistantID;		//辅助消息ID
#endif
	};

	typedef ZNetMsgHead*	LPZNetMsgHead;

	////////////////////////////////////////////////////////////////////////////
	// 普通消息 - 带数据区
	// ZNetMsg

	template<class T>
	class ZNetMsg{
	public:
		// 设置消息头
		void SetHead(ZNetMsgHead& Head) { m_Head = Head; }

		// 设置消息头
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// 获得消息头
		LPZNetMsgHead GetHead() { return &m_Head; }

		// 获得消息头
		const ZNetMsgHead& GetSafeHead() const { return m_Head; }

		// 请求
		void Request() { m_Head.Request(); }
		// 响应
		void Respond() { m_Head.Respond(); }

		// 设置消息数据
		void SetData(T& Data) { m_Data = Data; }
		// 获取消息数据
		T* GetData() { return &m_Data; }
		// 获取消息数据
		const T& GetSafeData() const { return m_Data; }

		// 获得消息长度
		WORD GetSize() const { return m_Head.GetSize(); }

		// 消息长度是否合法
		// 主要用于验证变长消息
		static bool IsValid(WORD size) {
			return size >= sizeof(ZNetMsgHead) && T::IsValid(size - sizeof(ZNetMsgHead));
		}

		// 保证消息正确性
		void Fix() {
			m_Data.Fix(sizeof(ZNetMsg<T>), GetSize());
		}
	protected:
		ZNetMsgHead	m_Head;
		T			m_Data;
	};

	////////////////////////////////////////////////////////////////////////////
	// 普通消息 - 不带数据区 (特例化)

	template<>
	class ZNetMsg<null_type>{
	public:
		// 设置消息头
		void SetHead(ZNetMsgHead& Head) { m_Head = Head; }

		// 设置消息头
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// 获取消息头
		LPZNetMsgHead GetHead() { return &m_Head; }
		// 获得消息头
		const ZNetMsgHead& GetSafeHead() const { return m_Head; }

		// 请求
		void Request() { m_Head.Request(); }
		// 响应
		void Respond() { m_Head.Respond(); }
	private:
		ZNetMsgHead	m_Head;
	};

	////////////////////////////////////////////////////////////////////////////
	// 请求消息 - 带数据区
	// ZRequestMsg

	template<class T>
	class ZRequestMsg{
	public:
		// 设置消息头
		void SetHead(ZNetMsgHead& Head) { m_Head = Head; }

		// 设置消息头
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,DWORD dwID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
			m_dwID = dwID;
		}

		// 获得消息头
		LPZNetMsgHead GetHead() { return &m_Head; }
		// 获得消息头
		const ZNetMsgHead& GetSafeHead() const { return m_Head; }

		// 请求
		void Request() { m_Head.Request(); }
		// 响应
		void Respond() { m_Head.Respond(); }

		// 设置消息数据
		void SetData(T& Data) { m_Data = Data; }
		// 获取消息数据
		T* GetData() { return &m_Data; }
		// 获取消息数据
		const T& GetSafeData() const { return m_Data; }

		// 获得ID
		DWORD GetID() const { return m_dwID; }

		// 消息长度是否合法
		// 主要用于验证变长消息
		static bool IsValid(WORD size) {
			return size >= sizeof(ZNetMsgHead) && T::IsValid(size - sizeof(ZNetMsgHead));
		}

		// 保证消息正确性
		void Fix() {
			m_Data.Fix(sizeof(ZNetMsg<T>),m_Head.GetSize());
		}
	protected:
		ZNetMsgHead	m_Head;
		DWORD		m_dwID;
		T			m_Data;
	};

	////////////////////////////////////////////////////////////////////////////
	// 请求消息 - 不带数据区 (特例化)

	template<>
	class ZRequestMsg<null_type>{
	public:
		// 设置消息头
		void SetHead(ZNetMsgHead& Head) { m_Head = Head; }

		// 设置消息头
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,DWORD dwID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
			m_dwID = dwID;
		}

		// 获取消息头
		ZNetMsgHead* GetHead() { return &m_Head; }

		// 请求
		void Request() { m_Head.Request(); }
		// 响应
		void Respond() { m_Head.Respond(); }

		// 获得ID
		DWORD GetID() const { return m_dwID; }
	private:
		ZNetMsgHead	m_Head;
		DWORD		m_dwID;
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长消息 － 发送端

	template<class T>
	class VarietyMsg_Send : public ZNetMsg<T>{
	public:
		// 设置消息头
		// 应先初始化消息
		void SetHead(BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(sizeof(VarietyMsg_Send<T>) - m_Data.GetFreeSize(),mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// 修正
		void Fix() {
			m_Data.Fix(sizeof(VarietyMsg_Recv<T>), GetSize());
		}
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长消息 － 发送端
	// 偏特化 － 不允许空变长消息

	template<>
	class VarietyMsg_Send<null_type>{
	private:
		VarietyMsg_Send() {}
		~VarietyMsg_Send() {}
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长请求消息 － 发送端

	template<class T>
	class VarietyMsg_R_Send : public ZRequestMsg<T>{
	public:
		// 设置消息头
		// 应先初始化消息
		void SetHead(BYTE mainID,BYTE assID,DWORD dwID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			ZRequestMsg<T>::SetHead(sizeof(VarietyMsg_R_Send<T>) - m_Data.GetFreeSize(),mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// 修正
		void Fix() {
			m_Data.Fix(sizeof(VarietyMsg_Send<T>), GetSize());
		}
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长请求消息 － 发送端
	// 偏特化 － 不允许空变长消息

	template<>
	class VarietyMsg_R_Send<null_type>{
	private:
		VarietyMsg_R_Send() {}
		~VarietyMsg_R_Send() {}
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长消息 － 接收端

	template<class T>
	class VarietyMsg_Recv{
	public:
		// 构造函数
		VarietyMsg_Recv(LPZNetMsgHead pHead) {
			ZASSERT(pHead != NULL);

			m_pHead = pHead;

			ZASSERT(GetSize() > sizeof(ZNetMsgHead));

			m_pData = (T*)((BYTE*)pHead + sizeof(ZNetMsgHead));

			Fix();
		}

		// 是合法的消息
		// 主要判断大小是否合法
		static bool IsViald(WORD size) {
			return size > sizeof(ZNetMsgHead) && T::IsInvalid(size - sizeof(ZNetMsgHead));
		}

		// 获得大小
		WORD GetSize() const { return m_pHead->GetSize(); }
		// 获得数据
		const T& GetData() const { return *m_pData; }
	protected:
		// 修正
		void Fix() {
			m_pData->Fix(sizeof(VarietyMsg_Recv<T>), GetSize());
		}
	protected:
		LPZNetMsgHead	m_pHead;
		T*				m_pData;
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长消息 － 接收端
	// 偏特化 － 不允许空变长消息

	template<>
	class VarietyMsg_Recv<null_type>{
	private:
		VarietyMsg_Recv() {}
		~VarietyMsg_Recv() {}
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长请求消息 － 接收端

	template<class T>
	class VarietyMsg_R_Recv{
		typedef ZRequestMsg<null_type>	_MsgHead;
		typedef _MsgHead*	_LPMsgHead;
	public:
		// 构造函数
		VarietyMsg_R_Recv(LPZNetMsgHead pHead) {
			ZASSERT(pHead != NULL);

			m_pHead = (_LPMsgHead)pHead;

			ZASSERT(GetSize() > sizeof(ZNetMsgHead));

			m_pData = (T*)((BYTE*)pHead + sizeof(_MsgHead));

			Fix();
		}

		// 是合法的消息
		// 主要判断大小是否合法
		static bool IsViald(WORD size) {
			return size > sizeof(ZNetMsgHead) && T::IsInvalid(size - sizeof(ZNetMsgHead));
		}

		// 获得大小
		WORD GetSize() const { return m_pHead->GetSize(); }
		// 获得数据
		const T& GetData() const { return *m_pData; }

		// 获得ID
		DWORD GetID() const { return m_pHead->GetID(); }
	protected:
		// 修正
		void Fix() {
			m_pData->Fix(sizeof(VarietyMsg_Recv<T>), GetSize());
		}
	protected:
		_LPMsgHead	m_pHead;
		T*			m_pData;
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长请求消息 － 接收端
	// 偏特化 － 不允许空变长消息

	template<>
	class VarietyMsg_R_Recv<null_type>{
	private:
		VarietyMsg_R_Recv() {}
		~VarietyMsg_R_Recv() {}
	};

	////////////////////////////////////////////////////////////////////////////
	// 连接中断消息

	class ZEPHYR_NET_API EndConnectMsg : public ZNetMsgHead{
	public:
		// 构造函数
		EndConnectMsg() {

			SetSize(sizeof(ZNetMsgHead));

			SetMainID(0);
		}
	};

	////////////////////////////////////////////////////////////////////////////
	// 变长消息

	// 注：
	// 消息长度 和 数据长度
	// 传入的参数 都是数据长度，会在内部变为实际消息长度

	class ZEPHYR_NET_API ZNetVarietyMsg{
	public:
		// 构造函数
		ZNetVarietyMsg(void* buff) {
			ZASSERT(buff != NULL);

			m_pHead = (ZNetMsgHead*)buff;
			m_pData = (BYTE*)buff + sizeof(ZNetMsgHead);

			m_pBuff = NULL;
		}

		// 构造函数
		ZNetVarietyMsg(int size) {
			Alloc(size);
		}

		// 析构函数
		~ZNetVarietyMsg() {
			Release();
		}

	// ------------------------------------------------------------------------
	// 操作

		// 资源释放
		void Release();

		// 重置大小
		void Resize(int size);

		// 设置消息头
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			ZASSERT(m_pHead != NULL);
			ZASSERT(wSize > 0);

			m_pHead->SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// 设置数据
		void SetData(int iOff,void* pData,int iSize) {
			ZASSERT(pData != NULL);
			ZASSERT(iSize > 0);
			ZASSERT(m_pData != NULL);
			ZASSERT(iOff > 0);
			ZASSERT(iOff < m_dataSize);
			ZASSERT(iSize + iOff <= m_dataSize);

			memcpy((BYTE*)m_pData + iOff,pData,iSize);
		}

		// 输入数据长度，获得整个消息长度
		int Size_Data2Msg(int datSize) {
			return datSize + sizeof(ZNetMsgHead);
		}

	// ------------------------------------------------------------------------
	// 属性

		// 获得数据区大小
		int GetDataSize() { return m_dataSize; }
		// 获得消息大小
		int GetMsgSize() { return m_dataSize + sizeof(ZNetMsgHead); }
		// 获得缓冲大小
		int GetBuffSize() { return m_buffSize; }
	private:
		// 分配内存
		void Alloc(int size);
	private:
		BYTE*			m_pBuff;
		ZNetMsgHead*	m_pHead;
		void*			m_pData;

		int				m_buffSize;
		int				m_dataSize;
	};

#pragma pack (pop)

};

#endif//_ZEPHYR_NET_2_NETMSG_H