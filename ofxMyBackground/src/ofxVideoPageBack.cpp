#include "ofxVideoPageBack.h"



ofxVideoPageBack::ofxVideoPageBack()
{
}


ofxVideoPageBack::~ofxVideoPageBack()
{
	video.close();
}

void ofxVideoPageBack::setup(string _fileName)
{
	video.load(_fileName);

	video.setLoopState(OF_LOOP_NORMAL);
	video.play();
}

void ofxVideoPageBack::update()
{
	video.update();
}

void ofxVideoPageBack::draw(int _x, int _y, int _w, int _h)
{
	video.draw(_x, _y, _w, _h);
}

void ofxVideoPageBack::play()
{
	video.play();
	video.setPaused(false);
}

void ofxVideoPageBack::pause()
{
	video.setPaused(true);
}

void ofxVideoPageBack::stop()
{
	video.stop();
}