#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxMyConstants.h"
/************************************************************************/
/* file describe:�������绽��
/* date:2017.7.16
/* author:hui
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
	struct sockaddr_in addr;
	SOCKET m_hSocket;
	ofxUDPManager udpConnection;
};

