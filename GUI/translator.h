#include <string>

using namespace std;

class Translator
{
public:
	string chineseToEnglish(string chinese);  //将英文翻译成中文
	string englishToChinese(string english);   //中文到英文
	string detectLanguage(string input);      //侦测语言的语种
	string autoTranslate(string input);       //自动知道输入的是英文还是中文，并且将之翻译
	string flexTranslate(string input, string sourcelang, string destlang);    //带有源语言和目标语言标示的翻译

};