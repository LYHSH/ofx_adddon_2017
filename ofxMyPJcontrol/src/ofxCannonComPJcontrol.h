#pragma once
#include "ofxPJcomControl.h"
/************************************************************************/
/* file describe:cannonͶӰ�����ڿ���
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

