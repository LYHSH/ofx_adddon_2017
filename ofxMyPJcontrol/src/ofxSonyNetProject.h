#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:����ͶӰ���������
/* date:2018.3.14
/* author:hui
/************************************************************************/
class ofxSonyNetProject : public ofxPJnetControlBase
{
public:
	ofxSonyNetProject();
	~ofxSonyNetProject();

	void setOnOoff(bool _state) override final;
};

