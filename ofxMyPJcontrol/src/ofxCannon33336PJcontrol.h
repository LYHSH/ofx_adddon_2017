#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:cannonͶӰ��33336�˿ڿ���
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

