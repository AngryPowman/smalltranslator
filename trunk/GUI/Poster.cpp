// Poster.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "Poster.h"
#include "translator.h"

#include "KeyBoard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void replaceall(string & input, string old, string newstr)
{
	int index=input.find(old);
	while(index!=string::npos)
	{
		input.replace(index,old.size(),newstr);
		index = input.find(old,index);
	}
}
/////////////////////////////////////////////////////////////////////////////
// Poster dialog
extern int unify_flag;

Poster::Poster(CWnd* pParent /*=NULL*/)
	: CDialog(Poster::IDD, pParent)
{
	this->autotran=true;
	this->source.erase();
	this->dest.erase();
	
	needmid  = false;

	m_crTextColor= ::GetSysColor(COLOR_WINDOWTEXT);   
	m_crBkColor = RGB(200,240,200);   
	m_brBkGround.CreateSolidBrush(RGB(200,240,200));   

	//{{AFX_DATA_INIT(Poster)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Poster::Poster(bool autotran , string source ,string dest,CWnd* pParent/*=NULL*/)
	: CDialog(Poster::IDD, pParent)
{
	this->autotran = autotran;
	this->source = source;
	this->dest = dest;

	needmid = false;

	m_crTextColor= ::GetSysColor(COLOR_WINDOWTEXT);   //设置框的颜色
	m_crBkColor = RGB(200,240,200);   
	m_brBkGround.CreateSolidBrush(RGB(200,240,200));   

	//{{AFX_DATA_INIT(Poster)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
Poster::Poster(bool autotran , string source ,string dest,bool needmid,CWnd* pParent/*=NULL*/)
	: CDialog(Poster::IDD, pParent)
{
	this->autotran = autotran;
	this->source = source;
	this->dest = dest;

	this->needmid = needmid;

	m_crTextColor= ::GetSysColor(COLOR_WINDOWTEXT);   //设置框的颜色
	m_crBkColor = RGB(200,240,200);   
	m_brBkGround.CreateSolidBrush(RGB(200,240,200));   

	//{{AFX_DATA_INIT(Poster)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Poster::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Poster)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Poster, CDialog)
	//{{AFX_MSG_MAP(Poster)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Poster message handlers

BOOL Poster::OnInitDialog() 
{
	HWND h_highligh = ::GetForegroundWindow();
	::SetForegroundWindow(h_highligh);
	string translated_result;
	Translator translator;

	POINT mouse_pos;   //获得鼠标坐标
	if (!GetCursorPos(&mouse_pos)) {
		return false;
	}
	//获得屏幕分辨率
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	int dialogW=400;  //对话框的宽

	string copyChar = getSeletedValue();
	replaceall(copyChar,"\r\n"," "); // 替换回车为空格，否则处理的时候会出错

	if (copyChar.size()>=512) 
	{
		translated_result = "字数太多";// http的get 最多512个字节
	}
	else
	{
		if (autotran) 
		{
			translated_result = translator.autoTranslate(copyChar);
		}
		else
		{
			if (needmid) 
			{
				translated_result = translator.flexTranslate(copyChar,source,"en");
				translated_result = translator.flexTranslate(translated_result,"en",dest);
			}
			else
			{
				translated_result = translator.flexTranslate(copyChar,source,dest);
			}

		}
	}

	int sizeofresult = translated_result.size();//准备调整对话框的大小
	int cy =sizeofresult/60+4;
	cy = cy*20;
	
	int dialogX=mouse_pos.x;
	int dialogY=mouse_pos.y;
	if (dialogX>screenX-dialogW) 
		dialogX=screenX-dialogW-30;
	if (dialogY>screenY-cy) 
		dialogY=screenY-cy-30;

	::SetWindowPos(this->m_hWnd,HWND_TOPMOST,dialogX,dialogY,dialogW,cy,SWP_SHOWWINDOW);

	replaceall(translated_result,"quot;","\"");
	replaceall(translated_result,"#39;","'");
	
	
//消除任务栏显示 
	LONG style = ::GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE); //获得窗体扩展风格 
	style &= ~WS_EX_APPWINDOW; //取消WS_EX_APPWINDOW 
	::SetWindowLong(GetSafeHwnd(), WS_EX_TOOLWINDOW , style); //设置窗体扩展风格 
    ShowWindow(SW_HIDE);
    ::SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, WS_EX_TOOLWINDOW); 
    ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_EDIT2)->SetWindowText(translated_result.c_str());

//消除任务栏显示 


	// TODO: Add extra initialization here
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Poster::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	unify_flag=0;
	cleardllVale();
	return CDialog::DestroyWindow();
}

void Poster::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	unify_flag=0;
	cleardllVale();
	CDialog::OnClose();
}

void Poster::OnDestroy() 
{
	unify_flag=0;
	CDialog::OnDestroy();
	cleardllVale();	
	// TODO: Add your message handler code here
	
}

void Poster::OnOK() 
{
	// TODO: Add extra validation here
	unify_flag=0;
	cleardllVale();
	CDialog::OnOK();
}



HBRUSH Poster::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetTextColor(m_crTextColor);   
	pDC->SetBkColor(m_crBkColor);   
	return  (HBRUSH)m_brBkGround;   
}
