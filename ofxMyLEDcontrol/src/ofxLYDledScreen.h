#pragma once
#include "ofMain.h"
#include "ofxLedScreen.h"
/************************************************************************/
/* project name:中控软件
/* file describe:利亚德LED
/* author:hui
/* date:2018.3.2
/************************************************************************/
class ofxLYDledScreen : public ofxLedScreen
{
public:
	ofxLYDledScreen();
	~ofxLYDledScreen();

	void setup(string _ip);

	void setOn() override final;
	void setOff() override final;
private:
	string ip;
};

