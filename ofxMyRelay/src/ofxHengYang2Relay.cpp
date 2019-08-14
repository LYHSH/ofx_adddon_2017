#include "ofxHengYang2Relay.h"



ofxHengYang2Relay::ofxHengYang2Relay()
{
}


ofxHengYang2Relay::~ofxHengYang2Relay()
{
}

void ofxHengYang2Relay::setOn(int _id)
{
	ofLogNotice(OF_FUNCTION_NAME) << _id << ":on" << endl;

	static int const DATA_LEN = 13;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x5C;
	dataCodes[1] = 0x30;
	dataCodes[2] = 0x35;
	dataCodes[3] = 0x33;
	dataCodes[4] = 0x38;
	dataCodes[5] = 0x30;
	dataCodes[6] = 0x30;
	dataCodes[7] = 0x37;
	dataCodes[8] = 0x39;
	dataCodes[9] = 0x30;


	if (_id >= 0 && _id <= 8)
	{
		dataCodes[10] = 0x31 + _id;
	}
	else if (_id >= 9 && _id <= 14)
	{
		dataCodes[10] = 0x41 + _id - 9;
	}
	else if (_id >= 15 && _id <= 23)
	{
		dataCodes[9] = 0x31;
		dataCodes[10] = 0x30 + _id - 15;
	}
	

	
	dataCodes[11] = 0x0D;
	dataCodes[12] = 0x0A;
	

	sendData(dataCodes, DATA_LEN);
}

void ofxHengYang2Relay::setOff(int _id)
{
	ofLogNotice(OF_FUNCTION_NAME) << _id << ":off" << endl;

	static int const DATA_LEN = 13;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x5C;
	dataCodes[1] = 0x30;
	dataCodes[2] = 0x35;
	dataCodes[3] = 0x33;
	dataCodes[4] = 0x38;
	dataCodes[5] = 0x30;
	dataCodes[6] = 0x30;
	dataCodes[7] = 0x30;
	dataCodes[8] = 0x31;
	dataCodes[9] = 0x30;

	if (_id >= 0 && _id <= 8)
	{
		dataCodes[10] = 0x31 + _id;
	}
	else if (_id >= 9 && _id <= 14)
	{
		dataCodes[10] = 0x41 + _id - 9;
	}
	else if (_id >= 15 && _id <= 23)
	{
		dataCodes[9] = 0x31;
		dataCodes[10] = 0x30 + _id - 15;
	}
	dataCodes[11] = 0x0D;
	dataCodes[12] = 0x0A;


	sendData(dataCodes, DATA_LEN);
}


