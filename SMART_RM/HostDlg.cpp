// HostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "HostDlg.h"
#include "afxdialogex.h"


// HostDlg dialog

IMPLEMENT_DYNAMIC(HostDlg, CDialogEx)

HostDlg::HostDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HostDlg::IDD, pParent)
{

}

HostDlg::~HostDlg()
{
}

void HostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HOST, edit_host);
	DDX_Control(pDX, IDC_STATIC_WELCOME, static_welcome);
}


BEGIN_MESSAGE_MAP(HostDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &HostDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &HostDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// HostDlg message handlers


BOOL HostDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CFont m_font;
	m_font.CreatePointFont(90, L"Courier New");
	static_welcome.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void HostDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString hostName;
	CString URL = urlMe;

	edit_host.GetWindowTextW(hostName);
	URL.Replace(_T("localhost"), hostName);

	CStringA finalURL(URL);

	int request = thesis_request((const char *)finalURL);
	if(!request){
		MessageBoxW(_T("Server not found!\nPlease try again"), _T("Error!"), MB_ICONERROR | MB_OK);
	}else{
		urlMe = URL;
		urlCons.Replace(_T("localhost"), hostName);
		CDialogEx::OnOK();
	}
}


void HostDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	ASSERT(AfxGetMainWnd() != NULL);
    AfxGetMainWnd()->SendMessage(WM_CLOSE);
	CDialogEx::OnCancel();
}


void HostDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	
	edit_host.SetFocus();

	// TODO: Add your message handler code here
}
