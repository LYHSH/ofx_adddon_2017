#include "texTextRectButton.h"


ofxTrueTypeFontUC texTextRectButton::font;
texTextRectButton::texTextRectButton()
{
	text = "";
	textOffset.set(0);
	textColor.set(0);
}


texTextRectButton::~texTextRectButton()
{
}

void texTextRectButton::loadFont(string _path)
{
	font.load(_path, 20);
	ofxTrueTypeFontUC::setGlobalDpi(96);
}

void texTextRectButton::setText(string _text)
{
	text = _text;
	textRect = font.getStringBoundingBox(text, 0, 0);
}

string texTextRectButton::getText()const
{
	return text;
}

void texTextRectButton::setOffset(float _x, float _y)
{
	textOffset.set(_x, _y);
}

void texTextRectButton::setColor(ofColor _color)
{
	textColor = _color;
}

void texTextRectButton::draw()
{
	ofPushStyle();
	ofEnableAlphaBlending();
	ofRectangle rect = getRect();
	if (getTouch())
		ofSetColor(100, 100, 100);
	else
		ofSetColor(255, 255, 255);
	tex.draw(rect);
	ofPushMatrix();
	ofVec2f pos = rect.getCenter();
	ofTranslate(pos + textOffset);
	ofPushStyle();
	ofSetColor(textColor);
	font.drawString(text, -textRect.getWidth() / 2, textRect.getHeight() / 2);
	ofPopStyle();
	ofPopMatrix();
	ofPopStyle();
}