// PPT2012.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPPT2012App:
// �йش����ʵ�֣������ PPT2012.cpp
//

class CPPT2012App : public CWinApp
{
public:
	CPPT2012App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPPT2012App theApp;