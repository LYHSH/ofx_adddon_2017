#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:����ͶӰ1024�˿ڿ���
/* date:2018.11.12
/* author:hui
/************************************************************************/
class ofxDLPproject : public ofxPJnetControlBase
{
public:
	ofxDLPproject();
	~ofxDLPproject();

	void setOnOoff(bool _state) override final;
	void setSingle(SINGLE_TYPE _type) override final;
};

