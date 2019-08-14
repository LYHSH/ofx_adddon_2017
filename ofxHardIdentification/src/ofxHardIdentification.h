#pragma once
#include "md5Converter.h"
#include "ofMain.h"
/************************************************************************/
/* project name:主机硬件标识码
/* file describe:
/* author:hui
/* date:2018.3.28
/************************************************************************/
class ofxHardIdentification
{
public:
	ofxHardIdentification();
	~ofxHardIdentification();

	static string getIdentification();						//获取唯一硬件码
	static string getCheckStr(string _identification);		//获取唯一硬件校验码
	static bool check(string _checkStr);		//校验码检测
	static void setExtraInfo(string _extraInfoStr);
private:
	static string extraInfoStr;					//附加信息，用于特定软件校验
};

