#include "ofxpjlinkPJcontrol.h"



ofxpjlinkPJcontrol::ofxpjlinkPJcontrol()
{
}


ofxpjlinkPJcontrol::~ofxpjlinkPJcontrol()
{
}

void ofxpjlinkPJcontrol::setOnOoff(bool _state)
{
	static int const port = 4352;
	string command = "";

	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          on" << endl;
		command = "%1POWR 1\r\n";
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "          off" << endl;
		command = "%1POWR 0\r\n";
	}

	addPJLinkCommand(command, port);
}

void ofxpjlinkPJcontrol::setSingle(SINGLE_TYPE _type)
{
	static int const port = 7142;
	string hexCmd = "";

	switch (_type)
	{
	case ofxPJcontrolBase::HDMI:
		break;
	case ofxPJcontrolBase::DVI:
		break;
	case ofxPJcontrolBase::RGB2:
		break;
	case ofxPJcontrolBase::HDMI1:
	{
		hexCmd = "0203000002011a22";
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "  switch to HDMI1" << endl;
	}
		break;
	case ofxPJcontrolBase::HDMI2:
	{
		hexCmd = "0203000002011b23";
		ofLogNotice(OF_FUNCTION_NAME) << "ip  " + getIp() + "  switch to HDMI2" << endl;
	}
		break;
	default:
		break;
	}

	string command = ofHexToString(hexCmd);

	addPJLinkCommand(command, 7142);
}