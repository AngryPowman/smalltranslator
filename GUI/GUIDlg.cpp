// GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "Poster.h"
#include "translator.h"
#include "KeyBoard.h"
#include "Daccelerator.h"

#include <sstream>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int unify_flag=0;
CSystemTray m_TrayIcon;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//从名字可以看出这个函数的意思
extern void replaceall(string & input, string old, string newstr);

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGUIDlg dialog

CGUIDlg::CGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGUIDlg::IDD, pParent)
{
	index =0;
	autotran = true;
	ifstream infstream("config");
	if (infstream.fail())
	{
		MessageBox("not find the config file");
		infstream.close();
		exit(1);
	}
	infstream>>checkedRadio;
	infstream.close();
	//{{AFX_DATA_INIT(CGUIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME_MY);
}

void CGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGUIDlg)
	DDX_Control(pDX, IDC_COMBO1,m_combo);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGUIDlg, CDialog)
	//{{AFX_MSG_MAP(CGUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnQuery)
	ON_COMMAND(ID_VIEW_MAIN_WINDOW, OnViewMainWindow)
	ON_COMMAND(ID_CANCEL, OnCancel1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_CBN_DBLCLK(IDC_COMBO1, OnDblclkCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonAccelerator)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MYMSG,OnMymsg)       //设定消息和处理函数的关联
	ON_MESSAGE(WM_MYMSG_DESTROY,OnMymsg_destroy)
	ON_MESSAGE(WM_MYMSG_TRAY,OnMymsg_Tray)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGUIDlg message handlers

BOOL CGUIDlg::OnInitDialog()
{
//设置只能起一个进程
	CString   mutexName   =   "oneInstanceMutexNew";
	::CreateMutex(NULL,FALSE,mutexName);   
	if(GetLastError()==ERROR_ALREADY_EXISTS)   
	{ 
		AfxMessageBox("The   Application   has   run   already!");   
		exit(0);   
	}
/////////////////

	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);  //初始化选中第一个radio
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);         //set combo box to disable
	autotran = true;   //中英互译为真

	popupPoster=NULL;
	hWind = AfxGetApp()->m_pMainWnd->GetSafeHwnd(); //得到当前窗口的句柄
	InstallLaunchEv(hWind,checkedRadio); //安装钩子，install hook ,and transfer the main dialog's handle;
	
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			//pSysMenu->AppendMenu(MF_SEPARATOR);
			//pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			pSysMenu->InsertMenu(5,MF_BYPOSITION, IDM_ABOUTBOX, strAboutMenu);// 将关于菜单放到上面
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_TrayIcon.Create(this, WM_MYMSG_TRAY, "SmallTranslator", m_hIcon, IDR_MENU1);// 创建托盘图标和消息


	//初始化语言选择框
	string word,line;
	langUnit unit;
	ifstream infstream("langlist.txt");
	while (getline(infstream,line)) 
	{
		istringstream istrstr(line);
		if (istrstr>>word)
			unit.description=word;
		if (istrstr>>word)
			unit.source=word;
		if (istrstr>>word)
			unit.dest=word;
		vectUnit.push_back(unit);
	}
	infstream.clear();
	infstream.close();
	
	for (vector<langUnit>::size_type i=0;i<vectUnit.size();i++) 
	{
		m_combo.AddString(vectUnit[i].description.c_str());
	}
	m_combo.SetCurSel(0);
//初始化语言选择框结束

	
//提取已经可以翻译的语种对 放到到map里面
	infstream.open("langpair.txt");
	while (getline(infstream,line)) 
	{
		string sourceword;
		string destword;
		istringstream istrstr(line);
		if(istrstr>>sourceword)
			if (istrstr>>destword) 
			{
				map_lang_pair[sourceword]=destword;
			}
	}
	infstream.clear();
	infstream.close();
//提取到map中结束
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	if ((nID & 0xFFF0) == SC_CLOSE) 
	{
		OnClose();//本来这个是关闭的这里，改为隐藏。
//        AnimateWindow(GetSafeHwnd(),600,AW_HIDE|AW_BLEND);
//        KillTimer(0);
//         ShowWindow(SW_HIDE);//系统菜单的关闭也改为隐藏。

	}
	else if ((nID & 0xFFF0) == SC_MINIMIZE) 
		{
			AnimateWindow(GetSafeHwnd(),600,AW_HIDE|AW_BLEND);
			KillTimer(0);
			 ShowWindow(SW_HIDE);//系统菜单的关闭也改为隐藏。

		}
		else
		{
			CDialog::OnSysCommand(nID, lParam);
		}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGUIDlg::OnMymsg(WPARAM, LPARAM) //自定义的消息相应函数,当dll确定复制到字符串后，向主窗口发送这个消息
{
	//收到这个消息后，当没有子窗口，并且有复制到的值的时候，创建一个子窗口
	if ((unify_flag==0)&&(!getSeletedValue().empty()))
	{
		if (popupPoster!=NULL) //撤销资源，防止内存泄露
		{
			delete popupPoster;
			popupPoster=NULL;
		}


		if (autotran) //如果是中英文自动翻译，使用参数为空的构造函数
		{
			popupPoster=new Poster();	
		}
		else
		{
			if (map_lang_pair[vectUnit[index].source]==vectUnit[index].dest) 
			//如果指定了翻译语言对，查找这个语言对是否在可以翻译的语言对中。如果在，调用下面的构造函数
			{
				popupPoster=new Poster(false,vectUnit[index].source,vectUnit[index].dest);
			}
			else  //如果翻译语言对不在可以直接翻译的语言对中，则先将english作为中间语言，多翻译一次，调用下面的构造函数
			{
				popupPoster = new Poster(false,vectUnit[index].source,vectUnit[index].dest,true);
			}
			
		}
		popupPoster->Create(IDD_DIALOG1,popupPoster->GetDesktopWindow());//设定桌面是子窗口的父窗口

		popupPoster->ShowWindow(SW_SHOW);
		h_child=popupPoster->m_hWnd; //获得子窗口的句柄，好到时候发close消息
		unify_flag=1;   //标志已经有一个子窗口了

	}
}

void CGUIDlg::OnMymsg_destroy(WPARAM, LPARAM)//处理撤销子窗口的消息
{
	::PostMessage(h_child,WM_CLOSE,0,0);
}

void CGUIDlg::OnMymsg_Tray(WPARAM wparam, LPARAM lparam)
{
	switch (lparam)
	{
	case WM_RBUTTONDOWN:
	{
		// 用户在托盘图标上单击鼠标右键，弹出上下文菜单隐藏/显示对话框。
		CMenu oMenu;
		if (oMenu.LoadMenu(IDR_MENU1))        
		{
			CMenu* pPopup;
			if (!(pPopup=oMenu.GetSubMenu(0)))   
				return;
			CPoint oPoint;
			if (IsWindowVisible())// 根据对话框窗口的显示/隐藏状态修改菜单名称
				oMenu.ModifyMenu(ID_VIEW_MAIN_WINDOW,MF_STRING,ID_VIEW_MAIN_WINDOW,"隐藏");
			else
				oMenu.ModifyMenu(ID_VIEW_MAIN_WINDOW,MF_STRING,ID_VIEW_MAIN_WINDOW,"显示");
			
			// 确定鼠标位置以便在该位置附近显示菜单
			GetCursorPos( &oPoint );
			SetForegroundWindow();
			pPopup->TrackPopupMenu(TPM_RIGHTALIGN|TPM_BOTTOMALIGN |TPM_RIGHTBUTTON,	oPoint.x, oPoint.y, this); 
			oMenu.DestroyMenu();   
		}
	}
	break;

	//case WM_LBUTTONDBLCLK:

	// 单击鼠标左键显示出对话框
	case WM_LBUTTONDOWN:
		
		if(this->IsWindowVisible()==0)			
		{
			SetForegroundWindow();
			ShowWindow(SW_RESTORE);
		}
		else
		{
			ShowWindow(SW_HIDE);
		}

		break;
	}

}

void CGUIDlg::OnQuery() //这个函数是处理在输入框输入翻译的情况
{
	CString c_input;
	CString c_output;
	string stroutput;
	GetDlgItem(IDC_EDIT1)->GetWindowText(c_input);
	
	
	Translator translator;
	if (autotran) 
	{
		stroutput = translator.autoTranslate(c_input.GetBuffer(0));
	}
	else
	{

		if (map_lang_pair[vectUnit[index].source]==vectUnit[index].dest)
		{
			stroutput = translator.flexTranslate(c_input.GetBuffer(0),vectUnit[index].source,vectUnit[index].dest);
		}
		else
		{
			string tempTrans = translator.flexTranslate(c_input.GetBuffer(0),vectUnit[index].source,"en");
			stroutput = translator.flexTranslate(tempTrans,"en",vectUnit[index].dest);
		}
	}

	//对翻译结果进行处理
	replaceall(stroutput,"quot;","\"");
	replaceall(stroutput,"#39;","'");
	
	c_output = stroutput.c_str();
	
	GetDlgItem(IDC_EDIT2)->SetWindowText(c_output);

	// TODO: Add your control notification handler code here
	
}

void CGUIDlg::OnCancel() 
{
	::PostQuitMessage(0);

//    AnimateWindow(GetSafeHwnd(),600,AW_HIDE|AW_BLEND);
//    KillTimer(0);
//    ShowWindow(SW_HIDE);//系统菜单的关闭也改为隐藏。
// 
	
}

void CGUIDlg::OnViewMainWindow() 
{
	
	if (IsWindowVisible()) 
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		SetForegroundWindow();
		ShowWindow(SW_RESTORE);
	}
	// TODO: Add your command handler code here
	
}

void CGUIDlg::OnCancel1() 
{
	delete popupPoster;
	popupPoster=NULL;
	::PostQuitMessage(0);
	// TODO: Add your command handler code here
	
}

void CGUIDlg::OnRadio1() 
{
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);
	autotran = true;
	// TODO: Add your control notification handler code here
	
}

void CGUIDlg::OnRadio2() 
{
	GetDlgItem(IDC_COMBO1)->EnableWindow(true);
	autotran = false;
	CString seletedText;
	m_combo.GetLBText(m_combo.GetCurSel(),seletedText);
	for (vector<langUnit>::size_type i=0;i<vectUnit.size();i++) 
	{
		if (vectUnit[i].description.c_str()==seletedText)
		{
			index = i;
			break;
		}
	}
	// TODO: Add your control notification handler code here
	
}

void CGUIDlg::OnDblclkCombo1() 
{
	// TODO: Add your control notification handler code here
	
}

void CGUIDlg::OnSelchangeCombo1() 
{
	index = m_combo.GetCurSel();
	autotran = false;
	
	CString seletedText;
	m_combo.GetLBText(m_combo.GetCurSel(),seletedText);
	for (vector<langUnit>::size_type i=0;i<vectUnit.size();i++) 
	{
		if (vectUnit[i].description.c_str()==seletedText)
		{
			index = i;
			break;
		}
	}
	// TODO: Add your control notification handler code here
	
}

void CGUIDlg::OnButtonAccelerator() 
{
	Daccelerator da(&checkedRadio,hWind);
	da.DoModal();
	ofstream outfstream("config");
	outfstream<<checkedRadio;
	outfstream.close();
	// TODO: Add your control notification handler code here
}
