#pragma once
#include "ofxRealRecorderBase.h"
/************************************************************************/
/* project name:¼��������
/* file describe:DMX512������-ɽ��������
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

