#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Thesis.h"
#include "TransparentStatic.h"
#include "ColorListCtrl.h"
#include "afxdtctl.h"


// EditSchedule dialog

class EditSchedule : public CDialogEx
{
	DECLARE_DYNAMIC(EditSchedule)

public:
	EditSchedule(CWnd* pParent = NULL);   // standard constructor
	virtual ~EditSchedule();

// Dialog Data
	enum { IDD = IDD_EDIT_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();

	CComboBox combo_upd_del;
	CColorListCtrl list_rooms;
	CTransparentStatic static_function;

	CColorListCtrl list_schedule;
	CButton btn_delete;

	CCheckListBox list_days;
	CTransparentStatic static_start_time;
	CTransparentStatic static_end_time;
	CTransparentStatic static_sched_name;
	CComboBox combo_start_hr;
	CComboBox combo_start_min;
	CComboBox combo_start_ampm;
	CComboBox combo_end_hr;
	CComboBox combo_end_min;
	CComboBox combo_end_ampm;
	CEdit edit_sched_name;
	CButton btn_save;
	CCheckListBox list_devices;

	afx_msg void OnCbnSelchangeComboUpdDel();
	afx_msg void OnNMClickListRooms(NMHDR *pNMHDR, LRESULT *pResult);

	int room_index;
	struct frg_ids idForEdit;
	struct frg_ids idForDelete;

	CStatic static_grp_manage_sched;
	CStatic static_grp_room_schedule;
	afx_msg void OnNMClickListSchedule(NMHDR *pNMHDR, LRESULT *pResult);
	int scheduleid[1000];
	afx_msg void OnBnClickedButtonDeletesched();
	afx_msg void OnBnClickedButtonSave();
	void populateSchedule();

	int indexDay;
	int arr_devices[100];
	int arr_days[100];

	int rds_id;
//	CComboBox combo_date_month;
//	CComboBox combo_date_day;
//	CComboBox combo_date_year;
	CButton check_date;
	afx_msg void OnBnClickedCheckDate();
	CDateTimeCtrl datepicker_date;
	afx_msg void OnDtnDatetimechangeDatetimepickerDate(NMHDR *pNMHDR, LRESULT *pResult);

	CString selectedDate;
};
