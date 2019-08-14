#include "ofxDLPproject.h"



ofxDLPproject::ofxDLPproject()
{
}


ofxDLPproject::~ofxDLPproject()
{
}


void ofxDLPproject::setOnOoff(bool _state)
{
	static int const port = 1024;
	string hexCmd = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          on" << endl;
		hexCmd = "3030504F4E0D";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          off" << endl;
		hexCmd = "3030504F460D";
	}
	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, port);
}

void ofxDLPproject::setSingle(SINGLE_TYPE _type)
{
	static int const port = 1024;
	string hexCmd = "";

	switch (_type)
	{
	case ofxPJnetControlBase::DVI:
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "  switch to DVI" << endl;
		hexCmd = "30304949533A4456490D";
	}
	break;
	case ofxPJnetControlBase::RGB2:
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "  switch to RGB2" << endl;
		hexCmd = "30304949533A5247320D";
	}
	break;
	default:
		break;
	}

	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, port);
}