
// SMART_RMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMART_RM.h"
#include "SMART_RMDlg.h"
#include "afxdialogex.h"
#include "ViewPageDlg.h"
#include "ManulSwDlg.h"
#include "EditSchedDlg.h"
#include "AddModuleDlg.h"
#include "ConfigDlg.h"
#include "AboutDlg.h"
#include "ConsumptionDlg.h"
#include "EditSchedule.h"
#include "HostDlg.h"
#include "Thesis.h"
#include <iostream>
#include <sstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CViewPageDlg p_view;
ManulSwDlg  p_manual_sw;
EditSchedDlg p_edit_sched;
AddModuleDlg p_add_module;
ConfigDlg p_config;
AboutDlg p_about;
ConsumptionDlg p_consumption;
EditSchedule p_edit_schedule;
int login;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSMART_RMDlg dialog



CSMART_RMDlg::CSMART_RMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSMART_RMDlg::IDD, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Instantiate and initialize the background brush to black.
	m_pEditBkBrush = new CBrush(RGB(0, 0, 0));

	m_pass = _T("");
}

void CSMART_RMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, img_btnhome, m_home);
	DDX_Control(pDX, input_password, input_pass);
	DDX_Text(pDX, input_password, m_pass);
	DDV_MaxChars(pDX, m_pass, 100);
	DDX_Control(pDX, auth_msg, m_auth_msg);
	DDX_Control(pDX, login_button, m_login);
	DDX_Control(pDX, IDC_STATIC_PANID, static_pan_id);
}

BEGIN_MESSAGE_MAP(CSMART_RMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btn_logout, &CSMART_RMDlg::OnBnClickedlogout)
	ON_BN_CLICKED(btn_settings, &CSMART_RMDlg::OnBnClickedsettings)
	ON_BN_CLICKED(btn_help, &CSMART_RMDlg::OnBnClickedhelp)
	ON_BN_CLICKED(btn_home, &CSMART_RMDlg::OnBnClickedhome)
	ON_BN_CLICKED(btn_view, &CSMART_RMDlg::OnBnClickedview)
	ON_BN_CLICKED(btn_manage, &CSMART_RMDlg::OnBnClickedmanage)
	ON_BN_CLICKED(login_button, &CSMART_RMDlg::OnBnClickedbutton)
	ON_EN_CHANGE(input_password, &CSMART_RMDlg::OnEnChangepassword)
	ON_BN_CLICKED(btn_manual_sw, &CSMART_RMDlg::OnBnClickedmanualsw)
	ON_BN_CLICKED(btn_edit_sched, &CSMART_RMDlg::OnBnClickededitsched)
	ON_BN_CLICKED(btn_add_room, &CSMART_RMDlg::OnBnClickedaddroom)
	ON_BN_CLICKED(btn_consumption, &CSMART_RMDlg::OnBnClickedconsumption)
	ON_BN_CLICKED(btn_edit_schedule, &CSMART_RMDlg::OnBnClickededitschedule)
	ON_BN_CLICKED(btn_thumb_manage, &CSMART_RMDlg::OnBnClickedthumbmanage)
END_MESSAGE_MAP()


// CSMART_RMDlg message handlers

BOOL CSMART_RMDlg::OnInitDialog()
{
	HostDlg dlg;
	dlg.DoModal();

	CDialogEx::OnInitDialog();
	//assign bmp to buttons

	CBitmap bmp_thumb_add,bmp_thumb_sched,bmp_thumb_room,bmp_thumb_manual,bmp_thumb_manage,bmp_thumb_view,bmp_manage_room,bmp_consumption,bmp_help,bmp_settings,bmp_logout,bmp_manage,bmp_view,bmp_home,bmp_manual_sw,bmp_edit_sched,bmp_manage_room_module;
	//btn_consumption
	bmp_consumption.LoadBitmap( IDB_btn_consumption );
	CButton* pButton = (CButton* )GetDlgItem(btn_consumption);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_consumption);	
	//btn_help
	bmp_help.LoadBitmap( IDB_btn_help );
	pButton = (CButton* )GetDlgItem(btn_help);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_help);
	//btn_settings
	bmp_settings.LoadBitmap( IDB_btn_settings );
	pButton = (CButton* )GetDlgItem(btn_settings);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_settings);
	//btn_logout
	bmp_logout.LoadBitmap( IDB_btn_logout );
	pButton = (CButton* )GetDlgItem(btn_logout);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_logout);
	//btn_manage
	bmp_manage.LoadBitmap( IDB_btn_manage );
	pButton = (CButton* )GetDlgItem(btn_manage);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_manage);
	//btn_view
	bmp_view.LoadBitmap( IDB_btn_view );
	pButton = (CButton* )GetDlgItem(btn_view);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_view);
	//btn_manual_sw
	bmp_manual_sw.LoadBitmap( IDB_btn_manual_sw );
	pButton = (CButton* )GetDlgItem(btn_manual_sw);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_manual_sw);	
	//btn_home
	bmp_home.LoadBitmap( IDB_btn_home );
	pButton = (CButton* )GetDlgItem(btn_home);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_home);

	//btn_edit_schededule
	bmp_edit_sched.LoadBitmap( IDB_btn_manage_sched );
	pButton = (CButton* )GetDlgItem(btn_edit_schedule);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_edit_sched);
	
	//btn_manage_room
	bmp_manage_room.LoadBitmap( IDB_btn_manage_room );
	pButton = (CButton* )GetDlgItem(btn_edit_sched);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_manage_room);

	//btn_manage_room_module
	bmp_manage_room_module.LoadBitmap( IDB_manage_room_module );
	pButton = (CButton* )GetDlgItem(btn_add_room);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_manage_room_module);

	//thumb_view
	bmp_thumb_view.LoadBitmap( IDB_thumb_view );
	pButton = (CButton* )GetDlgItem(btn_thumb_view);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_thumb_view);

	//thumb_manage
	bmp_thumb_manage.LoadBitmap( IDB_thumb_manage );
	pButton = (CButton* )GetDlgItem(btn_thumb_manage);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_thumb_manage);

	//thumb_manual
	bmp_thumb_manual.LoadBitmap( IDB_thumb_manual );
	pButton = (CButton* )GetDlgItem(btn_thumb_manual);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_thumb_manual);

	//thumb_room
	bmp_thumb_room.LoadBitmap( IDB_thumb_room );
	pButton = (CButton* )GetDlgItem(btn_thumb_room);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_thumb_room);

	//thumb_sched
	bmp_thumb_sched.LoadBitmap( IDB_thumb_sched );
	pButton = (CButton* )GetDlgItem(btn_thumb_sched);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_thumb_sched);

	//thumb_add
	bmp_thumb_add.LoadBitmap( IDB_thumb_add );
	pButton = (CButton* )GetDlgItem(btn_thumb_add);
	pButton->ModifyStyle(0,BS_BITMAP);
	pButton->SetBitmap(bmp_thumb_add);



	//child
		//VIEW 
		login = 0;
		CFont m_font;
		m_font.CreatePointFont(90, L"Courier New");
		static_pan_id.SetFont(&m_font);
		static_pan_id.ShowWindow(FALSE);

		p_view.Create( IDD_VIEW_PAGE, this );
		p_manual_sw.Create(IDD_MANUAL_SW, this);
		p_edit_sched.Create(IDD_EDIT_SCHED, this);
		p_add_module.Create(IDD_ADD_MODULE, this);
		p_config.Create(IDD_CONFIG, this);
		p_about.Create(IDD_ABOUT, this);
		p_consumption.Create(IDD_CONSUMPTION, this);
		p_edit_schedule.Create(IDD_EDIT_SCHEDULE, this);
		p_config.ShowWindow(FALSE);
	    p_view.ShowWindow(FALSE);
		p_manual_sw.ShowWindow(FALSE);
		p_edit_sched.ShowWindow(FALSE);
		p_add_module.ShowWindow(FALSE);
		p_about.ShowWindow(FALSE);
		p_edit_schedule.ShowWindow(FALSE);
		logouthide();
		//change font style password
		CFont *myFont = new CFont();
		myFont->CreateFont( 37, 0, 0, 0, FW_HEAVY, true, false, //bold , italc (true false)
        0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        FIXED_PITCH|FF_MODERN, _T("Courier New") );
		input_pass.SetFont(myFont);
		//change bgcolor password
		CEdit *m_ctrlEditOne = (CEdit*) GetDlgItem(input_password);
		CDC *m_ctrlEEditWee = m_ctrlEditOne->GetDC();
		m_ctrlEEditWee->SetBkColor(TRANSPARENT);
		   
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	int request = thesis_request((const char *)(CStringA)urlMe);
	if(!request){
		m_auth_msg.SetWindowTextW(L"Please contact Admin");
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
		ASSERT(AfxGetMainWnd() != NULL);
        AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}

	//HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	//SetIcon(hIcon, TRUE);
	//SetIcon(hIcon, FALSE);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSMART_RMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSMART_RMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSMART_RMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSMART_RMDlg::OnBnClickedlogout()
{
	// TODO: Add your control notification handler code here
	logouthide();
	ChangeDefaultButton();
	login=0;
	p_view.ShowWindow(FALSE);
	p_manual_sw.ShowWindow(FALSE);
	p_edit_sched.ShowWindow(FALSE);
	p_add_module.ShowWindow(FALSE);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	p_edit_schedule.ShowWindow(FALSE);
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
	GetDlgItem(btn_thumb_room)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manual)->ShowWindow(SW_HIDE);

}


void CSMART_RMDlg::OnBnClickedsettings()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(TRUE);
	p_consumption.ShowWindow(FALSE);
	GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
	p_view.ShowWindow(FALSE);
	p_manual_sw.ShowWindow(FALSE);
	p_edit_sched.ShowWindow(FALSE);
	p_add_module.ShowWindow(FALSE);
	p_edit_schedule.ShowWindow(FALSE);
	GetDlgItem(btn_thumb_room)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manual)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_add)->ShowWindow(SW_HIDE);
}




void CSMART_RMDlg::OnBnClickedhelp()
{
	// TODO: Add your control notification handler code here
		//CDialogEx::OnOK();
	p_about.ShowWindow(TRUE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
	GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	p_view.ShowWindow(FALSE);
	p_manual_sw.ShowWindow(FALSE);
	p_edit_sched.ShowWindow(FALSE);
	p_add_module.ShowWindow(FALSE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
	p_edit_schedule.ShowWindow(FALSE);

}


void CSMART_RMDlg::OnBnClickedhome()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(btn_thumb_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_room)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manual)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_view)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_manage)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	p_view.ShowWindow(FALSE);
	p_manual_sw.ShowWindow(FALSE);
	p_edit_sched.ShowWindow(FALSE);
	p_add_module.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_about.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
	p_edit_schedule.ShowWindow(FALSE);
	GetDlgItem(btn_thumb_add)->ShowWindow(SW_HIDE);


	
}


void CSMART_RMDlg::OnBnClickedview()
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manage)->ShowWindow(SW_HIDE);
	p_view.ShowWindow(TRUE);
	UpdateData(TRUE);
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
	GetDlgItem(btn_thumb_view)->ShowWindow(SW_SHOW);
}



void CSMART_RMDlg::OnBnClickedmanage()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_add_room)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manage)->ShowWindow(SW_HIDE);
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_thumb_manage)->ShowWindow(SW_SHOW);

}


HBRUSH CSMART_RMDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
   switch (nCtlColor) {
		  //case CTLCOLOR_STATIC:
          case CTLCOLOR_EDIT:
          case CTLCOLOR_MSGBOX:
              // Set color to green on black and return the background
              pDC->SetTextColor(RGB(255, 255, 255));
              pDC->SetBkColor(RGB(0,179,254));
              return (HBRUSH)(m_pEditBkBrush->GetSafeHandle()); 
          default:
              return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
          }


}

void CSMART_RMDlg::OnBnClickedbutton()
{
	// TODO: Add your control notification handler code here
	char *correct =  "Login successfull  ";
	char *wrong =  "Incorrect password!  ";

	CString password;
	GetDlgItemText(input_password, password);

	CString URL;
	URL.Format(_T("%sfunction=get_auth&password=%s"), urlMe, password);
	CStringA finalURL(URL);

	TRACE(URL);

	int request = thesis_request((const char*)finalURL);
	std::wostringstream tst;
	if(request){
		if(response["status"].GetInt()){
			tst << correct;
			input_pass.SetWindowTextW(L"");
			m_auth_msg.SetWindowTextW(L"      Input password.   ");
			ChangeDefaultButton();
			login=1;
			loginshow();
			UpdateData(FALSE);
			CString pan_id(response["data"][0]["user_details_pan_id"].GetString());
			static_pan_id.ShowWindow(TRUE);
			static_pan_id.SetWindowTextW(_T("PAN ID: ")+pan_id);
		}else{
			tst << wrong;
			input_pass.SetWindowTextW(L"");
			m_auth_msg.ShowWindow(TRUE);
			m_auth_msg.SetWindowTextW(L"Authentication failed.");
			MessageBoxW(_T("Invalid password!"), _T("Error!"), MB_ICONERROR | MB_OK);
		}
	}else{
		tst << "Server unavailable.";
		input_pass.SetWindowTextW(L"");
		m_auth_msg.ShowWindow(TRUE);
		m_auth_msg.SetWindowTextW(L"Please contact Admin");
		MessageBoxW(_T("Server not found!\nPlease contact administrator."), _T("Error!"), MB_ICONERROR | MB_OK);
	}

	GetDlgItem(img_enter)->ShowWindow(SW_HIDE);
}




void CSMART_RMDlg::OnEnChangepassword()
{
		GetDlgItem(img_enter)->ShowWindow(SW_SHOW);
}


void  CSMART_RMDlg::logouthide()

{
		GetDlgItem(btn_thumb_add)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_thumb_sched)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_thumb_manual)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_thumb_manage)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_thumb_view)->ShowWindow(SW_HIDE);
		GetDlgItem(img_logout_bg)->ShowWindow(SW_SHOW);
		GetDlgItem(btn_help)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_consumption)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_home)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_logout)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_manage)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_settings)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
	    GetDlgItem(img_Index)->ShowWindow(SW_HIDE);
		//loginpanel
		m_auth_msg.ShowWindow(TRUE);
		GetDlgItem(img_login_panel)->ShowWindow(SW_SHOW);
		GetDlgItem(input_password)->ShowWindow(SW_SHOW);
		GetDlgItem(img_enter)->ShowWindow(SW_SHOW);


} 


void  CSMART_RMDlg::loginshow()

{
		GetDlgItem(btn_thumb_add)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_thumb_sched)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_thumb_manual)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_thumb_manage)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_thumb_view)->ShowWindow(SW_HIDE);
		GetDlgItem(img_logout_bg)->ShowWindow(SW_HIDE);
		//GetDlgItem(btn_help)->ShowWindow(SW_SHOW);
		GetDlgItem(btn_help)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_home)->ShowWindow(SW_SHOW);
		GetDlgItem(btn_logout)->ShowWindow(SW_SHOW);
		GetDlgItem(btn_manage)->ShowWindow(SW_SHOW);
		GetDlgItem(btn_view)->ShowWindow(SW_SHOW);
		GetDlgItem(btn_settings)->ShowWindow(SW_SHOW);
		GetDlgItem(btn_view)->ShowWindow(SW_SHOW);
	    GetDlgItem(img_Index)->ShowWindow(SW_SHOW);
		//loginpanel
		m_auth_msg.ShowWindow(FALSE);
		GetDlgItem(img_login_panel)->ShowWindow(SW_HIDE);
		GetDlgItem(input_password)->ShowWindow(SW_HIDE);
		GetDlgItem(img_enter)->ShowWindow(SW_HIDE);
		GetDlgItem(btn_consumption)->ShowWindow(SW_SHOW);
		

} 

void CSMART_RMDlg::ChangeDefaultButton()
{
	DWORD style;
	if(login==0){
    // get the style
    style = GetDlgItem(login_button)->GetStyle();
    // remove default push button style
    style&=~BS_DEFPUSHBUTTON;
    // set the style
    ::SendMessage( GetDlgItem(login_button)->GetSafeHwnd(), BM_SETSTYLE, (WPARAM)style, (LPARAM)TRUE);
    // inform the dialog about the new default control id
    SendMessage(DM_SETDEFID, GetDlgItem(btn_default)->GetDlgCtrlID());
    // get the style
    style=GetDlgItem(btn_default)->GetStyle();
    // add the default push button style
    style|=BS_DEFPUSHBUTTON;
    // set the style
    ::SendMessage(GetDlgItem(btn_default)->GetSafeHwnd(), BM_SETSTYLE, (WPARAM)style, (LPARAM)TRUE);
    // now pButtonB is the default psuh button
	}
	else if(login==1)
	{
	// get the style
    style = GetDlgItem(btn_default)->GetStyle();
    // remove default push button style
    style&=~BS_DEFPUSHBUTTON;
    // set the style
    ::SendMessage( GetDlgItem(btn_default)->GetSafeHwnd(), BM_SETSTYLE, (WPARAM)style, (LPARAM)TRUE);
    // inform the dialog about the new default control id
    SendMessage(DM_SETDEFID, GetDlgItem(login_button)->GetDlgCtrlID());
    // get the style
    style=GetDlgItem(login_button)->GetStyle();
    // add the default push button style
    style|=BS_DEFPUSHBUTTON;
    // set the style
    ::SendMessage(GetDlgItem(login_button)->GetSafeHwnd(), BM_SETSTYLE, (WPARAM)style, (LPARAM)TRUE);
    // now pButtonB is the default psuh button
	}
}

void CSMART_RMDlg::OnBnClickedmanualsw()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(btn_thumb_manual)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
	
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	p_manual_sw.ShowWindow(TRUE);
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
}


void CSMART_RMDlg::OnBnClickededitsched()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(btn_thumb_room)->ShowWindow(TRUE);
	p_edit_sched.ShowWindow(TRUE);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
}


void CSMART_RMDlg::OnBnClickedaddroom()
{
	// TODO: Add your control notification handler code here
	p_add_module.ShowWindow(TRUE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
	GetDlgItem(btn_thumb_sched)->ShowWindow(SW_SHOW);
}

BOOL CSMART_RMDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	// ESC key
	if(pMsg->wParam == VK_ESCAPE) { return TRUE; }
	return CDialog::PreTranslateMessage(pMsg);
}

void CSMART_RMDlg::OnBnClickedconsumption()
{
	// TODO: Add your control notification handler code here
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(TRUE);
	GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	p_view.ShowWindow(FALSE);
	p_manual_sw.ShowWindow(FALSE);
	p_edit_sched.ShowWindow(FALSE);
	p_add_module.ShowWindow(FALSE);
	p_edit_schedule.ShowWindow(FALSE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manual)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_room)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_add)->ShowWindow(SW_HIDE);

}


void CSMART_RMDlg::OnBnClickededitschedule()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_add_room)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_HIDE);
	p_edit_schedule.ShowWindow(TRUE);
	GetDlgItem(btn_thumb_sched)->ShowWindow(SW_SHOW);

}


void CSMART_RMDlg::OnBnClickedthumbmanage()
{
	// TODO: Add your control notification handler code here
	p_add_module.ShowWindow(FALSE);
	GetDlgItem(btn_thumb_room)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_thumb_manual)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manual_sw)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_edit_sched)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_add_room)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_view)->ShowWindow(SW_HIDE);
	GetDlgItem(btn_manage)->ShowWindow(SW_HIDE);
	p_about.ShowWindow(FALSE);
	p_config.ShowWindow(FALSE);
	p_consumption.ShowWindow(FALSE);
	GetDlgItem(btn_edit_schedule)->ShowWindow(SW_SHOW);
	GetDlgItem(btn_thumb_manage)->ShowWindow(SW_SHOW);
	p_manual_sw.ShowWindow(FALSE);
	p_edit_sched.ShowWindow(FALSE);
	GetDlgItem(btn_thumb_sched)->ShowWindow(SW_HIDE);
	p_edit_schedule.ShowWindow(FALSE);
	GetDlgItem(btn_thumb_add)->ShowWindow(SW_HIDE);

}
