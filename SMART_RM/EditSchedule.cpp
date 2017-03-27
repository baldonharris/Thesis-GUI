// EditSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "EditSchedule.h"
#include "afxdialogex.h"


// EditSchedule dialog

IMPLEMENT_DYNAMIC(EditSchedule, CDialogEx)

EditSchedule::EditSchedule(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditSchedule::IDD, pParent)
{

}

EditSchedule::~EditSchedule()
{
}

void EditSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_UPD_DEL, combo_upd_del);
	DDX_Control(pDX, IDC_LIST_ROOMS, list_rooms);
	DDX_Control(pDX, IDC_LIST_SCHEDULE, list_schedule);
	DDX_Control(pDX, IDC_LIST_DAYS, list_days);
	DDX_Control(pDX, IDC_STATIC_START_TIME, static_start_time);
	DDX_Control(pDX, IDC_STATIC_ENDTIME, static_end_time);
	DDX_Control(pDX, IDC_STATIC_SCHED_NAME, static_sched_name);
	DDX_Control(pDX, IDC_COMBO_START_HR, combo_start_hr);
	DDX_Control(pDX, IDC_COMBO_START_MIN, combo_start_min);
	DDX_Control(pDX, IDC_COMBO_START_AMPM, combo_start_ampm);
	DDX_Control(pDX, IDC_COMBO_END_HR, combo_end_hr);
	DDX_Control(pDX, IDC_COMBO_END_MIN, combo_end_min);
	DDX_Control(pDX, IDC_COMBO_END_AMPM, combo_end_ampm);
	DDX_Control(pDX, IDC_EDIT_SCHED_NAME, edit_sched_name);
	DDX_Control(pDX, IDC_BUTTON_SAVE, btn_save);
	DDX_Control(pDX, IDC_BUTTON_DELETESCHED, btn_delete);
	DDX_Control(pDX, IDC_STATIC_MANAGE_SCHED, static_grp_manage_sched);
	DDX_Control(pDX, IDC_STATIC_ROOMSCHED, static_grp_room_schedule);
	DDX_Control(pDX, IDC_STATIC_FXN, static_function);
	DDX_Control(pDX, IDC_LIST2_DEVICES, list_devices);
	//  DDX_Control(pDX, IDC_COMBO_MONTH, combo_date_month);
	//  DDX_Control(pDX, IDC_COMBO_DAY, combo_date_day);
	//  DDX_Control(pDX, IDC_COMBO_YEAR, combo_date_year);
	DDX_Control(pDX, IDC_CHECK_DATE, check_date);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, datepicker_date);
}


BEGIN_MESSAGE_MAP(EditSchedule, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_UPD_DEL, &EditSchedule::OnCbnSelchangeComboUpdDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ROOMS, &EditSchedule::OnNMClickListRooms)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SCHEDULE, &EditSchedule::OnNMClickListSchedule)
	ON_BN_CLICKED(IDC_BUTTON_DELETESCHED, &EditSchedule::OnBnClickedButtonDeletesched)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &EditSchedule::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_CHECK_DATE, &EditSchedule::OnBnClickedCheckDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DATE, &EditSchedule::OnDtnDatetimechangeDatetimepickerDate)
END_MESSAGE_MAP()


// EditSchedule message handlers
LPWSTR convertStringYouMe(const char *cs){
	size_t size = strlen(cs)+1;
	wchar_t* wtext = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, wtext, size, cs, size-1);

	return (LPWSTR)wtext;
}

static void AddDataYouMe(CColorListCtrl &ctrl, int row, int col, const char *str)
{
    LVITEM lv;
    lv.iItem = row;
    lv.iSubItem = col;
    lv.pszText = convertStringYouMe(str);
    lv.mask = LVIF_TEXT;
    if(col == 0)
        ctrl.InsertItem(&lv);
    else
        ctrl.SetItem(&lv);
}

int PopulateScheduleYouMe(CColorListCtrl &schedList){
	int row = 0;
	int totalRow = 0;
	frg_topData = NULL;
	schedList.DeleteAllItems();
	clearData();
	for(int a=0; a<response["data"].Size(); a++){
		AddDataYouMe(schedList, row, 0, response["data"][a][0]["floors_name"].GetString());
		schedList.SetRowColor(RGB(255,247,0), row);
		row++;
		for(int b=0; b<response["data"][a].Size(); b++){
			AddDataYouMe(schedList, row, 0, "");
			AddDataYouMe(schedList, row, 1, response["data"][a][b]["rooms_name"].GetString());
			insertData(atoi(response["data"][a][b]["floor_room_groups_id"].GetString()), atoi(response["data"][a][b]["rooms_id"].GetString()), atoi(response["data"][a][b]["floors_id"].GetString()), row); // push to stack
			row++;
			totalRow++;
		}
	}

	return totalRow;
}


void EditSchedule::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	combo_upd_del.SetCurSel(0);
	check_date.SetCheck(0);

	datepicker_date.EnableWindow(false);
	list_days.EnableWindow(false);

	btn_delete.EnableWindow(FALSE);
	list_schedule.DeleteAllItems();

	static_grp_room_schedule.SetWindowTextW(_T("Room Schedule"));
	static_grp_manage_sched.SetWindowTextW(_T("Manage Schedule"));

	for(int x=0; x<list_days.GetCount(); x++){
		list_days.SetCheck(x, 0);
	}

	list_schedule.EnableWindow(TRUE);
	list_days.EnableWindow(TRUE);
	combo_start_hr.EnableWindow(TRUE);
	combo_start_min.EnableWindow(TRUE);
	combo_start_ampm.EnableWindow(TRUE);
	combo_end_hr.EnableWindow(TRUE);
	combo_end_min.EnableWindow(TRUE);
	combo_end_ampm.EnableWindow(TRUE);
	edit_sched_name.EnableWindow(TRUE);
	btn_save.EnableWindow(TRUE);

	if(bShow){
		SetTimer(1, 1000, NULL);
	}else{
		KillTimer(1);
	}

	combo_start_hr.SetCurSel(6);
	combo_start_min.SetCurSel(30);
	combo_start_ampm.SetCurSel(0);
	combo_end_hr.SetCurSel(7);
	combo_end_min.SetCurSel(30);
	combo_end_ampm.SetCurSel(0);
}


void EditSchedule::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString URL;
	URL.Format(_T("%sfunction=check_rooms&check_rooms_for=manage"), urlMe);
	CStringA finalURL(URL);
	int request = thesis_request((const char *)finalURL);

	if(request == 1){
		if(response["status"].GetInt()){
			if(!strcmp(response["data"][0]["check_rooms_status"].GetString(), "1")){
				list_rooms.DeleteAllItems();
				clearData();
				ASSERT(list_rooms.GetItemCount() == 0);
				CString URL;
				URL.Format(_T("%sfunction=view_room_status"), urlMe);
				CStringA finalURL(URL);
				thesis_request((const char *)finalURL);
				PopulateScheduleYouMe(list_rooms);
				TRACE("HALU!!");
			}
		}
	}else{
		TRACE("ALERT! SERVER ERROR!");
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL EditSchedule::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	datepicker_date.SetFormat(_T("yyyy-MM-dd"));

	CTime date = CTime::GetCurrentTime();
	datepicker_date.SetTime(&date);
	selectedDate = date.Format("%Y-%m-%d");

	list_rooms.InsertColumn(0, _T("Floor"), LVCFMT_CENTER, 70);
	list_rooms.InsertColumn(1, _T("Rooms"), LVCFMT_CENTER, 90);
	list_rooms.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
	list_schedule.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	list_schedule.InsertColumn(0, _T("Name"), LVCFMT_CENTER, 70);
	list_schedule.InsertColumn(1, _T("Date"), LVCFMT_CENTER, 90);
	list_schedule.InsertColumn(2, _T("Start"), LVCFMT_CENTER, 50);
	list_schedule.InsertColumn(3, _T("End"), LVCFMT_CENTER, 50);
	list_schedule.InsertColumn(4, _T("Type"), LVCFMT_CENTER, 40);

	CString URL;
	URL.Format(_T("%sfunction=view_room_status"), urlMe);
	CStringA finalURL(URL);
	int request = thesis_request((const char *)finalURL);

	if(request){
		if(response["status"].GetInt()){
			PopulateScheduleYouMe(list_rooms);
		}else{
			TRACE("ALERT! INVALID URL OR NO DATA!");
		}
	}else{
		TRACE("ALERT! SERVER ERROR!");
	}

	list_days.InsertString(0, _T("Mon"));
	list_days.SetCheck(0, 0);
	list_days.InsertString(1, _T("Tue"));
	list_days.SetCheck(1, 0);
	list_days.InsertString(2, _T("Wed"));
	list_days.SetCheck(2, 0);
	list_days.InsertString(3, _T("Thu"));
	list_days.SetCheck(3, 0);
	list_days.InsertString(4, _T("Fri"));
	list_days.SetCheck(4, 0);
	list_days.InsertString(5, _T("Sat"));
	list_days.SetCheck(5, 0);
	list_days.InsertString(6, _T("Sun"));
	list_days.SetCheck(6, 0);

	for(int min=0, hr=1; min<60; hr++, min++){
		CString minute;
		CString hour;
		if(min<10){
			minute.Format(_T("0%d"), min);
		}else{
			minute.Format(_T("%d"), min);
		}
		if(hr<13){
			if(hr<10){
				hour.Format(_T("0%d"), hr);
			}else{
				hour.Format(_T("%d"), hr);
			}
			combo_start_hr.AddString(hour);
			combo_end_hr.AddString(hour);
		}
		combo_start_min.AddString(minute);
		combo_end_min.AddString(minute);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void EditSchedule::OnCbnSelchangeComboUpdDel()
{
	// TODO: Add your control notification handler code here
	combo_start_hr.SetCurSel(6);
	combo_start_min.SetCurSel(30);
	combo_start_ampm.SetCurSel(0);
	combo_end_hr.SetCurSel(7);
	combo_end_min.SetCurSel(30);
	combo_end_ampm.SetCurSel(0);
	edit_sched_name.SetWindowTextW(_T(""));
	if(combo_upd_del.GetCurSel() == 2){ // delete
		btn_delete.EnableWindow(TRUE);

		list_schedule.EnableWindow(TRUE);
		list_days.EnableWindow(FALSE);
		combo_start_hr.EnableWindow(FALSE);
		combo_start_min.EnableWindow(FALSE);
		combo_start_ampm.EnableWindow(FALSE);
		combo_end_hr.EnableWindow(FALSE);
		combo_end_min.EnableWindow(FALSE);
		combo_end_ampm.EnableWindow(FALSE);
		edit_sched_name.EnableWindow(FALSE);
		btn_save.EnableWindow(FALSE);
		check_date.EnableWindow(FALSE);
	}else if(combo_upd_del.GetCurSel() == 0){	// add
		list_schedule.DeleteAllItems();
		btn_delete.EnableWindow(FALSE);

		check_date.EnableWindow(TRUE);
		list_schedule.EnableWindow(TRUE);
		list_days.EnableWindow(TRUE);
		combo_start_hr.EnableWindow(TRUE);
		combo_start_min.EnableWindow(TRUE);
		combo_start_ampm.EnableWindow(TRUE);
		combo_end_hr.EnableWindow(TRUE);
		combo_end_min.EnableWindow(TRUE);
		combo_end_ampm.EnableWindow(TRUE);
		edit_sched_name.EnableWindow(TRUE);
		btn_save.EnableWindow(TRUE);
	}else{	// add
		list_schedule.DeleteAllItems();
		btn_delete.EnableWindow(FALSE);

		check_date.EnableWindow(TRUE);
		list_schedule.EnableWindow(TRUE);
		list_days.EnableWindow(TRUE);
		combo_start_hr.EnableWindow(TRUE);
		combo_start_min.EnableWindow(TRUE);
		combo_start_ampm.EnableWindow(TRUE);
		combo_end_hr.EnableWindow(TRUE);
		combo_end_min.EnableWindow(TRUE);
		combo_end_ampm.EnableWindow(TRUE);
		edit_sched_name.EnableWindow(TRUE);
		btn_save.EnableWindow(TRUE);
	}
}

void EditSchedule::populateSchedule(){
	int row = list_rooms.GetSelectionMark();
	idForEdit = searchData(row);

	list_schedule.DeleteAllItems();
	CString URL;
	URL.Format(_T("%sfunction=get_rs&rooms_id=%d"), urlMe, idForEdit.rooms_id);
	CStringA finalURL(URL);
	TRACE(URL);
	thesis_request((const char *)finalURL);

	int requestMe = thesis_request((const char *)finalURL);
	if(requestMe){
		if(response["status"].GetInt()){
			for(int x=0; x<response["data"].Size(); x++){
				scheduleid[x] = atoi(response["data"][x]["room_schedules_id"].GetString());
				CStringA start_time = parseTime(atoi(response["data"][x]["room_schedules_start_time"].GetString()));
				CStringA end_time = parseTime(atoi(response["data"][x]["room_schedules_end_time"].GetString()));
				CString type = (atoi(response["data"][x]["room_schedules_type"].GetString())) ? _T("M") : _T("A");
				CStringA finalType(type);

				AddDataYouMe(list_schedule, x, 0, response["data"][x]["room_schedules_name"].GetString());
				AddDataYouMe(list_schedule, x, 1, (response["data"][x]["room_schedules_date"].IsNull() ? "" : response["data"][x]["room_schedules_date"].GetString()));
				AddDataYouMe(list_schedule, x, 2, (const char *)start_time);
				AddDataYouMe(list_schedule, x, 3, (const char *)end_time);
				AddDataYouMe(list_schedule, x, 4, (const char *)finalType);
			}
		}
		TRACE("hey");
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}
	
}


void EditSchedule::OnNMClickListRooms(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	int row = list_rooms.GetSelectionMark();
	populateSchedule();

	for(int x=0; x<list_days.GetCount(); x++){
		list_days.SetCheck(x, 0);
	}

	list_devices.ResetContent();
	struct frg_ids room_id = searchData(row);
	idForDelete = room_id;

	CString URL;
	URL.Format(_T("%sfunction=get_rd&rooms_id=%d"), urlMe, room_id.rooms_id);
	CStringA finalURL(URL);

	TRACE(URL);

	int request = thesis_request((const char *)finalURL);
	if(request){
		if(response["status"].GetInt()){
			for(int x=0; x<response["data"].Size(); x++){
				CString deviceName(response["data"][x]["room_devices_name"].GetString());
				list_devices.InsertString(x, deviceName);
				list_devices.SetCheck(x, 0);
			}
		}
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}

	*pResult = 0;
}


void EditSchedule::OnNMClickListSchedule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	combo_start_hr.SetCurSel(6);
	combo_start_min.SetCurSel(30);
	combo_start_ampm.SetCurSel(0);
	combo_end_hr.SetCurSel(7);
	combo_end_min.SetCurSel(30);
	combo_end_ampm.SetCurSel(0);
	edit_sched_name.SetWindowTextW(_T(""));

	for(int x=0; x<list_days.GetCount(); x++){
		list_days.SetCheck(x, 0);
	}

	for(int x=0; x<list_devices.GetCount(); x++){
		list_devices.SetCheck(x, 0);
	}

	int row = list_schedule.GetSelectionMark();
	CString URL;
	rds_id=scheduleid[row];
	URL.Format(_T("%sfunction=get_room_schedules_plus_device&room_schedules_id=%d"), urlMe, scheduleid[row]);
	CStringA finalURL(URL);
	TRACE(URL);

	int request = thesis_request(finalURL);
	if(request){
		if(response["status"].GetInt() && response["data"].Size() != 0){
			if(!strcmp(response["data"][0]["room_schedules_type"].GetString(), "0")){
				
				if(response["data"][0]["room_schedules_day"].IsNull() && !response["data"][0]["room_schedules_date"].IsNull()){
					CString date(response["data"][0]["room_schedules_date"].GetString());
					CStringA syear(date.Mid(0,4));
					CStringA smonth(date.Mid(5,2));
					CStringA sday(date.Mid(8,2));

					int year = atoi((const char *)syear);
					int month = atoi((const char *)smonth);
					int day = atoi((const char *)sday);

					CTime t(year, month, day, 0, 0, 0);
					datepicker_date.SetTime(&t);

					datepicker_date.EnableWindow(true);
					check_date.SetCheck(true);
					list_days.EnableWindow(false);
				}else{
					datepicker_date.EnableWindow(!true);
					check_date.SetCheck(!true);
					list_days.EnableWindow(!false);

					CString days(response["data"][0]["room_schedules_day"].GetString());
					if(days.Find(_T("Mon")) != -1){
						list_days.SetCheck(0, 1);
					}
					if(days.Find(_T("Tue")) != -1){
						list_days.SetCheck(1, 1);
					}
					if(days.Find(_T("Wed")) != -1){
						list_days.SetCheck(2, 1);
					}
					if(days.Find(_T("Thu")) != -1){
						list_days.SetCheck(3, 1);

					}
					if(days.Find(_T("Fri")) != -1){
						list_days.SetCheck(4, 1);
					}
					if(days.Find(_T("Sat")) != -1){
						list_days.SetCheck(5, 1);
					}
					if(days.Find(_T("Sun")) != -1){
						list_days.SetCheck(7, 1);
					}
				}

				struct schedTime start_time = explodeTime(atoi(response["data"][0]["room_schedules_start_time"].GetString()));
				struct schedTime end_time = explodeTime(atoi(response["data"][0]["room_schedules_end_time"].GetString()));

				combo_start_hr.SetCurSel(start_time.hour-1);
				combo_start_min.SetCurSel(start_time.minutes);
				combo_start_ampm.SetCurSel(start_time.ampm);
				combo_end_hr.SetCurSel(end_time.hour-1);
				combo_end_min.SetCurSel(end_time.minutes);
				combo_end_ampm.SetCurSel(end_time.ampm);

				CString schedName(response["data"][0]["room_schedules_name"].GetString());
				edit_sched_name.SetWindowTextW(schedName);

				CString dev_server(response["data"][0]["room_devices_name"].GetString());
				TRACE(dev_server);

				for(int x=0; x<list_devices.GetCount(); x++){
					CString device;
					list_devices.GetText(x, device);
					if(dev_server.Find(device) != -1){
						list_devices.SetCheck(x, 1);
					}
				}
			}
		}
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}

	*pResult = 0;
}


void EditSchedule::OnBnClickedButtonDeletesched()
{
	// TODO: Add your control notification handler code here
	// idForEdit, scheduleid[row]
	int row_sched = list_schedule.GetSelectionMark();

	CString URL;
	URL.Format(_T("%sfunction=del_rs&room_schedules_id=%d&rooms_id=%d&rds=%d"), urlMe, scheduleid[row_sched], idForDelete.rooms_id, rds_id);
	CStringA finalURL(URL);

	TRACE("\n\n\n\n\n\n");
	TRACE(URL);
	TRACE(" ******");

	int request = thesis_request((const char*)finalURL);
	if(request){
		if(response["status"].GetInt()){
			populateSchedule();
			MessageBoxW(_T("Room is successfully deleted"), _T("Success!"), MB_ICONASTERISK | MB_OK);
		}else{
			MessageBoxW(_T("Internal Server Error!"), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}


bool has_space_only(CString item){
	int counter=0;
	for(int x=0; x<item.GetLength(); x++){
		if(item.GetAt(x) == ' ') counter++;
	}
	if(counter == item.GetLength()) return true;
	else return false;
}


void EditSchedule::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	if(idForEdit.rooms_id != 0){
		CString toPass_days, toPass_devices, toPass_schedName, toPass_startTime, toPass_endTime;
		edit_sched_name.GetWindowTextW(toPass_schedName);

		if(check_date.GetCheck()){

			int checkDevice = 0;
			for(int x=0; x<list_devices.GetCount(); x++){
				if(list_devices.GetCheck(x) == 1){
					CString device;
					checkDevice++;
					list_devices.GetText(x, device);
					if((x+1) != list_devices.GetCount()){
						toPass_devices += device;
						toPass_devices += _T(",");
					}else{
						toPass_devices += device;
					}
				}
			}

			if(!checkDevice){
				toPass_devices = _T("NULL");
			}

			if(toPass_schedName.IsEmpty() || has_space_only(toPass_schedName)){
				MessageBoxW(_T("A field is empty or incorrect!"), _T("Error!"), MB_ICONERROR | MB_OK);
			}else{
				if(toPass_devices.GetAt(toPass_devices.GetLength()-1) == ',') toPass_devices.SetAt(toPass_devices.GetLength()-1, '\0');

				toPass_startTime.Format(_T("%d"), parseTimeToMin( (combo_start_hr.GetCurSel()+1), combo_start_min.GetCurSel(), combo_start_ampm.GetCurSel() ));
				toPass_endTime.Format(_T("%d"), parseTimeToMin( (combo_end_hr.GetCurSel()+1), combo_end_min.GetCurSel(), combo_end_ampm.GetCurSel() ));

				CString dash("-");
				toPass_devices.Replace(_T(" "), dash);
				toPass_schedName.Replace(_T(" "), dash);
				toPass_startTime.Replace(_T(" "), dash);
				toPass_endTime.Replace(_T(" "), dash);

				CString URL;
				CStringA finalURL;

				if(combo_upd_del.GetCurSel() == 0){
					URL.Format(_T("%sfunction=newSched&stime=%s&etime=%s&schedname=%s&rooms_id=%d&date=%s&device=%s"), urlMe, toPass_startTime, toPass_endTime, toPass_schedName, idForEdit.rooms_id, selectedDate, toPass_devices);
					finalURL = URL;
					TRACE(URL);
					int request = thesis_request((const char *)finalURL);
					if(request){
						if(response["status"].GetInt() == -1){
							MessageBoxW(_T("Schedule is in conflict!"), _T("Error!"), MB_ICONERROR | MB_OK);
						}else{
							populateSchedule();
							MessageBoxW(_T("Schedule is successfuly added!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
						}
					}else{
						MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
					}
				}else{
					URL.Format(_T("%sfunction=newSched&stime=%s&etime=%s&schedname=%s&rooms_id=%d&date=%s&device=%s&rs_id=%d"), urlMe, toPass_startTime, toPass_endTime, toPass_schedName, idForEdit.rooms_id, selectedDate, toPass_devices, rds_id);
					finalURL = URL;
					TRACE(URL);
					int request = thesis_request((const char *)finalURL);
					if(request){
						if(response["status"].GetInt() == -1){
							MessageBoxW(_T("Schedule is in conflict!"), _T("Error!"), MB_ICONERROR | MB_OK);
						}else{
							populateSchedule();
							MessageBoxW(_T("Schedule is successfuly updated!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
						}
					}else{
						MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
					}
				}

				
				
				
			}

		}else{
			int checkCounter = 0;
			for(int x=0; x<list_days.GetCount(); x++){
				if(list_days.GetCheck(x) == 1){
					checkCounter++;
					CString day;
					list_days.GetText(x, day);
					if((x+1) != list_days.GetCount()){
						toPass_days += day;
						toPass_days += _T(",");
					}else{
						toPass_days += day;
					}
				}
			}

			int checkDevice = 0;
			for(int x=0; x<list_devices.GetCount(); x++){
				if(list_devices.GetCheck(x) == 1){
					CString device;
					checkDevice++;
					list_devices.GetText(x, device);
					if((x+1) != list_devices.GetCount()){
						toPass_devices += device;
						toPass_devices += _T(",");
					}else{
						toPass_devices += device;
					}
				}
			}

			if(!checkDevice){
				toPass_devices = _T("NULL");
			}
			
			if(toPass_schedName.IsEmpty() || has_space_only(toPass_schedName) || !checkCounter){
				MessageBoxW(_T("A field is empty or incorrect!"), _T("Error!"), MB_ICONERROR | MB_OK);
			}else{
				if(toPass_devices.GetAt(toPass_devices.GetLength()-1) == ',') toPass_devices.SetAt(toPass_devices.GetLength()-1, '\0');
				if(toPass_days.GetAt(toPass_days.GetLength()-1) == ',') toPass_days.SetAt(toPass_days.GetLength()-1, '\0');

				toPass_startTime.Format(_T("%d"), parseTimeToMin( (combo_start_hr.GetCurSel()+1), combo_start_min.GetCurSel(), combo_start_ampm.GetCurSel() ));
				toPass_endTime.Format(_T("%d"), parseTimeToMin( (combo_end_hr.GetCurSel()+1), combo_end_min.GetCurSel(), combo_end_ampm.GetCurSel() ));

				CString dash("-");
				toPass_days.Replace(_T(" "), dash);
				toPass_devices.Replace(_T(" "), dash);
				toPass_schedName.Replace(_T(" "), dash);
				toPass_startTime.Replace(_T(" "), dash);
				toPass_endTime.Replace(_T(" "), dash);

				CString URL;
				CStringA finalURL;

				if(combo_upd_del.GetCurSel() == 0){
					URL.Format(_T("%sfunction=manage_schedule&days=%s&stime=%s&etime=%s&schedname=%s&devices=%s&rooms_id=%d"), urlMe, toPass_days, toPass_startTime, toPass_endTime, toPass_schedName, toPass_devices, idForEdit.rooms_id);
					finalURL = URL;
					TRACE(URL);
					int request = thesis_request((const char *)finalURL);
					if(request){
						if(response["status"].GetInt() == -1){
							MessageBoxW(_T("Schedule is in conflict!"), _T("Error!"), MB_ICONERROR | MB_OK);
						}else{
							populateSchedule();
							MessageBoxW(_T("Schedule is successfuly added!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
						}
					}else{
						MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
					}
				}else{
					URL.Format(_T("%sfunction=manage_schedule&days=%s&stime=%s&etime=%s&schedname=%s&devices=%s&rooms_id=%d&rs_id=%d"), urlMe, toPass_days, toPass_startTime, toPass_endTime, toPass_schedName, toPass_devices, idForEdit.rooms_id, rds_id);
					finalURL = URL;
					TRACE(URL);
					int request = thesis_request((const char *)finalURL);
					if(request){
						if(response["status"].GetInt() == -1){
							MessageBoxW(_T("Schedule is in conflict!"), _T("Error!"), MB_ICONERROR | MB_OK);
						}else{
							populateSchedule();
							MessageBoxW(_T("Schedule is successfuly updated!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
						}
					}else{
						MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
					}
				}
				TRACE("\n\n");
				TRACE(URL);
			}
		}
	}else{
		MessageBoxW(_T("Please select a room!"), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}

void EditSchedule::OnBnClickedCheckDate()
{
	// TODO: Add your control notification handler code here
	if(check_date.GetCheck()){
		datepicker_date.EnableWindow(true);
		list_days.EnableWindow(false);
	}else{
		datepicker_date.EnableWindow(false);
		list_days.EnableWindow(true);
	}
}


void EditSchedule::OnDtnDatetimechangeDatetimepickerDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	NMDATETIMECHANGE * a_pstHdr = (NMDATETIMECHANGE*)pNMHDR;
	selectedDate.Format(_T("%.4d-%.2d-%.2d"), a_pstHdr->st.wYear, a_pstHdr->st.wMonth, a_pstHdr->st.wDay);
	*pResult = 0;
}
