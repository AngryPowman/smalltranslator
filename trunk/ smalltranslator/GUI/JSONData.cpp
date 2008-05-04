#include "JSONData.h"
#include "json.h"


string JsonData::getTranslaetedText(string input)
{
	if (input.empty()) {
		return "服务器返回空值";
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(input, root );
	if ( !parsingSuccessful )
	{
		return "不能翻译目标语言,json 解析错误";
	}

	Json::Value responseDataValue;
	Json::Value translatedValue;
	try
	{
		responseDataValue=root["responseData"];
		translatedValue = responseDataValue["translatedText"];

	}
	catch (exception e) {
		return "解析JSON错误";
	}

	return translatedValue.asString();
}

string JsonData::getDetectText(string input)
{
	if (input.empty()) {
		return "服务器返回空值";
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(input, root );
	if ( !parsingSuccessful )
	{
		return "不能翻译目标语言，json 解析错误";
	}

	Json::Value responseDataValue;
	Json::Value detectedlanguage;
	try
	{
		responseDataValue=root["responseData"];
		detectedlanguage = responseDataValue["language"];
		
	}
	catch (exception e) {
		return "解析JSON错误";
	}
	return detectedlanguage.asString();
}

string JsonData::getResponseDetail(string input)
{
	if (input.empty()) {
		return "服务器返回空值";
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(input, root );
	if ( !parsingSuccessful )
	{
		return "不能翻译目标语言，json 解析错误";
	}

	Json::Value responseDetailsValue;
	try
	{
		responseDetailsValue=root["responseDetails"];		
	}
	catch (exception e) {
		return "解析JSON错误";
	}

	return responseDetailsValue.asString();
}