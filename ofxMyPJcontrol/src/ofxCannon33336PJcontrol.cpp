#include "ofxCannon33336PJcontrol.h"



ofxCannon33336PJcontrol::ofxCannon33336PJcontrol()
{
}


ofxCannon33336PJcontrol::~ofxCannon33336PJcontrol()
{
}

void ofxCannon33336PJcontrol::setOnOoff(bool _state)
{
	static int const port = 33336;
	string hexCmd = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          on" << endl;
		hexCmd = "504F5745523D4F4E0D0A";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          off" << endl;
		hexCmd = "504F5745523D4F46460D0A";
	}
	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, port);
}
