#include <string>

using namespace std;

class Translator
{
public:
	string chineseToEnglish(string chinese);  //��Ӣ�ķ��������
	string englishToChinese(string english);   //���ĵ�Ӣ��
	string detectLanguage(string input);      //������Ե�����
	string autoTranslate(string input);       //�Զ�֪���������Ӣ�Ļ������ģ����ҽ�֮����
	string flexTranslate(string input, string sourcelang, string destlang);    //����Դ���Ժ�Ŀ�����Ա�ʾ�ķ���

};