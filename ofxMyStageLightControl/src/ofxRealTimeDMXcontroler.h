#pragma once
#include "ofxRealRecorderBase.h"
/************************************************************************/
/* project name:录播控制器
/* file describe:DMX512控制器-山东廉政馆
/* author:hui
/* date:2018.10.7
/************************************************************************/
class ofxRealTimeDMXcontroler : public ofxRealRecorderBase
{
public:
	ofxRealTimeDMXcontroler();
	~ofxRealTimeDMXcontroler();

	void play(int _id) override final;
};

