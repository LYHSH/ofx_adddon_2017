#pragma once
#include "ofxPJnetControlBase.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:cannonͶӰ��230�˿ڿ���
/* date:2017.12.28
/* author:hui
/************************************************************************/
class ofxCannon230PJcontrol : public ofxPJnetControlBase
{
public:
	ofxCannon230PJcontrol();
	~ofxCannon230PJcontrol();

	void setOnOoff(bool _state) override final;
};

