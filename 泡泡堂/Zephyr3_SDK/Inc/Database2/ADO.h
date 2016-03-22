/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Database2\ADO.h

							Describe:	ADO

							Author:		赵洪松(xueren)

							CreateTime: 2004.06.29
							UpdateTime:
*/

#ifndef _ZEPHYR_3_DATABASE_2_ADO_H
#define _ZEPHYR_3_DATABASE_2_ADO_H

#include <icrsint.h>
#import <DataBase2\msado15.dll> no_namespace rename("EOF", "adoEOF")

#include <string>

namespace ZDatabase2{

	//////////////////////////////////////////////////////////////////////////////////
	// define

	const int DB_USER_LEN	=	32;
	const int DB_PSW_LEN	=	256;

	//////////////////////////////////////////////////////////////////////////////////
	// typedef

	typedef _ConnectionPtr	ConnectionPtr;
	typedef _RecordsetPtr	RecordsetPtr;
	typedef _CommandPtr		CommandPtr;
	typedef ParametersPtr   LPParam;
	typedef _ParameterPtr   ParamPtr;

	//////////////////////////////////////////////////////////////////////////////////
	// Func

	int ZEPHYR_3_DB2_API Var2Str(char *str,int len,_variant_t &var);

	//////////////////////////////////////////////////////////////////////////////////
	//	Database

	class ZEPHYR_3_DB2_API Database{
	public:

#ifdef _DEVELOP_CORE

		// 构造函数
		Database() 
			: m_vtEmpty(DISP_E_PARAMNOTFOUND, VT_ERROR)
			, m_bstrEmpty(L"")
		{
			m_connectPtr = NULL;
		}
		// 析购函数
		~Database() {}

		// 初始化CommandPtr
		void InitCommandPtr(CommandPtr& comPtr) {
			comPtr.CreateInstance(__uuidof(Command));
			comPtr->ActiveConnection = m_connectPtr;
		}

#endif // _DEVELOP_CORE

#ifdef _DEVELOP_SECOND

		// 构造函数
		Database();
		// 析购函数
		~Database() {}

		// 初始化CommandPtr
		void InitCommandPtr(CommandPtr& comPtr);

#endif // _DEVELOP_SECOND

		// 释放资源
		void Release() { Close(); }

		bool IsOpen() const;

		// 关闭数据库连接
		void Close();

		// 打开SQLServer数据库
		HRESULT OpenDatabase_SQLServer(const char* server,const char* database,const char* user,const char* psw);

		// 连接
		HRESULT Connect();

		// 打开表
		HRESULT OpenTable(RecordsetPtr& recordsetPtr,const char* sql);
		// 执行命令
		HRESULT Execute(RecordsetPtr& recordsetPtr,const char* sql);
	public:
		ConnectionPtr	m_connectPtr;
		_variant_t		m_vtEmpty;
		_bstr_t			m_bstrEmpty;

		std::string		m_strServer;
		std::string		m_strDB;
		std::string		m_strUser;
		std::string		m_strPSW;
	};
};

#endif // _ZEPHYR_3_DATABASE_2_ADO_H