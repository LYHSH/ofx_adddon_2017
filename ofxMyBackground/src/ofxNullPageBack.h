#pragma once
#include "ofxPageBack.h"
/************************************************************************/
/* project name:���汳��
/* file describe:���汳��-��
/* author:hui
/* date:2018.3.30
/************************************************************************/
class ofxNullPageBack : public ofxPageBack
{
public:
	ofxNullPageBack();
	~ofxNullPageBack();

	void setup(string _fileName) override final;
	void update() override final;
	void draw(int _x, int _y, int _w, int _h) override final;
};

