#include "ofxRecorderBase.h"
#include "ofxMyConstants.h"


ofxRecorderBase::ofxRecorderBase()
{
}


ofxRecorderBase::~ofxRecorderBase()
{
}

void ofxRecorderBase::play()
{
	ofLogNotice(OF_FUNCTION_NAME) <<"base method,do nothing..." << endl;
}

void ofxRecorderBase::pause()
{
	ofLogNotice(OF_FUNCTION_NAME) << "base method,do nothing..." << endl;
}

void ofxRecorderBase::stop()
{
	ofLogNotice(OF_FUNCTION_NAME) << "base method,do nothing..." << endl;
}

void ofxRecorderBase::setAddress(unsigned char _addressCode)
{
	address = _addressCode;
}

unsigned char ofxRecorderBase::getAddress()const
{
	return address;
}
