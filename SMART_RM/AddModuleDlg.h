#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Thesis.h"
#include "TransparentStatic.h"
#include "afxdtctl.h"

// AddModuleDlg dialog

class AddModuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddModuleDlg)

public:
	AddModuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddModuleDlg();

// Dialog Data
	enum { IDD = IDD_ADD_MODULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTransparentStatic static_room_mac_address;
	CTransparentStatic static_room_name;
	virtual BOOL OnInitDialog();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit edit_roomName;
	CEdit edit_mac_one;
	CEdit edit_mac_two;
	CEdit edit_mac_three;
	CEdit edit_mac_four;
	CEdit edit_mac_five;
	CEdit edit_mac_six;
	CEdit edit_mac_seven;
	CEdit edit_mac_eight;
	afx_msg void OnEnMaxtextMacOne();
	afx_msg void OnEnMaxtextMacTwo();
	afx_msg void OnEnMaxtextMacThree();
	afx_msg void OnEnMaxtextMacFour();
	afx_msg void OnEnMaxtextMacFive();
	afx_msg void OnEnMaxtextMacSix();
	afx_msg void OnEnMaxtextMacSeven();
	CTransparentStatic static_floor;
	CComboBox combo_floor;
	CCheckListBox list_ports;
	CTransparentStatic static_rmports;
	afx_msg void OnLbnSelchangeListPorts();
	CEdit edit_device_name;
	CTransparentStatic static_device_name;
	afx_msg void OnEnKillfocusEditDevicenme();
	int port_index;
	CString devicesNames[100];
	afx_msg void OnBnClickedButtonAddroom();
//	CTransparentStatic static_days;
//	CCheckListBox list_days;
//	CTransparentStatic static_end_time;
//	CTransparentStatic static_starttime;
//	CComboBox combo_start_hr;
//	CComboBox combo_start_min;
//	CComboBox combo_start_ampm;
//	CComboBox combo_end_hr;
//	CComboBox combo_end_min;
//	CComboBox combo_end_ampm;
//	CTransparentStatic static_grp_schedule;
	CTransparentStatic static_room_ports_grp;
	CTransparentStatic static_rmdet_grp;
//	CTransparentStatic static_schedName;
//	CEdit edit_sched_name;
//	CButton check_add_schedule;
//	afx_msg void OnBnHotItemChangeCheckAddSchedule(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnBnClickedCheckAddSchedule();
//	CButton btn_addroomwsched;
	CButton btn_addroomwosched;
//	afx_msg void OnBnClickedButtonAddrmsched();
//	CCheckListBox list_devices;
	CTransparentStatic static_devices;
	void clearControls();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
//	afx_msg void OnLbnSelchangeListDays();

	int schedStartTimeHr[100];
	int schedStartTimeMin[100];
	int schedStartTimeAmPm[100];
	int schedEndTimeHr[100];
	int schedEndTimeMin[100];
	int schedEndTimeAmPm[100];
	CString schedNameMe[100];
	int indexDay;
//	afx_msg void OnCbnKillfocusComboStartHr();
//	afx_msg void OnCbnKillfocusComboStartMin();
//	afx_msg void OnCbnKillfocusComboStartAmpm();
//	afx_msg void OnCbnKillfocusComboEndHr();
//	afx_msg void OnCbnKillfocusComboEndMin();
//	afx_msg void OnCbnKillfocusComboEndAmpm();
//	afx_msg void OnEnKillfocusEditSchedName();
};
