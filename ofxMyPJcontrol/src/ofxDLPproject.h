#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:松下投影1024端口控制
/* date:2018.11.12
/* author:hui
/************************************************************************/
class ofxDLPproject : public ofxPJnetControlBase
{
public:
	ofxDLPproject();
	~ofxDLPproject();

	void setOnOoff(bool _state) override final;
	void setSingle(SINGLE_TYPE _type) override final;
};

