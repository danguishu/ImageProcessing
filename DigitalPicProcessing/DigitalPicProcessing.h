
// DigitalPicProcessing.h : DigitalPicProcessing Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDigitalPicProcessingApp:
// �йش����ʵ�֣������ DigitalPicProcessing.cpp
//

class CDigitalPicProcessingApp : public CWinAppEx
{
public:
	CDigitalPicProcessingApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDigitalPicProcessingApp theApp;
