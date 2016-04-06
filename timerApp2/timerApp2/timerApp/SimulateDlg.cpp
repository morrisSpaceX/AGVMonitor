// SimulateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "timerApp.h"
#include "SimulateDlg.h"
#include "afxdialogex.h"

#include "MsgStruct.h"
#include "resource.h"
#include "timerAppDlg.h"

// CSimulateDlg �Ի���

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


// CSimulateDlg ��Ϣ�������


void CSimulateDlg::OnClickedButtonGenerate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStatic* pWndTag = (CStatic*)GetDlgItem(IDC_STATIC_TAG);
	CString str;
	if (++m_btTag > 255)
		m_btTag = 1;
	str.Format(_T("��Ϣ��ǩ��%d"), m_btTag);
	pWndTag->SetWindowTextW(str);
}


void CSimulateDlg::OnClickedButtonGenerate2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStatic* pWndTask = (CStatic*)GetDlgItem(IDC_STATIC_TASK);
	CString str;
	if (++m_usTask > 65535)
		m_usTask = 1;
	str.Format(_T("�����ǩ��%d"), m_usTask);
	pWndTask->SetWindowTextW(str);
}


void CSimulateDlg::OnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit* pWndTarget = (CEdit*)GetDlgItem(IDC_EDIT_TARGET);
	CEdit* pWndSource = (CEdit*)GetDlgItem(IDC_EDIT_SOURCE);
	CString strS, strT;
	pWndTarget->GetWindowTextW(strT);
	pWndSource->GetWindowTextW(strS);
	if (strT.IsEmpty() || strS.IsEmpty()) {
		AfxMessageBox(_T("������Դ��Ŀ���ţ�"));
		return;
	}
	//BYTE tag;						// ��Ϣ��ǩ
	//BYTE agvno;					// AGV����
	//BYTE taskno[2];				// ������
	//BYTE target[2];				// ����Ŀ���

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
