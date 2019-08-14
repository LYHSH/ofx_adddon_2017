#include "rectButton.h"


rectButton::rectButton(void)
{
}


rectButton::~rectButton(void)
{
}

void rectButton::setRect(const ofRectangle & _rect){
	rect = _rect;
}

const ofRectangle & rectButton::getRect()const{
	return rect;
}

ofRectangle & rectButton::getRect(){
	return rect;
}

bool rectButton::touch(int _x,int _y){
	if (!isEnable())
	{
		return false;
	}
	if (rect.inside(_x,_y))
	{
		setTouch(true);
		return true;
	}
	return false;
}

bool rectButton::release(int _x,int _y){
	if (!isEnable())
	{
		return false;
	}
	setTouch(false);
	return rect.inside(_x,_y);
}

void rectButton::draw(){
	ofPushStyle();
	getTouch()?ofSetColor(0,255,0):ofSetColor(0,0,255);
	ofFill();
	ofRect(rect);
	stringstream sss;
	sss<<"id:"<<getId()<<endl;
	sss<<"name:"<<getName();
	ofSetColor(0,255,255);
	ofDrawBitmapString(sss.str(),rect.x,rect.y + 15);
	ofPopStyle();
}