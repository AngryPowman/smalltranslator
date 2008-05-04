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

//�Զ������ͣ������ļ�������������Ϣ
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
	vector<langUnit> vectUnit;      //����langUnit�ṹ������
	vector<langUnit>::size_type index;  //����ѡ�е�vectUnit���±�
	bool autotran;                  //��־�Ƿ��õ�����Ӣ���Զ�����

	map<string,string> map_lang_pair;    //������Է�������Զԣ������ڴ��ڳ�ʼ����ʱ���langpair.txt�ļ��ж�ȡ
	
// Dialog Data
	//{{AFX_DATA(CGUIDlg)
	enum { IDD = IDD_GUI_DIALOG };
	CComboBox m_combo;                  //���������
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
	HWND h_child;                //�������������ɵ��Ӵ��ڵľ���������ڰ���̧���ʱ����
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
	afx_msg void OnMymsg(WPARAM, LPARAM);//�Զ�����Ϣ������������create����һ���Ӵ���
	afx_msg void OnMymsg_destroy(WPARAM, LPARAM);//�Զ�����Ϣ���������������Ӵ���
	afx_msg void OnMymsg_Tray(WPARAM, LPARAM);//ϵͳ������Ϣ
	Poster * popupPoster;   //ָ���Ӵ��ڶ����ָ�룬��Ϊ�Ӵ�����һ�����������ɵģ����ָ���Ƿ��㳷���Ӵ��ڵ�ʱ��
							//�����ָ��del��������Ϊnull
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDLG_H__E468CD0E_D640_4329_BE40_147CAFCC80AE__INCLUDED_)
