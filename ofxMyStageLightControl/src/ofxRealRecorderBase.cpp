#include "ofxRealRecorderBase.h"



ofxRealRecorderBase::ofxRealRecorderBase()
{
	sender = NULL;
}


ofxRealRecorderBase::~ofxRealRecorderBase()
{
	if (sender)
	{
		sender->close();
		delete sender;
		sender = NULL;
	}
}

void ofxRealRecorderBase::setup(int _comNum, int _nBaud, unsigned char _addressCode /* = 0x01 */)
{
	setAddress(_addressCode);
	sender = ofxDataSenderFacory::createSerialSender(_comNum, _nBaud);
}

void ofxRealRecorderBase::setup(string _ip, int _port, unsigned char _addressCode /* = 0x01 */)
{
	setAddress(_addressCode);
	sender = ofxDataSenderFacory::createTcpSender(_ip, _port);
}

void ofxRealRecorderBase::setupUdp(string _ip, int _port, unsigned char _addressCode /* = 0x01 */)
{
	setAddress(_addressCode);
	sender = ofxDataSenderFacory::createUdpSender(_ip, _port);
}

void ofxRealRecorderBase::setup(ofxDataSender * _sender, unsigned char _addressCode /* = 0x01 */)
{
	setAddress(_addressCode);
	if (sender)delete sender;
	
	sender = _sender;
}

bool ofxRealRecorderBase::sendData(const unsigned char * _data, int _size)
{
	if (NULL == sender)return false;

	return sender->sendData((char *)_data, _size);
}

void ofxRealRecorderBase::setAddress(unsigned char _addressCode)
{
	address = _addressCode;
}

unsigned char ofxRealRecorderBase::getAddress()const
{
	return address;
}
