#include "ofx55LongtengRelays.h"



ofx55LongtengRelays::ofx55LongtengRelays()
{
}


ofx55LongtengRelays::~ofx55LongtengRelays()
{
}

void ofx55LongtengRelays::setOn(int _id)
{
	ofLogNotice(OF_FUNCTION_NAME) << _id << ":on" << endl;

	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x55;
	dataCodes[1] = getAddress();
	dataCodes[2] = 0x12;
	dataCodes[3] = 0x00;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x00;
	dataCodes[6] = 0x01 + _id;
	dataCodes[7] = GetSumVerify(0, 6, dataCodes);

	sendData(dataCodes, DATA_LEN);
}

void ofx55LongtengRelays::setOff(int _id)
{
	ofLogNotice(OF_FUNCTION_NAME) << _id << ":off" << endl;
	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x55;
	dataCodes[1] = getAddress();
	dataCodes[2] = 0x11;
	dataCodes[3] = 0x00;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x00;
	dataCodes[6] = 0x01 + _id;
	dataCodes[7] = GetSumVerify(0, 6, dataCodes);

	sendData(dataCodes, DATA_LEN);
}

void ofx55LongtengRelays::setMultOn(vector<int> & _ids)
{
	stringstream sss;
	for (int i = 0; i < _ids.size(); i++)
	{
		sss << _ids[i] << " ";
	}
	ofLogNotice(OF_FUNCTION_NAME) << sss.str() << ":on" << endl;

	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x55;
	dataCodes[1] = getAddress();
	dataCodes[2] = 0x15;

	setDataBit(dataCodes, 3, 4, getBinaryStr(_ids));

	dataCodes[7] = GetSumVerify(0, 6, dataCodes);

	sendData(dataCodes, DATA_LEN);
}

void ofx55LongtengRelays::setMultOff(vector<int> & _ids)
{
	stringstream sss;
	for (int i = 0; i < _ids.size(); i++)
	{
		sss << _ids[i] << " ";
	}
	ofLogNotice(OF_FUNCTION_NAME) << sss.str() << ":off" << endl;
	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x55;
	dataCodes[1] = getAddress();
	dataCodes[2] = 0x16;

	setDataBit(dataCodes, 3, 4, getBinaryStr(_ids));

	dataCodes[7] = GetSumVerify(0, 6, dataCodes);

	sendData(dataCodes, DATA_LEN);
}

void ofx55LongtengRelays::setSingleOn(vector<int> & _ids)
{
	stringstream sss;
	for (int i = 0; i < _ids.size(); i++)
	{
		sss << _ids[i] << " ";
	}
	ofLogNotice(OF_FUNCTION_NAME) << sss.str() << ":mult single on" << endl;

	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x55;
	dataCodes[1] = getAddress();
	dataCodes[2] = 0x13;

	setDataBit(dataCodes, 3, 4, getBinaryStr(_ids));

	dataCodes[7] = GetSumVerify(0, 6, dataCodes);

	sendData(dataCodes, DATA_LEN);
}

void ofx55LongtengRelays::setAllOn()
{
	ofLogNotice(OF_FUNCTION_NAME) << "all on" << endl;
	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x55;
	dataCodes[1] = getAddress();
	dataCodes[2] = 0x13;
	dataCodes[3] = 0xFF;
	dataCodes[4] = 0xFF;
	dataCodes[5] = 0xFF;
	dataCodes[6] = 0xFF;
	dataCodes[7] = GetSumVerify(0, 6, dataCodes);

	sendData(dataCodes, DATA_LEN);
}

void ofx55LongtengRelays::setAllOff()
{
	ofLogNotice(OF_FUNCTION_NAME) << "all off" << endl;
	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = 0x55;
	dataCodes[1] = getAddress();
	dataCodes[2] = 0x13;
	dataCodes[3] = 0x00;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x00;
	dataCodes[6] = 0x00;
	dataCodes[7] = GetSumVerify(0, 6, dataCodes);

	sendData(dataCodes, DATA_LEN);
}