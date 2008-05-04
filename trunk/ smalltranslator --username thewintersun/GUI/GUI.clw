; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGUIDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GUI.h"

ClassCount=4
Class1=CGUIApp
Class2=CGUIDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_GUI_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=Poster
Resource4=IDD_DIALOG1
Resource5=IDR_MENU1

[CLS:CGUIApp]
Type=0
HeaderFile=GUI.h
ImplementationFile=GUI.cpp
Filter=N

[CLS:CGUIDlg]
Type=0
HeaderFile=GUIDlg.h
ImplementationFile=GUIDlg.cpp
Filter=D
LastObject=IDC_COMBO1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=GUIDlg.h
ImplementationFile=GUIDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889

[DLG:IDD_GUI_DIALOG]
Type=1
Class=CGUIDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350635524
Control5=IDC_RADIO1,button,1342177289
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_COMBO1,combobox,1344340226
Control8=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG1]
Type=1
Class=Poster
ControlCount=2
Control1=IDC_EDIT2,edit,1342183428
Control2=IDC_BUTTON1,button,1342242816

[CLS:Poster]
Type=0
HeaderFile=Poster.h
ImplementationFile=Poster.cpp
BaseClass=CDialog
Filter=D
LastObject=Poster
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_VIEW_MAIN_WINDOW
Command2=ID_CANCEL
CommandCount=2

