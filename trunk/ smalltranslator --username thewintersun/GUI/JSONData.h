#include <string>
using namespace std;

class JsonData
{
public:
	string getTranslaetedText(string input);  //���json�ṹ�е�translatedText������,�Ҳ����򷵻�Ϊempty��string

	string getDetectText(string input);   //����������Ե����֣��Ҳ����򷵻�Ϊempty��string

	string getResponseDetail(string input); //�õ���ϸ��Ϣ�����Ҳ���translatedText��ʱ������

};