
// OpenCV320.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// COpenCV320App:
// �� Ŭ������ ������ ���ؼ��� OpenCV320.cpp�� �����Ͻʽÿ�.
//

class COpenCV320App : public CWinApp
{
public:
	COpenCV320App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern COpenCV320App theApp;