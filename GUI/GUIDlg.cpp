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

//�����ֿ��Կ��������������˼
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
	ON_MESSAGE(WM_MYMSG,OnMymsg)       //�趨��Ϣ�ʹ������Ĺ���
	ON_MESSAGE(WM_MYMSG_DESTROY,OnMymsg_destroy)
	ON_MESSAGE(WM_MYMSG_TRAY,OnMymsg_Tray)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGUIDlg message handlers

BOOL CGUIDlg::OnInitDialog()
{
//����ֻ����һ������
	CString   mutexName   =   "oneInstanceMutexNew";
	::CreateMutex(NULL,FALSE,mutexName);   
	if(GetLastError()==ERROR_ALREADY_EXISTS)   
	{ 
		AfxMessageBox("The   Application   has   run   already!");   
		exit(0);   
	}
/////////////////

	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);  //��ʼ��ѡ�е�һ��radio
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);         //set combo box to disable
	autotran = true;   //��Ӣ����Ϊ��

	popupPoster=NULL;
	hWind = AfxGetApp()->m_pMainWnd->GetSafeHwnd(); //�õ���ǰ���ڵľ��
	InstallLaunchEv(hWind,checkedRadio); //��װ���ӣ�install hook ,and transfer the main dialog's handle;
	
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
			pSysMenu->InsertMenu(5,MF_BYPOSITION, IDM_ABOUTBOX, strAboutMenu);// �����ڲ˵��ŵ�����
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_TrayIcon.Create(this, WM_MYMSG_TRAY, "SmallTranslator", m_hIcon, IDR_MENU1);// ��������ͼ�����Ϣ


	//��ʼ������ѡ���
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
//��ʼ������ѡ������

	
//��ȡ�Ѿ����Է�������ֶ� �ŵ���map����
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
//��ȡ��map�н���
	
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
		OnClose();//��������ǹرյ������Ϊ���ء�
//        AnimateWindow(GetSafeHwnd(),600,AW_HIDE|AW_BLEND);
//        KillTimer(0);
//         ShowWindow(SW_HIDE);//ϵͳ�˵��Ĺر�Ҳ��Ϊ���ء�

	}
	else if ((nID & 0xFFF0) == SC_MINIMIZE) 
		{
			AnimateWindow(GetSafeHwnd(),600,AW_HIDE|AW_BLEND);
			KillTimer(0);
			 ShowWindow(SW_HIDE);//ϵͳ�˵��Ĺر�Ҳ��Ϊ���ء�

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

void CGUIDlg::OnMymsg(WPARAM, LPARAM) //�Զ������Ϣ��Ӧ����,��dllȷ�����Ƶ��ַ������������ڷ��������Ϣ
{
	//�յ������Ϣ�󣬵�û���Ӵ��ڣ������и��Ƶ���ֵ��ʱ�򣬴���һ���Ӵ���
	if ((unify_flag==0)&&(!getSeletedValue().empty()))
	{
		if (popupPoster!=NULL) //������Դ����ֹ�ڴ�й¶
		{
			delete popupPoster;
			popupPoster=NULL;
		}


		if (autotran) //�������Ӣ���Զ����룬ʹ�ò���Ϊ�յĹ��캯��
		{
			popupPoster=new Poster();	
		}
		else
		{
			if (map_lang_pair[vectUnit[index].source]==vectUnit[index].dest) 
			//���ָ���˷������Զԣ�����������Զ��Ƿ��ڿ��Է�������Զ��С�����ڣ���������Ĺ��캯��
			{
				popupPoster=new Poster(false,vectUnit[index].source,vectUnit[index].dest);
			}
			else  //����������ԶԲ��ڿ���ֱ�ӷ�������Զ��У����Ƚ�english��Ϊ�м����ԣ��෭��һ�Σ���������Ĺ��캯��
			{
				popupPoster = new Poster(false,vectUnit[index].source,vectUnit[index].dest,true);
			}
			
		}
		popupPoster->Create(IDD_DIALOG1,popupPoster->GetDesktopWindow());//�趨�������Ӵ��ڵĸ�����

		popupPoster->ShowWindow(SW_SHOW);
		h_child=popupPoster->m_hWnd; //����Ӵ��ڵľ�����õ�ʱ��close��Ϣ
		unify_flag=1;   //��־�Ѿ���һ���Ӵ�����

	}
}

void CGUIDlg::OnMymsg_destroy(WPARAM, LPARAM)//�������Ӵ��ڵ���Ϣ
{
	::PostMessage(h_child,WM_CLOSE,0,0);
}

void CGUIDlg::OnMymsg_Tray(WPARAM wparam, LPARAM lparam)
{
	switch (lparam)
	{
	case WM_RBUTTONDOWN:
	{
		// �û�������ͼ���ϵ�������Ҽ������������Ĳ˵�����/��ʾ�Ի���
		CMenu oMenu;
		if (oMenu.LoadMenu(IDR_MENU1))        
		{
			CMenu* pPopup;
			if (!(pPopup=oMenu.GetSubMenu(0)))   
				return;
			CPoint oPoint;
			if (IsWindowVisible())// ���ݶԻ��򴰿ڵ���ʾ/����״̬�޸Ĳ˵�����
				oMenu.ModifyMenu(ID_VIEW_MAIN_WINDOW,MF_STRING,ID_VIEW_MAIN_WINDOW,"����");
			else
				oMenu.ModifyMenu(ID_VIEW_MAIN_WINDOW,MF_STRING,ID_VIEW_MAIN_WINDOW,"��ʾ");
			
			// ȷ�����λ���Ա��ڸ�λ�ø�����ʾ�˵�
			GetCursorPos( &oPoint );
			SetForegroundWindow();
			pPopup->TrackPopupMenu(TPM_RIGHTALIGN|TPM_BOTTOMALIGN |TPM_RIGHTBUTTON,	oPoint.x, oPoint.y, this); 
			oMenu.DestroyMenu();   
		}
	}
	break;

	//case WM_LBUTTONDBLCLK:

	// ������������ʾ���Ի���
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

void CGUIDlg::OnQuery() //��������Ǵ�������������뷭������
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

	//�Է��������д���
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
//    ShowWindow(SW_HIDE);//ϵͳ�˵��Ĺر�Ҳ��Ϊ���ء�
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
