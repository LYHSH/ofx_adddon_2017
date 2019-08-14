#pragma once
#include "ofxPJcomControl.h"
/************************************************************************/
/* file describe:cannon投影机串口控制
/* date:2018.1.2
/* author:hui
/************************************************************************/
class ofxCannonComPJcontrol : public ofxPJcomControl
{
public:
	ofxCannonComPJcontrol();
	~ofxCannonComPJcontrol();

	void setOnOoff(bool _state) override final;
};

