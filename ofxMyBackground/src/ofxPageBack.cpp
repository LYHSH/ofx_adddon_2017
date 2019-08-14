#include "ofxPageBack.h"



ofxPageBack::ofxPageBack()
{
}


ofxPageBack::~ofxPageBack()
{
}

void ofxPageBack::draw(ofRectangle _rect)
{
	draw(_rect.getX(), _rect.getY(), _rect.getWidth(), _rect.getHeight());
}

void ofxPageBack::play(){
	//Do Nothing;
}

void ofxPageBack::pause() {
	//Do Nothing;
}

void ofxPageBack::stop(){
	//Do Nothing;
}