
// timerAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "timerApp.h"
#include "timerAppDlg.h"
#include "afxdialogex.h"
#include "MySocket.h"
#include "NetServer.h"
#include "NetMsgASync.h"


#pragma   comment(lib, "ws2_32.lib ") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMutex g_mux;
CMutex g_muxsvr;
extern int g_flag;

UINT WorkForce2(LPVOID lpParam)
{
    g_mux.Lock();
    AfxSocketInit();

    BOOL bOptVal = TRUE;
    int bOptLen = sizeof(BOOL);
    // int nPort = *((int*)lpParam);
    NetMsgASync * pServerSocket = new NetMsgASync();
    NetMsgASync * pReceiveSocket = new NetMsgASync();

    {
        // pServerSocket->Create(SVR_PORT);
#if 0
        TRACE("workforce:socket()\n");
        pServerSocket->Socket();
        //fix 10048 error
        pServerSocket->SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);
        TRACE("workforce:bind()\n");
        pServerSocket->Bind(SVR_PORT);
#endif
        TRACE("main:create(%d)\n", SVR_PORT);
#if 0
        pServerSocket->Create(SVR_PORT, SOCK_STREAM,
            FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT,
#endif
        pServerSocket->Create(SVR_PORT);
//            /*L"10.166.206.59"*/L"127.0.0.1");
        TRACE("main:listen()\n");
        pServerSocket->Listen(10);
        TRACE("main:delete(%d)\n");
        delete pReceiveSocket;
        // delete pServerSocket;
    }
    g_mux.Unlock();
    // g_flag = 1;
    TRACE("main:server ready\n");
    return 0;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtimerAppDlg dialog




CtimerAppDlg::CtimerAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtimerAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtimerAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtimerAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_START_TIMER, &CtimerAppDlg::OnBnClickedButtonStartTimer)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_SHOWMAP, &CtimerAppDlg::OnBnClickedButtonShowmap)
    ON_BN_CLICKED(IDC_BUTTON_DIJKSTRA, &CtimerAppDlg::OnBnClickedButtonDijkstra)
    ON_BN_CLICKED(IDC_BUTTON_NET, &CtimerAppDlg::OnBnClickedButtonNet)
END_MESSAGE_MAP()


// CtimerAppDlg message handlers

BOOL CtimerAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtimerAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtimerAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	CDC* pDC = GetDC();
	CStatic* pWatcher = (CStatic*)GetDlgItem(IDC_STATIC_WATCHER);
	RECT rcWatch;
	pWatcher->GetClientRect(&rcWatch);

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP_REPO3);
	
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&bitmap);
	
	RECT rcClient;
	GetClientRect(&rcClient);
	
	BITMAP bm;
	bitmap.GetBitmap(&bm);
	pDC->StretchBlt(0, 0, rcClient.right - rcWatch.right - 15, rcClient.bottom, &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtimerAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtimerAppDlg::OnBnClickedButtonStartTimer()
{
    // TODO: Add your control notification handler code here
    SetTimer(1, 100, NULL);
}


void CtimerAppDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    wchar_t buffer[2256];
    if (0) {
        m_curveEx.updateTrace();
    } else {
        m_curveEx.buildTrace();
    }
    wsprintf(buffer, L"X=%d", m_curveEx.m_point.x);
    GetDlgItem(IDC_STATIC_X)->SetWindowText(buffer);
    wsprintf(buffer, L"y=%d", m_curveEx.m_point.y);
    GetDlgItem(IDC_STATIC_Y)->SetWindowText(buffer);
    CDialogEx::OnTimer(nIDEvent);
}


void CtimerAppDlg::OnBnClickedButtonShowmap()
{
    // TODO: Add your control notification handler code here
    RECT rect;
    // MessageBox(L"Hi", L"World", MB_OK);
    rect.left = 0;
    rect.top = 0;
    rect.right = 1024;
    rect.bottom = 668;

    m_curveEx.createCavas(GetDC(), IDB_BITMAP_LIVE, rect);
    // m_curveEx.createCavas(GetDC(), IDB_BITMAP_REPO2, rect);
    m_curveEx.updateCavas(0);
}


void CtimerAppDlg::OnBnClickedButtonDijkstra()
{
    // TODO: Add your control notification handler code here
    m_curveEx.demoLinkTable(0);

}


void CtimerAppDlg::OnBnClickedButtonNet()
{
    //char MsgBuf[1024];
    // TODO: Add your control notification handler code here

    WorkForce2(0);



    NetServer * pNS = new NetServer();
    pNS->Run(0);

}
