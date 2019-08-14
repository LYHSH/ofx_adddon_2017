#pragma once
#include "ofMain.h"
#include "ofxMyConstants.h"
/************************************************************************/
/* project name:ͶӰ�����ƽӿڿ�
/* file describe:ͶӰ�����ƻ���
/* date:2017.12.28
/* author:hui
/* udpate:2018.11.12(����ͶӰ�ź��л��ӿ�)
/************************************************************************/
class ofxPJcontrolBase
{
public:
	ofxPJcontrolBase();
	virtual ~ofxPJcontrolBase();

	//���ؿ���
	virtual void setOn() = 0;
	virtual void setOff() = 0;

	//�ź��л��������������඼��Ҫʵ��
	enum SINGLE_TYPE
	{
		HDMI,
		DVI,
		RGB2,
		HDMI1,
		HDMI2
	};
	virtual void setHDMI();
	virtual void setDVI();
	virtual void setRGB2();
	virtual void setHDMI1();
	virtual void setHDMI2();

	virtual string getName()const = 0;



};

