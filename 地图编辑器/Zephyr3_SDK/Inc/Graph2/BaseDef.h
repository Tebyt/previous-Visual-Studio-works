/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\BaseDef.h

							Describe:	��������

							Author:		�Ժ���(xueren)

							CreateTime: 2003.11.24
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_2_BASE_DEFINE_H
#define _ZEPHYR_GRAPH_2_BASE_DEFINE_H

namespace ZGraph2{

// ��������

// ɫ��ģʽ

	// ɫ��ģʽ
	enum ZEPHYR_COLOR_MODE{
		ZCM_NODEFINE	= 0,	// δ����

		ZCM_R8G8B8		= 0x1,	// 24bits

		ZCM_A8R8G8B8	= 0x2,	// 32bits����1�ֽڵ�alpha
		ZCM_X8R8G8B8	= 0x3,	// 32bits������alpha

		ZCM_R5G6B5		= 0x4,	// 16bits 565
		ZCM_X1R5G5B5	= 0x5,	// 16bits 555
		ZCM_A1R5G5B5	= 0x6,	// 16bits 555����1λΪalpha
		ZCM_A4R4G4B4	= 0x7,	// 16bits 4444����4λ��alpha

		ZCM_P8			= 0x8,	// 8bits����ɫ��
		ZCM_GRAY		= 0x9	// 8bits �Ҷ�
	};


	// ���ܣ���� ɫ��ģʽ λ��
	// ������ö�ٱ��� ZEPHYR_COLOR_MODE
	// ���أ�λ�8��16��24��32
	// ע�⣺��
	inline int ColorBits(ZEPHYR_COLOR_MODE zcm)
	{
		return zcm & 0x8 ? 8 : (zcm & 0x4 ? 16 : (zcm & 0x2 ? 32 : 24));
	}

	// ���ܣ���� ɫ��ģʽ ������������Ҫ���ڵ������
	// ������ö�ٱ��� ZEPHYR_COLOR_MODE
	// ���أ�ɫ��ģʽ�������������磺"A8R8G8B8" �ȡ����ʧ�ܣ�����"ERROR!"�ַ�����
	// ע�⣺
	const char* GetColorBitsString(ZEPHYR_COLOR_MODE zcm);

// ��ɫ����

// 16 λɫ
	// 16 bits color
	typedef WORD	COLOR16B;

	// 16 bits,565
	union COLOR16B_565{
		WORD	color;

		struct{
			WORD	b:5;
			WORD	g:6;
			WORD	r:5;
		} rgb;
	};

	// 16 bits,555
	union COLOR16B_555{
		WORD	color;

		struct{
			WORD	b:5;
			WORD	g:5;
			WORD	r:5;
			WORD	a:1;
		} rgba;
	};

	// 16 bits,4444
	union COLOR16B_4444{
		WORD	color;

		struct{
			WORD	b:4;
			WORD	g:4;
			WORD	r:4;
			WORD	a:4;
		} rgba;
	};

	// ���ܣ�(a,r,g,b) to 16 bits 1555
	// ������a,r,g,b
	// ���أ�COLOR16B - 16 bits color(1555)
	// ע�⣺
	inline COLOR16B _RGBA_To_1555(int a,int r,int g,int b)
	{
		return (COLOR16B)((((WORD)a<<15) & 0x8000) | ((WORD)(r<<7) & 0x7c00) | ((WORD)(g<<2) & 0x03e0) | ((WORD)(b>>3) & 0x001f));
	}

	// ���ܣ�(a,r,g,b) to 16 bits 565
	// ������a,r,g,b
	// ���أ�COLOR16B - 16 bits color(565)
	// ע�⣺
	inline COLOR16B _RGBA_To_565(int a,int r,int g,int b)
	{
		return (COLOR16B)(((WORD)(r<<8)&0xf800)|((WORD)(g<<3)&0x07e0)|((WORD)(b>>3)&0x001f));
	}

	// ���ܣ�16bits 1555 to 16 bits 565
	// ������COLOR16B - 16 bits color(1555)
	// ���أ�COLOR16B
	// ע�⣺
	inline COLOR16B _1555_To_565(COLOR16B c1555)
	{
		return (COLOR16B)((WORD)((c1555 & 0x7fe0)<<1) | (c1555 & 0x001f));
	}

	// ���ܣ�16 bits 565 to 16 bits 1555
	// ������COLOR16B - 16 bits color(565)
	// ���أ�COLOR16B
	// ע�⣺
	inline COLOR16B _565_To_1555(COLOR16B c565)
	{
		return (COLOR16B)((WORD)((c565 & 0xffc0)>>1) | (c565 & 0x001f));
	}

// 24 λɫ
	// 24 bits color
	union COLOR24B{
		DWORD	color;

		struct{
			BYTE	r,g,b;
		} rgb;
	};

// 32 λɫ
	// 32 vits color
	union COLOR32B{
		DWORD	color;

		struct{
			BYTE	r,g,b,a;
		} rgba;
	};

// Bitmap Flag
	const WORD BITMAP_COLORKEY	=	0x01;
};

#endif//_ZEPHYR_GRAPH_2_BASE_DEFINE_H