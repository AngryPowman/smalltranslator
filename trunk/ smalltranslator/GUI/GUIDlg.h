// GUIDlg.h : header file
//

#include "systemTray.h"
#include "Poster.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

#if !defined(AFX_GUIDLG_H__E468CD0E_D640_4329_BE40_147CAFCC80AE__INCLUDED_)
#define AFX_GUIDLG_H__E468CD0E_D640_4329_BE40_147CAFCC80AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_MYMSG WM_USER+520
#define WM_MYMSG_DESTROY WM_USER+521
#define WM_MYMSG_TRAY WM_USER+522

/////////////////////////////////////////////////////////////////////////////
// CGUIDlg dialog

//自定义类型，保存文件的语言描述信息
class langUnit
{
public:
	string description;
	string source;
	string dest;
	
};

class CGUIDlg : public CDialog
{
// Construction
public:
	CGUIDlg(CWnd* pParent = NULL);	// standard constructor
	vector<langUnit> vectUnit;      //保存langUnit结构的容器
	vector<langUnit>::size_type index;  //保存选中的vectUnit的下标
	bool autotran;                  //标志是否用的是中英文自动翻译

	map<string,string> map_lang_pair;    //保存可以翻译的语言对，内容在窗口初始化的时候从langpair.txt文件中读取
	
// Dialog Data
	//{{AFX_DATA(CGUIDlg)
	enum { IDD = IDD_GUI_DIALOG };
	CComboBox m_combo;                  //下拉框对象
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HWND h_child;                //保存主窗口生成的子窗口的句柄，方便在按键抬起的时候撤销
	// Generated message map functions
	//{{AFX_MSG(CGUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnQuery();
	afx_msg void OnCancel();
	afx_msg void OnViewMainWindow();
	afx_msg void OnCancel1();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnDblclkCombo1();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMymsg(WPARAM, LPARAM);//自定义消息处理函数，负责create出来一个子窗口
	afx_msg void OnMymsg_destroy(WPARAM, LPARAM);//自定义消息处理函数，负责撤销子窗口
	afx_msg void OnMymsg_Tray(WPARAM, LPARAM);//系统托盘消息
	Poster * popupPoster;   //指向子窗口对象的指针，因为子窗口在一个方法中生成的，这个指针是方便撤销子窗口的时候
							//将这个指针del，并且置为null
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDLG_H__E468CD0E_D640_4329_BE40_147CAFCC80AE__INCLUDED_)
