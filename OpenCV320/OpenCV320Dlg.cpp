
// OpenCV320Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "OpenCV320.h"
#include "OpenCV320Dlg.h"
#include "afxdialogex.h"

//#include "Common/streamingsender.h"
#include "Common/streamingreceiver.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenCV320Dlg 대화 상자



COpenCV320Dlg::COpenCV320Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENCV320_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCV320Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditPort);
	DDX_Control(pDX, IDC_EDIT2, m_EditFrame);
}

BEGIN_MESSAGE_MAP(COpenCV320Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &COpenCV320Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COpenCV320Dlg 메시지 처리기

BOOL COpenCV320Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_EditPort.SetWindowTextW(L"13001");
	m_EditFrame.SetWindowTextW(L"5");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COpenCV320Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COpenCV320Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR COpenCV320Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpenCV320Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//VideoCapture capture;
	/*if (!capture.isOpened())
	{
		cout << "웹캠을 열수 없습니다." << endl;
	}*/

	/*if (!capture.open("rtsp://admin:12345@192.168.1.80/1")) {
		AfxMessageBox(L"웹캠을 열수 없습니다.");
		return;
	}*/

	//캡처 영상을 320x240으로 지정  
	/*capture.set(CAP_PROP_FRAME_WIDTH, 320);
	capture.set(CAP_PROP_FRAME_HEIGHT, 240);*/

	//CvCapture *capture = cvCreateFileCapture("D:\\work3\\개발_04\\프로젝트\\광주과기원과제\\OpenCV320\\x64\\Debug\\1.avi");
	//CvCapture *capture = cvCreateFileCapture("rtsp://admin:admin@qa.nexpa.co.kr:40025/stream2");
	CvCapture *capture = cvCreateFileCapture("rtsp://192.168.1.80/1");
	//CvCapture *capture = cvCreateFileCapture("rtsp://admin:12345@172.16.53.150/trackID=1&streamID=1");
	//CvCapture *capture2 = cvCreateFileCapture("rtsp://admin:12345@qa.nexpa.co.kr:50003/2");
	//CvCapture *capture = cvCreateFileCapture("rtsp://admin:admin123-@qa.nexpa.co.kr:50017/stream2");

	// Streaming  Client
	//cvproc::cStreamingSender streamSender;
	//if (!streamSender.Init(false, "127.0.0.1", 12001, false, true))
	//{
	//	//cout << "Camera Streaming Init Error!!!" << endl;
	//}
	//else
	//{
	//	//cout << "Camera Streaming Init Success" << endl;
	//}
	CString sPort;
	int iPort;
	m_EditPort.GetWindowTextW(sPort);
	iPort = _ttoi(sPort);

	cvproc::cStreamingReceiver streamRcv;
	if (!streamRcv.Init(false, iPort, false, true))
	{
		//cout << "Camera Streaming Error!!!" << endl;
	}
	else
	{
		//cout << "Camera Streaming Success" << endl;
	}

	//Mat frame;
	IplImage *frame;
	//IplImage *frame2;
	//IplImage *frame3;
	Mat SendImage;
	namedWindow("Server", 1);
	//namedWindow("StreamingSender2", 1);
	//namedWindow("StreamingSender3", 1);

	while (1)
	{
		//웹캡으로부터 한 프레임을 읽어옴  
		//capture >> frame;
		/*if (!capture.read(frame)) {
			waitKey();
		}*/
		/*cvGrabFrame(capture);
		frame = cvRetrieveFrame(capture);*/
		frame = cvQueryFrame(capture);
		//frame2 = cvQueryFrame(capture2);
		//frame3 = cvQueryFrame(capture3);
		if (!frame) break;

		//화면에 영상을 보여줌
		//imshow("input", frame);
		SendImage = cvarrToMat(frame);
		//streamSender.Send(SendImage);
		streamRcv.Send(SendImage);

		cvShowImage("Server", frame);
		//cvShowImage("StreamingSender2", frame2);
		//cvShowImage("StreamingSender3", frame3);

		//ESC키 누르면 종료
		if (waitKey(1) == 27) break;
	}

	CDialogEx::OnOK();
}
