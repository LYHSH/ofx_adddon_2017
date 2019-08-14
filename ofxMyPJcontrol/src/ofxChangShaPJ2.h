#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:长沙升明月投影机控制2-三洋投影机
/* date:2019.4.11
/* author:hui
/************************************************************************/
class ofxChangShaPJ2 : public ofxPJnetControlBase
{
public:
	ofxChangShaPJ2();
	~ofxChangShaPJ2();

	void setOnOoff(bool _state) override final;
};

