#pragma once
/************************************************************************/
/* project name:视频播放远程控制库
/* file describe:视频播放远程控制类
/* author:hui
/* date:2017.8.31
/************************************************************************/
#include "ofMain.h"
#include "ofxDataSenderFacory.h"
#include "ofxMyConstants.h"

class ofxRemoteVideoControl
{
public:
	ofxRemoteVideoControl();
	~ofxRemoteVideoControl();

	void setup(string _ip);
	
	void play();
	void play(int _videoIndex);
	void pause();
	void stop();
	void rePlay();
	void volumeAdd();
	void volumeSub();
	void mute();
	void unMute();
	void playNextMovie();
	void playPrevMovie();

	void setActive(bool _state);

	string getIP()const;
private:
	void sendCmd(string _cmd);
	string convert(string _sourceStr);
	string ip;
	int port;
	ofxDataSender * sender;
	
};

