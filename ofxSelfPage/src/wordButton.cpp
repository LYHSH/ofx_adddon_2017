#include "wordButton.h"


ofxTrueTypeFontUC wordButton::font;
ofImage wordButton::blueLargeImg;
ofImage wordButton::redLargeImg;
ofImage wordButton::blueMiddleImg;
ofImage wordButton::redMiddleImg;
ofImage wordButton::blueSmallImg;
ofImage wordButton::redSmallImg;
ofSoundPlayer wordButton::touchSound;
float wordButton::sleepTimeLen;
ofColor wordButton::btnColor = ofColor(255, 255, 255);
int wordButton::fontSize = 22;
wordButton::wordButton()
{
	init();

	orderId = -10000;
	bTouched = false;
	sleepTime = 0.0f;
	bSleep = false;
	sleepTimeLen = 15.0f;
}


wordButton::~wordButton()
{
}

void wordButton::setup(string _word,ofVec2f _pos, BTN_TYPE _type)
{
	wordType = WORD_STRING;
	wordStr = _word;
	stringRect = font.getStringBoundingBox(wordStr, 0, 0);
	pos = _pos;
	btnType = _type;
	switch (btnType)
	{
	case BTN_BLUE_LARGE:
		touchRect.set(pos.x, pos.y, blueLargeImg.getWidth(), blueLargeImg.getHeight());
		break;
	case BTN_RED_LARGE:
		touchRect.set(pos.x, pos.y, redLargeImg.getWidth(), redLargeImg.getHeight());
		break;
	case BTN_BLUE_MIDDLE:
		touchRect.set(pos.x, pos.y, blueMiddleImg.getWidth(), blueMiddleImg.getHeight());
		break;
	case BTN_RED_MIDDLE:
		touchRect.set(pos.x, pos.y, redMiddleImg.getWidth(), redMiddleImg.getHeight());
		break;
	case BTN_BLUE_SMALL:
		touchRect.set(pos.x, pos.y, blueSmallImg.getWidth(), blueSmallImg.getHeight());
		break;
	case BTN_RED_SMALL:
		touchRect.set(pos.x, pos.y, redSmallImg.getWidth(), redSmallImg.getHeight());
		break;
	default:
		break;
	}
}

void wordButton::setup(ofImage & _tex, ofVec2f _pos)
{
	wordType = WORD_OFIMAGE;
	wordImg = _tex;
	wordImg.setAnchorPercent(0.5,0.5);
	pos = _pos;

	touchRect.set(pos,wordImg.getWidth(),wordImg.getHeight());
}

void wordButton::update()
{

}

void wordButton::draw()
{
	ofPushMatrix();
	ofPushStyle();
	ofEnableAlphaBlending();
	if (bTouched)
		ofSetColor(100, 100, 100);
	else
		ofSetColor(255, 255, 255);

	if (bSleep)
	{
		ofSetColor(100, 100, 100);
		if (ofGetElapsedTimef() - sleepTime > sleepTimeLen)
		{
			bSleep = false;
		}
	}

	ofTranslate(touchRect.getCenter());

	switch (wordType)
	{
	case wordButton::WORD_STRING:
	{
		switch (btnType)
		{
		case BTN_BLUE_LARGE:
			blueLargeImg.draw(0, 0);
			break;
		case BTN_RED_LARGE:
			redLargeImg.draw(0, 0);
			break;
		case BTN_BLUE_MIDDLE:
			blueMiddleImg.draw(0, 0);
			break;
		case BTN_RED_MIDDLE:
			redMiddleImg.draw(0, 0);
			break;
		case BTN_BLUE_SMALL:
			blueSmallImg.draw(0, 0);
			break;
		case BTN_RED_SMALL:
			redSmallImg.draw(0, 0);
			break;
		default:
			break;
		}
		ofPushStyle();
		ofSetColor(btnColor);
		{
			ofRectangle wordRect = font.getStringBoundingBox(wordStr,0,0);
			ofPushMatrix();
		//	ofTranslate(-touchRect.getWidth() / 2, -touchRect.getHeight() / 2);
		//	float x = (touchRect.getWidth() - wordRect.getWidth()) * 0.5f - wordRect.getX();
		//	float y = (touchRect.getHeight() - wordRect.getHeight()) * 0.5f - wordRect.getY();
			float x = -wordRect.getWidth() * 0.5f - wordRect.getX();
			float y = -wordRect.getHeight()  * 0.5f - wordRect.getY();
			font.drawString(wordStr, x,y);
			//font.drawString(wordStr, -stringRect.getWidth() / 2, stringRect.getHeight() / 3);
			ofPopMatrix();
			
		}
		
		ofPopStyle();
	}
		break;
	case wordButton::WORD_OFIMAGE:
	{
		wordImg.draw(0,0);
	}
		break;
	default:
		break;
	}
	
	
	ofPopStyle();
	ofPopMatrix();
}

void wordButton::touch(float xx, float yy)
{
	if (bSleep)
	{
		return;
	}
	if (touchRect.inside(xx, yy))
	{
		bTouched = true;
		touchPos = ofVec2f(xx,yy);
		pos = touchRect.getPosition();
	}
}

bool wordButton::release(float xx, float yy)
{
	if (bSleep)
	{
		return false;
	}
	if (touchRect.inside(xx, yy))
	{
		bTouched = false;
		touchSound.play();
		return true;
	}
	else
	{
		bTouched = false;
		return false;
	}
}

void wordButton::dragged(float xx, float yy)
{
	if (bSleep)
	{
		return;
	}
	if (bTouched)
	{
		touchRect.setPosition(pos.x + xx - touchPos.x, pos.y + yy - touchPos.y);
	}
}

void wordButton::setOrderID(int _id)
{
	orderId = _id;
}

int wordButton::getOrderID()
{
	return orderId;
}

ofVec2f wordButton::getPos()
{
	return touchRect.getPosition();
}

void wordButton::sleep()
{
	sleepTime = ofGetElapsedTimef();
	bSleep = true;
}

void wordButton::setSleepTimeLen(float _timeLen)
{
	sleepTimeLen = _timeLen;
}

void wordButton::setBtnColor(ofColor _color)
{
	btnColor = _color;
}

void wordButton::setBtnFontSize(int _size)
{
	fontSize = _size;
}

void wordButton::init()
{
	static bool first = true;
	if (first)
	{
		blueLargeImg.loadImage("wordButton/blueLarge.png");
		blueLargeImg.setAnchorPercent(0.5, 0.5);
		redLargeImg.loadImage("wordButton/redLarge.png");
		redLargeImg.setAnchorPercent(0.5, 0.5);
		blueMiddleImg.loadImage("wordButton/blueMiddle.png");
		blueMiddleImg.setAnchorPercent(0.5, 0.5);
		redMiddleImg.loadImage("wordButton/redMiddle.png");
		redMiddleImg.setAnchorPercent(0.5, 0.5);
		blueSmallImg.loadImage("wordButton/blueSmall.png");
		blueSmallImg.setAnchorPercent(0.5, 0.5);
		redSmallImg.loadImage("wordButton/redSmall.png");
		redSmallImg.setAnchorPercent(0.5, 0.5);


		font.load("fonts/btn.TTF", fontSize);
		ofxTrueTypeFontUC::setGlobalDpi(96);

		touchSound.load("sound.wav");
		touchSound.setLoop(false);
		first = false;
	}
}