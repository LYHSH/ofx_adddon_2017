#include "ofxTcpDataSender.h"



ofxTcpDataSender::ofxTcpDataSender()
{
}


ofxTcpDataSender::~ofxTcpDataSender()
{
	close();
}

void ofxTcpDataSender::setup(string _ip, int _port)
{
	ip = _ip;
	port = _port;
}

int ofxTcpDataSender::sendData(const char *_data, int _size, bool _bPrint /* = true */)
{
	if (_bPrint)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip:" << ip << " port:" << port << " send:" << endl;
		printTestData(_data, _size);
	}
	
#ifndef LOCAL_DEBUG
	if (!tcpClient.isConnected())
	{
		bConnected = tcpClient.setup(ip, port, false);
	}

	if (bConnected)
	{
        if (isDelay()) {
            Sleep(300);				//ͶӰ��ָ���ʱ���ӳ�
        }
		

		bConnected = tcpClient.sendRawBytes(_data, _size);


        if (isDelay()) {
            Sleep(300);				//ͶӰ��ָ���ʱ���ӳ�
        }
        if (IsShortConnection()) {
            tcpClient.close();      //������
        }
		
	}
#endif
	
	return bConnected;
}

int ofxTcpDataSender::recvData(char * _data, int _size)
{
	if (!tcpClient.isConnected())
	{
		bConnected = tcpClient.setup(ip, port, false);
	}

	if (bConnected)
	{
        if (isDelay()) {
            Sleep(200);			
        }
		

		return tcpClient.receiveRawBytes(_data, _size);
	}
	return 0;
}

void ofxTcpDataSender::close()
{
	tcpClient.close();
}
