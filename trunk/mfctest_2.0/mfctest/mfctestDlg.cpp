
// TempDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfctest.h"
#include "mfctestDlg.h"
#include "WinUser.h"
#include "XmlReader.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HHOOK m_hkeyboard;
HWND m_hgame;
HWND topWnd;
int count;
XmlReader *xmlReader;
map<string , string> map_Key;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
HMODULE WINAPI ModuleFromAddress(PVOID pv) //获得钩子函数的地址 
{ 
MEMORY_BASIC_INFORMATION mbi; 
if(::VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) 
{ 
   return (HMODULE)mbi.AllocationBase; 
} 
else 
{ 
   return NULL; 
} 
} 
//HHOOK m_hkeyboard;    //handler of keyboard hook
LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	//Find the front window
	topWnd = GetForegroundWindow();
	
	PKBDLLHOOKSTRUCT kbstruct;
	kbstruct=(PKBDLLHOOKSTRUCT)lParam;
	DWORD dtemp = kbstruct->vkCode;//vkCode is the press buttom



	//we need to read keys configure from gameconfiguration.xml
	char ch_Temp = char(dtemp); /*- 0x41 + char('A');*/
	char ch_Corl;//doesn't take double key into account
	map<string , string>::iterator iter_Key = map_Key.begin();
	bool found = false;

	if(ch_Temp >= 96)
	{
		ch_Temp = ch_Temp - 96 + 48;
	}
	if(topWnd == m_hgame)
	{
		string str_Temp;
		str_Temp.clear();
		str_Temp.push_back(ch_Temp);
		if(WM_KEYDOWN == int(wParam))
		{
				/*int key_value = ch_Corl - char('A') + 0x41;
				keybd_event(key_value,0,0,0);*/
			switch (dtemp)
			{
				case 0x58:
					mouse_event(MOUSEEVENTF_LEFTDOWN , 0 , 0 , 0 , 0);
					return 1;
				case char('A'):
					mouse_event(MOUSEEVENTF_MOVE , -10 , 0 , 0 , 0);
					return 1;
				case char('S'):
					mouse_event(MOUSEEVENTF_MOVE , 10 , 0 , 0 , 0);
					return 1;
				case char('W'):
					mouse_event(MOUSEEVENTF_MOVE , 0 , 10 , 0 , 0);
					return 1;
				case char('E'):
					mouse_event(MOUSEEVENTF_MOVE , 0 , -10 , 0 , 0);
					return 1;
				default:
					break;	
			}
			
		}
		if(WM_KEYUP == int(wParam))
		{
			if(VK_RETURN == dtemp)
			{
				mouse_event(MOUSEEVENTF_LEFTUP , 0 , 0 , 0 , 0);
				return 1;
			}
		}
 			while(map_Key.end() != iter_Key)
			{
				if(0 == iter_Key->first.compare(str_Temp))
				{
					found = true;
					//ch_Corl = *(iter_Key->second.c_str());
					break;
				}
				iter_Key++;
			}

			if(found)
			{
				if(1 == iter_Key->second.length())
				{
					ch_Corl = *(iter_Key->second.c_str());
					if(WM_KEYDOWN == int(wParam))
					{
						int key_value = ch_Corl; /*- char('A') + 0x41;*/
						keybd_event(key_value,0,0,0);
						return 1;
					}
					if(WM_KEYUP == int(wParam))
					{
						int key_value = ch_Corl;/* - char('A') + 0x41;*/
						keybd_event(key_value,0,KEYEVENTF_KEYUP,0);
						return 1;
					}
				}
				else
				{
					int key_value;
					if(0 == string("UP").compare(iter_Key->second))
					{
						key_value = 0x26;
					}
					else if(0 == string("LEFT").compare(iter_Key->second))
					{
						key_value = 0x25;
					}
					else if(0 == string("RIGHT").compare(iter_Key->second))
					{
						key_value = 0x27;
					}
					else if(0 == string("DOWN").compare(iter_Key->second))
					{
						key_value = 0x28;
					}
					if(WM_KEYDOWN == int(wParam))
					{

						//int key_value = ch_Corl - char('A') + 0x41;
						keybd_event(key_value,0,0,0);
						return 1;
					}
					if(WM_KEYUP == int(wParam))
					{
						//int key_value = ch_Corl - char('A') + 0x41;
						keybd_event(key_value,0,KEYEVENTF_KEYUP,0);
						return 1;
					}
				}
			}


			
			

	}

	return CallNextHookEx(m_hkeyboard,nCode,wParam,lParam);
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmfctestDlg 对话框




CmfctestDlg::CmfctestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfctestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfctestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfctestDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CmfctestDlg 消息处理程序

BOOL CmfctestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	count = 0;
	xmlReader = new XmlReader(string("gameconfiguration.xml"));
	map_Key = xmlReader->FindConfByID(string("875689"));
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	SetTimer(1,2000,NULL);//SetTimer(ID, 1000 = 1 seconds, NULL)
	
	//m_hkeyboard = SetWindowsHookEx(WH_KEYBOARD_LL,LowLevelKeyboardProc, ModuleFromAddress(LowLevelKeyboardProc),0);
	
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

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmfctestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmfctestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmfctestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmfctestDlg::OnTimer(UINT_PTR nIDEvent)
{
	//Check "Love Shooting Love" program open or not in the screen
	m_hgame = ::FindWindowW(NULL , L"Let's Shooting Love ARCADE Beta 0.1"/*L"Fowl Play"*/);//we should read the name from gameconfiguration.xml
	
	if(m_hgame)
	{
		if (m_hkeyboard)//Check the hook function already exists or not
		{	
			 CDialog::OnTimer(nIDEvent);
			 return;
		}
		m_hkeyboard = SetWindowsHookEx(WH_KEYBOARD_LL,LowLevelKeyboardProc, ModuleFromAddress(LowLevelKeyboardProc),0);

	}
	
	CDialog::OnTimer(nIDEvent);
}