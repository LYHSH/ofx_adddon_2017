#include "ofxPJnetControlBase.h"



ofxPJnetControlBase::ofxPJnetControlBase()
{
	connected = false;
	ipAddress = "";
	sender = NULL;
	bFirstSend = true;
}


ofxPJnetControlBase::~ofxPJnetControlBase()
{
	waitForThread();
	ofLogNotice(OF_FUNCTION_NAME) << "�ȴ��߳��˳���..." << getThreadId() << endl;
	if (sender)
	{
		sender->close();
		delete sender;
		sender = NULL;
	}
}

void ofxPJnetControlBase::setup(string _ip)
{
	ipAddress = _ip;

	startThread(true, false);
}

void ofxPJnetControlBase::setOn()
{
	setOnOoff(true);
}

void ofxPJnetControlBase::setOff()
{
	setOnOoff(false);
}

void ofxPJnetControlBase::setHDMI()
{
	setSingle(HDMI);
}

void ofxPJnetControlBase::setDVI()
{
	setSingle(DVI);
}

void ofxPJnetControlBase::setRGB2()
{
	setSingle(RGB2);
}

void ofxPJnetControlBase::setHDMI1()
{
	setSingle(HDMI1);
}

void ofxPJnetControlBase::setHDMI2()
{
	setSingle(HDMI2);
}

void ofxPJnetControlBase::setSingle(SINGLE_TYPE _type)
{
	ofLogNotice(OF_FUNCTION_NAME) << "setSingle invalid" << endl;
}

string ofxPJnetControlBase::getName()const
{
	return getIp();
}

void ofxPJnetControlBase::addPJLinkCommand(string _command, int _port)
{
	msgNode node;
	node.msg = _command;
	node.port = _port;
	if (lock())
	{
		msgNodes.push(node);
		unlock();
	}
}

void ofxPJnetControlBase::sendPJLinkCommand(string _command, int _port)
{
	if (bFirstSend)
	{
		sender = (ofxTcpDataSender *)ofxDataSenderFacory::createTcpSender(ipAddress, _port);
		bFirstSend = false;
	}
	sender->setup(ipAddress, _port);				//�������ö˿�ֵ���޸���ͬ�˿ڵ�ָ���bug2018.12.1   ��ԣ�����п�

	//ͶӰ��ָ������Ҫ������200ms�ķ����ӳ�
	sender->sendData(_command.c_str(), _command.size());
}


string ofxPJnetControlBase::getIp()const
{
	return ipAddress;
}

void ofxPJnetControlBase::threadedFunction()
{
	while (isThreadRunning())
	{
		if (msgNodes.size())
		{
			if (lock())
			{
				msgNode  node = msgNodes.front();
				msgNodes.pop();
				unlock();
				sendPJLinkCommand(node.msg, node.port);
				sleep(100);
			}
		}
		sleep(10);
	}
}
