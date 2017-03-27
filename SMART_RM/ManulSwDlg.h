#pragma once


// ManulSwDlg dialog
#include "afxwin.h"
#include "afxcmn.h"
#include "Thesis.h"
#include "ColorListCtrl.h"
#include "TransparentStatic.h"

class ManulSwDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ManulSwDlg)

public:
	ManulSwDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ManulSwDlg();

// Dialog Data
	enum { IDD = IDD_MANUAL_SW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CColorListCtrl list_manualSW;
	virtual BOOL OnInitDialog();
	CCheckListBox listbox_device;
	CTransparentStatic text_timeDuration;
	afx_msg void OnNMClickManualswList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CTransparentStatic text_roomName;
	afx_msg void OnBnClickedSavebtn();
	CEdit edit_inputDuration;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedCancelbtn();
	CString deviceDuration[100];
	afx_msg void OnLbnSelchangeListboxManualsw();
};
