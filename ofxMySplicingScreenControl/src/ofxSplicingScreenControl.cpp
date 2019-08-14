#include "ofxSplicingScreenControl.h"
#include "ofxScreenCmd.h"
#include "cmdConverter.h"


ofxSplicingScreenControl::ofxSplicingScreenControl()
{
	sender = NULL;
}


ofxSplicingScreenControl::~ofxSplicingScreenControl()
{
	if (sender)
	{
		delete sender;
	}
}

void ofxSplicingScreenControl::setup(string _ip)
{
	ip = _ip;
	sender = ofxDataSenderFacory::createUdpSender(ip, PORT_SPLICING_SCREEN_CONTROL);
}

void ofxSplicingScreenControl::setOn()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " on" << endl;
	sendCmd(convert(CMD_SPLICING_SCREEN_ON));
}

void ofxSplicingScreenControl::setOff()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " off" << endl;
	sendCmd(convert(CMD_SPLICING_SCREEN_OFF));
}

string ofxSplicingScreenControl::getIP()const
{
	return ip;
}

void ofxSplicingScreenControl::sendCmd(string _cmd)
{
	sender->sendData(_cmd.c_str(), _cmd.size());
}

string ofxSplicingScreenControl::convert(string _sourceStr)
{
	return cmdConverter::getEncryCmd(_sourceStr);
}