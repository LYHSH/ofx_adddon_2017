#pragma once
#include "ofxLedScreen.h"
/************************************************************************/
/* project name:�п����
/* file describe:LED������
/* author:hui
/* date:2018.3.2
/************************************************************************/
typedef enum
{
	LED_TYPE_LYD,
	LED_TYPE_8080
}LED_TYPE;
class ofxLedScreenFactory
{
public:
	ofxLedScreenFactory();
	~ofxLedScreenFactory();

	static ofxLedScreen * createLed(string _ip,LED_TYPE _type);

	static ofxLedScreen * createLYDled(string _ip);
	static ofxLedScreen * create8080Led(string _ip);
};

