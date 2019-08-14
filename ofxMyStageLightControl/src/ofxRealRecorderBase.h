#pragma once
#include "ofMain.h"
#include "ofxRecorderBase.h"
#include "ofxDataSenderFacory.h"
/************************************************************************/
/* project name:录播控制器
/* file describe:实际控制器基类
/* author:hui
/* date:2018.3.19
/************************************************************************/
class ofxRealRecorderBase : public ofxRecorderBase
{
public:
	ofxRealRecorderBase();
	virtual ~ofxRealRecorderBase();

	void setup(int _comNum, int _nBaud, unsigned char _addressCode = 0x01);
	void setup(string _ip, int _port, unsigned char _addressCode = 0x01);
	void setupUdp(string _ip, int _port, unsigned char _addressCode = 0x01);

	void setup(ofxDataSender * _sender, unsigned char _addressCode = 0x01);
protected:
	bool sendData(const unsigned char * _data, int _size);

	void setAddress(unsigned char _address);
	unsigned char getAddress()const;
private:
	ofxDataSender * sender;
	unsigned char address;
};

