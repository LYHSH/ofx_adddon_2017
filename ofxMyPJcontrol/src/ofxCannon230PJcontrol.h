#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:cannon投影机230端口控制
/* date:2017.12.28
/* author:hui
/************************************************************************/
class ofxCannon230PJcontrol : public ofxPJnetControlBase
{
public:
	ofxCannon230PJcontrol();
	~ofxCannon230PJcontrol();

	void setOnOoff(bool _state) override final;
};

