// ConsumptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "ConsumptionDlg.h"
#include "afxdialogex.h"


// ConsumptionDlg dialog

IMPLEMENT_DYNAMIC(ConsumptionDlg, CDialogEx)

ConsumptionDlg::ConsumptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ConsumptionDlg::IDD, pParent)
{

}

ConsumptionDlg::~ConsumptionDlg()
{
}

void ConsumptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, consumption_web);
}


BEGIN_MESSAGE_MAP(ConsumptionDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
//	ON_BN_CLICKED(IDC_BUTTON1, &ConsumptionDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ConsumptionDlg message handlers


BOOL ConsumptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void ConsumptionDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	/*
		CString harris("https://msdn.microsoft.com/en-us/library/aa752046%28v=vs.85%29.aspx");
	*/

	consumption_web.Navigate(urlCons, NULL, NULL, NULL, NULL);

	// TODO: Add your message handler code here
}