#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"
/************************************************************************/
/* project name:主机硬件标识码
/* file describe:管理器
/* author:hui
/* date:2018.3.28
/************************************************************************/
class ofxIdentificationMgr
{
public:
	
	static void setup();
	static void update();

	static void generateIdentification();
	static bool check();
	static void generateCheckStr();
	static void generateCheckStr(string _filename);
	static void generateCheckStr(string _filename,string _dir);
	static void setExtraInfo(string _extraInfoStr);
private:
	ofxIdentificationMgr();
	~ofxIdentificationMgr();
	static bool isRegistered;

	static int checkKey;
};

