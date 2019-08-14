#include "ofxLYDledScreen.h"



ofxLYDledScreen::ofxLYDledScreen()
{
}


ofxLYDledScreen::~ofxLYDledScreen()
{
}

void ofxLYDledScreen::setup(string _ip)
{
	static int const port = 6666;

	ip = _ip;

	sender = ofxDataSenderFacory::createUdpSender(ip, port);
}

void ofxLYDledScreen::setOn()
{
	static int const cmdSize = 21;
	static unsigned char onCmd[cmdSize] = { 
		0x3A,0x30,0x30,0x31,0x30,0x30,0x30,
		0x42,0x30,0x30,0x30,0x30,0x31,0x30,
		0x30,0x30,0x31,0x33,0x45,0x0D,0x0A };

	ofLogNotice(OF_FUNCTION_NAME) << "ip: " << ip <<"  on"<<endl;

	sendData((char *)onCmd, cmdSize);
}

void ofxLYDledScreen::setOff()
{
	static int const cmdSize = 21;
	static unsigned char offCmd[cmdSize] = { 
		0x3A,0x30,0x30,0x31,0x30,0x30,0x30,
		0x42,0x30,0x30,0x30,0x30,0x31,0x30,
		0x30,0x30,0x32,0x33,0x44,0x0D,0x0A };

	ofLogNotice(OF_FUNCTION_NAME) << "ip: " << ip << "  off" << endl;

	sendData((char *)offCmd, cmdSize);
}
