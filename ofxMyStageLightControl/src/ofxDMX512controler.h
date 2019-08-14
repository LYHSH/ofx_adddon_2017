#pragma once
#include "ofxRealRecorderBase.h"
/************************************************************************/
/* project name:Â¼²¥¿ØÖÆÆ÷
/* file describe:DMX512¿ØÖÆÆ÷
/* author:hui
/* date:2018.3.19
/************************************************************************/
class ofxDMX512controler : public ofxRealRecorderBase
{
public:
	ofxDMX512controler();
	~ofxDMX512controler();

	void play(int _id) override final;
};

