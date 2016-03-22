/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\NetMsg.h

							Describe:	������Ϣ

							Author:		�Ժ���(xueren)

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
	// ͳһ��Ϣͷ
	// ZNetMsgHead

	class ZEPHYR_NET_API ZNetMsgHead{
	public:

	// ------------------------------------------------------------------------
	// ����
#if _ZEPHYR_NET_VER >= 2200
		// ������Ϣͷ
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
		// ������Ϣͷ
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

		// �� 0
		void Clear() { memset(this, 0, sizeof(ZNetMsgHead)); }

	// ------------------------------------------------------------------------
	// ����

		// �����Ϣ����
		int GetSize() const { return m_wSize; }
		// ������Ϣ����
		void SetSize(WORD size) { 

			ZASSERT(size <= MAX_PKG_SIZE);

			m_wSize = size; 
		}

		// �������ϢID
		BYTE GetMainID() const { return m_bMainID; }
		// ��������ϢID
		void SetMainID(BYTE mainID) { 

			ZASSERT(mainID <= 0x4f);

			m_bMainID = mainID; 
		}

		// ��ø�����ϢID
		BYTE GetAssistantID() const { return m_bAssistantID; }
		// ��ø�����ϢID
		BYTE GetAssID() const { return m_bAssistantID; }
		// ���ø�����ϢID
		void SetAssistantID(BYTE assID) { m_bAssistantID = assID; }
#ifndef __ZEPHYR3_USE_ZEPHYRNET3__
		// �Ƿ���������Ϣ
		bool IsRequestMsg() const { return m_bRequestMsg; }
		// ����
		void Request() { m_bRequestMsg = true; }

		// �Ƿ���Ӧ������Ϣ
		bool IsRespondMsg() const { return m_bRespondMsg; }
		// ��Ӧ
		void Respond() { m_bRespondMsg = true; }

		// �Ƿ�����
		bool IsOrdinal() const { return m_bOrdinalMsg; }
		// ����
		void Ordinal() { m_bOrdinalMsg = true; }
#else // __ZEPHYR3_USE_ZEPHYRNET3__
		// �Ƿ���������Ϣ
		bool IsRequestMsg() const { return false; }
		// ����
		void Request() {}

		// �Ƿ���Ӧ������Ϣ
		bool IsRespondMsg() const { return false; }
		// ��Ӧ
		void Respond() {}

		// �Ƿ�����
		bool IsOrdinal() const { return true; }
		// ����
		void Ordinal() {}
#endif // __ZEPHYR3_USE_ZEPHYRNET3__
		// �Ƿ��ǶϿ�������Ϣ
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
		WORD	m_wSize:15;			//��Ϣ��С
		WORD	m_bOrdinalMsg:1;	//��Ϣ�Ƿ��������
		BYTE	m_bRequestMsg:1;	//�Ƿ�Ϊ������Ϣ
		BYTE	m_bRespondMsg:1;	//�Ƿ�Ϊ��Ӧ������Ϣ
		BYTE	m_bMainID:6;		//����ϢID
#else // __ZEPHYR3_USE_ZEPHYRNET3__
		WORD	m_wSize;			//��Ϣ��С
		BYTE	m_bMainID;			//����ϢID
#endif // __ZEPHYR3_USE_ZEPHYRNET3__
#if _ZEPHYR_NET_VER >= 2200
		BYTE	m_bToOther:1;		// �Ƿ�Ϊת����Ϣ
		BYTE	m_bAssistantID:7;	// ������ϢID
#else
		BYTE	m_bAssistantID;		//������ϢID
#endif
	};

	typedef ZNetMsgHead*	LPZNetMsgHead;

	////////////////////////////////////////////////////////////////////////////
	// ��ͨ��Ϣ - ��������
	// ZNetMsg

	template<class T>
	class ZNetMsg{
	public:
		// ������Ϣͷ
		void SetHead(ZNetMsgHead& Head) { m_Head = Head; }

		// ������Ϣͷ
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// �����Ϣͷ
		LPZNetMsgHead GetHead() { return &m_Head; }

		// �����Ϣͷ
		const ZNetMsgHead& GetSafeHead() const { return m_Head; }

		// ����
		void Request() { m_Head.Request(); }
		// ��Ӧ
		void Respond() { m_Head.Respond(); }

		// ������Ϣ����
		void SetData(T& Data) { m_Data = Data; }
		// ��ȡ��Ϣ����
		T* GetData() { return &m_Data; }
		// ��ȡ��Ϣ����
		const T& GetSafeData() const { return m_Data; }

		// �����Ϣ����
		WORD GetSize() const { return m_Head.GetSize(); }

		// ��Ϣ�����Ƿ�Ϸ�
		// ��Ҫ������֤�䳤��Ϣ
		static bool IsValid(WORD size) {
			return size >= sizeof(ZNetMsgHead) && T::IsValid(size - sizeof(ZNetMsgHead));
		}

		// ��֤��Ϣ��ȷ��
		void Fix() {
			m_Data.Fix(sizeof(ZNetMsg<T>), GetSize());
		}
	protected:
		ZNetMsgHead	m_Head;
		T			m_Data;
	};

	////////////////////////////////////////////////////////////////////////////
	// ��ͨ��Ϣ - ���������� (������)

	template<>
	class ZNetMsg<null_type>{
	public:
		// ������Ϣͷ
		void SetHead(ZNetMsgHead& Head) { m_Head = Head; }

		// ������Ϣͷ
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// ��ȡ��Ϣͷ
		LPZNetMsgHead GetHead() { return &m_Head; }
		// �����Ϣͷ
		const ZNetMsgHead& GetSafeHead() const { return m_Head; }

		// ����
		void Request() { m_Head.Request(); }
		// ��Ӧ
		void Respond() { m_Head.Respond(); }
	private:
		ZNetMsgHead	m_Head;
	};

	////////////////////////////////////////////////////////////////////////////
	// ������Ϣ - ��������
	// ZRequestMsg

	template<class T>
	class ZRequestMsg{
	public:
		// ������Ϣͷ
		void SetHead(ZNetMsgHead& Head) { m_Head = Head; }

		// ������Ϣͷ
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,DWORD dwID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
			m_dwID = dwID;
		}

		// �����Ϣͷ
		LPZNetMsgHead GetHead() { return &m_Head; }
		// �����Ϣͷ
		const ZNetMsgHead& GetSafeHead() const { return m_Head; }

		// ����
		void Request() { m_Head.Request(); }
		// ��Ӧ
		void Respond() { m_Head.Respond(); }

		// ������Ϣ����
		void SetData(T& Data) { m_Data = Data; }
		// ��ȡ��Ϣ����
		T* GetData() { return &m_Data; }
		// ��ȡ��Ϣ����
		const T& GetSafeData() const { return m_Data; }

		// ���ID
		DWORD GetID() const { return m_dwID; }

		// ��Ϣ�����Ƿ�Ϸ�
		// ��Ҫ������֤�䳤��Ϣ
		static bool IsValid(WORD size) {
			return size >= sizeof(ZNetMsgHead) && T::IsValid(size - sizeof(ZNetMsgHead));
		}

		// ��֤��Ϣ��ȷ��
		void Fix() {
			m_Data.Fix(sizeof(ZNetMsg<T>),m_Head.GetSize());
		}
	protected:
		ZNetMsgHead	m_Head;
		DWORD		m_dwID;
		T			m_Data;
	};

	////////////////////////////////////////////////////////////////////////////
	// ������Ϣ - ���������� (������)

	template<>
	class ZRequestMsg<null_type>{
	public:
		// ������Ϣͷ
		void SetHead(ZNetMsgHead& Head) { m_Head = Head; }

		// ������Ϣͷ
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,DWORD dwID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
			m_dwID = dwID;
		}

		// ��ȡ��Ϣͷ
		ZNetMsgHead* GetHead() { return &m_Head; }

		// ����
		void Request() { m_Head.Request(); }
		// ��Ӧ
		void Respond() { m_Head.Respond(); }

		// ���ID
		DWORD GetID() const { return m_dwID; }
	private:
		ZNetMsgHead	m_Head;
		DWORD		m_dwID;
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤��Ϣ �� ���Ͷ�

	template<class T>
	class VarietyMsg_Send : public ZNetMsg<T>{
	public:
		// ������Ϣͷ
		// Ӧ�ȳ�ʼ����Ϣ
		void SetHead(BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			m_Head.SetHead(sizeof(VarietyMsg_Send<T>) - m_Data.GetFreeSize(),mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// ����
		void Fix() {
			m_Data.Fix(sizeof(VarietyMsg_Recv<T>), GetSize());
		}
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤��Ϣ �� ���Ͷ�
	// ƫ�ػ� �� ������ձ䳤��Ϣ

	template<>
	class VarietyMsg_Send<null_type>{
	private:
		VarietyMsg_Send() {}
		~VarietyMsg_Send() {}
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤������Ϣ �� ���Ͷ�

	template<class T>
	class VarietyMsg_R_Send : public ZRequestMsg<T>{
	public:
		// ������Ϣͷ
		// Ӧ�ȳ�ʼ����Ϣ
		void SetHead(BYTE mainID,BYTE assID,DWORD dwID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			ZRequestMsg<T>::SetHead(sizeof(VarietyMsg_R_Send<T>) - m_Data.GetFreeSize(),mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// ����
		void Fix() {
			m_Data.Fix(sizeof(VarietyMsg_Send<T>), GetSize());
		}
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤������Ϣ �� ���Ͷ�
	// ƫ�ػ� �� ������ձ䳤��Ϣ

	template<>
	class VarietyMsg_R_Send<null_type>{
	private:
		VarietyMsg_R_Send() {}
		~VarietyMsg_R_Send() {}
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤��Ϣ �� ���ն�

	template<class T>
	class VarietyMsg_Recv{
	public:
		// ���캯��
		VarietyMsg_Recv(LPZNetMsgHead pHead) {
			ZASSERT(pHead != NULL);

			m_pHead = pHead;

			ZASSERT(GetSize() > sizeof(ZNetMsgHead));

			m_pData = (T*)((BYTE*)pHead + sizeof(ZNetMsgHead));

			Fix();
		}

		// �ǺϷ�����Ϣ
		// ��Ҫ�жϴ�С�Ƿ�Ϸ�
		static bool IsViald(WORD size) {
			return size > sizeof(ZNetMsgHead) && T::IsInvalid(size - sizeof(ZNetMsgHead));
		}

		// ��ô�С
		WORD GetSize() const { return m_pHead->GetSize(); }
		// �������
		const T& GetData() const { return *m_pData; }
	protected:
		// ����
		void Fix() {
			m_pData->Fix(sizeof(VarietyMsg_Recv<T>), GetSize());
		}
	protected:
		LPZNetMsgHead	m_pHead;
		T*				m_pData;
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤��Ϣ �� ���ն�
	// ƫ�ػ� �� ������ձ䳤��Ϣ

	template<>
	class VarietyMsg_Recv<null_type>{
	private:
		VarietyMsg_Recv() {}
		~VarietyMsg_Recv() {}
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤������Ϣ �� ���ն�

	template<class T>
	class VarietyMsg_R_Recv{
		typedef ZRequestMsg<null_type>	_MsgHead;
		typedef _MsgHead*	_LPMsgHead;
	public:
		// ���캯��
		VarietyMsg_R_Recv(LPZNetMsgHead pHead) {
			ZASSERT(pHead != NULL);

			m_pHead = (_LPMsgHead)pHead;

			ZASSERT(GetSize() > sizeof(ZNetMsgHead));

			m_pData = (T*)((BYTE*)pHead + sizeof(_MsgHead));

			Fix();
		}

		// �ǺϷ�����Ϣ
		// ��Ҫ�жϴ�С�Ƿ�Ϸ�
		static bool IsViald(WORD size) {
			return size > sizeof(ZNetMsgHead) && T::IsInvalid(size - sizeof(ZNetMsgHead));
		}

		// ��ô�С
		WORD GetSize() const { return m_pHead->GetSize(); }
		// �������
		const T& GetData() const { return *m_pData; }

		// ���ID
		DWORD GetID() const { return m_pHead->GetID(); }
	protected:
		// ����
		void Fix() {
			m_pData->Fix(sizeof(VarietyMsg_Recv<T>), GetSize());
		}
	protected:
		_LPMsgHead	m_pHead;
		T*			m_pData;
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤������Ϣ �� ���ն�
	// ƫ�ػ� �� ������ձ䳤��Ϣ

	template<>
	class VarietyMsg_R_Recv<null_type>{
	private:
		VarietyMsg_R_Recv() {}
		~VarietyMsg_R_Recv() {}
	};

	////////////////////////////////////////////////////////////////////////////
	// �����ж���Ϣ

	class ZEPHYR_NET_API EndConnectMsg : public ZNetMsgHead{
	public:
		// ���캯��
		EndConnectMsg() {

			SetSize(sizeof(ZNetMsgHead));

			SetMainID(0);
		}
	};

	////////////////////////////////////////////////////////////////////////////
	// �䳤��Ϣ

	// ע��
	// ��Ϣ���� �� ���ݳ���
	// ����Ĳ��� �������ݳ��ȣ������ڲ���Ϊʵ����Ϣ����

	class ZEPHYR_NET_API ZNetVarietyMsg{
	public:
		// ���캯��
		ZNetVarietyMsg(void* buff) {
			ZASSERT(buff != NULL);

			m_pHead = (ZNetMsgHead*)buff;
			m_pData = (BYTE*)buff + sizeof(ZNetMsgHead);

			m_pBuff = NULL;
		}

		// ���캯��
		ZNetVarietyMsg(int size) {
			Alloc(size);
		}

		// ��������
		~ZNetVarietyMsg() {
			Release();
		}

	// ------------------------------------------------------------------------
	// ����

		// ��Դ�ͷ�
		void Release();

		// ���ô�С
		void Resize(int size);

		// ������Ϣͷ
		void SetHead(WORD wSize,BYTE mainID,BYTE assID,bool bRequest = false,bool bRespond = false,bool bOrdinal = true) {
			ZASSERT(m_pHead != NULL);
			ZASSERT(wSize > 0);

			m_pHead->SetHead(wSize,mainID,assID,bRequest,bRespond,bOrdinal);
		}

		// ��������
		void SetData(int iOff,void* pData,int iSize) {
			ZASSERT(pData != NULL);
			ZASSERT(iSize > 0);
			ZASSERT(m_pData != NULL);
			ZASSERT(iOff > 0);
			ZASSERT(iOff < m_dataSize);
			ZASSERT(iSize + iOff <= m_dataSize);

			memcpy((BYTE*)m_pData + iOff,pData,iSize);
		}

		// �������ݳ��ȣ����������Ϣ����
		int Size_Data2Msg(int datSize) {
			return datSize + sizeof(ZNetMsgHead);
		}

	// ------------------------------------------------------------------------
	// ����

		// �����������С
		int GetDataSize() { return m_dataSize; }
		// �����Ϣ��С
		int GetMsgSize() { return m_dataSize + sizeof(ZNetMsgHead); }
		// ��û����С
		int GetBuffSize() { return m_buffSize; }
	private:
		// �����ڴ�
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