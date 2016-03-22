/*
 *	Cloud Wu's JPEG decoder
 *
 *			2000/3/4 第 1 版
 *
 *		允许非赢利性质的自由使用, 但如果使用此代码的全部或部分
 *		请署上 Cloud Wu (云风)
 *
 *		商业使用请向作者直接联系
 *
 *		http://member.netease.com/~cloudwu
 *		cloudwu@263.net
 *	
 *		JPEG 内部头文件
 */

#ifndef _JPEG_INTERNAL_
#define _JPEG_INTERNAL_

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#pragma pack (push)
#pragma pack (1)

typedef struct {
	WORD code;	// huffman 编码
	BYTE len;	// 掩码长度
	BYTE num;	// 代表的字节
} JPEG_HUFFMANCODE;

typedef struct {
	BYTE v;
	BYTE h;
	BYTE qtb;
	BYTE act;
	BYTE dct;
} JPEG_COMPONENT;

typedef struct {
	BYTE colordepth;
	WORD height;
	WORD width;
	BYTE components;
	JPEG_COMPONENT component[3];
} JPEG_SOF0;

#pragma pack (pop)

typedef struct {
	JPEG_HUFFMANCODE *htb;
	int num;
} JPEG_HUFFMANTABLE;

extern JPEG_HUFFMANTABLE jpeg_htable[8];
extern short *jpeg_qtable[4];
extern JPEG_SOF0 jpeg_head;
extern short jpeg_DC[3];
extern BYTE jpeg_bit,*jpeg_stream;
extern BYTE jpeg_zigzag[64];
extern WORD jpeg_DRI;

#define READ_MWORD(a,stream) \
	__asm mov esi,stream	\
	__asm xor eax,eax		\
	__asm lodsw				\
    __asm xchg al,ah		\
	__asm mov a,ax			\
	__asm mov stream,esi	

BYTE READ_BYTE(BYTE* &lpb);

WORD READ_WORD(BYTE* &lpb);

void* read_DQT(BYTE *stream);
void* read_DHT(BYTE *stream);
void *read_SOF0(BYTE *stream);
void *read_DRI(void *stream);
void *read_SOS(BYTE *stream);
void *skip_SEG(void *stream);

// 预处理, 去掉 FF
void jpeg_preprocess(BYTE *stream);

// 从数据流 jpeg_stream 解码一个 DU 到 buf
void jpeg_decode_DU(short *buf,int com);

void jpeg_idct8x8aan (short *src_result);
void jpeg_idct2d(short *buf);
extern void (*jpeg_idct) (short *buf);
void Y2RGB(WORD *bmppixel,int pitch);	
extern void (*YCbCr411)(WORD *bmppixel,int pitch);
void YCbCr111(WORD *bmppixel,int pitch);
void jpeg_setcolormode(int is555,int isMMX);

//zhs007	改变颜色模式设置
void jpeg_changecolormode(int is555);

#endif