#pragma once
#include "ofMain.h"
#include "ofxMyConstants.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:投影机控制基类
/* date:2017.12.28
/* author:hui
/* udpate:2018.11.12(新增投影信号切换接口)
/************************************************************************/
class ofxPJcontrolBase
{
public:
	ofxPJcontrolBase();
	virtual ~ofxPJcontrolBase();

	//开关控制
	virtual void setOn() = 0;
	virtual void setOff() = 0;

	//信号切换，不是所有子类都需要实现
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

