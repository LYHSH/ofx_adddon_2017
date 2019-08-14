#include "ofxPJcomControl.h"



ofxPJcomControl::ofxPJcomControl()
{
	sender = NULL;
	bFirstSend = true;
}


ofxPJcomControl::~ofxPJcomControl()
{
	if (sender)
	{
		sender->close();
		delete sender;
		sender = NULL;
	}
}

void ofxPJcomControl::setup(string _comName)
{
	comName = _comName;
}

void ofxPJcomControl::setOn()
{
	setOnOoff(true);
}

void ofxPJcomControl::setOff()
{
	setOnOoff(false);
}

string ofxPJcomControl::getName()const
{
	return getCOM();
}

string ofxPJcomControl::getCOM()const
{
	return comName;
}

void ofxPJcomControl::sendCmd(string _msg,int _nbaud)
{
	if (bFirstSend)
	{
		sender = ofxDataSenderFacory::createSerialSender(comName, _nbaud);
		bFirstSend = false;
	}
	sender->sendData(_msg.c_str(), _msg.size());
}
