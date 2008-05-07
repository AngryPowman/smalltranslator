// KeyBoard.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "KeyBoard.h"
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//共享内存段   // share memory segment
#pragma data_seg("seletedValue")
string seletedValue;
#pragma data_seg()
#pragma comment(linker,"/SECTION:seletedValue,RWS")

//一个句柄，是InstallLaunchEv函数的参数传进来的，开始把这个钩子安上的窗口的句柄
//a handle,whoes value is the InstallLaunchEv function's parament
HWND h_globalWind;
int g_hookkey;
#define WM_MYMSG WM_USER+520           //自定义消息//self define message
#define WM_MYMSG_DESTROY WM_USER+521

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CKeyBoardApp



BEGIN_MESSAGE_MAP(CKeyBoardApp, CWinApp)
	//{{AFX_MSG_MAP(CKeyBoardApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyBoardApp construction

CKeyBoardApp::CKeyBoardApp()
{
	//MessageBox(NULL, "CKeyBoardApp()", "KeyHook", MB_OK);
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


CKeyBoardApp::~CKeyBoardApp()
{
	//MessageBox(NULL, "~CKeyBoardApp()", "KeyHook", MB_OK);
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKeyBoardApp object

CKeyBoardApp theApp;

//my code
HHOOK Hook; 
int keydown=0;


//获取键盘消息，并且得到数据，数据保存在共享内存段的seletedValue里面
LRESULT CALLBACK LauncherHook(int nCode,WPARAM wParam,LPARAM lParam) 
{ 
	BOOL fEatKeystroke = FALSE;
    PKBDLLHOOKSTRUCT p = NULL;
	
	if (nCode < 0 ) // do not process message 
        return CallNextHookEx(Hook, nCode, wParam, lParam); 

	if(nCode==HC_ACTION) 
	{
		HWND h_Highlight_Wind;
		p = (PKBDLLHOOKSTRUCT) lParam;	

		
		switch(wParam) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if((p->vkCode==g_hookkey)&&(keydown==0)) //160,161是shift键的 ,164,165是alt键 ，162,163是ctrl键
			{		
				clock_t start=clock();
				TRACE("key down :%d",p->vkCode);
				keydown=1;
				h_Highlight_Wind=GetForegroundWindow();

				if (h_Highlight_Wind!=NULL) 
				{
					if (!OpenClipboard(NULL)) 
					{
						TRACE("can't open clipboard!");
						return CallNextHookEx(Hook,nCode,wParam,lParam); 
					}

					HGLOBAL data_clipboard[20];
					int id_format[20];
					unsigned long nSize[20];
					char * lpBuffer[20];
					LPSTR lpszData=NULL;
					
					UINT format=0;
					int i =0;   //保存剪贴板以前的内容！！！
					while(format=EnumClipboardFormats(format))
					{
						data_clipboard[i]=GetClipboardData(format);
						id_format[i]=format;
						if (data_clipboard[i]==NULL) 
						{
							lpBuffer[i]=NULL;
							nSize[i]=0;
							i++;
							continue;
						}
						lpszData=(LPSTR)GlobalLock(data_clipboard[i]);
						if(lpszData==NULL)
						{
							lpBuffer[i]=NULL;
							nSize[i]=0;
							i++;
							continue;
						}
						nSize[i]=GlobalSize(data_clipboard[i]);
						lpBuffer[i]=new char[nSize[i]];
						for (unsigned long j=0;j<nSize[i];j++) 
						{
							*(lpBuffer[i]+j)=*(lpszData+j);
						}
						GlobalUnlock(data_clipboard[i]);
						i++;
					}
					EmptyClipboard();
 					CloseClipboard();

					//按下ctrl+c键
					keybd_event(VK_CONTROL, 0, 0 ,0);
					keybd_event('C',(BYTE)0, 0 ,0); //此处可以用   'C', 用'c'不起作用.
					keybd_event('C', (BYTE)0, KEYEVENTF_KEYUP,0);
					if (g_hookkey!=162) 
						keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP,0);
					

					Sleep(20);
					
					if (!OpenClipboard(NULL)) 
					{
						TRACE("can't open clipboard!");
						return CallNextHookEx(Hook,nCode,wParam,lParam); 
					}

					HGLOBAL hMem_value=GetClipboardData(CF_TEXT);
					if(hMem_value!=NULL)
					{
						TRACE("....is not null....");
						LPSTR lptest=(LPSTR)GlobalLock(hMem_value);
						if (lptest!=NULL) {
							TRACE("data length is %d",strlen(lptest));
							seletedValue = lptest;
							GlobalUnlock(hMem_value);

							TRACE("sending create windows message!!!");
							PostMessage(h_globalWind,WM_MYMSG,0,0);
						}
					}
					else
						TRACE("no data in clipboard.!!!!!!!");

					EmptyClipboard();
					TRACE("clear clipboard.............");

					HGLOBAL hGlobal;
					lpszData=NULL;
					int j=0;
					TRACE("%d   %d",i,j);
					while (j<i)   //复原剪贴板的内容
					{
						if (lpBuffer[j]==NULL)
						{
							delete lpBuffer[j];
							lpBuffer[j]=NULL;
							j++;
							continue;
						}

						hGlobal=GlobalAlloc(GMEM_ZEROINIT,nSize[j]);
						if (hGlobal==NULL) 
						{
							delete lpBuffer[j];
							lpBuffer[j]=NULL;
							j++;
							continue;
						}

						lpszData = (LPSTR)GlobalLock(hGlobal);
						if (lpszData==NULL)
						{
							delete lpBuffer[j];
							lpBuffer[j]=NULL;
							j++;
							continue;
						}

						for (UINT pos=0;pos<nSize[j];pos++) 
						{
							*(lpszData+pos)=*(lpBuffer[j]+pos);
						}
						GlobalUnlock(hGlobal);

						SetClipboardData(id_format[j],hGlobal);

						delete lpBuffer[j];
						lpBuffer[j]=NULL;
						j++;
					}
					CloseClipboard();
				}
			}
				break;
				
			case WM_KEYUP:
			case WM_SYSKEYUP:

				if(p->vkCode==g_hookkey) //160是shift键的，164是alt键 ，162是ctrl键
				{
					if (g_hookkey == 162) 
						keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP,0);
					
					TRACE("key up :%d",p->vkCode);
					keydown=0;
					TRACE("GET shite up message ....");
					PostMessage(h_globalWind,WM_MYMSG_DESTROY,0,0);
				}
		default:;
		}
	} 
	return CallNextHookEx(Hook,nCode,wParam,lParam); 
} 


//安装钩子
DllExport void WINAPI InstallLaunchEv(HWND hWind,int hookkey) 
{
	h_globalWind = hWind;
	g_hookkey = hookkey;
	Hook=(HHOOK)SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LauncherHook, theApp.m_hInstance, 0); 
} 
DllExport bool WINAPI unHook()
{
	return UnhookWindowsHookEx(Hook);
}
//获得共享段的数据
DllExport string WINAPI getSeletedValue()
{
	return seletedValue;
}
//清空共享段的数据
DllExport void WINAPI cleardllVale()
{
	seletedValue.erase();
}
