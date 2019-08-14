#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:索尼投影机网络控制
/* date:2018.3.14
/* author:hui
/************************************************************************/
class ofxSonyNetProject : public ofxPJnetControlBase
{
public:
	ofxSonyNetProject();
	~ofxSonyNetProject();

	void setOnOoff(bool _state) override final;
};

