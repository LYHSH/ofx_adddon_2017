#include "ofxLightingRelays.h"



ofxLightingRelays::ofxLightingRelays()
{
}


ofxLightingRelays::~ofxLightingRelays()
{
}



void ofxLightingRelays::setOn(int _id)
{
	ofLogNotice(OF_FUNCTION_NAME) << _id << ":on" << endl;

	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = getAddress();
	dataCodes[1] = 0x06;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0x03 + _id;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x01;

	unsigned short kk = CRC166(dataCodes, 6);
	unsigned char temp[2];

	memcpy(temp, &kk, 2);

	dataCodes[6] = temp[1];
	dataCodes[7] = temp[0];

	sendData(dataCodes, DATA_LEN);
}

void ofxLightingRelays::setOff(int _id)
{
	ofLogNotice(OF_FUNCTION_NAME) << _id << ":off" << endl;

	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = getAddress();
	dataCodes[1] = 0x06;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0x03 + _id;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x00;

	unsigned short kk = CRC166(dataCodes, 6);
	unsigned char temp[2];

	memcpy(temp, &kk, 2);

	dataCodes[6] = temp[1];
	dataCodes[7] = temp[0];

	sendData(dataCodes, DATA_LEN);
}

void ofxLightingRelays::setAllOn()
{
	ofLogNotice(OF_FUNCTION_NAME) << ":all on" << endl;

#ifdef ONE_AND_ONE
	for (int i = 0; i < MAX_LOOPS; i++)
	{
		setOn(i);
		ofSleepMillis(150);
	}
#else
	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 };
	dataCodes[0] = getAddress();
	dataCodes[1] = 0x06;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0x02;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x01;

	unsigned short kk = CRC166(dataCodes, 6);
	unsigned char temp[2];

	memcpy(temp, &kk, 2);

	dataCodes[6] = temp[1];
	dataCodes[7] = temp[0];

	sendData(dataCodes, DATA_LEN);
#endif
	
}

void ofxLightingRelays::setAllOff()
{
	ofLogNotice(OF_FUNCTION_NAME) << ":all off" << endl;

#ifdef ONE_AND_ONE
	for (int i = 0; i <  MAX_LOOPS; i++)
	{
		setOff(i);
		ofSleepMillis(150);
	}
#else
	static int const DATA_LEN = 8;
	unsigned char dataCodes[DATA_LEN] = { 0x00 }; 
	dataCodes[0] = getAddress();
	dataCodes[1] = 0x06;
	dataCodes[2] = 0x00;
	dataCodes[3] = 0x01;
	dataCodes[4] = 0x00;
	dataCodes[5] = 0x00;

	unsigned short kk = CRC166(dataCodes, 6);
	unsigned char temp[2];

	memcpy(temp, &kk, 2);

	dataCodes[6] = temp[1];
	dataCodes[7] = temp[0];

	sendData(dataCodes, DATA_LEN);
#endif
	
}

void ofxLightingRelays::setMultOn(vector<int> & _ids)
{
	stringstream sss;
	for (int i = 0; i < _ids.size(); i++)
	{
		sss << _ids[i] << " ";
	}
	ofLogNotice(OF_FUNCTION_NAME) << sss.str() << ":on" << endl;


	for (int i = 0; i < _ids.size(); i++)
	{
		setOn(_ids[i]);
		ofSleepMillis(200);
	}
}

void ofxLightingRelays::setMultOff(vector<int> & _ids)
{
	stringstream sss;
	for (int i = 0; i < _ids.size(); i++)
	{
		sss << _ids[i] << " ";
	}
	ofLogNotice(OF_FUNCTION_NAME) << sss.str() << ":off" << endl;

	for (int i = 0; i < _ids.size(); i++)
	{
		setOff(_ids[i]);
		ofSleepMillis(200);
	}
}


