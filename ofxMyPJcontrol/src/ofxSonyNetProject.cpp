#include "ofxSonyNetProject.h"



ofxSonyNetProject::ofxSonyNetProject()
{
}


ofxSonyNetProject::~ofxSonyNetProject()
{
}

void ofxSonyNetProject::setOnOoff(bool _state)
{
	static int const port = 4352;
	string hexCmd = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          on" << endl;
		hexCmd = "2531504F575220310D";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          off" << endl;
		hexCmd = "2531504F575220300D";
	}
	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, port);
}
