#include "ofxRealRelayBase.h"

ofxRealRelayBase::ofxRealRelayBase()
{
	sender = NULL;
}


ofxRealRelayBase::~ofxRealRelayBase()
{
	close();
	if (sender){
		delete sender;
		sender = NULL;
	}
}

void ofxRealRelayBase::setup(ofxDataSender * _sender, unsigned char _addressCode /* = 0x01 */)
{
	setAddress(_addressCode);
	if (sender)delete sender;
	
	sender = _sender;
}

void ofxRealRelayBase::setup(int _comNum, int _nBaud, unsigned char _addressCode /* = 0x01 */)
{
	setAddress(_addressCode);
	sender = ofxDataSenderFacory::createSerialSender(_comNum, _nBaud);
}

void ofxRealRelayBase::setup(string _ip, int _port, unsigned char _addressCode /* = 0x01 */)
{
	setAddress(_addressCode);
	sender = ofxDataSenderFacory::createTcpSender(_ip, _port);
}

void ofxRealRelayBase::udpSetup(string _ip, int _port, unsigned char _addressCode /* = 0x01 */)
{
	setAddress(_addressCode);
	sender = ofxDataSenderFacory::createUdpSender(_ip, _port);
}



void ofxRealRelayBase::close()
{
	sender->close();
}

bool ofxRealRelayBase::sendData(const unsigned char * _data, int _size)
{
	int len = sender->sendData((char *)_data, _size);
	Sleep(100);
	return len == _size;
}

unsigned char ofxRealRelayBase::GetSumVerify(int nStart, int nEnd, const unsigned char * _dataCode)
{
	return ofGetSumVerify(nStart, nEnd, _dataCode);
}

unsigned short ofxRealRelayBase::CRC166(unsigned char *puchMsg, unsigned short usDataLen)
{
	return ofCRC166(puchMsg,usDataLen);
}

string ofxRealRelayBase::getBinaryStr(vector<int> & _ids)
{
	string binaryStr = "00000000000000000000000000000000";
	for (int i = 0; i < _ids.size(); i++)
	{
		int curId = _ids[i];
		binaryStr[32 - curId - 1] = '1';
	}

	return binaryStr;
}

void ofxRealRelayBase::setDataBit(unsigned char *_data, int _nStart, int _len, string _binaryStr)
{
	string str;
	int size = 8;
	int start = 0;

	for (int i = 0; i < _len; i++)
	{
		str = _binaryStr.substr(start, size);
		start += size;
		_data[_nStart + i] = ofBinaryToChar(str);
	}
}
