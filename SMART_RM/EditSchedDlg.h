#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Thesis.h"
#include "TransparentStatic.h"
#include "ColorListCtrl.h"

// EditSchedDlg dialog

class EditSchedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditSchedDlg)

public:
	EditSchedDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~EditSchedDlg();

// Dialog Data
	enum { IDD = IDD_EDIT_SCHED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboUpdDel();
	afx_msg void OnNMClickListRooms(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	CColorListCtrl list_rooms;
	CComboBox combo_upd_del;
	CButton btn_del;

	CTransparentStatic static_floor;
	CTransparentStatic static_rmname;
	CTransparentStatic static_rmmac;
	CComboBox combo_floor;
	CEdit edit_rmname;
	CEdit edit_mac_1;
	CEdit edit_mac_2;
	CEdit edit_mac_3;
	CEdit edit_mac_4;
	CEdit edit_mac_5;
	CEdit edit_mac_6;
	CEdit edit_mac_7;
	CEdit edit_mac_8;
	CString devices_name[100];

	CCheckListBox list_port;
	CEdit edit_device_name;
	CTransparentStatic static_rm_ports;
	int port_index;
	struct frg_ids idForEdit;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLbnSelchangeListEditPorts();
	afx_msg void OnBnClickedButtonRoomDetails();
	afx_msg void OnBnClickedButtonRoomDev();
	afx_msg void OnBnClickedButtonRoomSched();
	afx_msg void OnEnKillfocusEditDevicename();
	afx_msg void OnEnMaxtextEditMac1();
	afx_msg void OnEnMaxtextEditMac2();
	afx_msg void OnEnMaxtextEditMac3();
	afx_msg void OnEnMaxtextEditMac4();
	afx_msg void OnEnMaxtextEditMac5();
	afx_msg void OnEnMaxtextEditMac6();
	afx_msg void OnEnMaxtextEditMac7();
	CTransparentStatic static_function;
	CButton btn_save_rm_details;
	CButton btn_save_rm_dev;
	afx_msg void OnBnClickedButtonSync();

	int rooms_id;
};
