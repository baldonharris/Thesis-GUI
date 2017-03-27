// ManulSwDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "ManulSwDlg.h"
#include "afxdialogex.h"
#include "Thesis.h"
#include "atltime.h"
#include "ColorListCtrl.h"
#include <cctype>
//#include "CheckListBoxCBN.h"


// ManulSwDlg dialog

IMPLEMENT_DYNAMIC(ManulSwDlg, CDialogEx)

ManulSwDlg::ManulSwDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManulSwDlg::IDD, pParent)
{

}

ManulSwDlg::~ManulSwDlg()
{
}

void ManulSwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MANUALSW_LIST, list_manualSW);
	DDX_Control(pDX, IDC_LISTBOX_MANUALSW, listbox_device);
	DDX_Control(pDX, IDC_TEXTDURATION, text_timeDuration);
	DDX_Control(pDX, IDC_ROOM_NAME, text_roomName);
	DDX_Control(pDX, IDC_EDIT_INPDURATION, edit_inputDuration);
}


BEGIN_MESSAGE_MAP(ManulSwDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_MANUALSW_LIST, &ManulSwDlg::OnNMClickManualswList)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SAVEBTN, &ManulSwDlg::OnBnClickedSavebtn)
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LISTBOX_MANUALSW, &ManulSwDlg::OnLbnSelchangeListboxManualsw)
END_MESSAGE_MAP()


// ManulSwDlg message handlers

LPWSTR convertStringMe(const char *cs){
	size_t size = strlen(cs)+1;
	wchar_t* wtext = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, wtext, size, cs, size-1);

	return (LPWSTR)wtext;
}

static void AddDataMe(CColorListCtrl &ctrl, int row, int col, const char *str)
{
    LVITEM lv;
    lv.iItem = row;
    lv.iSubItem = col;
    lv.pszText = convertStringMe(str);
    lv.mask = LVIF_TEXT;
    if(col == 0)
        ctrl.InsertItem(&lv);
    else
        ctrl.SetItem(&lv);
}

static void EditDataMe(CColorListCtrl &ctrl, int row, int col, const char *str)
{
    LVITEM lv;
    lv.iItem = row;
    lv.iSubItem = col;
    lv.pszText = convertStringMe(str);
    lv.mask = LVIF_TEXT;
	ctrl.SetItem(&lv);
}

void RefreshColorMe(CColorListCtrl &ctrl){
	ctrl.ResetColors();
	for(int x=0; x<ctrl.GetItemCount(); x++){
		if(!ctrl.GetItemText(x, 2).IsEmpty()){
			if(!ctrl.GetItemText(x, 2).Compare(_T("ON"))){
				ctrl.SetCellColor(RGB(76,153,0), x, 2);
			}else if(!ctrl.GetItemText(x, 2).Compare(_T("OFF"))){
				ctrl.SetCellColor(RGB(255,0,0), x, 2);
			}else{
				ctrl.SetCellColor(RGB(255,51,255), x, 2);
			}
		}else{
			ctrl.SetRowColor(RGB(255,247,0), x);
		}
	}
}

int PopulateScheduleMe(CColorListCtrl &schedList){
	int row = 0;
	int totalRow = 0;
	frg_topData = NULL;
	clearData();	// clear the stack
	for(int a=0; a<response["data"].Size(); a++){
		AddDataMe(schedList, row, 0, response["data"][a][0]["floors_name"].GetString());
		schedList.SetRowColor(RGB(255,247,0), row);
		row++;
		for(int b=0; b<response["data"][a].Size(); b++){
			AddDataMe(schedList, row, 0, "");
			AddDataMe(schedList, row, 1, response["data"][a][b]["rooms_name"].GetString());
			if(!strcmp(response["data"][a][b]["rooms_status"].GetString(), "1")){
				AddDataMe(schedList, row, 2, "ON");
				schedList.SetCellColor(RGB(76,153,0), row, 2);
			}else if(!strcmp(response["data"][a][b]["rooms_status"].GetString(), "0")){
				AddDataMe(schedList, row, 2, "OFF");
				schedList.SetCellColor(RGB(255,0,0), row, 2);
			}else{
				AddDataMe(schedList, row, 2, "ERR");
				schedList.SetCellColor(RGB(255,51,255), row, 2);
			}
			
			insertData(atoi(response["data"][a][b]["floor_room_groups_id"].GetString()), atoi(response["data"][a][b]["rooms_id"].GetString()), atoi(response["data"][a][b]["floors_id"].GetString()), row); // push to stack
			row++;
			totalRow++;
		}
	}

	return totalRow;
}

BOOL ManulSwDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	list_manualSW.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
	list_manualSW.InsertColumn(0, _T("Floor"), LVCFMT_CENTER, 80);
	list_manualSW.InsertColumn(1, _T("Room"), LVCFMT_CENTER, 90);
	list_manualSW.InsertColumn(2, _T("Status"), LVCFMT_CENTER, 60);

	CString URL;
	URL.Format(_T("%sfunction=view_room_status"), urlMe);
	CStringA finalURL(URL);
	int request = thesis_request((const char *)finalURL);
	
	if(request){
		if(response["status"].GetInt()){
			PopulateScheduleMe(list_manualSW);
		}else{
			TRACE("ALERT! INVALID URL OR NO DATA!");
		}
	}else{
		TRACE("ALERT! SERVER ERROR!");
	}

	listbox_device.ResetContent();
	listbox_device.SetCheckStyle(BS_AUTOCHECKBOX);

	CFont m_font;
	m_font.CreatePointFont(90, L"Courier New");
	list_manualSW.SetFont(&m_font);
	text_timeDuration.SetFont(&m_font);
	text_roomName.SetFont(&m_font);
	listbox_device.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void ManulSwDlg::OnNMClickManualswList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	int row = list_manualSW.GetSelectionMark();

	CString URL;
	struct frg_ids ids;
	int currentRoomID;

	if(row < 0)
		return;

	CString roomName;
	roomName = list_manualSW.GetItemText(row, 1);

	if(!roomName.IsEmpty()){
		ids = searchData(row);	// search in stack. global variable
		URL.Format(_T("%sfunction=get_rd&rooms_id=%d"), urlMe, ids.rooms_id);
		TRACE(URL);
		currentRoomID = ids.rooms_id;
		CStringA finalURL(URL);

		CString itemStat("Devices of ");
		itemStat += list_manualSW.GetItemText(row, 1);
		text_roomName.SetWindowTextW(itemStat);
		//TRACE("\n%s\n", (const char*)finalURL);
		
		int request = thesis_request((const char *)finalURL);
		if(request){
			clearDevice();
			listbox_device.ResetContent();
			listbox_device.SetCheckStyle(BS_AUTOCHECKBOX);
			if(response["status"].GetInt()){
				for(int x=0; x<response["data"].Size(); x++){
					CString devName(response["data"][x]["room_devices_name"].GetString());
					listbox_device.AddString(devName);
					insertDevice(ids.rooms_id, atoi(response["data"][x]["room_devices_id"].GetString()), x);
					if(!strcmp("1", response["data"][x]["room_devices_status"].GetString())){
						listbox_device.SetCheck(x, 1);	// checked
					}else{
						listbox_device.SetCheck(x, 0);	// unchecked
					}
				}
			}
		}else{
			// should alert or something if error.
			MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
			KillTimer(9);
		}
	}else{
		listbox_device.ResetContent();
		listbox_device.SetCheckStyle(BS_AUTOCHECKBOX);
		text_roomName.SetWindowTextW(list_manualSW.GetItemText(row, 0));
	}

	*pResult = 0;
}


void ManulSwDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CString URL;
	URL.Format(_T("%sfunction=check_rooms&check_rooms_for=manual"), urlMe);
	CStringA finalURL(URL);
	int request = thesis_request((const char *)finalURL);

	if(request == 1){
		if(response["status"].GetInt()){
			if(!strcmp(response["data"][0]["check_rooms_status"].GetString(), "1")){
				list_manualSW.DeleteAllItems();
				clearData();
				ASSERT(list_manualSW.GetItemCount() == 0);
				CString URL;
				URL.Format(_T("%sfunction=view_room_status"), urlMe);
				CStringA finalURL(URL);
				thesis_request((const char *)finalURL);
				PopulateScheduleMe(list_manualSW);
			}
		}
	}else{
		TRACE("ALERT! SERVER ERROR!");
	}


	CDialogEx::OnTimer(nIDEvent);
}


void ManulSwDlg::OnBnClickedSavebtn()
{
	// TODO: Add your control notification handler code here

	CString URL;
	CStringA finalURL(URL);
	int totalRow = 0;

	CString inputDuration;
	GetDlgItemText(IDC_EDIT_INPDURATION, inputDuration);
	CStringA conInputDuration(inputDuration);
	int flag = 0;

	for(int x=0; x<inputDuration.GetLength(); x++){
		if(!std::isdigit(inputDuration[x])){
			flag=1;
			break;
		}
	}

	if(listbox_device.GetCount() > 0){
		if(!inputDuration.IsEmpty() && !flag){
			int temp_id;
			for(int x=0; x<listbox_device.GetCount(); x++){
				struct device_ids temp;
				temp = searchDevice(x);
				temp_id = temp.rooms_id;
				int status = (listbox_device.GetCheck(x)) ? 1 : 0;
				URL.Format(_T("%sfunction=set_manual_switch&rooms_id=%d&type=1&room_devices_id=%d&status=%d&duration=%d&checked=%d"), urlMe, temp.rooms_id, temp.device_id, (listbox_device.GetCheck(x) ? 1 : 0), atoi((const char*)conInputDuration), status);
				CStringA finalURL(URL);
				TRACE("\n\n\n\n");
				TRACE(URL);
				TRACE(" ****\n\n");
				int request = thesis_request((const char *)finalURL);
			}

			CString URL;
			URL.Format(_T("%sfunction=check_devices&rooms_id=%dstatus=1"), urlMe, temp_id);
			CStringA finalURL(URL);
			thesis_request((const char *)finalURL);
			CString URLMe;
			URLMe.Format(_T("%sfunction=upd_rooms&rooms_id=%d&new_rooms_status=1"), urlMe, temp_id);
			CStringA finalURLMe(URLMe);
			thesis_request((const char *)finalURLMe);
			CString URLYou;
			URLYou.Format(_T("%sfunction=set_trigger_manual&rooms_id=%d"), urlMe, temp_id);
			CStringA finalURLYou(URLYou);
			thesis_request((const char *)finalURLYou);
			MessageBoxW(_T("Successfuly updated the devices!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
		}else{
			MessageBoxW(_T("Please check devices or duration!"), _T("Error!"), MB_ICONERROR | MB_OK);
		}
		edit_inputDuration.SetWindowTextW(_T(""));
	}else{
		MessageBoxW(_T("Please check devices or duration!"), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}


void ManulSwDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if(bShow){
		SetTimer(9, 1000, NULL);
	}else{
		KillTimer(9);
	}
	
}


void ManulSwDlg::OnLbnSelchangeListboxManualsw()
{
	// TODO: Add your control notification handler code here
	TRACE("HUHU");
}
