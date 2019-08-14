#include "ofxHuangControler.h"



ofxHuangControler::ofxHuangControler()
{
}


ofxHuangControler::~ofxHuangControler()
{
}

void ofxHuangControler::play(int _id)
{
	if (_id < 0)
	{
		ofLogError(OF_FUNCTION_NAME) << "id out of range!!!" << " id = " << _id << endl;
	}

	ofLogNotice(OF_FUNCTION_NAME) << _id << ":play" << endl;

	static int const codeNums = 12;
	static const unsigned char initCodes[codeNums] = { 0x68, 0x06, 0x00, 0xFF, 0xFF, 0x05, 0x04, 0x30, 0x31, 0x6E, 0xC3, 0x16 };
	unsigned char codes[codeNums] = { 0x00 };
	memcpy(codes, initCodes, codeNums);
	if (_id >= 1 && _id < 10)
	{
		codes[7] = 0x30;
		codes[8] = 0x31;
		codes[9] = 0x6E;
	}
	else if (_id >= 11 && _id < 20)
	{
		_id -= 10;
		codes[7] = 0x31;
		codes[8] = 0x31;
		codes[9] = 0x6F;
	}
	else if (_id >= 21 && _id < 30)
	{
		_id -= 20;
		codes[7] = 0x32;
		codes[8] = 0x31;
		codes[9] = 0x70;
	}
	else if (_id >= 31 && _id < 40)
	{
		_id -= 30;
		codes[7] = 0x33;
		codes[8] = 0x31;
		codes[9] = 0x71;
	}
	else if (_id >= 41 && _id < 50)
	{
		_id -= 40;
		codes[7] = 0x34;
		codes[8] = 0x31;
		codes[9] = 0x72;
	}
	else if (_id >= 51 && _id < 60)
	{
		_id -= 50;
		codes[7] = 0x35;
		codes[8] = 0x31;
		codes[9] = 0x73;
	}
	else if (_id >= 61 && _id < 70)
	{
		_id -= 60;
		codes[7] = 0x36;
		codes[8] = 0x31;
		codes[9] = 0x74;
	}
	else if (_id >= 71 && _id < 80)
	{
		_id -= 70;
		codes[7] = 0x37;
		codes[8] = 0x31;
		codes[9] = 0x75;
	}
	else if (_id >= 81 && _id < 90)
	{
		_id -= 80;
		codes[7] = 0x38;
		codes[8] = 0x31;
		codes[9] = 0x76;
	}
	else if (_id >= 91 && _id < 100)
	{
		_id -= 90;
		codes[7] = 0x39;
		codes[8] = 0x31;
		codes[9] = 0x77;
	}
	codes[8] += (_id - 1);
	codes[9] += (_id - 1);

	sendData(codes, codeNums);
}

void ofxHuangControler::play()
{
	ofLogNotice(OF_FUNCTION_NAME) <<":play" << endl;
	static int const codeNums = 10;
	static const unsigned char initCodes[codeNums] = { 0x68, 0x04, 0x00, 0xFF, 0xFF, 0x05, 0xA4, 
		0xAB, 0xC3, 0x16};

	unsigned char codes[codeNums] = { 0x00 };
	memcpy(codes, initCodes, codeNums);

	sendData(codes,codeNums);
}

void ofxHuangControler::pause()
{
	ofLogNotice(OF_FUNCTION_NAME) << ":pause" << endl;

	static int const codeNums = 10;
	static const unsigned char initCodes[codeNums] = { 0x68, 0x04, 0x00, 0xFF, 0xFF, 0x05, 0xA4,
		0xAB, 0xC3, 0x16 };

	unsigned char codes[codeNums] = { 0x00 };
	memcpy(codes, initCodes, codeNums);

	sendData(codes, codeNums);
}

void ofxHuangControler::stop()
{
	ofLogNotice(OF_FUNCTION_NAME) << ":stop" << endl;

	static int const codeNums = 12;
	static const unsigned char initCodes[codeNums] = { 0x68, 0x06, 0x00, 0xFF, 0xFF, 0x05, 0x04, 0x30,
		0x31, 0x6E, 0xC7, 0x1A };

	unsigned char codes[codeNums] = { 0x00 };
	memcpy(codes, initCodes, codeNums);

	sendData(codes, codeNums);
}
