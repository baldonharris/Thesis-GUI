#pragma once


// AboutDlg dialog

class AboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AboutDlg)

public:
	AboutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
