/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Debug.h

							Describe:	�������

							Author:		�Ժ���(xueren)

							CreateTime: 2003.04.16
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_DEBUG_H
#define _ZEPHYR_3_BASE_DEBUG_H

#include <Base\Assert.h>
#include <Base\LogFile.h>

namespace Zephyr3{

	////////////////////////////////////////////////////////////////////////////
	// Debuger

	class ZEPHYR_3_API Debuger : public LogFile{
	public:
		// ���캯��
		Debuger();

		// ��ʼ��
		HRESULT Init(bool bInLocal,bool bMulFile,const char* str);

		// �ͷ���Դ
		void Release();

		// ���أ�����ʾ����
		HRESULT Ret(HRESULT hRet,const char* str) {

			Output(str);

			return hRet;
		}

		// ���أ�����ʾ����
		HRESULT Ret_Time(HRESULT hRet,const char* str) {

			Output_Time(str);

			return hRet;
		}
	private:
		static const char* BuildFileName(bool bInLocal,bool bMulFile);
	};
};

#endif // _ZEPHYR_3_BASE_DEBUG_H