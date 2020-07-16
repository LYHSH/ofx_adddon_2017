#pragma once
#include "ofxRelaysBase.h"
#include "ofxDataSenderFacory.h"
#include "checkDigitCalculation.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:��ʵ�̵�������
/* date:2017.1.29
/* author:hui
/* update:2018.11.12   ����ӿ�����
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

	//ͨ���������ַ�����������λֵ(�ĸ��ֽ�32λ)
	string getBinaryStr(vector<int> & _ids);
	void setDataBit(unsigned char *_data, int _nStart, int _len, string _binaryStr);

private:
	ofxDataSender * sender;
};

