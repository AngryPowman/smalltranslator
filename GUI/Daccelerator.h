#if !defined(AFX_DACCELERATOR_H__CD03CEE4_C79E_4DF4_90D4_36DE1F1F3376__INCLUDED_)
#define AFX_DACCELERATOR_H__CD03CEE4_C79E_4DF4_90D4_36DE1F1F3376__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Daccelerator.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Daccelerator dialog

class Daccelerator : public CDialog
{
// Construction
public:
	Daccelerator(CWnd* pParent = NULL);   // standard constructor
	Daccelerator(int * num,HWND hWind, CWnd* pParent = NULL);  
// Dialog Data
	//{{AFX_DATA(Daccelerator)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Daccelerator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int * num;
	HWND hWind;
	// Generated message map functions
	//{{AFX_MSG(Daccelerator)
	virtual BOOL OnInitDialog();
	afx_msg void OnOKAccelerator();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DACCELERATOR_H__CD03CEE4_C79E_4DF4_90D4_36DE1F1F3376__INCLUDED_)
