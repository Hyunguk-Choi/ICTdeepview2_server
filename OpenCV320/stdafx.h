
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����



// ��ũ�� ����
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if (p) { delete p; p=NULL;} }
#endif
#ifndef SAFE_DELETEA
#define SAFE_DELETEA(p) {if (p) { delete[] p; p=NULL;} }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) {if (p) { p->Release(); p=NULL;} }
#endif
#ifndef SAFE_RELEASE2
#define SAFE_RELEASE2(p) {if (p) { p->release(); p=NULL;} }
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#define RET(exp)		{if((exp)) return; }			// exp�� true�̸� ����
#define RETV(exp,val)	{if((exp)) return val; }
#define ASSERT_RET(exp)		{assert(exp); RET(!(exp) ); }
#define ASSERT_RETV(exp,val)		{assert(exp); RETV(!(exp),val ); }
#define BRK(exp)		{if((exp)) break; }			// exp�� break

typedef unsigned int    u_int;

#include <string>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>

using std::string;
using std::wstring;
using std::vector;
using std::map;
using std::list;
using std::set;
using std::stringstream;
using std::wstringstream;

#include <windows.h>
#include <winsock.h>

#pragma comment( lib, "wsock32.lib" )

namespace network {
	enum {
		BUFFER_LENGTH = 512,
	};
}

namespace common
{
	/**
	@brief this function only avaible to unique ty value
	remove ty and then rotate vector to sequence elements
	*/
	template <class Seq>
	bool removevector(Seq &seq, const typename Seq::value_type &ty)
	{
		for (size_t i = 0; i < seq.size(); ++i)
		{
			if (seq[i] == ty)
			{
				if ((seq.size() - 1) > i) // elements�� ȸ���ؼ� �����Ѵ�.
					std::rotate(seq.begin() + i, seq.begin() + i + 1, seq.end());
				seq.pop_back();
				return true;
			}
		}
		return false;
	}

	template <class Seq>
	void rotatepopvector(Seq &seq, const unsigned int idx)
	{
		if ((seq.size() - 1) > idx) // elements�� ȸ���ؼ� �����Ѵ�.
			std::rotate(seq.begin() + idx, seq.begin() + idx + 1, seq.end());
		seq.pop_back();
	}
}


class cAutoCS
{
public:
	cAutoCS(CRITICAL_SECTION &cs) :
		m_cs(cs)
		, m_isLeave(false) {
		EnterCriticalSection(&cs);
	}
	virtual ~cAutoCS() {
		if (!m_isLeave)
			LeaveCriticalSection(&m_cs);
		m_isLeave = true;
	}
	void Enter() {
		if (m_isLeave)
			EnterCriticalSection(&m_cs);
		m_isLeave = false;
	}
	void Leave() {
		LeaveCriticalSection(&m_cs);
		m_isLeave = true;
	}
	CRITICAL_SECTION &m_cs;
	bool m_isLeave;
};

#include "opencv2/opencv.hpp"
using namespace cv;

#include "Common/launcher.h"
#include "Common/protocol.h"
#include "Common/udpclient.h"
#include "Common/udpserver.h"
#include "Common/tcpserver.h"
#include "Common/tcpclient.h"

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


