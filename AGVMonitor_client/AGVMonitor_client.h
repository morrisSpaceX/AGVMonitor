
// AGVMonitor_client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAGVMonitor_clientApp: 
// �йش����ʵ�֣������ AGVMonitor_client.cpp
//

class CAGVMonitor_clientApp : public CWinApp
{
public:
	CAGVMonitor_clientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAGVMonitor_clientApp theApp;