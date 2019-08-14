#include "texRectButton.h"


texRectButton::texRectButton(void)
{
}


texRectButton::~texRectButton(void)
{
}

void texRectButton::draw(){
	ofPushStyle();
	ofEnableAlphaBlending();
	if (!isEnable())
	{
		ofSetColor(100, 100, 100);
	}
	ofRectangle rect = getRect();
	//getTouch()?rect.scaleFromCenter(1.1):0;
	getTouch() ? ofSetColor(100, 100, 100) : ofSetColor(255, 255, 255);
	tex.draw(rect);
	ofPopStyle();
}


void texRectButton::setTex(const ofImage & _tex){
	tex.clear();
	tex = _tex;
	tex.setAnchorPercent(0.0,0.0);
}

ofImage & texRectButton::getTex(){
	return tex;
}

void texRectButton::setPos(ofVec2f _pos){
	setRect(ofRectangle(_pos,tex.getWidth(),tex.getHeight()));
}