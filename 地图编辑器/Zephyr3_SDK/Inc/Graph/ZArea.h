/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZArea.h

							Describe:	���� ����

							Author:		�Ժ���(xueren)

							CreateTime: 2003.10.23
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_AREA_H
#define _ZEPHYR_GRAPH_AREA_H

#include <ZState.h>
#include <ZLink.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZAreaData

const BYTE	ZAREADATA_STATE_HIDE	=	0x01;

class ZEPHYR_API ZAreaData{
	union _Data{
		void	*pVoid;
		DWORD	dwData;
	};
public:
	// ���캯��
	inline ZAreaData();
	// ��������
	~ZAreaData() {}

	// �Ƿ�����
	bool IsHide() { return m_bState.Has(ZAREADATA_STATE_HIDE); }
	// ����
	void Hide() { m_bState += ZAREADATA_STATE_HIDE; }

	// �������ݣ�DWORD
	void SetData(DWORD dwData) { m_Data.dwData = dwData; }
	// �������ݣ�ָ��
	void SetData(void *pVoid) { m_Data.pVoid = pVoid; }

	// ��ȡ���ݣ�DWORD
	DWORD GetData_DWord() { return m_Data.dwData; }
	// ��ȡ���ݣ�ָ��
	void *GetData_pVoid() { return m_Data.pVoid; }

	// ��������
	void SetState(BYTE bState) { m_bState = bState; }
	// ��ȡ����
	BYTE GetState() { return m_bState.Get(); }

	// ���þ���
	void SetRect(RECT &rect) { memcpy(&m_Rect,&rect,sizeof(rect)); }
	// ��ȡ����
	RECT *GetRect() { return &m_Rect; }

	// ��ֵ
	void Equ(ZAreaData &dat);
private:
	RECT			m_Rect;
	_Data			m_Data;
	ZState_Byte		m_bState;
};

// ���캯��
inline ZAreaData::ZAreaData()
{
	m_Data.dwData = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZArea

// �з� AreaData ����ʹ�õķ������
const BYTE	ZAREA_CUT_DIR_LT		=	0;
const BYTE	ZAREA_CUT_DIR_RT		=	1;
const BYTE	ZAREA_CUT_DIR_LB		=	2;
const BYTE	ZAREA_CUT_DIR_RB		=	3;

class ZEPHYR_API ZArea{
	typedef ZDLinkEx<ZAreaData,4,4>	_AreaLink;
public:
	// ���캯��
	inline ZArea();
	// ��������
	~ZArea() { Release(); }

	// ��������
	void Add(ZArea &area);
	// ���Ӿ�������
	void Add(ZAreaData &dat);
	// ���Ӿ�������
	void Add(RECT &rect,DWORD dwData,BYTE bState);
	// ���Ӿ�������
	void Add(RECT &rect,void *pVoid,BYTE bState);

	// ����
	void Sub(ZArea &area);
	// ���پ���
	void Sub(RECT &rect);

	// ���
	void Clear() { m_Link.Clear(); }
	// �Ƿ�Ϊ��
	bool IsEmpty() { return m_Link.GetUsed() == 0; }

	// ��Դ�ͷ�
	void Release();

	// ����
	void GetData(ZAreaData* &dat,void* &index) { m_Link.GetData(dat,index); }
private:
	// ����
	ZAreaData *Insert(RECT &rect,DWORD dwData,BYTE bState);
	// ����
	ZAreaData *Insert(RECT &rect,void *pVoid,BYTE bState);
	// ����
	ZAreaData *Insert(ZAreaData &dat);
	// ����
	void Insert(ZArea &area);

	// �з�AreaData
	bool CutArea(void* &index,ZAreaData* &dat,long x,long y,BYTE dir);
	// �з�AreaData
	bool CutArea_X(void* &index,ZAreaData* &dat,long x,bool bLeft);
	// �з�AreaData
	bool CutArea_Y(void* &index,ZAreaData* &dat,long y,bool bTop);

	bool IsInRect(RECT &dst,RECT &src);

	bool IsInRect(RECT &dst,long x,long y,long dx,long dy);

	// �������
	void DebugLink();

	// ��ȡ������Ҫ����ʱ����
	ZArea *GetTmpArea();
	// �ͷ���ʱ�����ڴ�
	void ReleaseTmpArea();
private:
	_AreaLink	m_Link;
	ZArea		*m_pTmp;
};

// ���캯��
inline ZArea::ZArea()
{
	m_pTmp = NULL;
}

#endif//_ZEPHYR_GRAPH_AREA_H