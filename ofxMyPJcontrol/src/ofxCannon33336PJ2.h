#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:cannonͶӰ��33336�˿ڿ���-���Ͷ�
/* date:2017.1.8
/* author:hui
/************************************************************************/
class ofxCannon33336PJ2 : public ofxPJnetControlBase
{
public:
	ofxCannon33336PJ2();
	~ofxCannon33336PJ2();

	void setOnOoff(bool _state) override final;
};

