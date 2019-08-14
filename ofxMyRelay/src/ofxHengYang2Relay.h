#pragma once
#include "ofxRealRelayBase.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:衡阳二期灯光继电器
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

