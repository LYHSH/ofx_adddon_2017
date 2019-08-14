#include "ofxRecorderThread.h"



ofxRecorderThread::ofxRecorderThread(ofxRecorderBase * _recorder)
{
	recorder = _recorder;
}


ofxRecorderThread::~ofxRecorderThread()
{
}

void ofxRecorderThread::play(int _id)
{
	orders.push(_id);
}

void ofxRecorderThread::threadedFunction()
{
	while (isThreadRunning())
	{
		while (orders.size())
		{
			lock();
			int order = orders.front();
			orders.pop();
			unlock();
			recorder->play(order);
		}
		sleep(10);
	}
}
