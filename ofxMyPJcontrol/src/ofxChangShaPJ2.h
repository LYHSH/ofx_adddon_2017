#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:��ɳ������ͶӰ������2-����ͶӰ��
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

