
#pragma once

#include <icrsint.h>
#import <DataBase3\msado15.dll> no_namespace rename("EOF", "adoEOF")

namespace ZDatabase3{

	const int DB_NAME_LEN			=	32;
	const int DB_USER_LEN			=	64;
	const int DB_PSW_LEN			=	128;
	const int CONNECT_STRING_LEN	=	128;


	int ZEPHYR_3_DB3_API Var2Str(char *str,int len,_variant_t &var);

	//////////////////////////////////////////////////////////////////////////////////
	//	DBMgr

	class ZEPHYR_3_DB3_API CDBMgr
	{
	public:
		CDBMgr(void);
		virtual ~CDBMgr(void);


		//构造对象后调用
		BOOL Create();

		void SetConnectStr(const char* pConnectString) { strcpy(m_szConnectStr, pConnectString); }

		void SetConnectStr(const char* server,const char* database,const char* user,const char* psw);

		//判断是否有效
		BOOL IsValid() { return m_pConnection!=NULL && m_pCommand!=NULL; }

		//与数据库进行连接
		BOOL Connect(long lOptions = adConnectUnspecified, long lTime = 30);

		//与数据库断开连接
		BOOL Disconnect();

		//判断连接是否打开
		BOOL IsOpen();

		//取消与_ConnectionPtr正在执行的命令，如果该连接忙
		BOOL Cancel();

		//判断是否连接，没则进行连接
		BOOL	CheckDB();

		//执行SQL命令
		_RecordsetPtr ExecuteSql(const char* strSqlText, VARIANT* RecordsAffected, long Options );

		BOOL ExecuteSql(LPCTSTR strSqlText, VARIANT* RecordsAffected, long Options, _RecordsetPtr &pRecord);

		//直接将SQL语句写入数据库
		BOOL ExecuteSql(LPCSTR strSqlText);

		//执行存储过程
		BOOL ExecStoredProc(_CommandPtr& pCmd, const char* pStoredProcName);

		//执行存储过程,并返回记录集
		BOOL ExecStoredProc(_CommandPtr& pCmd, const char* pStoredProcName, _RecordsetPtr& rec);

		//获得记录集的数目
		LONG GetRecordCount(_RecordsetPtr &record);//会出错!!!

		//获得表的数目
		LONG GetRecordCount(const char* pszCountText);

		//处理COM错误
		void DealComError(_com_error &e, const char* pszCaller);

		//开始事务
		long BeginTrans();

		//回滚事务
		BOOL RollbackTrans();

		//执行事务
		BOOL CommitTrans();

		_ConnectionPtr GetConnection();

	protected:
		//释放所有资源
		BOOL Release();

	protected:
		char			m_szConnectStr[128];

		_ConnectionPtr	m_pConnection;
		_CommandPtr		m_pCommand;
	};
};

