#pragma once
#include "ofxLedScreen.h"
/************************************************************************/
/* project name:ÖÐ¿ØÈí¼þ
/* file describe:8080LED
/* author:hui
/* date:2018.5.15
/************************************************************************/
class ofx8080LedScreen : public ofxLedScreen
{
public:
	ofx8080LedScreen();
	~ofx8080LedScreen();

	void setup(string _ip);

	void setOn() override final;
	void setOff() override final;

private:
	string ip;
};

