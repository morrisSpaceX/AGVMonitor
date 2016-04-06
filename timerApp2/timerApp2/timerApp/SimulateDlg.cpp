// SimulateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "timerApp.h"
#include "SimulateDlg.h"
#include "afxdialogex.h"

#include "MsgStruct.h"
#include "resource.h"
#include "timerAppDlg.h"

// CSimulateDlg 对话框

IMPLEMENT_DYNAMIC(CSimulateDlg, CDialogEx)

CSimulateDlg::CSimulateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SIMULATE, pParent)
{
	m_btTag = 0;
	m_usTask = 0;
}

CSimulateDlg::CSimulateDlg(CtimerAppDlg* appdlg, CWnd* pParent)
	: m_appdlg(appdlg), CDialogEx(IDD_DIALOG_SIMULATE, pParent)
{
	m_btTag = 0;
	m_usTask = 0;
}


CSimulateDlg::~CSimulateDlg()
{
}

void CSimulateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSimulateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CSimulateDlg::OnClickedButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE2, &CSimulateDlg::OnClickedButtonGenerate2)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSimulateDlg::OnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CSimulateDlg::OnClickedButtonQuit)
END_MESSAGE_MAP()


// CSimulateDlg 消息处理程序


void CSimulateDlg::OnClickedButtonGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* pWndTag = (CStatic*)GetDlgItem(IDC_STATIC_TAG);
	CString str;
	if (++m_btTag > 255)
		m_btTag = 1;
	str.Format(_T("消息标签：%d"), m_btTag);
	pWndTag->SetWindowTextW(str);
}


void CSimulateDlg::OnClickedButtonGenerate2()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* pWndTask = (CStatic*)GetDlgItem(IDC_STATIC_TASK);
	CString str;
	if (++m_usTask > 65535)
		m_usTask = 1;
	str.Format(_T("任务标签：%d"), m_usTask);
	pWndTask->SetWindowTextW(str);
}


void CSimulateDlg::OnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* pWndTarget = (CEdit*)GetDlgItem(IDC_EDIT_TARGET);
	CEdit* pWndSource = (CEdit*)GetDlgItem(IDC_EDIT_SOURCE);
	CString strS, strT;
	pWndTarget->GetWindowTextW(strT);
	pWndSource->GetWindowTextW(strS);
	if (strT.IsEmpty() || strS.IsEmpty()) {
		AfxMessageBox(_T("请输入源和目标点号！"));
		return;
	}
	//BYTE tag;						// 消息标签
	//BYTE agvno;					// AGV车号
	//BYTE taskno[2];				// 任务编号
	//BYTE target[2];				// 任务目标点

	Msg_M6 m6;
	m6.tag = m_btTag;
	m6.taskno = m_usTask;
	m6.agvno = _ttoi(strS);
	m6.target = _ttoi(strT);

	m_appdlg->m_msgM6 = new Msg_M6(m6);
	
	CDialogEx::OnOK();
}


void CSimulateDlg::OnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
