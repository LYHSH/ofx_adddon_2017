#pragma once
#include "md5Converter.h"
#include "ofMain.h"
/************************************************************************/
/* project name:����Ӳ����ʶ��
/* file describe:
/* author:hui
/* date:2018.3.28
/************************************************************************/
class ofxHardIdentification
{
public:
	ofxHardIdentification();
	~ofxHardIdentification();

	static string getIdentification();						//��ȡΨһӲ����
	static string getCheckStr(string _identification);		//��ȡΨһӲ��У����
	static bool check(string _checkStr);		//У������
	static void setExtraInfo(string _extraInfoStr);
private:
	static string extraInfoStr;					//������Ϣ�������ض����У��
};

