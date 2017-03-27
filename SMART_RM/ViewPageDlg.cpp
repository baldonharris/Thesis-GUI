// ViewPageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "ViewPageDlg.h"
#include "afxdialogex.h"
#include "TransparentStatic.h"
#include "Thesis.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// CViewPageDlg dialog

IMPLEMENT_DYNAMIC(CViewPageDlg, CDialogEx)

CViewPageDlg::CViewPageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewPageDlg::IDD, pParent)
{

}

CViewPageDlg::~CViewPageDlg()
{
}

void CViewPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCHEDLIST, schedList);
	DDX_Control(pDX, IDC_SUBSCHEDLIST, subSchedList);
	DDX_Control(pDX, IDC_BUTTON_SYNCDATA, sync_data);
}


BEGIN_MESSAGE_MAP(CViewPageDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_SCHEDLIST, &CViewPageDlg::OnNMClickSchedlist)
	ON_NOTIFY(NM_KILLFOCUS, IDC_SCHEDLIST, &CViewPageDlg::OnNMKillfocusSchedlist)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_SYNCDATA, &CViewPageDlg::OnBnClickedButtonSyncdata)
END_MESSAGE_MAP()

LPWSTR convertString(const char *cs){
	size_t size = strlen(cs)+1;
	wchar_t* wtext = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, wtext, size, cs, size-1);

	return (LPWSTR)wtext;
}

static void AddData(CColorListCtrl &ctrl, int row, int col, const char *str)
{
    LVITEM lv;
    lv.iItem = row;
    lv.iSubItem = col;
    lv.pszText = convertString(str);
    lv.mask = LVIF_TEXT;
    if(col == 0)
        ctrl.InsertItem(&lv);
    else
        ctrl.SetItem(&lv);
}

static void EditData(CColorListCtrl &ctrl, int row, int col, const char *str)
{
    LVITEM lv;
    lv.iItem = row;
    lv.iSubItem = col;
    lv.pszText = convertString(str);
    lv.mask = LVIF_TEXT;
	ctrl.SetItem(&lv);
}

void RefreshColor(CColorListCtrl &ctrl){
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

CString getColumnName(CColorListCtrl &ctrl, const int columnNumber){
	TCHAR pcName[MAX_PATH];
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_TEXT;
	lvColumn.pszText = (LPTSTR)pcName;
	lvColumn.cchTextMax = MAX_PATH;

	ctrl.GetColumn(columnNumber, &lvColumn);

	return (CString)lvColumn.pszText;
}

void AddColumn(CColorListCtrl &ctrl, const char *columnName){
	int getNumberOfColumn = ctrl.GetHeaderCtrl()->GetItemCount();
	int columnNameChecker = 0;
	CString insert(columnName);

	for(int x=0; x<getNumberOfColumn; x++){
		if(!getColumnName(ctrl, x).Compare(insert)){
			columnNameChecker = 1;
			break;
		}
	}

	if(!columnNameChecker){
		ctrl.InsertColumn(getNumberOfColumn, insert, LVCFMT_CENTER, 60);
		//ctrl.AdjustColumnWidth();
	}
}

int getColumnNumber(CColorListCtrl &ctrl, const char *columnName){
	CString temp(columnName);
	int x=0;
	for(x; x<ctrl.GetColumnCount(); x++){
		if( !getColumnName(ctrl, x).Compare(temp) ){
			break;
		}
	}

	return x;
}

int PopulateSchedule(CColorListCtrl &schedList){
	int row = 0;
	int totalRow = 0;
	frg_topData = NULL;
	clearData();	// clear the stack
	for(int a=0; a<response["data"].Size(); a++){
		AddData(schedList, row, 0, response["data"][a][0]["floors_name"].GetString());
		schedList.SetRowColor(RGB(255,247,0), row);
		row++;
		for(int b=0; b<response["data"][a].Size(); b++){
			AddData(schedList, row, 0, "");
			AddData(schedList, row, 1, response["data"][a][b]["rooms_id"].GetString());
			AddData(schedList, row, 2, response["data"][a][b]["rooms_name"].GetString());
			if(!strcmp(response["data"][a][b]["rooms_status"].GetString(), "1")){
				AddData(schedList, row, 3, "ON");
				schedList.SetCellColor(RGB(76,153,0), row, 3);
			}else if(!strcmp(response["data"][a][b]["rooms_status"].GetString(), "0")){
				AddData(schedList, row, 3, "OFF");
				schedList.SetCellColor(RGB(255,0,0), row, 3);
			}else{
				AddData(schedList, row, 3, "ERR");
				schedList.SetCellColor(RGB(255,51,255), row, 3);
			}
			
			insertData(atoi(response["data"][a][b]["floor_room_groups_id"].GetString()), atoi(response["data"][a][b]["rooms_id"].GetString()), atoi(response["data"][a][b]["floors_id"].GetString()), row); // push to stack
			row++;
			totalRow++;
		}
	}

	return totalRow;
}

void populateDevices(CColorListCtrl &subSchedList){
	int getNumberOfColumn = subSchedList.GetHeaderCtrl()->GetItemCount();
	if((getNumberOfColumn-2) != 0){
		for(int x=2; x<getNumberOfColumn; x++){
			subSchedList.DeleteColumn(2); // Delete columns except Time and Day
		}
	}
	subSchedList.DeleteAllItems();
	ASSERT(subSchedList.GetItemCount() == 0);
	if(response["status"].GetInt() == 1 && response["data"].Size() > 0){
		AddColumn(subSchedList, response["data"][0][0]["room_devices_name"].GetString());
		int row = 0;
		for(int x=0; x<response["data"].Size(); x++){
			AddData(subSchedList, row, 0, response["data"][x][0]["room_schedules_day"].GetString());
			subSchedList.SetRowColor(RGB(255,247,0), row);
			row++;
			for(int y=0; y<response["data"][x].Size(); y++){
				AddColumn(subSchedList, response["data"][x][y]["room_devices_name"].GetString());
				AddData(subSchedList, row, 0, "");

				CStringA itemHour(subSchedList.GetItemText((row-1), 1));
				int columnNumberOfDevice = getColumnNumber(subSchedList, response["data"][x][y]["room_devices_name"].GetString());
						
				if(itemHour.Compare(response["data"][x][y]["room_schedules_time"].GetString())){
					AddData(subSchedList, row, 1, response["data"][x][y]["room_schedules_time"].GetString());
					//TRACE("** %d %d **\n", row, columnNumberOfDevice);
					if(!strcmp(response["data"][x][y]["room_devices_status"].GetString(), "1")){
						AddData(subSchedList, row, columnNumberOfDevice, "ON");
						subSchedList.SetCellColor(RGB(76,153,0), row, columnNumberOfDevice);
					}else{
						AddData(subSchedList, row, columnNumberOfDevice, "OFF");
						subSchedList.SetCellColor(RGB(255,0,0), row, columnNumberOfDevice);
					}
					row++;
				}else{
					if(!strcmp(response["data"][x][y]["room_devices_status"].GetString(), "1")){
						AddData(subSchedList, (row-1), columnNumberOfDevice, "ON");
						subSchedList.SetCellColor(RGB(76,153,0), (row-1), columnNumberOfDevice);
					}else{
						AddData(subSchedList, (row-1), columnNumberOfDevice, "OFF");
						subSchedList.SetCellColor(RGB(255,0,0), (row-1), columnNumberOfDevice);
					}
				}
			}
		}
		AddColumn(subSchedList, " ");
		//subSchedList.AdjustColumnWidth();
		for(int d=subSchedList.GetItemCount(); d>(row-1); --d){
			subSchedList.DeleteItem(d);
		}
	}else{
		// should alert or something if status != 1
		AddData(subSchedList, 0, 1, (const char *)"No data.");
	}
}

void checkDevices(CColorListCtrl &subSchedList){
	int getNumberOfColumn = subSchedList.GetHeaderCtrl()->GetItemCount();

	int counterSize=0;
	for(int x=0; x<response["data"].Size(); x++){
		counterSize += response["data"][x].Size();
	}
	
	int counterOfStatus = 0;
	for(int x=0; x<subSchedList.GetItemCount(); x++){
		for(int y=0; y<getNumberOfColumn; y++){
			if(!subSchedList.GetItemText(x, y).Compare(_T("ON")) || !subSchedList.GetItemText(x, y).Compare(_T("OFF"))){
				counterOfStatus += 1;
			}
		}
	}

	if((counterOfStatus-counterSize) != 0){
		populateDevices(subSchedList);
	}
}

// CViewPageDlg message handlers
BOOL CViewPageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString URL;
	totalRow = 0; // global, declared in ViewPageDlg.h
	showCounter = 0; // global, declared in ViewPageDlg.h

	schedList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
	//subSchedList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	subSchedList.InsertColumn(0, _T("Day"), LVCFMT_CENTER, 60);
	subSchedList.InsertColumn(1, _T("Time"), LVCFMT_CENTER, 100);

	schedList.InsertColumn(0, _T("Floor"), LVCFMT_CENTER, 65);
	schedList.InsertColumn(1, _T("ID"), LVCFMT_CENTER, 40);
	schedList.InsertColumn(2, _T("Room"), LVCFMT_CENTER, 80);
	schedList.InsertColumn(3, _T("Status"), LVCFMT_CENTER, 55);

	URL.Format(_T("%sfunction=view_room_status"), urlMe);
	CStringA finalURL(URL);
	
	int request = thesis_request((const char*)finalURL);
	if(request == 1){
		if(response["status"].GetInt() == 1){
			totalRow = PopulateSchedule(schedList);
		}else{
			// should alert or something if status != 1
			TRACE("ALERT! INVALID URL OR NO DATA!");
		}
	}else{
		// should alert or something if error.
	}

	CFont m_font;
	m_font.CreatePointFont(90, L"Courier New");
	schedList.SetFont(&m_font);
	subSchedList.SetFont(&m_font);

	return TRUE;
}

void CViewPageDlg::OnTimer(UINT_PTR nIDEvent)  
{
	if(nIDEvent == 1){
		//TRACE("** EVENT: %d **\n", nIDEvent);
		CString URL;
		URL.Format(_T("%sfunction=check_rooms&check_rooms_for=view"), urlMe);
		CStringA finalURL(URL);
		int request = thesis_request((const char *)finalURL);

		if(request == 1){
			if(response["status"].GetInt()){
				if(!strcmp(response["data"][0]["check_rooms_status"].GetString(), "1")){
					schedList.DeleteAllItems();
					clearData();
					ASSERT(schedList.GetItemCount() == 0);
					CString URL;
					URL.Format(_T("%sfunction=view_room_status"), urlMe);
					CStringA finalURL(URL);
					thesis_request((const char *)finalURL);
					totalRow = PopulateSchedule(schedList);
				}
			}
		}else{
			TRACE("ALERT! SERVER ERROR!");
			MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		CString URL;
		URL.Format(_T("%sfunction=check_devices&rooms_id=%d"), urlMe, ids.rooms_id);
		CStringA finalURL(URL);
		int request = thesis_request((const char *)finalURL);

		if(request){
			if(response["status"].GetInt()){
				if(response["data"].Size() > 0){
					CString URL;
					URL.Format(_T("%sfunction=view_ras&rooms_id=%d"), urlMe, ids.rooms_id);
					CStringA finalURL(URL);
					int request = thesis_request((const char *)finalURL);
					populateDevices(subSchedList);
				}
			}
		}else{
			// should alert or something if error.
			TRACE("ALERT! SERVER ERROR!");
		}
	}
}

void CViewPageDlg::OnNMClickSchedlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	KillTimer(1);
	int row = schedList.GetSelectionMark();

	CString URL;

	if(row < 0)
		return;

	CString roomName;
	roomName = schedList.GetItemText(row, 1);
	roomNameHolder.Format(_T("Room: %s"), schedList.GetItemText(row, 1));	// global variable

	if(!roomName.IsEmpty()){
		sync_data.EnableWindow(true);
		ids = searchData(row);	// search in stack. global variable
		URL.Format(_T("%sfunction=view_ras&rooms_id=%d&room_schedules_type=0"), urlMe, ids.rooms_id);
		currentRoomID = ids.rooms_id;
		CStringA finalURL(URL);
		TRACE(URL);
		
		int request = thesis_request((const char *)finalURL);
		if(request){
			populateDevices(subSchedList);
		}else{
			// should alert or something if error.
			TRACE("ALERT! SERVER ERROR!");
			MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
			KillTimer(1);
			KillTimer(2);
		}
	}else{
		sync_data.EnableWindow(false);
	}

	SetTimer(1, 1000, NULL);

	*pResult = 0;
}


void CViewPageDlg::OnNMKillfocusSchedlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


void CViewPageDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if(showCounter < 2){
		showCounter++;
	}else{
		if(bShow){
			SetTimer(1, 1000, NULL);	// for schedList
			SetTimer(2, 1500, NULL);	// for subSchedList
			sync_data.EnableWindow(false);
		}

		if(!bShow){
			int getNumberOfColumn = subSchedList.GetHeaderCtrl()->GetItemCount();
			if((getNumberOfColumn-2) != 0){
				for(int x=2; x<getNumberOfColumn; x++){
					subSchedList.DeleteColumn(2); // Delete columns except Time and Day
				}
			}
			subSchedList.DeleteAllItems();
			KillTimer(1);
			KillTimer(2);
		}
	}
}


void CViewPageDlg::OnBnClickedButtonSyncdata()
{
	// TODO: Add your control notification handler code here
	CString URL;
	URL.Format(_T("%sfunction=sync_data&rooms_id=%d"), urlMe, ids.rooms_id);
	CStringA finalURL(URL);
	int request = thesis_request((const char *)finalURL);
}
