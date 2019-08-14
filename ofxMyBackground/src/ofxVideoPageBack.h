#pragma once
#include "ofMain.h"
#include "ofxPageBack.h"
/************************************************************************/
/* project name:���汳��
/* file describe:���汳��-��Ƶ
/* author:hui
/* date:2018.3.30
/************************************************************************/
class ofxVideoPageBack : public ofxPageBack
{
public:
	ofxVideoPageBack();
	~ofxVideoPageBack();

	void setup(string _fileName) override final;
	void update() override final;
	void draw(int _x, int _y, int _w, int _h) override final;

	void play() override final;
	void pause() override final;
	void stop() override final;

private:
	ofVideoPlayer video;
};

