
// SMART_RMDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Thesis.h"
#include "TransparentStatic.h"
#include "TransparentStaticWhite.h"


// CSMART_RMDlg dialog
class CSMART_RMDlg : public CDialogEx
{
// Construction
public:
	CSMART_RMDlg(CWnd* pParent = NULL);	// standard constructor

// Add a CBrush* to store the new background brush for edit controls.
          CBrush* m_pEditBkBrush;

// Dialog Data
	enum { IDD = IDD_SMART_RM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CTransparentStaticWhite static_pan_id;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedlogout();
	afx_msg void OnBnClickedsettings();
	afx_msg void OnBnClickedhelp();
	afx_msg void OnBnClickedhome();
	afx_msg void OnBnClickedview();
	afx_msg void OnBnClickedmanage();
//	CStatic m_home;

	afx_msg void OnStnClickedpanel();
	CEdit input_pass;
	afx_msg void OnBnClickedbutton();
	CString m_pass;
	afx_msg void OnEnChangepassword();
	afx_msg void logouthide();
	afx_msg void loginshow();
	afx_msg void ChangeDefaultButton();
	CTransparentStaticWhite m_auth_msg;
	CButton m_login;
	afx_msg void OnBnClickeddefault();
	afx_msg void OnBnClickedmanualsw();
	afx_msg void OnBnClickededitsched();
	afx_msg void OnBnClickedaddroom();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedconsumption();
	afx_msg void OnBnClickededitschedule();
	afx_msg void OnBnClickedthumbmanage();
};
