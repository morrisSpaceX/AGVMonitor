
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
public:
//	afx_msg void OnButtonOutput();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(IDC_BUTTON_OUTPUT, &CAboutDlg::OnButtonOutput)
END_MESSAGE_MAP()


// CtimerAppDlg dialog




CtimerAppDlg::CtimerAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtimerAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bMouseAppoint = false;
	m_bFirstInput = true;
	m_uCurNum = 0;
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
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, &CtimerAppDlg::OnClickedButtonOutput)
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
	pDC->StretchBlt(0, 0, rcClient.right - rcWatch.right - 15, rcClient.bottom, 
		&memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	// 弹出提示框;
	if (m_bFirstInput) {
		if (IDOK == AfxMessageBox(_T("第一次导入场地需要指定点号，左键单击确定，右键取消，点击ok键完成。")))
			m_bMouseAppoint = true; // 用户开始指定点号
		m_bFirstInput = false;
	}
		
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


void CtimerAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMouseAppoint)
	{
		++m_uCurNum;
		// 保存点的坐标
		m_mapPoint[m_uCurNum] = point;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CtimerAppDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_bMouseAppoint = false;

	OnPaint(); 
	
	// CDialogEx::OnOK();
}


void CtimerAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strMsg;
	CBitmap bitmap;
	if (m_bMouseAppoint)
	{
		CDC* pDC = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		
		// 获取区域大小
		RECT rc;
		GetClientRect(&rc);
		CStatic* pWatcher = (CStatic*)GetDlgItem(IDC_STATIC_WATCHER);
		RECT rcWatch;
		pWatcher->GetClientRect(&rcWatch);

		bitmap.LoadBitmapW(IDB_BITMAP_REPO3);
		memDC.SelectObject(&bitmap);

		// 获取位图信息
		BITMAP bm;
		bitmap.GetBitmap(&bm);

		strMsg.Format(_T("请设置点号%d"), m_uCurNum+1);
		float xRatio = bm.bmWidth * 1.0f / (rc.right - rcWatch.right);
		float yRatio = bm.bmHeight * 1.0f / rc.bottom;
		memDC.TextOutW(int(point.x * xRatio), int(point.y * yRatio), strMsg);

		// 显示数字
		POSITION pos = m_mapPoint.GetStartPosition();
		unsigned key;
		CPoint pt;
		while (pos)
		{
			m_mapPoint.GetNextAssoc(pos, key, pt);
			strMsg.Format(_T("%d"), key);
			memDC.TextOutW(int(pt.x * xRatio), int(pt.y * yRatio), strMsg);
		}

		pDC->StretchBlt(0, 0, rc.right - rcWatch.right - 15, rc.bottom,
			&memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CtimerAppDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMouseAppoint)
	{
		if (m_mapPoint.IsEmpty()){
			m_uCurNum = 0;
			return;
		}

		m_mapPoint.RemoveKey(m_mapPoint.GetCount());
		--m_uCurNum;
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}


//void CAboutDlg::OnButtonOutput()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CtimerAppDlg::OnClickedButtonOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szPath[MAX_PATH];
	SHGetFolderPath(nullptr, CSIDL_DESKTOP, nullptr, 0, szPath);

	PathAppend(szPath, _T("点号&坐标.txt"));

	CStdioFile file(szPath, 
		CFile::modeWrite | CFile::modeCreate | CFile::typeText);

	POSITION pos = m_mapPoint.GetStartPosition();
	unsigned key;
	CPoint pt;
	CString str;
	file.WriteString(_T("点号\t坐标\n"));
	while (pos)
	{
		m_mapPoint.GetNextAssoc(pos, key, pt);
		str.Format(_T("%d\t(%d,%d)\n"), key, pt.x, pt.y);
		file.WriteString(str);
	}

}
