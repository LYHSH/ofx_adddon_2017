#include "ofxSerialDataSender.h"



ofxSerialDataSender::ofxSerialDataSender()
{
}


ofxSerialDataSender::~ofxSerialDataSender()
{
	close();
}

bool ofxSerialDataSender::setup(int _comNum, int _nBaud)
{
	return setup("COM" + ofToString(_comNum), _nBaud);
}

bool ofxSerialDataSender::setup(string _comName, int _nBaud)
{
	portName = _comName;
	nBaud = _nBaud;

	bool res = serial.setup(portName, nBaud);
	if (res)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "���ڣ�"<< portName<< ",�����ʣ�" << ofToString(nBaud) << "���ӳɹ���" << endl;
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "���ڣ�" << portName << ",�����ʣ�" << ofToString(nBaud) << "����ʧ�ܡ�" << endl;
	}

	return res;
}

int ofxSerialDataSender::sendData(const char *_data, int _size,bool _bPrint /* = true */)
{
	if (_bPrint)
	{
		ofLogNotice(OF_FUNCTION_NAME) << portName << " send:" << endl;
		printTestData(_data, _size);
	}
	
	return serial.writeBytes((unsigned char *)_data, _size);
}

int ofxSerialDataSender::recvData(char * _data, int _size)
{
	return serial.readBytes((unsigned char *)_data, _size);
}

void ofxSerialDataSender::close()
{
	serial.close();
}

ofxSerial * ofxSerialDataSender::getSerial()
{
	return &serial;
}