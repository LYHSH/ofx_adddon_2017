#include "ofxMyConstants.h"

void ofDrawDemoStr()
{
	ofPushStyle();
	ofSetColor(255, 0, 0);
	string demoStr = "";
	for (int i = 0; i < 5; i++)
	{
		demoStr += "demodemodemodemodemodemodemodemodemo\n";
	}
	ofDrawBitmapString(demoStr, 20, 20);
	ofPopStyle();
}

void ofMyCmdSendSleep()
{
	Sleep(50);
}

void ofScreenCrossTopmost(int _w, int _h)
{
	//´°¿ÚÉèÖÃ
	HWND thiswnd;
	thiswnd = ofGetWin32Window();
	SetWindowLong(thiswnd, -16, 0x800000);
	SetWindowPos(thiswnd, HWND_TOPMOST, -1, -1, _w + 2, _h + 2, 0x40);
}