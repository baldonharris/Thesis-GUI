// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// ConfigDlg dialog

IMPLEMENT_DYNAMIC(ConfigDlg, CDialogEx)

ConfigDlg::ConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ConfigDlg::IDD, pParent)
{

}

ConfigDlg::~ConfigDlg()
{
}

void ConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FLOORNME, edit_floorname);
	DDX_Control(pDX, IDC_BUTTON_ADDFLR, btn_add_floor);
	DDX_Control(pDX, IDC_COMBO_UPD_DEL, combo_updel);
	DDX_Control(pDX, IDC_LIST_FLOORS, list_floors);
	DDX_Control(pDX, IDC_STATIC_NEWFLRNME, static_flrname);
	DDX_Control(pDX, IDC_EDIT_NEWFLRNME, edit_newflrname);
	DDX_Control(pDX, IDC_BUTTON_DELFLR, btn_delflr);
	DDX_Control(pDX, IDC_BUTTON_SAVENEWFLRNME, btn_newflrnme);
	DDX_Control(pDX, IDC_STATIC_CUR_PASS, static_cur_password);
	DDX_Control(pDX, IDC_STATIC_NEW_PASS, static_new_password);
	DDX_Control(pDX, IDC_STATIC_CONFNEW_PASS, static_confnew_password);
	DDX_Control(pDX, IDC_EDIT_CUR_PASS, edit_cur_password);
	DDX_Control(pDX, IDC_EDIT_NEW_PASS, edit_new_password);
	DDX_Control(pDX, IDC_EDIT_CONFNEW_PASS, edit_confnew_password);
	DDX_Control(pDX, IDC_STATIC_NEWPANID, static_new_panid);
	DDX_Control(pDX, IDC_STATIC_CURPASSWORD, static_curpassword);
	DDX_Control(pDX, IDC_EDIT_PANID, edit_new_panid);
	DDX_Control(pDX, IDC_EDIT_CURPASSWORD, edit_panid_password);
}


BEGIN_MESSAGE_MAP(ConfigDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_UPD_DEL, &ConfigDlg::OnCbnSelchangeComboUpdDel)
	ON_BN_CLICKED(IDC_BUTTON_ADDFLR, &ConfigDlg::OnBnClickedButtonAddflr)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FLOORS, &ConfigDlg::OnNMClickListFloors)
	ON_BN_CLICKED(IDC_BUTTON_SAVENEWFLRNME, &ConfigDlg::OnBnClickedButtonSavenewflrnme)
	ON_BN_CLICKED(IDC_BUTTON_DELFLR, &ConfigDlg::OnBnClickedButtonDelflr)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_PASS, &ConfigDlg::OnBnClickedButtonSavePass)
	ON_BN_CLICKED(IDC_BUTTON_CHANGEPANID, &ConfigDlg::OnBnClickedButtonChangepanid)
END_MESSAGE_MAP()


// ConfigDlg message handlers
LPWSTR convertStringFloor(const char *cs){
	size_t size = strlen(cs)+1;
	wchar_t* wtext = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, wtext, size, cs, size-1);

	return (LPWSTR)wtext;
}

static void AddFloor(CColorListCtrl &ctrl, int row, int col, const char *str)
{
    LVITEM lv;
    lv.iItem = row;
    lv.iSubItem = col;
    lv.pszText = convertStringFloor(str);
    lv.mask = LVIF_TEXT;
    if(col == 0)
        ctrl.InsertItem(&lv);
    else
        ctrl.SetItem(&lv);
}


void ConfigDlg::populateFloors(int mode){
	CString URL;
	URL.Format(_T("%sfunction=get_floor"), urlMe);
	CStringA finalURL(URL);

	int request = thesis_request((const char *)finalURL);

	if(request){
		if(response["status"].GetInt()){
			if(mode){	
				if(response["data"].Size() != list_floors.GetItemCount()){
					list_floors.DeleteAllItems();
					for(int x=0; x<response["data"].Size(); x++){
						AddFloor(list_floors, x, 0, response["data"][x]["floors_name"].GetString());
					}
				}
			}else{
				TRACE("PLEASE");
				list_floors.DeleteAllItems();
				for(int x=0; x<response["data"].Size(); x++){
					AddFloor(list_floors, x, 0, response["data"][x]["floors_name"].GetString());
				}
			}
		}
	}else{
		KillTimer(1);
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}


void ConfigDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if(bShow){
		SetTimer(1, 1000, NULL);
		populateFloors(1);
	}else{
		KillTimer(1);
	}
}


BOOL ConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CFont m_font;
	m_font.CreatePointFont(90, L"Courier New");
	list_floors.SetFont(&m_font);
	static_cur_password.SetFont(&m_font);
	static_new_password.SetFont(&m_font);
	static_confnew_password.SetFont(&m_font);
	static_new_panid.SetFont(&m_font);
	static_curpassword.SetFont(&m_font);

	combo_updel.SetCurSel(0);
	btn_delflr.EnableWindow(FALSE);

	list_floors.InsertColumn(0, _T("Floor"), LVCFMT_CENTER, 110);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void ConfigDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	populateFloors(1);
	CDialogEx::OnTimer(nIDEvent);
}


void ConfigDlg::OnCbnSelchangeComboUpdDel()
{
	// TODO: Add your control notification handler code here
	btn_delflr.EnableWindow(combo_updel.GetCurSel());
	btn_newflrnme.EnableWindow(!combo_updel.GetCurSel());
	edit_newflrname.EnableWindow(!combo_updel.GetCurSel());
}


void ConfigDlg::OnBnClickedButtonAddflr()
{
	// TODO: Add your control notification handler code here
	CString floor_name;
	edit_floorname.GetWindowTextW(floor_name);
	floor_name.Replace(_T(" "), _T("-"));

	if(!floor_name.IsEmpty()){
		CString URL;
		URL.Format(_T("%sfunction=add_floor&floors_name=%s"), urlMe, floor_name);
		CStringA finalURL(URL);

		int request = thesis_request((const char *)finalURL);

		if(request){
			if(response["status"].GetInt()){
				MessageBoxW(_T("Floor has been added successfuly!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
			}else{
				MessageBoxW(_T("Internal Server Error!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
			}
		}else{
			MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		MessageBoxW(_T("Floor name should not be empty!"), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}


void ConfigDlg::OnNMClickListFloors(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	int row = list_floors.GetSelectionMark();
	clickedRow = row;
	edit_newflrname.SetWindowTextW(list_floors.GetItemText(row, 0));
	*pResult = 0;
}


void ConfigDlg::OnBnClickedButtonSavenewflrnme()
{
	// TODO: Add your control notification handler code here
	CString newflrname;
	CString curflrname;
	edit_newflrname.GetWindowTextW(newflrname);
	curflrname = list_floors.GetItemText(clickedRow, 0);

	newflrname.Replace(_T(" "), _T("-"));
	curflrname.Replace(_T(" "), _T("-"));

	if(!curflrname.Compare(newflrname)){
		MessageBoxW(_T("No changes has been made!"), _T("Error!"), MB_ICONERROR | MB_OK);
	}else{
		CString URL;
		URL.Format(_T("%sfunction=upd_floor&floors_name=%s&new_floors_name=%s"), urlMe, curflrname, newflrname);
		CStringA finalURL(URL);
		TRACE(URL);

		int request = thesis_request((const char *)finalURL);
		if(request){
			if(response["status"].GetInt() == 1){
				populateFloors(0);
				MessageBoxW(_T("Success!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
			}else if(response["status"].GetInt() == -1){
				MessageBoxW(_T("No changes has been mades!"), _T("Error!"), MB_ICONERROR | MB_OK);
			}else{
				MessageBoxW(_T("Internal Server Error!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
			}
		}else{
			MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}
}


void ConfigDlg::OnBnClickedButtonDelflr()
{
	// TODO: Add your control notification handler code here
	CString curflrname;
	curflrname = list_floors.GetItemText(clickedRow, 0);
	curflrname.Replace(_T(" "), _T("-"));

	CString URL;
	URL.Format(_T("%sfunction=del_floor&floors_name=%s"), urlMe, curflrname);
	CStringA finalURL(URL);
	TRACE(URL);
	int request = thesis_request((const char *)finalURL);
	if(request){
		if(response["status"].GetInt() == 1){
			populateFloors(0);
			MessageBoxW(_T("Success!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
		}else if(response["status"].GetInt() == -1){
			MessageBoxW(_T("No changes has been mades!"), _T("Error!"), MB_ICONERROR | MB_OK);
		}else{
			MessageBoxW(_T("Internal Server Error!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}


void ConfigDlg::OnBnClickedButtonSavePass()
{
	// TODO: Add your control notification handler code here
	CString cur_pass;

	edit_cur_password.GetWindowTextW(cur_pass);

	CString URL;
	URL.Format(_T("%sfunction=get_auth&password=%s"), urlMe, cur_pass);
	CStringA finalURL(URL);

	int request = thesis_request((const char *)finalURL);
	if(request){
		if(response["status"].GetInt()){
			CString new_pass, conf_pass;

			edit_new_password.GetWindowTextW(new_pass);
			edit_confnew_password.GetWindowTextW(conf_pass);

			if(!new_pass.Compare(conf_pass)){
				CString URL;
				URL.Format(_T("%sfunction=upd_auth&new_pass=%s&cur_pass=%s"), urlMe, new_pass, cur_pass);
				CStringA finalURL(URL);

				int request = thesis_request((const char *)finalURL);
				if(request){
					if(response["status"].GetInt()){
						MessageBoxW(_T("Success!\nPlease use new password for the next login."), _T("Success!"), MB_ICONASTERISK | MB_OK);
						edit_cur_password.SetWindowTextW(_T(""));
						edit_new_password.SetWindowTextW(_T(""));
						edit_confnew_password.SetWindowTextW(_T(""));
					}else{
						MessageBoxW(_T("Internal Server Error!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
					}
				}else{
					MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
				}
			}else{
				MessageBoxW(_T("New password does not match!"), _T("Error!"), MB_ICONERROR | MB_OK);
			}
		}else{
			MessageBoxW(_T("Wrong password, please try again!"), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}


void ConfigDlg::OnBnClickedButtonChangepanid()
{
	// TODO: Add your control notification handler code here
	CString password, pan_id;

	edit_new_panid.GetWindowTextW(pan_id);
	edit_panid_password.GetWindowTextW(password);

	CString URL;
	URL.Format(_T("%sfunction=get_auth&password=%s"), urlMe, password);
	CStringA finalURL(URL);

	int request = thesis_request((const char *)finalURL);
	if(request){
		if(response["status"].GetInt()){
			CString URL;
			URL.Format(_T("%sfunction=upd_pan_id&cur_pass=%s&new_pan_id=%s"), urlMe, password, pan_id);
			CStringA finalURL(URL);

			int request = thesis_request((const char *)finalURL);
			if(request){
				if(response["status"].GetInt()){
					MessageBoxW(_T("Success!\nPlease restart the application!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
				}else{
					MessageBoxW(_T("Internal Server Error!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
				}
			}else{
				MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
			}
		}else{
			MessageBoxW(_T("Wrong password, please try again!"), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}
}
