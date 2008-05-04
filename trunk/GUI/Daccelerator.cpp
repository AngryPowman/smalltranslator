// Daccelerator.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "Daccelerator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Daccelerator dialog


Daccelerator::Daccelerator(CWnd* pParent /*=NULL*/)
	: CDialog(Daccelerator::IDD, pParent)
{
	//{{AFX_DATA_INIT(Daccelerator)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Daccelerator::Daccelerator(int * num,CWnd* pParent /*=NULL*/)
	: CDialog(Daccelerator::IDD, pParent)
{
	this->num = num;
	//{{AFX_DATA_INIT(Daccelerator)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void Daccelerator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Daccelerator)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Daccelerator, CDialog)
	//{{AFX_MSG_MAP(Daccelerator)
	ON_BN_CLICKED(IDOK, OnOKAccelerator)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Daccelerator message handlers



void Daccelerator::OnOKAccelerator() 
{
	int checkednum = GetCheckedRadioButton(IDC_RADIO3,IDC_RADIO4);
	if (checkednum != 0)
	{
		if (checkednum == IDC_RADIO3)
			*(this->num) = 160;
		if(checkednum == IDC_RADIO4)
			*(this->num) = 162;
	}
	CDialog::OnOK();
	// TODO: Add your control notification handler code here
	
}
