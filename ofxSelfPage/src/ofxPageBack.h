#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name:���汳��
/* file describe:���汳������
/* author:hui
/* date:2018.3.30
/************************************************************************/
class ofxPageBack
{
public:
	ofxPageBack();
	virtual ~ofxPageBack();

	virtual void setup(string _fileName) = 0;
	virtual void update() = 0;
	void draw(ofRectangle _rect);
	virtual void draw(int _x, int _y, int _w, int _h) = 0;
};

