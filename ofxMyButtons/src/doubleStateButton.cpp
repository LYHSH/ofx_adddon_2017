#include "doubleStateButton.h"



doubleStateButton::doubleStateButton()
{
}


doubleStateButton::~doubleStateButton()
{
}

void doubleStateButton::setTex(const ofImage & _showTex, const ofImage & _touchTex)
{
	showTex = _showTex;
	touchTex = _touchTex;

	showTex.setAnchorPercent(0.5f, 0.5f);
	touchTex.setAnchorPercent(0.5f, 0.5f);
}

void doubleStateButton::draw()
{
	ofPushStyle();
	ofEnableAlphaBlending();
	if (!isEnable())
	{
		ofSetColor(100, 100, 100);
	}
	ofRectangle rect = getRect();
	//getTouch()?rect.scaleFromCenter(1.1):0;
	if (getTouch())
	{
		touchTex.draw(getRect().getCenter());
	}
	else
	{
		showTex.draw(getRect().getCenter());
	}
	ofPopStyle();
}


