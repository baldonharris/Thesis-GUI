#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Thesis.h"
#include "TransparentStatic.h"
#include "ColorListCtrl.h"
#include "explorer1.h"


// ConsumptionDlg dialog

class ConsumptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConsumptionDlg)

public:
	ConsumptionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ConsumptionDlg();

// Dialog Data
	enum { IDD = IDD_CONSUMPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CExplorer1 consumption_web;
//	afx_msg void OnBnClickedButton1();
};
