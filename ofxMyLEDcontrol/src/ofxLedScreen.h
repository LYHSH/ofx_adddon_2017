#pragma once
#include "ofxDataSenderFacory.h"
#include "ofxMyConstants.h"
/************************************************************************/
/* project name:中控软件
/* file describe:LED抽象类
/* author:hui
/* date:2018.3.2
/************************************************************************/
class ofxLedScreen
{
public:
	ofxLedScreen();
	~ofxLedScreen();

	virtual void setOn() = 0;
	virtual void setOff() = 0;

protected:
	void sendData(const char *_data, int _size);
	ofxDataSender * sender;
};

