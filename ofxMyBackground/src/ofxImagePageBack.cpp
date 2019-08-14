#include "ofxImagePageBack.h"



ofxImagePageBack::ofxImagePageBack()
{
}


ofxImagePageBack::~ofxImagePageBack()
{
}

void ofxImagePageBack::setup(string _fileName)
{
	backimg.load(_fileName);
}

void ofxImagePageBack::update()
{

}

void ofxImagePageBack::draw(int _x, int _y, int _w, int _h)
{
	backimg.draw(_x, _y, _w, _h);
}
