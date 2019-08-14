#include "ofxLEDmgr.h"



ofxLEDmgr::ofxLEDmgr()
{
}


ofxLEDmgr::~ofxLEDmgr()
{
}

void ofxLEDmgr::setup(const string & _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);

	int ledNums = xml.getNumTags("LED");
	for (int i = 0; i < ledNums; i++)
	{
		xml.pushTag("LED", i);

		int numType = xml.getValue("TYPE", 0);
		LED_TYPE ledType = LED_TYPE(numType);

		string ip = xml.getValue("IP", "127.0.0.1");
		ofxLedScreen * led = ofxLedScreenFactory::createLed(ip,ledType);
		leds.push_back(led);

		xml.popTag();
	}
}

void ofxLEDmgr::setOn(int _index)
 {
	if (!checkOut(_index))return;

	leds[_index]->setOn();
}

void ofxLEDmgr::setOff(int _index)
{
	if (!checkOut(_index))return;

	leds[_index]->setOff();
}

void ofxLEDmgr::setAllOn()
{
	for (auto ite = leds.begin(); ite != leds.end(); ++ite)
	{
		(*ite)->setOn();
		Sleep(1000);
	}
}

void ofxLEDmgr::setAllOff()
{
	for (auto ite = leds.begin(); ite != leds.end(); ++ite)
	{
		(*ite)->setOff();
		Sleep(1000);
	}
}

int ofxLEDmgr::size()const
{
	return leds.size();
}

bool ofxLEDmgr::checkOut(int _index)
{
	bool res = true;
	res &= (_index >= 0);
	res &= (_index < size());
	return res;
}
