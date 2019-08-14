#include "ofxChangShaPJ1.h"



ofxChangShaPJ1::ofxChangShaPJ1()
{
}


ofxChangShaPJ1::~ofxChangShaPJ1()
{
}

void ofxChangShaPJ1::setOnOoff(bool _state)
{
	static int const port = 38888;
	string hexCmd = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          on" << endl;
		hexCmd = "505752204F4E0D";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          off" << endl;
		hexCmd = "505752204F46460D";
	}
	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, port);
}
