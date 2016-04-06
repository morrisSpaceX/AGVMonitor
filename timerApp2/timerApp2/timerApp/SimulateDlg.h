#pragma once

class CtimerAppDlg;
// CSimulateDlg 对话框

class CSimulateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimulateDlg)

public:
	CSimulateDlg(CWnd* pParent = NULL);   // 标准构造函数
	CSimulateDlg(CtimerAppDlg* appdlg, CWnd* pParent = NULL);
	virtual ~CSimulateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIMULATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	BYTE				m_btTag;		// 消息标签 1-255循环使用
	unsigned short		m_usTask;		// 任务标签

	CtimerAppDlg*		m_appdlg;

public:
	afx_msg void OnClickedButtonGenerate();
	afx_msg void OnClickedButtonGenerate2();
	afx_msg void OnClickedButtonSend();
	afx_msg void OnClickedButtonQuit();
};
