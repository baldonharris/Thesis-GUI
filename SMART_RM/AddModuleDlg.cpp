// AddModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "AddModuleDlg.h"
#include "afxdialogex.h"
#include "Thesis.h"


// AddModuleDlg dialog

IMPLEMENT_DYNAMIC(AddModuleDlg, CDialogEx)

AddModuleDlg::AddModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddModuleDlg::IDD, pParent)
{

}

AddModuleDlg::~AddModuleDlg()
{
}

void AddModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDMOD_MAC_ADDRESS, static_room_mac_address);
	DDX_Control(pDX, IDC_ADDMOD_ROOMNAME, static_room_name);
	DDX_Control(pDX, IDC_ROOM_NAME, edit_roomName);
	DDX_Control(pDX, IDC_MAC_ONE, edit_mac_one);
	DDX_Control(pDX, IDC_MAC_TWO, edit_mac_two);
	DDX_Control(pDX, IDC_MAC_THREE, edit_mac_three);
	DDX_Control(pDX, IDC_MAC_FOUR, edit_mac_four);
	DDX_Control(pDX, IDC_MAC_FIVE, edit_mac_five);
	DDX_Control(pDX, IDC_MAC_SIX, edit_mac_six);
	DDX_Control(pDX, IDC_MAC_SEVEN, edit_mac_seven);
	DDX_Control(pDX, IDC_MAC_EIGHT, edit_mac_eight);
	DDX_Control(pDX, IDC_STATIC_FLOOR, static_floor);
	DDX_Control(pDX, IDC_COMBO_FLOOR, combo_floor);
	DDX_Control(pDX, IDC_LIST_PORTS, list_ports);
	DDX_Control(pDX, IDC_STATIC_RMPORTS, static_rmports);
	DDX_Control(pDX, IDC_EDIT_DEVICENME, edit_device_name);
	DDX_Control(pDX, IDC_STATIC_DEVICENME, static_device_name);
	DDX_Control(pDX, IDC_STATIC_GRP_PORTS, static_room_ports_grp);
	DDX_Control(pDX, IDC_STATIC_RMDET_GRP, static_rmdet_grp);
	DDX_Control(pDX, IDC_BUTTON_ADDROOM, btn_addroomwosched);
}


BEGIN_MESSAGE_MAP(AddModuleDlg, CDialogEx)
//	ON_WM_TIMER()
	ON_EN_MAXTEXT(IDC_MAC_ONE, &AddModuleDlg::OnEnMaxtextMacOne)
	ON_EN_MAXTEXT(IDC_MAC_TWO, &AddModuleDlg::OnEnMaxtextMacTwo)
	ON_EN_MAXTEXT(IDC_MAC_THREE, &AddModuleDlg::OnEnMaxtextMacThree)
	ON_EN_MAXTEXT(IDC_MAC_FOUR, &AddModuleDlg::OnEnMaxtextMacFour)
	ON_EN_MAXTEXT(IDC_MAC_FIVE, &AddModuleDlg::OnEnMaxtextMacFive)
	ON_EN_MAXTEXT(IDC_MAC_SIX, &AddModuleDlg::OnEnMaxtextMacSix)
	ON_EN_MAXTEXT(IDC_MAC_SEVEN, &AddModuleDlg::OnEnMaxtextMacSeven)
ON_LBN_SELCHANGE(IDC_LIST_PORTS, &AddModuleDlg::OnLbnSelchangeListPorts)
ON_EN_KILLFOCUS(IDC_EDIT_DEVICENME, &AddModuleDlg::OnEnKillfocusEditDevicenme)
ON_BN_CLICKED(IDC_BUTTON_ADDROOM, &AddModuleDlg::OnBnClickedButtonAddroom)
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// AddModuleDlg message handlers


BOOL AddModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	edit_mac_one.SetLimitText(2);
	edit_mac_two.SetLimitText(2);
	edit_mac_three.SetLimitText(2);
	edit_mac_four.SetLimitText(2);
	edit_mac_five.SetLimitText(2);
	edit_mac_six.SetLimitText(2);
	edit_mac_seven.SetLimitText(2);
	edit_mac_eight.SetLimitText(2);

	CFont m_font;
	m_font.CreatePointFont(90, L"Courier New");
	static_room_mac_address.SetFont(&m_font);
	static_room_name.SetFont(&m_font);
	static_floor.SetFont(&m_font);
	static_rmports.SetFont(&m_font);
	list_ports.SetFont(&m_font);
	static_device_name.SetFont(&m_font);
	static_room_ports_grp.SetFont(&m_font);
	static_rmdet_grp.SetFont(&m_font);

	int row=0;
	for(char letter='A'; letter<='D'; letter++, row++){
		CString empty("");
		CString port;
		port.Format(_T("Port %c"), letter);
		list_ports.AddString(port);
		list_ports.SetCheck(row, 0);
	}

	combo_floor.SetCurSel(0);

	edit_device_name.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void AddModuleDlg::OnEnMaxtextMacOne()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_MAC_TWO));
}


void AddModuleDlg::OnEnMaxtextMacTwo()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_MAC_THREE));
}


void AddModuleDlg::OnEnMaxtextMacThree()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_MAC_FOUR));
}


void AddModuleDlg::OnEnMaxtextMacFour()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_MAC_FIVE));
}


void AddModuleDlg::OnEnMaxtextMacFive()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_MAC_SIX));
}


void AddModuleDlg::OnEnMaxtextMacSix()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_MAC_SEVEN));
}


void AddModuleDlg::OnEnMaxtextMacSeven()
{
	// TODO: Add your control notification handler code here
	GotoDlgCtrl(GetDlgItem(IDC_MAC_EIGHT));
}


void AddModuleDlg::OnLbnSelchangeListPorts()
{
	// TODO: Add your control notification handler code here
	port_index = list_ports.GetCurSel(); // global variable
	edit_device_name.SetWindowTextW(_T(""));
	CString portName;
	list_ports.GetText(port_index, portName);
	static_device_name.SetWindowTextW(_T("Device for ")+portName);
	
	if(list_ports.GetCheck(port_index) == 0){
		edit_device_name.EnableWindow(FALSE);
	}else{
		edit_device_name.EnableWindow(TRUE);
		edit_device_name.SetWindowTextW(devicesNames[port_index]);
	}
}


void AddModuleDlg::OnEnKillfocusEditDevicenme()
{
	// TODO: Add your control notification handler code here
	int index = port_index;	// port_index is global
	CString deviceName;
	GetDlgItemText(IDC_EDIT_DEVICENME, deviceName);

	int diPwede=0;
	for(int x=0; x<list_ports.GetCount(); x++){
		if(!deviceName.Compare(devicesNames[x])){
			diPwede++;
			break;
		}
	}

	if(diPwede){
		MessageBoxW(_T("Existing device!"), _T("Error!"), MB_ICONERROR | MB_OK);
	}else{
		devicesNames[index] = deviceName;
	}
}

void AddModuleDlg::clearControls(){
	combo_floor.SetCurSel(0);
	edit_roomName.SetWindowTextW(_T(""));
	edit_mac_one.SetWindowTextW(_T(""));
	edit_mac_two.SetWindowTextW(_T(""));
	edit_mac_three.SetWindowTextW(_T(""));
	edit_mac_four.SetWindowTextW(_T(""));
	edit_mac_five.SetWindowTextW(_T(""));
	edit_mac_six.SetWindowTextW(_T(""));
	edit_mac_seven.SetWindowTextW(_T(""));
	edit_mac_eight.SetWindowTextW(_T(""));
	
	edit_device_name.SetWindowTextW(_T(""));
	for(int x=0; x<list_ports.GetCount(); x++){
		list_ports.SetCheck(x, 0);
		devicesNames[x] = "";
	}

	combo_floor.SetCurSel(0);

	edit_device_name.EnableWindow(FALSE);

	btn_addroomwosched.EnableWindow(TRUE);
}

void AddModuleDlg::OnBnClickedButtonAddroom()
{
	// TODO: Add your control notification handler code here
	int emptyCounter = 0;
	CString mac[8];
	CString toPass_floor, toPass_roomName, toPass_mac(""), toPass_portsName, toPass_deviceName;

	combo_floor.GetLBText(combo_floor.GetCurSel(), toPass_floor);
	edit_roomName.GetWindowTextW(toPass_roomName);
	edit_mac_one.GetWindowTextW(mac[0]);
	edit_mac_two.GetWindowTextW(mac[1]);
	edit_mac_three.GetWindowTextW(mac[2]);
	edit_mac_four.GetWindowTextW(mac[3]);
	edit_mac_five.GetWindowTextW(mac[4]);
	edit_mac_six.GetWindowTextW(mac[5]);
	edit_mac_seven.GetWindowTextW(mac[6]);
	edit_mac_eight.GetWindowTextW(mac[7]);

	emptyCounter += (toPass_roomName.IsEmpty()) ? 1 : 0;

	for(int x=0; x<8; x++){
		emptyCounter += (mac[x].IsEmpty()) ? 1 : 0;
		if(mac[x].GetLength() == 1){
			emptyCounter += 1;
		}
	}

	CString tempPort[100];
	CString tempDevice[100];

	int counter = 0;
	for(int x=0; x<list_ports.GetCount(); x++){
		if(list_ports.GetCheck(x) == 1){
			if(devicesNames[x].IsEmpty()){
				emptyCounter += 1;
			}else{
				tempDevice[counter] = devicesNames[x];
				list_ports.GetText(x, tempPort[counter]);
				counter++;
			}
		}
	}

	if(emptyCounter > 0){
		MessageBoxW(_T("A field is empty or incorrect!"), _T("Error!"), MB_ICONERROR | MB_OK);
	}

	if(emptyCounter == 0){
		for(int x=0; x<counter; x++){
			if((x+1) != counter){
				toPass_portsName += tempPort[x];
				toPass_portsName += ",";
				toPass_deviceName += tempDevice[x];
				toPass_deviceName += ",";
			}else{
				toPass_portsName += tempPort[x];
				toPass_deviceName += tempDevice[x];
			}
		}

		for(int x=0; x<8; x++){
			if((x+1) != 8){
				toPass_mac += mac[x];
				toPass_mac += " ";
			}else{
				toPass_mac += mac[x];
			}
		}

		CString dash("-");
		toPass_floor.Replace(_T(" "), dash);
		toPass_mac.Replace(_T(" "), dash);
		toPass_roomName.Replace(_T(" "), dash);
		toPass_mac.Replace(_T(" "), dash);
		toPass_portsName.Replace(_T(" "), dash);
		toPass_deviceName.Replace(_T(" "), dash);

		CString URL;
		URL.Format(_T("%sfunction=add_room_module&floors_name=%s&rooms_name=%s&rooms_address=%s&rooms_port=%d&rooms_status=%d&room_devices=%s&room_devices_port=%s"), urlMe, toPass_floor,		toPass_roomName, toPass_mac, 9, 0, toPass_deviceName, toPass_portsName);
		CStringA finalURL(URL);
		TRACE(URL);
		int request = thesis_request((const char *)finalURL);
		if(request){
			if(response["status"].GetInt()){
				MessageBoxW(_T("Room is successfully added!"), _T("Success!"), MB_ICONASTERISK | MB_OK);
				clearControls();
			}else{
				MessageBoxW(_T("Please check your fields!"), _T("Error!"), MB_ICONERROR | MB_OK);
			}
		}else{
			MessageBoxW(_T("Server error!\nPlease contact administrator!"), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}
}

void AddModuleDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	CString URL;
	URL.Format(_T("%sfunction=get_floor"), urlMe);
	CStringA finalURL(URL);

	int request = thesis_request((const char *)finalURL);

	if(request){
		if(response["status"].GetInt()){
			combo_floor.ResetContent();
			for(int x=0; x<response["data"].Size(); x++){
				CString floor(response["data"][x]["floors_name"].GetString());
				combo_floor.AddString(floor);
			}
			combo_floor.SetCurSel(0);
		}
	}
}