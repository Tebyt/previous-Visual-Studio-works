/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\BaseDef.h

							Describe:	基本定义

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.24
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_2_BASE_DEFINE_H
#define _ZEPHYR_GRAPH_2_BASE_DEFINE_H

namespace ZGraph2{

// 基本定义

// 色彩模式

	// 色彩模式
	enum ZEPHYR_COLOR_MODE{
		ZCM_NODEFINE	= 0,	// 未定义

		ZCM_R8G8B8		= 0x1,	// 24bits

		ZCM_A8R8G8B8	= 0x2,	// 32bits，带1字节的alpha
		ZCM_X8R8G8B8	= 0x3,	// 32bits，不带alpha

		ZCM_R5G6B5		= 0x4,	// 16bits 565
		ZCM_X1R5G5B5	= 0x5,	// 16bits 555
		ZCM_A1R5G5B5	= 0x6,	// 16bits 555，高1位为alpha
		ZCM_A4R4G4B4	= 0x7,	// 16bits 4444，带4位的alpha

		ZCM_P8			= 0x8,	// 8bits，调色板
		ZCM_GRAY		= 0x9	// 8bits 灰度
	};


	// 功能：获得 色彩模式 位深
	// 参数：枚举变量 ZEPHYR_COLOR_MODE
	// 返回：位深，8、16、24、32
	// 注意：无
	inline int ColorBits(ZEPHYR_COLOR_MODE zcm)
	{
		return zcm & 0x8 ? 8 : (zcm & 0x4 ? 16 : (zcm & 0x2 ? 32 : 24));
	}

	// 功能：获得 色彩模式 文字描述。主要用于调试输出
	// 参数：枚举变量 ZEPHYR_COLOR_MODE
	// 返回：色彩模式文字描述，例如："A8R8G8B8" 等。如果失败，返回"ERROR!"字符串。
	// 注意：
	const char* GetColorBitsString(ZEPHYR_COLOR_MODE zcm);

// 颜色定义

// 16 位色
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

	// 功能：(a,r,g,b) to 16 bits 1555
	// 参数：a,r,g,b
	// 返回：COLOR16B - 16 bits color(1555)
	// 注意：
	inline COLOR16B _RGBA_To_1555(int a,int r,int g,int b)
	{
		return (COLOR16B)((((WORD)a<<15) & 0x8000) | ((WORD)(r<<7) & 0x7c00) | ((WORD)(g<<2) & 0x03e0) | ((WORD)(b>>3) & 0x001f));
	}

	// 功能：(a,r,g,b) to 16 bits 565
	// 参数：a,r,g,b
	// 返回：COLOR16B - 16 bits color(565)
	// 注意：
	inline COLOR16B _RGBA_To_565(int a,int r,int g,int b)
	{
		return (COLOR16B)(((WORD)(r<<8)&0xf800)|((WORD)(g<<3)&0x07e0)|((WORD)(b>>3)&0x001f));
	}

	// 功能：16bits 1555 to 16 bits 565
	// 参数：COLOR16B - 16 bits color(1555)
	// 返回：COLOR16B
	// 注意：
	inline COLOR16B _1555_To_565(COLOR16B c1555)
	{
		return (COLOR16B)((WORD)((c1555 & 0x7fe0)<<1) | (c1555 & 0x001f));
	}

	// 功能：16 bits 565 to 16 bits 1555
	// 参数：COLOR16B - 16 bits color(565)
	// 返回：COLOR16B
	// 注意：
	inline COLOR16B _565_To_1555(COLOR16B c565)
	{
		return (COLOR16B)((WORD)((c565 & 0xffc0)>>1) | (c565 & 0x001f));
	}

// 24 位色
	// 24 bits color
	union COLOR24B{
		DWORD	color;

		struct{
			BYTE	r,g,b;
		} rgb;
	};

// 32 位色
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