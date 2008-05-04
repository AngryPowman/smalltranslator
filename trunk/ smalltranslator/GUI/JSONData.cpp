#include "JSONData.h"
#include "json.h"


string JsonData::getTranslaetedText(string input)
{
	if (input.empty()) {
		return "���������ؿ�ֵ";
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(input, root );
	if ( !parsingSuccessful )
	{
		return "���ܷ���Ŀ������,json ��������";
	}

	Json::Value responseDataValue;
	Json::Value translatedValue;
	try
	{
		responseDataValue=root["responseData"];
		translatedValue = responseDataValue["translatedText"];

	}
	catch (exception e) {
		return "����JSON����";
	}

	return translatedValue.asString();
}

string JsonData::getDetectText(string input)
{
	if (input.empty()) {
		return "���������ؿ�ֵ";
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(input, root );
	if ( !parsingSuccessful )
	{
		return "���ܷ���Ŀ�����ԣ�json ��������";
	}

	Json::Value responseDataValue;
	Json::Value detectedlanguage;
	try
	{
		responseDataValue=root["responseData"];
		detectedlanguage = responseDataValue["language"];
		
	}
	catch (exception e) {
		return "����JSON����";
	}
	return detectedlanguage.asString();
}

string JsonData::getResponseDetail(string input)
{
	if (input.empty()) {
		return "���������ؿ�ֵ";
	}
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(input, root );
	if ( !parsingSuccessful )
	{
		return "���ܷ���Ŀ�����ԣ�json ��������";
	}

	Json::Value responseDetailsValue;
	try
	{
		responseDetailsValue=root["responseDetails"];		
	}
	catch (exception e) {
		return "����JSON����";
	}

	return responseDetailsValue.asString();
}