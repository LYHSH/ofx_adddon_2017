#pragma once
#include "ofxRecorderBase.h"
#include "ofMain.h"
/************************************************************************/
/* project name:录播控制器
/* file describe:线程装饰
/* author:hui
/* date:2018.3.19
/************************************************************************/
class ofxRecorderThread : public ofxRecorderBase, public ofThread
{
public:
	ofxRecorderThread(ofxRecorderBase * _recorder);
	~ofxRecorderThread();

	void play(int _id)override final;

private:
	void threadedFunction()override;

	ofxRecorderBase * recorder;

	queue<int> orders;
};

