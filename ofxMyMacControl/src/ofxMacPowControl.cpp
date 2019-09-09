#include "ofxMacPowControl.h"

ofxMacPowControl::ofxMacPowControl()
{
}


ofxMacPowControl::~ofxMacPowControl()
{
}

void ofxMacPowControl::setup()
{
	shutdownUdp.Create();
	shutdownUdp.SetNonBlocking(true);


	wakeupUdp.Create();
	wakeupUdp.SetNonBlocking(true);
	wakeupUdp.SetEnableBroadcast(true);
	wakeupUdp.Connect("255.255.255.255", 9999);
}

void ofxMacPowControl::powOn(string macStr)
{
	ofLogNotice(OF_FUNCTION_NAME) << macStr << endl;
	//Buffer for packet
	char magicP[102];

	for (int i = 0; i < 6; i++)
         magicP[i] = 0xff;

	vector <string> sss = ofSplitString(macStr, "-");
	for (int i = 0; i < 6; i++)
		magicP[i + 6] = ofHexToInt(sss[i].c_str());

	//fill remaining 90 bytes (15 time repeat)
	//Warning : It is higly recommended not to use functions like
	//memcpy, read MSDN for more details.
	for (int i = 0; i < 15; i++)
		memcpy(&magicP[(i + 2) * 6], &magicP[6], 6);
	
	wakeupUdp.Send(magicP, 102);
}
void ofxMacPowControl::powOff(string ip)
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << endl;

	static const string msg = "shutdown";

	shutdownUdp.Connect(ip.c_str(), 1000);
	shutdownUdp.Send(msg.c_str(), msg.length());

	Sleep(100);

	shutdownUdp.Connect(ip.c_str(), 30801);
	shutdownUdp.Send(msg.c_str(), msg.length());
}