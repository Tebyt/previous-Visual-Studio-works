#ifndef __ZEPHYR_DATABASE_ADO_H
#define __ZEPHYR_DATABASE_ADO_H

const int	DB_USER_ID_LEN			=	64;
const int	DB_USER_PSW_LEN			=	128;

const int	DB_TABLENAME_LEN		=	32;

//#ifdef __ZEPHYR_DATABASE_USE_ADO_H
#include <icrsint.h>
#import <DataBase\msado15.dll> no_namespace rename("EOF", "adoEOF")

//////////////////////////////////////////////////////////////////////////////////
//	Func

int Var2Str(char *str,int len,_variant_t &var);

int GetStrLen(_variant_t &var,int len);

//////////////////////////////////////////////////////////////////////////////////
//	Class

class ZDatabase;

class ZRecordSet{
	friend class ZDatabase;
protected:
	_RecordsetPtr	m_pRecordset;
public:
	inline ZRecordSet() { m_pRecordset = NULL; }
	inline ~ZRecordSet() { Release(); }

	//Release
	void Release();
	//GetCollect
	inline _variant_t GetCollect(const _variant_t &Index);
	//PutCollect
	inline void PutCollect(const _variant_t &Index,const _variant_t &pVar);
	//Is BOF
	inline bool IsBOF();
	//Is EOF
	inline bool IsEOF();
	//Move to Begin
	inline void MoveFirst();
	//Move Next
	inline void MoveNext();
	//Move
	inline void Move(long sel);
	//Move to End
	inline void MoveLast();
	//Add New
	inline void AddNew();
	//Update
	inline void Update();
	//Del Cur
	inline void DelCur();
};

//GetCollect
inline _variant_t ZRecordSet::GetCollect(const _variant_t &Index)
{ 
	return m_pRecordset->GetCollect(Index); 
}

//PutCollect
inline void ZRecordSet::PutCollect(const _variant_t &Index,const _variant_t &pVar)
{
	m_pRecordset->PutCollect(Index,pVar);
}

//Move to Begin
inline void ZRecordSet::MoveFirst()
{
	m_pRecordset->MoveFirst();
}

//Is EOF
inline bool ZRecordSet::IsEOF()
{
	return m_pRecordset->adoEOF;
}

//Is BOF
inline bool ZRecordSet::IsBOF()
{
	return m_pRecordset->BOF;
}

//Move Next
inline void ZRecordSet::MoveNext()
{
	m_pRecordset->MoveNext();
}

//Move
inline void ZRecordSet::Move(long sel)
{
	m_pRecordset->Move(sel);
}

//Move to End
inline void ZRecordSet::MoveLast()
{
	m_pRecordset->MoveLast();
}

//Add New
inline void ZRecordSet::AddNew()
{
	m_pRecordset->AddNew();
}

//Update
inline void ZRecordSet::Update()
{
	m_pRecordset->Update();
}

//Del Cur
inline void ZRecordSet::DelCur()
{
	m_pRecordset->Delete(adAffectCurrent);
}

class ZDatabase{
private:
	char	m_strUserName[64];
	char	m_strPassword[64];
	char	m_strDatabase[64];
	char	m_strServer[64];

	_ConnectionPtr	m_pConnection;
public:
	inline ZDatabase();
	inline ~ZDatabase() { Release(); }

	//Open
	HRESULT Open(const char *strServer,const char *strDatabase,const char *strUser,const char *strPsw);
	//Close
	void Close();
	//Open Table
	ZRecordSet *OpenTable(const char *strTable);
	//Open Table
	ZRecordSet *SQL_OpenTable(const char *strSQL);
	//Release
	void Release();
};

inline ZDatabase::ZDatabase()
{
	m_pConnection = NULL;
}

//#endif

#endif//__ZEPHYR_DATABASE_ADO_H
