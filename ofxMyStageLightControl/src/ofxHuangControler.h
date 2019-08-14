#pragma once
#include "ofxRealRecorderBase.h"
/************************************************************************/
/* project name:Â¼²¥¿ØÖÆÆ÷
/* file describe:Ð¡»ÆµÄµÆ¹âÂ¼²¥Æ÷
/* author:hui
/* date:2018.3.19
/************************************************************************/
class ofxHuangControler : public ofxRealRecorderBase
{
public:
	ofxHuangControler();
	~ofxHuangControler();

	void play(int _id)override final;

	void play() override final;
	void pause() override final;
	void stop() override final;
};

