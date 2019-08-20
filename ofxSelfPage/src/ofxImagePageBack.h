#pragma once
#include "ofxPageBack.h"
/************************************************************************/
/* project name:界面背景
/* file describe:界面背景-图片
/* author:hui
/* date:2018.3.30
/************************************************************************/
class ofxImagePageBack : public ofxPageBack
{
public:
	ofxImagePageBack();
	~ofxImagePageBack();

	void setup(string _fileName) override final;
	void update() override final;
	void draw(int _x, int _y, int _w, int _h) override final;

private:
	ofImage backimg;
};

