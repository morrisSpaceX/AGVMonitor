
// bitblt_dlgDlg.h : header file
//

#pragma once
#define EN_SSPEED (0)

// Cbitblt_dlgDlg dialog
class Cbitblt_dlgDlg : public CDialogEx
{
// Construction
public:
	Cbitblt_dlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BITBLT_DLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClickedButtonStart();
    afx_msg void OnClickedButtonStop();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    int drawEclipseOldWay();
    int replaySimpleCurve();
    int pp;
};
