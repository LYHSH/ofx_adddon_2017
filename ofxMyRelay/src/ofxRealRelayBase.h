#pragma once
#include "ofxRelaysBase.h"
#include "ofxDataSenderFacory.h"
#include "checkDigitCalculation.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:真实继电器基类
/* date:2017.1.29
/* author:hui
/* update:2018.11.12   子类接口上移
/************************************************************************/
class ofxRealRelayBase : public ofxRelaysBase
{
public:
	ofxRealRelayBase();
	~ofxRealRelayBase();

	void setup(ofxDataSender * _sender, unsigned char _addressCode = 0x01);
	void setup(int _comNum, int _nBaud, unsigned char _addressCode = 0x01);
	void setup(string _ip, int _port, unsigned char _addressCode = 0x01);
	void udpSetup(string _ip, int _port, unsigned char _addressCode = 0x01);

	void close() final;
protected:
	bool sendData(const unsigned char * _data, int _size);

	unsigned char GetSumVerify(int nStart, int nEnd, const unsigned char * _dataCode);
	unsigned short CRC166(unsigned char *puchMsg, unsigned short usDataLen);

	//通过二进制字符串设置数据位值(四个字节32位)
	string getBinaryStr(vector<int> & _ids);
	void setDataBit(unsigned char *_data, int _nStart, int _len, string _binaryStr);

private:
	ofxDataSender * sender;
};

