
// bitblt_dlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bitblt_dlg.h"
#include "bitblt_dlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// Cbitblt_dlgDlg dialog



Cbitblt_dlgDlg::Cbitblt_dlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BITBLT_DLG_DIALOG, pParent)
    , pp(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbitblt_dlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cbitblt_dlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_START, &Cbitblt_dlgDlg::OnClickedButtonStart)
    ON_BN_CLICKED(IDC_BUTTON_STOP, &Cbitblt_dlgDlg::OnClickedButtonStop)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// Cbitblt_dlgDlg message handlers

BOOL Cbitblt_dlgDlg::OnInitDialog()
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

void Cbitblt_dlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cbitblt_dlgDlg::OnPaint()
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
        // drawEclipseOldWay();
        CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cbitblt_dlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cbitblt_dlgDlg::OnClickedButtonStart()
{
    // TODO: Add your control notification handler code here
    pp = 0;
    SetTimer(1, 10, NULL);
}


void Cbitblt_dlgDlg::OnClickedButtonStop()
{
    // TODO: Add your control notification handler code here
    KillTimer(1);
}


void Cbitblt_dlgDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    CWnd * pWnd = NULL;
    CString strTmp = L"";
    static int nTimer = 0;

    switch (nIDEvent)
    {
    case 1:
        if (1)
        {
            drawEclipseOldWay();
            strTmp.Format(L"Timer: %d", nTimer++);
        } else {
            replaySimpleCurve();
            strTmp.Format(L"Timer: %d", pp);
        }

        pWnd = GetDlgItem(IDC_STATIC_TIMER);
        pWnd->SetWindowText(strTmp);  
        break;
    default:
        pWnd = NULL;
        break;
    }

    CDialogEx::OnTimer(nIDEvent);
}

#define CLT_WIDTH   (1133)
#define CLT_HEIGHT  (804)
#define RADIUS  (30)

// y=ax?+bx+c£¨a¡Ù0£©
// y=n*x
#define moveXY2 { \
    static int arrow = 0;   \
    srand(GetTickCount());  \
    int n = rand() % 10;    \
    if (y < (CLT_HEIGHT - RADIUS) && x < (CLT_WIDTH - RADIUS) && 0 == arrow)  \
    {   \
        x ++; y +=(0 == x % n) ? 1:0;    \
        if (x == (CLT_HEIGHT - RADIUS)) arrow = 1;  \
    } if (y < (CLT_HEIGHT - RADIUS) && x < (CLT_WIDTH - RADIUS) && 0 == arrow)  \
    { } \
}

#define moveXY { \
    if (0 == y && x < (CLT_WIDTH - RADIUS))  \
    {   \
        x++;    \
    }   \
    else if (x == (CLT_WIDTH - RADIUS) && y < (CLT_HEIGHT - RADIUS))   \
    {   \
        y++;    \
    }   \
    else if (y == (CLT_HEIGHT - RADIUS) && x > 0) \
    {   \
        x--;    \
    }   \
    else if (x == 0 && y > 0)   \
    {   \
        y--;    \
    }   \
}

int Cbitblt_dlgDlg::drawEclipseOldWay()
{
    CDC *ClientDC = GetDC();
    static int flag = true, x = 0, y = 0;
    CRect rect, clientRect;
    CBrush * brush = NULL;

    CBitmap * newBitmap = new CBitmap();
    newBitmap->LoadBitmapW(IDB_BITMAP1);

    GetClientRect(&clientRect);
    CDC memDC;
    memDC.CreateCompatibleDC(ClientDC);

    // CBitmap *pOldBitmap = memDC.SelectObject(&memBitmap);
    CBitmap *pOldBitmap = memDC.SelectObject(newBitmap);

    // memDC.FillSolidRect(0, 0, clientRect.Width(), clientRect.Height(), ClientDC->GetBkColor());
    memDC.SelectStockObject(BLACK_BRUSH);

    CBrush bbrush;
    bbrush.CreateSolidBrush(RGB(255, 0, 0));
    memDC.SelectObject(bbrush);

    POINT topleft;
    topleft.x = x;
    topleft.y = y;
    POINT bottomright;
    bottomright.x = topleft.x + RADIUS;
    bottomright.y = topleft.y + RADIUS;
    rect.SetRect(topleft, bottomright);
    memDC.Ellipse(rect);    // we draw the circle right here

    moveXY;

    ClientDC->BitBlt(0, 0, CLT_WIDTH, CLT_HEIGHT, &memDC, 0, 0, SRCCOPY);
    memDC.SelectObject(pOldBitmap);
    // memDC.SelectObject(oldBrush);

    memDC.DeleteDC();
    ReleaseDC(ClientDC);
    delete newBitmap;

    return 0;
}


int Cbitblt_dlgDlg::replaySimpleCurve()
{
    static int flag = 1;
    static CDC *ClientDC;
    static CDC memDC;
    static int x = 0, y = 0;
    static CRect rect, clientRect;
    static CBitmap * newBitmap;
    static CDC bitmapDC;
    static BITMAP bitmap;
    int curve_width;
    int curve_heigth;
    int xx = 0, yy = 0;
    static int p = 1;
    POINT curvepoint = { 0,0 };
    CBrush bbrush;

    ClientDC = GetDC();

    if (flag)
    {
        memDC.CreateCompatibleDC(ClientDC);

        GetClientRect(&clientRect);

        newBitmap = new CBitmap();

        // newBitmap->LoadBitmapW(IDB_BITMAP_SC2);
        newBitmap->LoadBitmapW(IDB_BITMAP_ROUTE_1);
        
        bitmapDC.CreateCompatibleDC(ClientDC);

        newBitmap->GetBitmap(&bitmap);

        bitmapDC.SelectObject(newBitmap);

#if 0
        CBitmap *pOldBitmap = memDC.SelectObject(newBitmap);
#else
        CBitmap * compatibleBitmap = new CBitmap();
        compatibleBitmap->CreateCompatibleBitmap(ClientDC, 1024, 768);
        CBitmap *pOldBitmap = memDC.SelectObject(compatibleBitmap);
#endif
        memDC.SelectStockObject(BLACK_BRUSH);
        bbrush.CreateSolidBrush(RGB(255, 0, 0));
        HGDIOBJ pOldBrush = memDC.SelectObject(bbrush);
        flag = 0;
    }
    curve_width = bitmap.bmWidth;
    curve_heigth = bitmap.bmHeight;

    // memDC.FillSolidRect(0, 0, clientRect.Width(), clientRect.Height(), ClientDC->GetBkColor());

#if 1
    // for (xx = 0; xx < (pp); xx++)
    {
        for (yy = 0; yy < curve_heigth; yy ++)
        {
            curvepoint.x = pp;
            curvepoint.y = yy;
            COLORREF colorref = bitmapDC.GetPixel(curvepoint);
            if (colorref != RGB(255, 255, 255))
            {
                memDC.SetPixel(pp, yy, RGB(255,0,0));
            }
        }
    }
#else


    POINT topleft;
    topleft.x = 0;
    topleft.y = 0;    
    POINT bottomright;
    bottomright.x = topleft.x + RADIUS;
    bottomright.y = topleft.y + RADIUS;
    rect.SetRect(topleft, bottomright);
    memDC.Ellipse(rect);    // we draw the circle right here

#endif

    ClientDC->BitBlt(0, 0, curve_width, curve_heigth, &memDC, 0, 0, SRCCOPY);

    pp++;
    if (pp == curve_width)
    {
        KillTimer(1);
    }

#if 0
    // bitmapDC.SelectObject(pOldBitmap);
    memDC.SelectObject(pOldBitmap);


    bitmapDC.DeleteDC();
    memDC.DeleteDC();
    ReleaseDC(ClientDC);
    delete newBitmap;
    delete compatibleBitmap;
#endif
    return 0;
}
