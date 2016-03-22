/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\Tile.h

							Describe:	��Ϸ���� Tile ����

							Author:		�Ժ���(xueren)

							CreateTime: 2003.09.17
							UpdateTime:
*/

#ifndef _ZEPHYR_GAMEENGINE_H
#define _ZEPHYR_GAMEENGINE_H

//////////////////////////////////////////////////////////////////////////////////////////
// ZGameTileType

const DWORD		ZGAMETILE_NULL		=	0;
const DWORD		ZGAMETILE_16X16		=	16;
const DWORD		ZGAMETILE_32X32		=	32;

class ZGameTileType{
protected:
	union _Tile{
		DWORD	dwTile;
		WORD	wTile[2];
	};

	_Tile	m_Tile;
public:
	// ȱʡ���캯��
	ZGameTileType() { m_Tile.dwTile = ZGAMETILE_NULL; }
	// ���캯��
	ZGameTileType(DWORD tile) { m_Tile.dwTile = tile; }
	// �������캯��
	ZGameTileType(ZGameTileType &tile) { m_Tile.dwTile = tile.m_Tile.dwTile; }
	// ��������
	~ZGameTileType() { ; }

	// ��þ���Tile��С
	int GetRectTileSize() { return m_Tile.wTile[0]; }
	// ���Tile����
	WORD GetTileState() { return m_Tile.wTile[1]; }

	void SetRectTile(int tileSize) { m_Tile.dwTile = tileSize; }
};

//////////////////////////////////////////////////////////////////////////////////////////
// ZGameTileData

template<class T>
class ZGameTileData{
protected:
	T		**m_Data;
	long	m_lWidth,m_lHeight;
public:
	// ���캯��
	inline ZGameTileData();
	// ���캯��
	ZGameTileData(long w,long h) { Init(w,h); }
	// ��������
	~ZGameTileData() { Release(); }

	// ��ʼ��
	HRESULT Init(long w,long h);

	// ��� (x,y) ������ÿһ�������
	DWORD GetData(long x,long y);

	// ���� (x,y) ���������
	void SetData(long x,long y,DWORD dat);

	// ���Tile���ݴ�С
	int GetTileDataLen() { return sizeof(T); }

	// �ͷ���Դ
	void Release();

	// �������ݵ��ļ�
	// ע�� -	�ļ�Ӧ�����Ѿ��򿪵�
	HRESULT SaveLayerData(ZFile &file);

	// ���ļ���ȡ����
	// ע�� -	�ļ�Ӧ�����Ѿ��򿪵�
	HRESULT LoadLayerData(ZFile &file);
};

// ���캯��
template<class T>
inline ZGameTileData<T>::ZGameTileData() 
{
	m_lWidth = 0;
	m_lHeight = 0;

	m_Data = NULL;
}

// ��ʼ��
template<class T>
HRESULT ZGameTileData<T>::Init(long w,long h)
{
	ZASSERT(m_lWidth == 0 && m_lHeight == 0);
	ZASSERT(w > 0 && h > 0);
	ZASSERT(m_Data == NULL);

	m_lWidth = w;
	m_lHeight = h;

	m_Data = (T **)malloc(sizeof(T *) * h + sizeof(T) * w * h);
	assert(m_Data != NULL);

	memset(m_Data,0,sizeof(T *) * h + sizeof(T) * w * h);

	BYTE *tmp = (BYTE *)((BYTE *)m_Data + sizeof(BYTE *) * h);

	for(int i = 0; i < h; i++)
	{
		m_Data[i] = (T *)tmp;

		tmp += sizeof(T) * w;
	}

	return S_OK;
}

// ��� (x,y) ������ÿһ�������
template<class T>
DWORD ZGameTileData<T>::GetData(long x,long y)
{
	ZASSERT(m_Data != NULL);
	ZASSERT(x >= 0 && x < m_lWidth);
	ZASSERT(y >= 0 && y < m_lHeight);

	return m_Data[y][x];
}

// ���� (x,y) ���������
template<class T>
void ZGameTileData<T>::SetData(long x,long y,DWORD dat)
{
	ZASSERT(m_Data != NULL);
	ZASSERT(x >= 0 && x < m_lWidth);
	ZASSERT(y >= 0 && y < m_lHeight);

	m_Data[y][x] = (T)dat;
}

// �ͷ���Դ
template<class T>
void ZGameTileData<T>::Release()
{
	if(m_Data != NULL)
	{
		free(m_Data);

		m_Data = NULL;
	}

	m_lWidth = m_lHeight = 0;
}

// �������ݵ��ļ�
// ע�� -	�ļ�Ӧ�����Ѿ��򿪵�
template<class T>
HRESULT ZGameTileData<T>::SaveLayerData(ZFile &file)
{
	ZASSERT(file.IsOpen());
	ZASSERT(m_Data != NULL);

	for(int y = 0; y < m_lHeight; y++)
		file.Write(m_Data[y],sizeof(T) * m_lWidth);

	return S_OK;
}

// ���ļ���ȡ����
// ע�� -	�ļ�Ӧ�����Ѿ��򿪵�
template<class T>
HRESULT ZGameTileData<T>::LoadLayerData(ZFile &file)
{
	ZASSERT(file.IsOpen());
	ZASSERT(m_Data != NULL);

	for(int y = 0; y < m_lHeight; y++)
		file.Read(m_Data[y],sizeof(T) * m_lWidth);

	return S_OK;
}

#endif//_ZEPHYR_GAMEENGINE_H