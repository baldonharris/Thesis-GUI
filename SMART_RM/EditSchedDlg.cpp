// EditSchedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "EditSchedDlg.h"
#include "afxdialogex.h"
#include "Thesis.h"


// EditSchedDlg dialog

IMPLEMENT_DYNAMIC(EditSchedDlg, CDialogEx)

EditSchedDlg::EditSchedDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditSchedDlg::IDD, pParent)
{

}

EditSchedDlg::~EditSchedDlg()
{
}

void EditSchedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_UPD_DEL, combo_upd_del);
	DDX_Control(pDX, IDC_LIST_ROOMS, list_rooms);
	DDX_Control(pDX, IDC_BUTTON_DELETE, btn_del);
	DDX_Control(pDX, IDC_STATIC_FLOOR, static_floor);
	DDX_Control(pDX, IDC_ADDMOD_ROOMNAME, static_rmname);
	DDX_Control(pDX, IDC_ADDMOD_MAC_ADDRESS, static_rmmac);
	DDX_Control(pDX, IDC_COMBO_FLOOR, combo_floor);
	DDX_Control(pDX, IDC_EDIT_RMNAME, edit_rmname);
	DDX_Control(pDX, IDC_EDIT_MAC_1, edit_mac_1);
	DDX_Control(pDX, IDC_EDIT_MAC_2, edit_mac_2);
	DDX_Control(pDX, IDC_EDIT_MAC_3, edit_mac_3);
	DDX_Control(pDX, IDC_EDIT_MAC_4, edit_mac_4);
	DDX_Control(pDX, IDC_EDIT_MAC_5, edit_mac_5);
	DDX_Control(pDX, IDC_EDIT_MAC_6, edit_mac_6);
	DDX_Control(pDX, IDC_EDIT_MAC_7, edit_mac_7);
	DDX_Control(pDX, IDC_EDIT_MAC_8, edit_mac_8);
	DDX_Control(pDX, IDC_LIST_EDIT_PORTS, list_port);
	DDX_Control(pDX, IDC_EDIT_DEVICENAME, edit_device_name);
	DDX_Control(pDX, IDC_STATIC_PORTS, static_rm_ports);
	DDX_Control(pDX, IDC_STATIC_FXNS, static_function);
	DDX_Control(pDX, IDC_BUTTON_ROOM_DETAILS, btn_save_rm_details);
	DDX_Control(pDX, IDC_BUTTON_ROOM_DEV, btn_save_rm_dev);
}


BEGIN_MESSAGE_MAP(EditSchedDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_UPD_DEL, &EditSchedDlg::OnCbnSelchangeComboUpdDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ROOMS, &EditSchedDlg::OnNMClickListRooms)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &EditSchedDlg::OnBnClickedButtonDelete)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LIST_EDIT_PORTS, &EditSchedDlg::OnLbnSelchangeListEditPorts)
	ON_BN_CLICKED(IDC_BUTTON_ROOM_DETAILS, &EditSchedDlg::OnBnClickedButtonRoomDetails)
	ON_BN_CLICKED(IDC_BUTTON_ROOM_DEV, &EditSchedDlg::OnBnClickedButtonRoomDev)
	ON_BN_CLICKED(IDC_BUTTON_ROOM_SCHED, &EditSchedDlg::OnBnClickedButtonRoomSched)
	ON_EN_KILLFOCUS(IDC_EDIT_DEVICENAME, &EditSchedDlg::OnEnKillfocusEditDevicename)
	ON_EN_MAXTEXT(IDC_EDIT_MAC_1, &EditSchedDlg::OnEnMaxtextEditMac1)
	ON_EN_MAXTEXT(IDC_EDIT_MAC_2, &EditSchedDlg::OnEnMaxtextEditMac2)
	ON_EN_MAXTEXT(IDC_EDIT_MAC_3, &EditSchedDlg::OnEnMaxtextEditMac3)
	ON_EN_MAXTEXT(IDC_EDIT_MAC_4, &EditSchedDlg::OnEnMaxtextEditMac4)
	ON_EN_MAXTEXT(IDC_EDIT_MAC_5, &EditSchedDlg::OnEnMaxtextEditMac5)
	ON_EN_MAXTEXT(IDC_EDIT_MAC_6, &EditSchedDlg::OnEnMaxtextEditMac6)
	ON_EN_MAXTEXT(IDC_EDIT_MAC_7, &EditSchedDlg::OnEnMaxtextEditMac7)
	ON_BN_CLICKED(IDC_BUTTON_SYNC, &EditSchedDlg::OnBnClickedButtonSync)
END_MESSAGE_MAP()


// EditSchedDlg message handlers

LPWSTR convertStringYou(const char *cs){
	size_t size = strlen(cs)+1;
	wchar_t* wtext = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, wtext, size, cs, size-1);

	return (LPWSTR)wtext;
}

static void AddDataYou(CColorListCtrl &ctrl, int row, int col, const char *str)
{
    LVITEM lv;
    lv.iItem = row;
    lv.iSubItem = col;
    lv.pszText = convertStringYou(str);
    lv.mask = LVIF_TEXT;
    if(col == 0)
        ctrl.InsertItem(&lv);
    else
        ctrl.SetItem(&lv);
}

int PopulateScheduleYou(CColorListCtrl &schedList){
	int row = 0;
	int totalRow = 0;
	frg_topData = NULL;
	schedList.DeleteAllItems();
	clearData();
	for(int a=0; a<response["data"].Size(); a++){
		AddDataYou(schedList, row, 0, response["data"][a][0]["floors_name"].GetString());
		schedList.SetRowColor(RGB(255,247,0), row);
		row++;
		for(int b=0; b<response["data"][a].Size(); b++){
			AddDataYou(schedList, row, 0, "");
			AddDataYou(schedList, row, 1, response["data"][a][b]["rooms_name"].GetString());
			insertData(atoi(response["data"][a][b]["floor_room_groups_id"].GetString()), atoi(response["data"][a][b]["rooms_id"].GetString()), atoi(response["data"][a][b]["floors_id"].GetString()), row); // push to stack
			row++;
			totalRow++;
		}
	}

	return totalRow;
}


BOOL EditSchedDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CFont m_font;
	m_font.CreatePointFont(90, L"Courier New");
	list_rooms.SetFont(&m_font);
	static_floor.SetFont(&m_font);
	static_rmname.SetFont(&m_font);
	static_rmmac.SetFont(&m_font);
	list_port.SetFont(&m_font);
	static_rm_ports.SetFont(&m_font);
	static_function.SetFont(&m_font);

	combo_upd_del.SetCurSel(0);
	btn_del.EnableWindow(FALSE);

	edit_mac_1.SetLimitText(2);
	edit_mac_2.SetLimitText(2);
	edit_mac_3.SetLimitText(2);
	edit_mac_4.SetLimitText(2);
	edit_mac_5.SetLimitText(2);
	edit_mac_6.SetLimitText(2);
	edit_mac_7.SetLimitText(2);
	edit_mac_8.SetLimitText(2);

	list_rooms.InsertColumn(0, _T("Floor"), LVCFMT_CENTER, 70);
	list_rooms.InsertColumn(1, _T("Rooms"), LVCFMT_CENTER, 100);

	CString URL;
	URL.Format(_T("%sfunction=view_room_status"), urlMe);
	CStringA finalURL(URL);
	int request = thesis_request((const char *)finalURL);

	if(request){
		if(response["status"].GetInt()){
			PopulateScheduleYou(list_rooms);
			CString URL;
			URL.Format(_T("%sfunction=get_floor"), urlMe);
			CStringA finalURL(URL);
			int request = thesis_request((const char *)finalURL);
			combo_floor.ResetContent();
			if(request){
				if(response["status"].GetInt()){
					for(int x=0; x<response["data"].Size(); x++){
						CString floor(response["data"][x]["floors_name"].GetString());
						combo_floor.AddString(floor);
					}
				}else{
					TRACE("ALERT! INVALID URL OR NO DATA!");
				}
			}else{
				TRACE("ALERT! SERVER ERROR!");
			}
		}else{
			TRACE("ALERT! INVALID URL OR NO DATA!");
		}
	}else{
		TRACE("ALERT! SERVER ERROR!");
	}

	list_rooms.AdjustColumnWidth();
	list_rooms.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void EditSchedDlg::OnCbnSelchangeComboUpdDel()
{
	// TODO: Add your control notification handler code here
	bool check = (bool)combo_upd_del.GetCurSel();

	btn_del.EnableWindow(check);

	combo_floor.EnableWindow(!check);
	edit_rmname.EnableWindow(!check);
	edit_mac_1.EnableWindow(!check);
	edit_mac_2.EnableWindow(!check);
	edit_mac_3.EnableWindow(!check);
	edit_mac_4.EnableWindow(!check);
	edit_mac_5.EnableWindow(!check);
	edit_mac_6.EnableWindow(!check);
	edit_mac_7.EnableWindow(!check);
	edit_mac_8.EnableWindow(!check);
	btn_save_rm_details.EnableWindow(!check);
	list_port.EnableWindow(!check);
	edit_device_name.EnableWindow(!check);
	btn_save_rm_dev.EnableWindow(!check);

	combo_floor.ResetContent();
	if(!check){
		CString URL;
		URL.Format(_T("%sfunction=get_floor"), urlMe);
		CStringA finalURL(URL);
		int request = thesis_request((const char *)finalURL);
		if(request){
			if(response["status"].GetInt()){
				for(int x=0; x<response["data"].Size(); x++){
					CString floor(response["data"][x]["floors_name"].GetString());
					combo_floor.AddString(floor);
				}
			}else{
				TRACE("ALERT! INVALID URL OR NO DATA!");
			}
		}else{
			TRACE("ALERT! SERVER ERROR!");
		}
	}else{
		CString empty("");
		edit_rmname.SetWindowTextW(empty);
		edit_mac_1.SetWindowTextW(empty);
		edit_mac_2.SetWindowTextW(empty);
		edit_mac_3.SetWindowTextW(empty);
		edit_mac_4.SetWindowTextW(empty);
		edit_mac_5.SetWindowTextW(empty);
		edit_mac_6.SetWindowTextW(empty);
		edit_mac_7.SetWindowTextW(empty);
		edit_mac_8.SetWindowTextW(empty);
	}
}


void EditSchedDlg::OnNMClickListRooms(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	int row = list_rooms.GetSelectionMark();

	if(!list_rooms.GetItemText(row, 1).IsEmpty()){
		int curSel = -1;
		bool check = (bool)combo_upd_del.GetCurSel();
		struct frg_ids ids = searchData(row);
		idForEdit = ids;	// global variable
		edit_device_name.SetWindowTextW(_T(""));

		list_port.ResetContent();
		list_port.InsertString(0, _T("Port A"));
		list_port.SetCheck(0, 0);
		list_port.InsertString(1, _T("Port B"));
		list_port.SetCheck(1, 0);
		list_port.InsertString(2, _T("Port C"));
		list_port.SetCheck(2, 0);
		list_port.InsertString(3, _T("Port D"));
		list_port.SetCheck(3, 0);

		if(!check){
			CString URL;
			URL.Format(_T("%sfunction=get_room_details&rooms_id=%d"), urlMe, ids.rooms_id);
			CStringA finalURL(URL);
			int request = thesis_request((const char *)finalURL);

			if(request){
				if(response["status"].GetInt()){
					for(int x=0; x<combo_floor.GetCount(); x++){
						CString floor;
						CString floor_data(response["data"]["room_details"][0]["floors_name"].GetString());
						combo_floor.GetLBText(x, floor);
						if(!floor.Compare(floor_data)){
							combo_floor.SetCurSel(x);
							break;
						}
					}
					CString roomName(response["data"]["room_details"][0]["rooms_name"].GetString());
					CString mac[8];
					for(int x=0; x<response["data"]["room_details"][0]["rooms_address"].Size(); x++){
						mac[x] = response["data"]["room_details"][0]["rooms_address"][x].GetString();
					}

					edit_rmname.SetWindowTextW(roomName);
					edit_mac_1.SetWindowTextW(mac[0]);
					edit_mac_2.SetWindowTextW(mac[1]);
					edit_mac_3.SetWindowTextW(mac[2]);
					edit_mac_4.SetWindowTextW(mac[3]);
					edit_mac_5.SetWindowTextW(mac[4]);
					edit_mac_6.SetWindowTextW(mac[5]);
					edit_mac_7.SetWindowTextW(mac[6]);
					edit_mac_8.SetWindowTextW(mac[7]);

					for(int x=0; x<list_port.GetCount(); x++){
						devices_name[x] = _T("");
					}

					if(response["data"]["room_devices"].Size() > 0){
						TRACE("HEEEEYYYYYYY %d *******\n\n\n", response["data"]["room_devices"].Size());
						for(int x=0; x<response["data"]["room_devices"].Size(); x++){
							CString portName;
							CString portNumber(response["data"]["room_devices"][x]["room_devices_port"].GetString());
							if(!portNumber.Compare(_T("5"))){
								portName = _T("Port A");
							}else if(!portNumber.Compare(_T("6"))){
								portName = _T("Port B");
							}else if(!portNumber.Compare(_T("7"))){
								portName = _T("Port C");
							}else if(!portNumber.Compare(_T("8"))){
								portName = _T("Port D");
							}else{
								portName = _T("Unknown Port");
							}
				
							for(int y=0; y<list_port.GetCount(); y++){
								CString portNameCur;
								list_port.GetText(y, portNameCur);
								TRACE("\n\n*** ");
								TRACE(portNameCur);
								TRACE(" ");
								TRACE(portName);
								TRACE(" ***\n\n");
								if(!portNameCur.Compare(portName)){
									list_port.SetCheck(y, 1);
									devices_name[y] = response["data"]["room_devices"][x]["room_devices_name"].GetString();
								}
							}
						}
					}

					/*for(int x=0; x<response["data"]["room_schedules"].Size(); x++){
						WHY LOOP HERE ?
					}*/
				}
			}else{
				MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
			}
		}
	}else{
		CString empty("");
		edit_rmname.SetWindowTextW(empty);
		edit_mac_1.SetWindowTextW(empty);
		edit_mac_2.SetWindowTextW(empty);
		edit_mac_3.SetWindowTextW(empty);
		edit_mac_4.SetWindowTextW(empty);
		edit_mac_5.SetWindowTextW(empty);
		edit_mac_6.SetWindowTextW(empty);
		edit_mac_7.SetWindowTextW(empty);
		edit_mac_8.SetWindowTextW(empty);
		edit_device_name.SetWindowTextW(empty);
		for(int x=0; x<list_port.GetCount(); x++){
			list_port.SetCheck(x, 0);
			devices_name[x] = _T("");
		}
	}

	*pResult = 0;
}


void EditSchedDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	int row = list_rooms.GetSelectionMark();
	struct frg_ids ids;
	ids = searchData(row);

	TRACE("%d %d ***\n", ids.rooms_id, ids.frg_id);
	CString URL;
	URL.Format(_T("%sfunction=delete_room_module&rooms_id=%d"), urlMe, ids.rooms_id);
	CStringA finalURL(URL);
	TRACE("\n\n\n\n");
	TRACE(URL);
	TRACE(" *****%d %d\n\n\n", ids.rooms_id, ids.frg_id);

	int request = thesis_request((const char *)finalURL);
	if(request){
		if(response["status"].GetInt()){
			CString URL;
			URL.Format(_T("%sfunction=view_room_status"), urlMe);
			CStringA finalURL(URL);
			thesis_request((const char *)finalURL);
			PopulateScheduleYou(list_rooms);
			MessageBoxW(_T("Room successfuly deleted!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
		}else{
			MessageBoxW(_T("Internal server error!\nPlease contact administrator"), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}

void EditSchedDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString URL;
	URL.Format(_T("%sfunction=check_rooms&check_rooms_for=update"), urlMe);
	CStringA finalURL(URL);

	int request = thesis_request((const char *)finalURL);
	if(request){
		if(response["status"].GetInt()){
			if(!strcmp(response["data"][0]["check_rooms_status"].GetString(), "1")){
				CString URL;
				URL.Format(_T("%sfunction=view_room_status&mode=1"), urlMe);
				CStringA finalURL(URL);
				TRACE(URL);
				thesis_request((const char *)finalURL);
				list_rooms.DeleteAllItems();
				PopulateScheduleYou(list_rooms);
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void EditSchedDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if(bShow){
		SetTimer(1, 1300, NULL);
		CString URL;
		URL.Format(_T("%sfunction=view_room_status"), urlMe);
		CStringA finalURL(URL);
		int request = thesis_request((const char *)finalURL);

		if(request){
			if(response["status"].GetInt()){
				PopulateScheduleYou(list_rooms);
				CString URL;
				URL.Format(_T("%sfunction=get_floor"), urlMe);
				CStringA finalURL(URL);
				int request = thesis_request((const char *)finalURL);
				combo_floor.ResetContent();
				if(request){
					if(response["status"].GetInt()){
						for(int x=0; x<response["data"].Size(); x++){
							CString floor(response["data"][x]["floors_name"].GetString());
							combo_floor.AddString(floor);
						}
					}else{
						TRACE("ALERT! INVALID URL OR NO DATA!");
					}
				}else{
					TRACE("ALERT! SERVER ERROR!");
				}
			}else{
				TRACE("ALERT! INVALID URL OR NO DATA!");
			}
		}else{
			TRACE("ALERT! SERVER ERROR!");
		}
	}else{
		KillTimer(1);
		CString empty("");
		edit_rmname.SetWindowTextW(empty);
		edit_mac_1.SetWindowTextW(empty);
		edit_mac_2.SetWindowTextW(empty);
		edit_mac_3.SetWindowTextW(empty);
		edit_mac_4.SetWindowTextW(empty);
		edit_mac_5.SetWindowTextW(empty);
		edit_mac_6.SetWindowTextW(empty);
		edit_mac_7.SetWindowTextW(empty);
		edit_mac_8.SetWindowTextW(empty);
		edit_device_name.SetWindowTextW(empty);
		combo_floor.ResetContent();
		for(int x=0; x<list_port.GetCount(); x++){
			list_port.SetCheck(x, 0);
			devices_name[x] = _T("");
		}
	}
}


void EditSchedDlg::OnLbnSelchangeListEditPorts()
{
	// TODO: Add your control notification handler code here
	port_index = list_port.GetCurSel();
	CString portName;
	list_port.GetText(port_index, portName);

	edit_device_name.SetWindowTextW(devices_name[port_index]);

	if(list_port.GetCheck(port_index) == 0){
		edit_device_name.EnableWindow(FALSE);
	}else{
		edit_device_name.EnableWindow(TRUE);
	}
}

void EditSchedDlg::OnEnKillfocusEditDevicename()
{
	// TODO: Add your control notification handler code here
	int index = port_index; // global variable
	CString deviceName;
	edit_device_name.GetWindowTextW(deviceName);

	int diPwede=0;
	for(int x=0; x<list_port.GetCount(); x++){
		if(!deviceName.Compare(devices_name[x])){
			diPwede++;
			break;
		}
	}

	if(diPwede){
		MessageBoxW(_T("Existing device!"), _T("Error!"), MB_ICONERROR | MB_OK);
	}else{
		devices_name[index] = deviceName;
	}
}


void EditSchedDlg::OnBnClickedButtonRoomDetails()
{
	// TODO: Add your control notification handler code here
	struct frg_ids ids = searchData(list_rooms.GetSelectionMark());
	CString toPass_floor, toPass_room_name, toPass_mac;
	CString mac[8];
	int emptyCounter = 0;

	combo_floor.GetLBText(combo_floor.GetCurSel(), toPass_floor);
	edit_rmname.GetWindowTextW(toPass_room_name);
	edit_mac_1.GetWindowTextW(mac[0]);
	edit_mac_2.GetWindowTextW(mac[1]);
	edit_mac_3.GetWindowTextW(mac[2]);
	edit_mac_4.GetWindowTextW(mac[3]);
	edit_mac_5.GetWindowTextW(mac[4]);
	edit_mac_6.GetWindowTextW(mac[5]);
	edit_mac_7.GetWindowTextW(mac[6]);
	edit_mac_8.GetWindowTextW(mac[7]);

	emptyCounter += (toPass_room_name.IsEmpty()) ? 1 : 0;

	for(int x=0; x<8; x++){
		emptyCounter += (mac[x].IsEmpty()) ? 1 : 0;
		if(mac[x].GetLength() == 1){
			emptyCounter += 1;
		}
	}

	if(emptyCounter > 0){
		MessageBoxW(_T("A field is empty or incorrect!"), _T("Error!"), MB_ICONERROR | MB_OK);
	}else{
		for(int x=0; x<8; x++){
			if((x+1) != 8){
				toPass_mac += mac[x];
				toPass_mac += "-";
			}else{
				toPass_mac += mac[x];
			}
		}
		CString dash("-");
		toPass_floor.Replace(_T(" "), dash);
		toPass_room_name.Replace(_T(" "), dash);

		rooms_id = ids.rooms_id; // global variable for trigger device

		CString URL;
		URL.Format(_T("%sfunction=edit_room_details&floor=%s&room_name=%s&room_address=%s&rooms_id=%d"), urlMe, toPass_floor, toPass_room_name, toPass_mac, ids.rooms_id);
		CStringA finalURL(URL);
		TRACE(URL);
		
		int request = thesis_request((const char *)finalURL);
		if(request){
			if(response["status"].GetInt()){
				MessageBoxW(_T("Room details successfuly updated!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
			}else{
				MessageBoxW(_T("Internal server error!\nPlease contact administrator"), _T("Error!"), MB_ICONERROR | MB_OK);
			}
		}else{
			MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
		}

	}
}


void EditSchedDlg::OnBnClickedButtonRoomDev()
{
	// TODO: Add your control notification handler code here
	CString toPass_portsName, toPass_deviceName;

	CString tempPort[100];
	CString tempDevice[100];
	int emptyCounter = 0;

	int index=0;
	for(int x=0; x<list_port.GetCount(); x++){
		if(list_port.GetCheck(x) == 1){
			if(devices_name[x].IsEmpty()){
				emptyCounter++;
			}else{
				tempDevice[index] = devices_name[x];
				list_port.GetText(x, tempPort[index]);
				index++;
			}
		}
	}

	for(int x=0; x<index; x++){
		if((x+1) != index){
			toPass_portsName += tempPort[x];
			toPass_portsName += ",";
			toPass_deviceName += tempDevice[x];
			toPass_deviceName += ",";
		}else{
			toPass_portsName += tempPort[x];
			toPass_deviceName += tempDevice[x];
		}
	}

	CString dash("-");
	toPass_deviceName.Replace(_T(" "), dash);
	toPass_portsName.Replace(_T(" "), dash);
	
	CString URL;
	URL.Format(_T("%sfunction=edit_device_ports&ports=%s&device=%s&rooms_id=%d"), urlMe, toPass_portsName, toPass_deviceName, idForEdit.rooms_id);
	CStringA finalURL(URL);

	TRACE("\n\n\n\n");
	TRACE(URL);
	TRACE(" ****");

	int request = thesis_request((const char *)finalURL);
	if(request){
		if(response["status"].GetInt()){
			MessageBoxW(_T("Room details successfuly updated!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
		}else{
			MessageBoxW(_T("Internal server error!\nPlease contact administrator"), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}

	TRACE(URL);
	TRACE("\n\n");
}


void EditSchedDlg::OnBnClickedButtonRoomSched()
{
	// TODO: Add your control notification handler code here
}

void EditSchedDlg::OnEnMaxtextEditMac1()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_EDIT_MAC_2));
}


void EditSchedDlg::OnEnMaxtextEditMac2()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_EDIT_MAC_3));
}


void EditSchedDlg::OnEnMaxtextEditMac3()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_EDIT_MAC_4));
}


void EditSchedDlg::OnEnMaxtextEditMac4()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_EDIT_MAC_5));
}


void EditSchedDlg::OnEnMaxtextEditMac5()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_EDIT_MAC_6));
}


void EditSchedDlg::OnEnMaxtextEditMac6()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_EDIT_MAC_7));
}


void EditSchedDlg::OnEnMaxtextEditMac7()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_EDIT_MAC_8));
}


void EditSchedDlg::OnBnClickedButtonSync()
{
	// TODO: Add your control notification handler code here
	CString URL;
	URL.Format(_T("%sfunction=set_trigger_device&rooms_id=%d"), urlMe, rooms_id);
	CStringA finalURL(URL);
	thesis_request((const char *)finalURL);
}
