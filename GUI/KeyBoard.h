// KeyBoard.h : main header file for the KEYBOARD DLL
//

#if !defined(AFX_KEYBOARD_H__7DFD3763_76CD_46F3_8945_CD831AE20B61__INCLUDED_)
#define AFX_KEYBOARD_H__7DFD3763_76CD_46F3_8945_CD831AE20B61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <string>

using namespace std;

//My code
#define WH_KEYBOARD_LL     13

typedef struct tagKBDLLHOOKSTRUCT {

    DWORD   vkCode;

    DWORD   scanCode;

    DWORD   flags;

    DWORD   time;

    DWORD   dwExtraInfo;

} KBDLLHOOKSTRUCT, FAR *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;

#define DllExport __declspec(dllexport) 

DllExport void WINAPI InstallLaunchEv(HWND hWind,int hookkey); 
DllExport string WINAPI getSeletedValue();
DllExport void WINAPI cleardllVale();
DllExport bool WINAPI unHook();

/////////////////////////////////////////////////////////////////////////////
// CKeyBoardApp
// See KeyBoard.cpp for the implementation of this class
//

class CKeyBoardApp : public CWinApp
{
public:
	CKeyBoardApp();
	~CKeyBoardApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyBoardApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKeyBoardApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYBOARD_H__7DFD3763_76CD_46F3_8945_CD831AE20B61__INCLUDED_)
