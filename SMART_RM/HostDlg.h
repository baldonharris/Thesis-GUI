#include "Thesis.h"
#include "TransparentStatic.h"

#pragma once


// HostDlg dialog

class HostDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HostDlg)

public:
	HostDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~HostDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_HOST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_host;
	CTransparentStatic static_welcome;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
