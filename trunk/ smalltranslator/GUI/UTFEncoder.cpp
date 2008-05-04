#include "UTFEncoder.h"
#include <afx.h>
#include <iostream>
#include <stdio.h>
#include <strstream>



string UTFEncoder::url_UTFEncoder(string input)
{
	CString c_input = input.c_str();
	ConvertGBKToUtf8(c_input);

	std::ostrstream utf_code;
	std::string outputstring;

	for (int i=0;i<c_input.GetLength();i++) 
	{
		int temp=c_input[i];
		temp=temp&0xff;
		utf_code<<'%';
		utf_code<<hex<<temp;
	}
	outputstring=utf_code.str();
	outputstring=outputstring.substr(0,c_input.GetLength()*3);
	return outputstring;
}


void UTFEncoder::ConvertUtf8ToGBK(CString& strUtf8) {
     int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0);
     unsigned short * wszGBK = new unsigned short[len+1];
     memset(wszGBK, 0, len * 2 + 2);
     MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, wszGBK, len);

     len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL); 
     char *szGBK=new char[len + 1];
     memset(szGBK, 0, len + 1);
     WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL);

     strUtf8 = szGBK;
     delete[] szGBK;
     delete[] wszGBK;
}

void UTFEncoder::ConvertGBKToUtf8(CString& strGBK) {
     int len=MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, NULL,0);
     unsigned short * wszUtf8 = new unsigned short[len+1];
     memset(wszUtf8, 0, len * 2 + 2);
     MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, wszUtf8, len);

     len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL); 
     char *szUtf8=new char[len + 1];
     memset(szUtf8, 0, len + 1);
     WideCharToMultiByte (CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL,NULL);

     strGBK = szUtf8;
     delete[] szUtf8;
     delete[] wszUtf8;
}