#pragma once
#include "ofxRecorderBase.h"
#include "ofMain.h"
/************************************************************************/
/* project name:¼��������
/* file describe:�߳�װ��
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

