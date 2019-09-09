#pragma once
#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "button.h"
/************************************************************************/
/* file describe:ÎÄ×Ö°´Å¥
/* author:hui
/* date:2017.4.27
/************************************************************************/
typedef enum 
{
	BTN_BLUE_LARGE,
	BTN_RED_LARGE,
	BTN_BLUE_SMALL,
	BTN_RED_SMALL,
	BTN_BLUE_MIDDLE,
	BTN_RED_MIDDLE,
}BTN_TYPE;
class wordButton : public button
{
public:
	wordButton();
	~wordButton();

	void setup(string _word,ofVec2f _pos, BTN_TYPE _type);
	void setup(ofImage & _tex, ofVec2f _pos);
	void update();
	void draw();

	void touch(float xx, float yy);
	bool release(float xx, float yy);
	void dragged(float xx,float yy);

	void setOrderID(int _id);
	int getOrderID();

	ofVec2f getPos();

	void sleep();

	static void setSleepTimeLen(float _timeLen);
	static void setBtnColor(ofColor _color);
	static void setBtnFontSize(int _size);
private:
	string wordStr;
	ofImage wordImg;
	ofVec2f pos;
	ofVec2f touchPos;
	ofRectangle touchRect;

	bool bTouched;
	int orderId;
	static ofSoundPlayer touchSound;

	BTN_TYPE btnType;
	static void init();
	static ofxTrueTypeFontUC font;
	static int fontSize;
	ofRectangle stringRect;
	static ofImage blueLargeImg;
	static ofImage redLargeImg;
	static ofImage blueMiddleImg;
	static ofImage redMiddleImg;
	static ofImage blueSmallImg;
	static ofImage redSmallImg;

	static float sleepTimeLen;
	static ofColor btnColor;

	enum 
	{
		WORD_STRING,
		WORD_OFIMAGE
	}wordType;

	float sleepTime;
	bool bSleep;
};

