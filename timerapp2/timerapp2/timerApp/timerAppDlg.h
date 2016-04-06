
// timerAppDlg.h : header file
//

#pragma once
#include "CurveEx.h"
#include "ListCollection.h"
#include "MySocket.h"

struct Msg_M6;
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
	bool			m_bMouseAppoint;	// 是否在指定点号
	bool			m_bFirstInput;		// 是否第一次导入场地
	unsigned		m_uCurNum;			// 当前点号

	CMap<unsigned, unsigned, CPoint, CPoint> m_mapPoint; // 点号，坐标 映射
	vector<CPoint>	m_vecPoint;			// 经过的点
	vector<CPoint>::iterator			m_curPointIt;			// 当前点迭代器
	vector<CPoint>::iterator			m_nextPointIt;			// 下一个点迭代器

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnOK();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonOutput();
	afx_msg void OnBnClickedButtonAgvmsg();

public:
	Msg_M6*			m_msgM6;			// M6消息
};
