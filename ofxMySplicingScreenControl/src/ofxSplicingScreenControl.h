#pragma once
#include "ofMain.h"
#include "ofxDataSenderFacory.h"
#include "ofxMyConstants.h"
/************************************************************************/
/* file describe:拼接屏远程控制类
/* author:hui
/* date:2017.9.27
/************************************************************************/
class ofxSplicingScreenControl
{
public:
	ofxSplicingScreenControl();
	~ofxSplicingScreenControl();

	void setup(string _ip);

	void setOn();
	void setOff();

	string getIP()const;
private:
	void sendCmd(string _cmd);
	string convert(string _sourceStr);
	string ip;
	int port;
	ofxDataSender * sender;
};

