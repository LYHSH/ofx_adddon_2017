#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:��ɳ������ͶӰ������1
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

