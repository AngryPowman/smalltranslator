#include <string>

using namespace std;

#if !defined(AFX_POSTER_H__035F9F0E_5747_4671_ADD7_98CE7444BF5F__INCLUDED_)
#define AFX_POSTER_H__035F9F0E_5747_4671_ADD7_98CE7444BF5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Poster.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Poster dialog


class Poster : public CDialog
{
// Construction
public:
	Poster(CWnd* pParent = NULL);   // standard constructor
	Poster(bool autotran,string source ,string dest,CWnd* pParent = NULL);
	Poster(bool autotran,string source ,string dest,bool needmid,CWnd* pParent = NULL);
	bool autotran;
	bool needmid;  //是否中间需要转换成英语再翻译
	string source;
	string dest;
// Dialog Data
	//{{AFX_DATA(Poster)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Poster)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush       m_brBkGround;   
	COLORREF   m_crBkColor;   
	COLORREF   m_crTextColor;   
	// Generated message map functions
	//{{AFX_MSG(Poster)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSTER_H__035F9F0E_5747_4671_ADD7_98CE7444BF5F__INCLUDED_)
