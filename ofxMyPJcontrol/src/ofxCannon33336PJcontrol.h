#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:cannon投影机33336端口控制
/* date:2017.12.28
/* author:hui
/************************************************************************/
class ofxCannon33336PJcontrol : public ofxPJnetControlBase
{
public:
	ofxCannon33336PJcontrol();
	~ofxCannon33336PJcontrol();

	void setOnOoff(bool _state) override final;
};

