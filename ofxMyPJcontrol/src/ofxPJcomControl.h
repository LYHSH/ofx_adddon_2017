#pragma once
#include "ofxPJcontrolBase.h"
#include "ofxDataSenderFacory.h"
/************************************************************************/
/* file describe:投影机串口控制基类
/* date:2018.1.2
/* author:hui
/************************************************************************/
class ofxPJcomControl : public ofxPJcontrolBase
{
public:
	ofxPJcomControl();
	virtual ~ofxPJcomControl();

	void setup(string _comName);

	void setOn() override final;
	void setOff() override final;

	string getName()const override final;

	
protected:
	string getCOM()const;
	virtual void setOnOoff(bool _state) = 0;

	void sendCmd(string _msg,int _nbaud);

	ofxDataSender * sender;
	
private:
	string comName;
	bool bFirstSend;
};

