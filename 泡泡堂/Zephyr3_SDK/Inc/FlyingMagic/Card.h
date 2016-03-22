/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	FlyingMagic\Card.h

							Describe:	FlyingMagic ���Ʋ���

							Author:		�Ժ���(xueren)

							CreateTime: 2003.09.18
							UpdateTime:
*/

#ifndef _ZEPHYR_FLYINGMAGIC_CARD_H
#define _ZEPHYR_FLYINGMAGIC_CARD_H

#include <ZDebug.h>
#include <Graph\ZGraph.h>

///////////////////////////////////////////////////////////////////////////////////
// ZCard

const BYTE	ZCARD_TYPE_PEACH	=	0x10;	//����
const BYTE	ZCARD_TYPE_HEART	=	0x20;	//����
const BYTE	ZCARD_TYPE_CLUB		=	0x30;	//÷��
const BYTE	ZCARD_TYPE_DIAMOND	=	0x40;	//����

const BYTE	ZCARD_TYPE_KING		=	0x50;	//С��
const BYTE	ZCARD_TYPE_KING_BIG	=	0x60;	//����

const BYTE	ZCARD_TYPE			=	0xf0;
const BYTE	ZCARD_VALUE			=	0x0f;

class ZCard{
private:
	BYTE	m_Card;
public:
	// Ĭ�Ϲ��ۺ���
	ZCard() { m_Card = 0; }
	// �������캯��
	ZCard(ZCard &card) { m_Card = card.m_Card; }
	// ���캯��
	ZCard(BYTE type,BYTE value) { SetCard(type,value); }

	// ���������
	BYTE GetType() { return m_Card & ZCARD_TYPE; }
	// ����ƴ�С
	BYTE GetValue() { return m_Card & ZCARD_VALUE; }
	// ������
	void SetCard(BYTE type,BYTE value) { m_Card = type | value; }
};

typedef ZCard *	LPZCard;

///////////////////////////////////////////////////////////////////////////////////
// ZCards

class ZCards{
protected:
	LPZCard		m_Cards;
	int			m_Nums;
public:
	// ȱʡ���캯��
	inline ZCards();
	// ���캯��
	inline ZCards(int nums);

	// ����ڲ�����
	LPZCard GetData() { return m_Cards; }

	// ɾ����
	void Del(int index);
	// ������
	// ���� -1 ����û�ҵ�
	int Find(ZCard &card);
protected:
	// ����ռ�
	void Alloc(int nums);
};

// ȱʡ���캯��
inline ZCards::ZCards()
{
	m_Cards = NULL;
	m_Nums = 0;
}

// ���캯��
inline ZCards::ZCards(int nums)
{
	m_Cards = NULL;
	m_Nums = 0;

	Alloc(nums);
}

// ����ռ�
inline void ZCards::Alloc(int nums)
{
	ZASSERT(m_Cards == NULL);
	ZASSERT(nums > 0);

	m_Cards = new ZCard[nums];
	assert(m_Cards != NULL);

	m_Nums = nums;
}

typedef ZCards *	LPZCards;

///////////////////////////////////////////////////////////////////////////////////
// ZCardsView

class ZCardsView{
protected:
	static LPZSprite	m_sprCards;

	LPZCards	m_Cards;
public:

	void Draw();
};

#endif//_ZEPHYR_FLYINGMAGIC_CARD_H