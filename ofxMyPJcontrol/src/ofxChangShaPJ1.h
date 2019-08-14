#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:长沙升明月投影机控制1
/* date:2019.4.11
/* author:hui
/************************************************************************/
class ofxChangShaPJ1 : public ofxPJnetControlBase
{
public:
	ofxChangShaPJ1();
	~ofxChangShaPJ1();

	void setOnOoff(bool _state) override final;
};

