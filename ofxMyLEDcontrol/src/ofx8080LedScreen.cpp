#include "ofx8080LedScreen.h"



ofx8080LedScreen::ofx8080LedScreen()
{
}


ofx8080LedScreen::~ofx8080LedScreen()
{
}

void ofx8080LedScreen::setup(string _ip)
{
	static int const port = 8080;

	ip = _ip;

	sender = ofxDataSenderFacory::createUdpSender(ip, port);
}

void ofx8080LedScreen::setOn()
{
	static int const cmdSize = 15;
	static unsigned char onCmd[cmdSize] = {
		0x00,0x00,0x00,0x00,0x00,
		0x09,0xff,0x10,0x00,0x02,
		0x00,0x01,0x02,0x03,0xff };

	ofLogNotice(OF_FUNCTION_NAME) << "ip: " << ip << "  on" << endl;

	sendData((char *)onCmd, cmdSize);
}

void ofx8080LedScreen::setOff()
{
	static int const cmdSize = 15;
	static unsigned char offCmd[cmdSize] = {
		0x00,0x00,0x00,0x00,0x00,
		0x09,0xff,0x10,0x00,0x03,
		0x00,0x01,0x02,0x03,0xff };

	ofLogNotice(OF_FUNCTION_NAME) << "ip: " << ip << "  off" << endl;

	sendData((char *)offCmd, cmdSize);
}