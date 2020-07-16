#include "ofxDataSender.h"



ofxDataSender::ofxDataSender()
{
}


ofxDataSender::~ofxDataSender()
{
}

void ofxDataSender::printTestData(const char *_data, int _size)
{
	stringstream sss;
	for (int i = 0; i < _size; i++)
	{
		sss << " " << ofToHex(_data[i]);;
	}

	ofLogNotice(OF_FUNCTION_NAME) <<"[HEX]" <<sss.str() << endl;
	ofLogNotice(OF_FUNCTION_NAME) << "[STRING]"<<_data << endl;
}

void ofxDataSender::setDelay(bool _isDelay)
{
    m_isDelay = _isDelay;
}

void ofxDataSender::SetConnectState(bool _isShort)
{
    m_isShortConnection = _isShort;
}

bool ofxDataSender::isDelay() const
{
    return m_isDelay;
}

bool ofxDataSender::IsShortConnection()const
{
    return m_isShortConnection;
}