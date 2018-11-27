
// OpenCV320Dlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// COpenCV320Dlg ��ȭ ����



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


// COpenCV320Dlg �޽��� ó����

BOOL COpenCV320Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_EditPort.SetWindowTextW(L"13001");
	m_EditFrame.SetWindowTextW(L"5");

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void COpenCV320Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR COpenCV320Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpenCV320Dlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//VideoCapture capture;
	/*if (!capture.isOpened())
	{
		cout << "��ķ�� ���� �����ϴ�." << endl;
	}*/

	/*if (!capture.open("rtsp://admin:12345@192.168.1.80/1")) {
		AfxMessageBox(L"��ķ�� ���� �����ϴ�.");
		return;
	}*/

	//ĸó ������ 320x240���� ����  
	/*capture.set(CAP_PROP_FRAME_WIDTH, 320);
	capture.set(CAP_PROP_FRAME_HEIGHT, 240);*/

	//CvCapture *capture = cvCreateFileCapture("D:\\work3\\����_04\\������Ʈ\\���ְ��������\\OpenCV320\\x64\\Debug\\1.avi");
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
		//��ĸ���κ��� �� �������� �о��  
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

		//ȭ�鿡 ������ ������
		//imshow("input", frame);
		SendImage = cvarrToMat(frame);
		//streamSender.Send(SendImage);
		streamRcv.Send(SendImage);

		cvShowImage("Server", frame);
		//cvShowImage("StreamingSender2", frame2);
		//cvShowImage("StreamingSender3", frame3);

		//ESCŰ ������ ����
		if (waitKey(1) == 27) break;
	}

	CDialogEx::OnOK();
}
