#pragma once
#include "ofxRealRelayBase.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:�������ڵƹ�̵���
/* date:2017.10.3
/* author:hui
/************************************************************************/
class ofxHengYang2Relay : public ofxRealRelayBase
{
public:
	ofxHengYang2Relay();
	~ofxHengYang2Relay();

	void setOn(int _id) override;
	void setOff(int _id) override;
};

