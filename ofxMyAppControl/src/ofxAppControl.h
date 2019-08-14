#pragma once
#include "ofxXmlSettings.h"
/************************************************************************/
/* file describe:appœ‘ æøÿ÷∆
/* author:hui
/* date:2018.10.15
/************************************************************************/
class ofxAppControl
{
public:
	static void setup(string _titleName);
	static void udpate();

	static bool isShowing();
private:
	ofxAppControl();
	~ofxAppControl();

	static string fileDir;
	static HWND thiswnd;
	static bool bShow;
};

