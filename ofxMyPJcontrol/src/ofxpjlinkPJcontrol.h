#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:pjlink协议投影机控制
/* date:2017.12.28
/* author:hui
/************************************************************************/
class ofxpjlinkPJcontrol : public ofxPJnetControlBase
{
public:
	ofxpjlinkPJcontrol();
	~ofxpjlinkPJcontrol();

	void setOnOoff(bool _state) override final;

	void setSingle(SINGLE_TYPE _type) override final;
};

