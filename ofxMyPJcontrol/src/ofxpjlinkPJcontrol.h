#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:pjlinkЭ��ͶӰ������
/* date:2017.12.28
/* author:hui
/************************************************************************/
class ofxpjlinkPJcontrol : public ofxPJnetControlBase
{
public:
	ofxpjlinkPJcontrol();
	~ofxpjlinkPJcontrol();

	void setOnOoff(bool _state) override final;

	void setSingle(SINGLE_TYPE _type) override final;
};

