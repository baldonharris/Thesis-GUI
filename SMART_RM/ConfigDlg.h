#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Thesis.h"
#include "TransparentStatic.h"
#include "ColorListCtrl.h"


// ConfigDlg dialog

class ConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigDlg)

public:
	ConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ConfigDlg();

// Dialog Data
	enum { IDD = IDD_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();

	CEdit edit_floorname;
	CButton btn_add_floor;
	CComboBox combo_updel;
	CColorListCtrl list_floors;
	CTransparentStatic static_flrname;
	CEdit edit_newflrname;
	CButton btn_delflr;
	CButton btn_newflrnme;
	afx_msg void OnCbnSelchangeComboUpdDel();
	void populateFloors(int mode);
	afx_msg void OnBnClickedButtonAddflr();
	afx_msg void OnNMClickListFloors(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSavenewflrnme();
	int clickedRow;
	afx_msg void OnBnClickedButtonDelflr();

	CTransparentStatic static_cur_password;
	CTransparentStatic static_new_password;
	CTransparentStatic static_confnew_password;
	CEdit edit_cur_password;
	CEdit edit_new_password;
	CEdit edit_confnew_password;
	afx_msg void OnBnClickedButtonSavePass();

	CTransparentStatic static_new_panid;
	CTransparentStatic static_curpassword;
	CEdit edit_new_panid;
	CEdit edit_panid_password;
	afx_msg void OnBnClickedButtonChangepanid();
};
