#pragma once

class CtimerAppDlg;
// CSimulateDlg �Ի���

class CSimulateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimulateDlg)

public:
	CSimulateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CSimulateDlg(CtimerAppDlg* appdlg, CWnd* pParent = NULL);
	virtual ~CSimulateDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIMULATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	BYTE				m_btTag;		// ��Ϣ��ǩ 1-255ѭ��ʹ��
	unsigned short		m_usTask;		// �����ǩ

	CtimerAppDlg*		m_appdlg;

public:
	afx_msg void OnClickedButtonGenerate();
	afx_msg void OnClickedButtonGenerate2();
	afx_msg void OnClickedButtonSend();
	afx_msg void OnClickedButtonQuit();
};
