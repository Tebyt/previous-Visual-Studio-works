/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\BaseDef.h

							Describe:	��������

							Author:		�Ժ���(xueren)

							CreateTime: 2003.04.22
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_BASEDEF_H
#define _ZEPHYR_3_BASE_BASEDEF_H

namespace Zephyr3{

	// �������
	HRESULT ZEPHYR_3_API Ret(HRESULT hRet,const char* str, ...);

	// �������
	HRESULT ZEPHYR_3_API Ret_Time(HRESULT hRet,const char* str, ...);

	// ���log
	void ZEPHYR_3_API OutputLog(const char* str, ...);

	// ���log
	void ZEPHYR_3_API OutputLog_Time(const char* str, ...);

	// �ַ�����ʽ��
	// ������Լ���֤Ŀ���ַ����������
	void ZEPHYR_3_API _StrFormat(char* buf, DWORD bufSize, const char* str,...);
};

#ifndef _DEBUG
#define OUTPUTLOG_TIME(param)	Zephyr3::PutputLog_Time(param)
#define OUTPUTLOG_TIME2(param1,param2)	Zephyr3::PutputLog_Time(param1,param2)
#else
#define OUTPUTLOG_TIME(param)	
#define OUTPUTLOG_TIME2(param1,param2)	
#endif

#endif // _ZEPHYR_3_BASE_BASEDEF_H