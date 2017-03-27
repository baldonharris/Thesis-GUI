#pragma once


// CHomePage dialog

class CHomePage : public CDialogEx
{
	DECLARE_DYNAMIC(CHomePage)

public:
	CHomePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHomePage();

// Dialog Data
	enum { IDD = IDD_HOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedbgHome();
	afx_msg void OnBnClickedview();
};
