#include "ofxVivitekComProject.h"



ofxVivitekComProject::ofxVivitekComProject()
{
}


ofxVivitekComProject::~ofxVivitekComProject()
{
}

void ofxVivitekComProject::setOnOoff(bool _state)
{
	static int const nbaud = 115200;
	string hexCmd = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << getCOM() + "          on" << endl;
		hexCmd = "0614000400341100005D";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << getCOM() + "          off" << endl;
		hexCmd = "0614000400341101005E";
	}
	string command = ofHexToString(hexCmd);

	sendCmd(command, nbaud);
}

