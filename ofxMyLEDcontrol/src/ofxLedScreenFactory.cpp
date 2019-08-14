#include "ofxLedScreenFactory.h"
#include "ofxLYDledScreen.h"
#include "ofx8080LedScreen.h"


ofxLedScreenFactory::ofxLedScreenFactory()
{
}


ofxLedScreenFactory::~ofxLedScreenFactory()
{
}

ofxLedScreen * ofxLedScreenFactory::createLed(string _ip, LED_TYPE _type) 
{
	switch (_type)
	{
	case LED_TYPE_LYD:
		return createLYDled(_ip);
		break;
	case LED_TYPE_8080:
		return create8080Led(_ip);
		break;
	default:
		return NULL;
		break;
	}
}

ofxLedScreen * ofxLedScreenFactory::createLYDled(string _ip)
{
	ofxLYDledScreen * led = new ofxLYDledScreen();
	led->setup(_ip);

	return led;
}

ofxLedScreen * ofxLedScreenFactory::create8080Led(string _ip)
{
	ofx8080LedScreen * led = new ofx8080LedScreen();
	led->setup(_ip);

	return led;
}
