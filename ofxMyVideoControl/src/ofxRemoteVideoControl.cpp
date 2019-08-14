#include "ofxRemoteVideoControl.h"
#include "ofxDataSenderFacory.h"
#include "videoControlCmd.h"
#include "cmdConverter.h"

ofxRemoteVideoControl::ofxRemoteVideoControl()
{
	sender = NULL;
}


ofxRemoteVideoControl::~ofxRemoteVideoControl()
{
	if (sender)
	{
		delete sender;
	}
}

void ofxRemoteVideoControl::setup(string _ip)
{
	ip = _ip;
	sender = ofxDataSenderFacory::createUdpSender(ip, PORT_MOVIE_CONTROL);
}

void ofxRemoteVideoControl::play()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " play" << endl;
	sendCmd(convert(CMD_MOVIE_PLAY));
}

void ofxRemoteVideoControl::play(int _videoIndex)
{
	ofLogNotice() << ip << " play"<<_videoIndex<<" movie" << endl;

	string cmd = FLAG_MOVIE_INDEX + SEPERATOR_MOVIE_INDEX + ofToString(_videoIndex);
	sendCmd(convert(cmd));
}

void ofxRemoteVideoControl::pause()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " pause" << endl;
	sendCmd(convert(CMD_MOVIE_PAUSE));
}

void ofxRemoteVideoControl::stop()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " stop" << endl;
	sendCmd(convert(CMD_MOVIE_STOP));
}

void ofxRemoteVideoControl::rePlay()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " replay" << endl;
	sendCmd(convert(CMD_MOVIE_REPLAY));
}

void ofxRemoteVideoControl::volumeAdd()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " volume add" << endl;
	sendCmd(convert(CMD_VOLUME_ADD));
}

void ofxRemoteVideoControl::volumeSub()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " volume sub" << endl;
	sendCmd(convert(CMD_VOLUME_SUB));
}

void ofxRemoteVideoControl::mute()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " mute" << endl;
	sendCmd(convert(CMD_VOLUME_OFF));
}

void ofxRemoteVideoControl::unMute()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " unMute" << endl;
	sendCmd(convert(CMD_VOLUME_ON));
}

void ofxRemoteVideoControl::playNextMovie()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " playNextMovie" << endl;
	sendCmd(convert(CMD_NEXT_MOVIE));
}

void ofxRemoteVideoControl::playPrevMovie()
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << " playPrevMovie" << endl;
	sendCmd(convert(CMD_PRVE_MOVIE));
}

void ofxRemoteVideoControl::setActive(bool _state)
{
	if (_state)
	{
		ofLogNotice(OF_FUNCTION_NAME) << ip << " active true" << endl;
		sendCmd(convert(CMD_ACTIVE_TRUE));
	}
	else
	{
		ofLogNotice(OF_FUNCTION_NAME) << ip << " active false" << endl;
		sendCmd(convert(CMD_ACTIVE_FALSE));
	}
}

string ofxRemoteVideoControl::getIP()const
{
	return ip;
}

void ofxRemoteVideoControl::sendCmd(string _cmd)
{
	sender->sendData(_cmd.c_str(), _cmd.size());
}

string ofxRemoteVideoControl::convert(string _sourceStr)
{
	return cmdConverter::getEncryCmd(_sourceStr);
}
