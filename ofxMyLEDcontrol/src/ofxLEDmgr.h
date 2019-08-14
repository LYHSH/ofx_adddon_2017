#pragma once
#include "ofxLedScreenFactory.h"
#include "ofxXmlSettings.h"
/************************************************************************/
/* project name:中控软件
/* file describe:LED管理器
/* author:hui
/* date:2018.3.2
/************************************************************************/
class ofxLEDmgr
{
public:
	ofxLEDmgr();
	~ofxLEDmgr();

	void setup(const string & _filename);

	void setOn(int _index);
	void setOff(int _index);

	void setAllOn();
	void setAllOff();

	int size()const;

private:
	bool checkOut(int _index);
	vector<ofxLedScreen *> leds;
};

