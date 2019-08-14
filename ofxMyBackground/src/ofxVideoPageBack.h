#pragma once
#include "ofMain.h"
#include "ofxPageBack.h"
/************************************************************************/
/* project name:界面背景
/* file describe:界面背景-视频
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

