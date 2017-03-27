#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TransparentStatic.h"
#include "ColorListCtrl.h"
#include "Thesis.h"


// CViewPageDlg dialog

class CViewPageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewPageDlg)

public:
	CViewPageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CViewPageDlg();

// Dialog Data
	enum { IDD = IDD_VIEW_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:


	CEdit m_count;
	afx_msg void OnBnClickedstart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CColorListCtrl schedList;
	int totalRow;
	CColorListCtrl subSchedList;
	CString roomNameHolder;
	afx_msg void OnNMClickSchedlist(NMHDR *pNMHDR, LRESULT *pResult);
	int currentRoomID;
	struct frg_ids ids;
	//afx_msg void OnStnClickedbgView();
	afx_msg void OnNMKillfocusSchedlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	int showCounter;
	afx_msg void OnBnClickedButtonSyncdata();
	CButton sync_data;
};
