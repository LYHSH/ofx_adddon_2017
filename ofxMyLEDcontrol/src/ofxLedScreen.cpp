#include "ofxLedScreen.h"



ofxLedScreen::ofxLedScreen()
{
}


ofxLedScreen::~ofxLedScreen()
{
}

void ofxLedScreen::sendData(const char *_data, int _size)
{
	if (NULL == sender)return;

	sender->sendData(_data, _size);
}
