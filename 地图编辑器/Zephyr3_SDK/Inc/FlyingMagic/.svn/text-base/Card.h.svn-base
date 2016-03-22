/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	FlyingMagic\Card.h

							Describe:	FlyingMagic 棋牌部分

							Author:		赵洪松(xueren)

							CreateTime: 2003.09.18
							UpdateTime:
*/

#ifndef _ZEPHYR_FLYINGMAGIC_CARD_H
#define _ZEPHYR_FLYINGMAGIC_CARD_H

#include <ZDebug.h>
#include <Graph\ZGraph.h>

///////////////////////////////////////////////////////////////////////////////////
// ZCard

const BYTE	ZCARD_TYPE_PEACH	=	0x10;	//黑桃
const BYTE	ZCARD_TYPE_HEART	=	0x20;	//红心
const BYTE	ZCARD_TYPE_CLUB		=	0x30;	//梅花
const BYTE	ZCARD_TYPE_DIAMOND	=	0x40;	//方块

const BYTE	ZCARD_TYPE_KING		=	0x50;	//小王
const BYTE	ZCARD_TYPE_KING_BIG	=	0x60;	//大王

const BYTE	ZCARD_TYPE			=	0xf0;
const BYTE	ZCARD_VALUE			=	0x0f;

class ZCard{
private:
	BYTE	m_Card;
public:
	// 默认构咱函数
	ZCard() { m_Card = 0; }
	// 拷贝构造函数
	ZCard(ZCard &card) { m_Card = card.m_Card; }
	// 构造函数
	ZCard(BYTE type,BYTE value) { SetCard(type,value); }

	// 获得牌种类
	BYTE GetType() { return m_Card & ZCARD_TYPE; }
	// 获得牌大小
	BYTE GetValue() { return m_Card & ZCARD_VALUE; }
	// 设置牌
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
	// 缺省构造函数
	inline ZCards();
	// 构造函数
	inline ZCards(int nums);

	// 获得内部数据
	LPZCard GetData() { return m_Cards; }

	// 删除牌
	void Del(int index);
	// 查找牌
	// 返回 -1 代表没找到
	int Find(ZCard &card);
protected:
	// 分配空间
	void Alloc(int nums);
};

// 缺省构造函数
inline ZCards::ZCards()
{
	m_Cards = NULL;
	m_Nums = 0;
}

// 构造函数
inline ZCards::ZCards(int nums)
{
	m_Cards = NULL;
	m_Nums = 0;

	Alloc(nums);
}

// 分配空间
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