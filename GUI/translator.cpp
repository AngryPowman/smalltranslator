#include "UTFEncoder.h"
#include "JSONData.h"
#include "translator.h"

#include "curl/curl.h"
#include <iostream>

using namespace std;

#pragma comment(lib,"libcurl_imp.lib")

int writer(char *data, size_t size, size_t nmemb, string *writerData)
{
    if (writerData == NULL)
        return 0;
    int len = size*nmemb;
    writerData->append(data, len); 

    return len;
}

string Translator::chineseToEnglish(const string chinese)
{
	return flexTranslate(chinese, "zh","en");
}

string Translator::englishToChinese(string english)
{
	return flexTranslate(english, "en", "zh-CN");
}

string Translator::detectLanguage(string input)
{
	string detected;
	if (input.empty()) 
	{
		detected.erase();
		return detected;
	}
	string buffer;
	string detect_url("http://ajax.googleapis.com/ajax/services/language/detect?");
	string param_v("v=1.0");
	string param_q("q=");

	UTFEncoder encoder;
	string text = encoder.url_UTFEncoder(input);

	detect_url+=param_v+"&"+param_q+text;

	CURL * curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) 
	{
		curl_easy_setopt(curl,CURLOPT_URL,detect_url.c_str());
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writer);
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,&buffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	JsonData json;
	detected = json.getDetectText(buffer);
	return detected;
}

string Translator::autoTranslate(string input)
{
	string result;
	string detectedlang=detectLanguage(input);
	if (detectedlang.empty()||(detectedlang.size()<2)) 
	{
		result.erase();
		return result;
	}
	if ((detectedlang[0]=='z')&&(detectedlang[1]=='h')) //源语言是中文
	{
		result = chineseToEnglish(input);
		return result;
	}
	
#if 0

	if(detectedlang=="en")
	{
		result = englishToChinese(input);
		return result;
	}
	else
	{
		result="不能翻译目标语言";
		return result;
	}
	
#else
	result = englishToChinese(input);        //english to chinese
	return result;	
#endif
	
}


string Translator::flexTranslate(const string input, string sourcelang, string destlang)
{
	string buffer;
	string translate_url("http://ajax.googleapis.com/ajax/services/language/translate?");
	string param_v("v=1.0");
	string param_q("q=");
	string param_langpair("langpair=");
	string langpair=sourcelang + "%7C" + destlang;

	UTFEncoder encoder;
	string text = encoder.url_UTFEncoder(input);
	translate_url += param_v+"&"+ param_q + text + "&" + param_langpair + langpair;

	CURL * curl;
	CURLcode res;
	curl = curl_easy_init();

	if (curl) 
	{
		curl_easy_setopt(curl,CURLOPT_URL,translate_url.c_str());
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writer);
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,&buffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	
	JsonData json;

	string translated = json.getTranslaetedText(buffer);
	if (translated.empty())
	{
		translated = json.getResponseDetail(buffer);
	}
	CString c_translated = translated.c_str();
	encoder.ConvertUtf8ToGBK(c_translated);
	translated = c_translated.GetBuffer(0);
	return translated;
}