#include "flipTexRectButton.h"


flipTexRectButton::flipTexRectButton(void)
{
}


flipTexRectButton::~flipTexRectButton(void)
{
}

bool flipTexRectButton::touch(int _x,int _y){
	if (getDrawRect().inside(_x,_y))
	{
		//setTouch(true);
		return true;
	}
	return false;
}

bool flipTexRectButton::release(int _x,int _y){
	//setTouch(false);
	return getDrawRect().inside(_x,_y);
}

void flipTexRectButton::draw()
{
	ofPushStyle();
	ofEnableAlphaBlending();
	ofRectangle rect = getRect();
	rect.translate(getOffSet());
	getTouch()?rect.scaleFromCenter(1.1):0;
	getTex().draw(rect);
	ofPopStyle();
}

void flipTexRectButton::setOffsetX(float _x){
	offset.x = _x;
}

void flipTexRectButton::setOffsetY(float _y){
	offset.y = _y;
}

const ofVec2f & flipTexRectButton::getOffSet()const{
	return offset;
}

ofRectangle  flipTexRectButton::getDrawRect(){
	ofRectangle rect = getRect();
	rect.translate(getOffSet());
	return rect;
}