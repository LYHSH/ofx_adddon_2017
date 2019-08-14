#pragma once
#include "ofxPJcomControl.h"
/************************************************************************/
/* file describe:丽讯投影机串口控制
/* date:2018.3.13
/* author:hui
/************************************************************************/
class ofxVivitekComProject : public ofxPJcomControl
{
public:
	ofxVivitekComProject();
	~ofxVivitekComProject();

	void setOnOoff(bool _state) override final;
};

