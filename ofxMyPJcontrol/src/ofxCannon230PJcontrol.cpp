#include "ofxCannon230PJcontrol.h"



ofxCannon230PJcontrol::ofxCannon230PJcontrol()
{
}


ofxCannon230PJcontrol::~ofxCannon230PJcontrol()
{
}

void ofxCannon230PJcontrol::setOnOoff(bool _state)
{
	static int const port = 23;
	string hexCmd = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          on" << endl;
		hexCmd = "7E504E0D";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          off" << endl;
		hexCmd = "7E50460D";
	}
	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, port);
}
