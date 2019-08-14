#pragma once
#include "ofMain.h"
#include "ofxPJcontrolBase.h"
#include "ofxDataSenderFacory.h"
#include "ofxTcpDataSender.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:投影机网络控制基类
/* date:2017.12.28
/* author:hui
/************************************************************************/
class ofxPJnetControlBase : public ofxPJcontrolBase, public ofThread
{
public:
	ofxPJnetControlBase();
	virtual ~ofxPJnetControlBase();
	void setup(string _ip);

	void setOn() override final;
	void setOff() override final;

	void setHDMI() override final;
	void setDVI() override final;
	void setRGB2() override final;
	void setHDMI1() override final;
	void setHDMI2() override final;
	
	string getName()const override final;
protected:
	virtual void setOnOoff(bool _state) = 0;

	virtual void setSingle(SINGLE_TYPE _type);
	string getIp()const;
	void threadedFunction();

	void addPJLinkCommand(string _command, int _port);
	void sendPJLinkCommand(string _command, int _port);
	bool bFirstSend;

	struct msgNode
	{
		string msg;
		int port;
	};

	queue<msgNode> msgNodes;

	ofxTcpDataSender * sender;

	string ipAddress;
	bool connected;
};

