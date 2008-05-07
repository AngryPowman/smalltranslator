#include <string>
using namespace std;

class JsonData
{
public:
	string getTranslaetedText(string input);  //获得json结构中的translatedText的内容,找不到则返回为empty的string

	string getDetectText(string input);   //获得侦测的语言的语种，找不到则返回为empty的string

	string getResponseDetail(string input); //得到详细信息，当找不到translatedText的时候有用

};