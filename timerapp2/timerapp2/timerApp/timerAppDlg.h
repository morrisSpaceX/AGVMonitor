
// timerAppDlg.h : header file
//

#pragma once
#include "CurveEx.h"
#include "ListCollection.h"
#include "MySocket.h"

// CtimerAppDlg dialog
class CtimerAppDlg : public CDialogEx
{
// Construction
public:
	CtimerAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TIMERAPP_DIALOG };

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
    afx_msg void OnBnClickedButtonStartTimer();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CurveEx m_curveEx;
    ListCollection* m_pLC;

    afx_msg void OnBnClickedButtonShowmap();
    afx_msg void OnBnClickedButtonDijkstra();
    afx_msg void OnBnClickedButtonNet();

private:
	// ������Ӧ�����Ϣ�ı�־λ
	bool			m_bMouseAppoint;	// �Ƿ���ָ�����
	bool			m_bFirstInput;		// �Ƿ��һ�ε��볡��
	unsigned		m_uCurNum;			// ��ǰ���

	CMap<unsigned, unsigned, CPoint, CPoint> m_mapPoint; // ��ţ����� ӳ��

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnOK();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonOutput();
};
