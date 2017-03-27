// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "AboutDlg.h"
#include "afxdialogex.h"


// AboutDlg dialog

IMPLEMENT_DYNAMIC(AboutDlg, CDialogEx)

AboutDlg::AboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AboutDlg::IDD, pParent)
{

}

AboutDlg::~AboutDlg()
{
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// AboutDlg message handlers


void AboutDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	TRACE("HOOLLAAA!!\n\n");
}
