#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxMyConstants.h"
/************************************************************************/
/* file describe:�������绽��
/* date:2017.7.16
/* author:hui
/* update:2019.7.18(�Ż�)
/************************************************************************/
class ofxMacPowControl
{
public:
	ofxMacPowControl();
	~ofxMacPowControl();

	void setup();
	void powOn(string macStr);
	void powOff(string ip);

private:
	ofxUDPManager shutdownUdp;

	ofxUDPManager wakeupUdp;
};

