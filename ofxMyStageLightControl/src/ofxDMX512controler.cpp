#include "ofxDMX512controler.h"
#include "checkDigitCalculation.h"


ofxDMX512controler::ofxDMX512controler()
{
}


ofxDMX512controler::~ofxDMX512controler()
{
}

void ofxDMX512controler::play(int _id)
{
	if (_id < 0)
	{
		ofLogError(OF_FUNCTION_NAME) << "id out of range!!!" << " id = " << _id << endl;
	}

	ofLogNotice(OF_FUNCTION_NAME) << _id << ":play" << endl;

	static int const DATA_LEN = 10;
	static unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x55;
	dataCodes[1] = 0xAA;
	dataCodes[2] = getAddress();
	dataCodes[3] = 0x03;
	dataCodes[4] = 0x09;
	dataCodes[5] = 0x03;
	int hundredsValue = _id / 100;
	int tenBitValue = (_id % 100) / 10;
	int oneBitValue = _id % 10;
	dataCodes[6] = 0x30 + hundredsValue;
	dataCodes[7] = 0x30 + tenBitValue;
	dataCodes[8] = 0x30 + oneBitValue;
	dataCodes[9] = ofGetSumVerifySub(2, DATA_LEN-2, dataCodes);

	sendData(dataCodes, DATA_LEN);
}
