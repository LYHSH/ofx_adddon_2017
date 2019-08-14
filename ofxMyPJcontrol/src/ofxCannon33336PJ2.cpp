#include "ofxCannon33336PJ2.h"



ofxCannon33336PJ2::ofxCannon33336PJ2()
{
}


ofxCannon33336PJ2::~ofxCannon33336PJ2()
{
}

void ofxCannon33336PJ2::setOnOoff(bool _state)
{
	static int const port = 33336;
	string hexCmd = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          on" << endl;
		hexCmd = "504F574552204F4E0D0A";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          off" << endl;
		hexCmd = "504F574552204F46460D0A0D0A";
	}
	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, port);
}