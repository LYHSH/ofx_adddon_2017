#include "ofx2000seriesRelays.h"



ofx2000seriesRelays::ofx2000seriesRelays()
{
}


ofx2000seriesRelays::~ofx2000seriesRelays()
{
}

void ofx2000seriesRelays::setOn(int _id)
{
	ofLogNotice(OF_FUNCTION_NAME) << _id << ":on" << endl;

	static int const DATA_LEN = 9;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x25;
	dataCodes[1] = 0x00;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0x00;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x02;
	dataCodes[6] = 0x00 ;
	dataCodes[7] = 0x00 + _id;
	dataCodes[8] = 0x00;

	sendData(dataCodes, DATA_LEN);
}

void ofx2000seriesRelays::setOff(int _id)
{
	ofLogNotice(OF_FUNCTION_NAME) << _id << ":off" << endl;
	static int const DATA_LEN = 9;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x26;
	dataCodes[1] = 0x00;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0x00;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x02;
	dataCodes[6] = 0x00;
	dataCodes[7] = 0x00 + _id;
	dataCodes[8] = 0x00;

	sendData(dataCodes, DATA_LEN);
}

void ofx2000seriesRelays::setAllOn()
{
	ofLogNotice(OF_FUNCTION_NAME) << "all on" << endl;
	static int const DATA_LEN = 12;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x03;
	dataCodes[1] = 0x00;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0x00;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x05;
	dataCodes[6] = 0x00;
	dataCodes[7] = 0x20;
	dataCodes[8] = 0xFF;
	dataCodes[9] = 0xFF;
	dataCodes[10] = 0xFF;
	dataCodes[11] = 0xFF;

	sendData(dataCodes, DATA_LEN);
}

void ofx2000seriesRelays::setAllOff()
{
	ofLogNotice(OF_FUNCTION_NAME) << "all off" << endl;
	static int const DATA_LEN = 12;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x03;
	dataCodes[1] = 0x00;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0x00;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x05;
	dataCodes[6] = 0x00;
	dataCodes[7] = 0x20;
	dataCodes[8] = 0x00;
	dataCodes[9] = 0x00;
	dataCodes[10] = 0x00;
	dataCodes[11] = 0x00;

	sendData(dataCodes, DATA_LEN);
}

