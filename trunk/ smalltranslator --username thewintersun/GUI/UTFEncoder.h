#include <afx.h>
#include <string>

using namespace std;

class UTFEncoder
{
public:

	string url_UTFEncoder(string input);  //将UTF-8改成在url中包含%的字符串

	void ConvertUtf8ToGBK(CString& strUtf8); //将UTF-8编码的改成GBK编码

	void ConvertGBKToUtf8(CString& strGBK); //将GBK 改成 UTF-8
};