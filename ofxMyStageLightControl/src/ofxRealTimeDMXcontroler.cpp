#include "ofxRealTimeDMXcontroler.h"



ofxRealTimeDMXcontroler::ofxRealTimeDMXcontroler()
{
	setAddress(0x26);
}


ofxRealTimeDMXcontroler::~ofxRealTimeDMXcontroler()
{
}

void ofxRealTimeDMXcontroler::play(int _id)
{
	if (_id < 0)
	{
		ofLogError(OF_FUNCTION_NAME) << "id out of range!!!" << " id = " << _id << endl;
	}

	ofLogNotice(OF_FUNCTION_NAME) << _id << ":play" << endl;

	static int const DATA_LEN = 12;
	static unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x68;
	dataCodes[1] = 0x06;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0xFF;
	dataCodes[4] = 0xFF;
	dataCodes[5] = 0x05;
	dataCodes[6] = 0x26;
	int tenBitValue = _id / 10;
	int oneBitValue = _id % 10;
	dataCodes[7] = 0x30 + tenBitValue;
	dataCodes[8] = 0x30 + oneBitValue;
	dataCodes[9] = 0x90 + oneBitValue + tenBitValue - 1;
	dataCodes[10] = 0xC3;
	dataCodes[11] = 0x16;

	sendData(dataCodes, DATA_LEN);
}
