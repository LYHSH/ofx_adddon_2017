#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:cannon投影机33336端口控制-类型二
/* date:2017.1.8
/* author:hui
/************************************************************************/
class ofxCannon33336PJ2 : public ofxPJnetControlBase
{
public:
	ofxCannon33336PJ2();
	~ofxCannon33336PJ2();

	void setOnOoff(bool _state) override final;
};

