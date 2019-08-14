#include "ofxChangShaPJ2.h"



ofxChangShaPJ2::ofxChangShaPJ2()
{
}


ofxChangShaPJ2::~ofxChangShaPJ2()
{
}

void ofxChangShaPJ2::setOnOoff(bool _state)
{
	static int const port = 38888;
	string hexCmd = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          on" << endl;
		hexCmd = "020000000002";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          off" << endl;
		hexCmd = "020100000003";
	}
	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, port);
}
