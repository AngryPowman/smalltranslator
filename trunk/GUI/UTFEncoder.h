#include <afx.h>
#include <string>

using namespace std;

class UTFEncoder
{
public:

	string url_UTFEncoder(string input);  //��UTF-8�ĳ���url�а���%���ַ���

	void ConvertUtf8ToGBK(CString& strUtf8); //��UTF-8����ĸĳ�GBK����

	void ConvertGBKToUtf8(CString& strGBK); //��GBK �ĳ� UTF-8
};