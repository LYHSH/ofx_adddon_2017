#pragma once
/************************************************************************/
/* project name:视频播放远程控制库
/* file describe:管理器
/* author:hui
/* date:2017.8.31
/************************************************************************/
#include "ofMain.h"
#include "ofxRemoteVideoControl.h"
class ofxRemoteVideoControlMgr
{
public:
	ofxRemoteVideoControlMgr();
	~ofxRemoteVideoControlMgr();

	void setup(const string & _filename);

	void play(int _index);
	void play(int _index,int _videoIndex);
	void pause(int _index);
	void stop(int _index);
	void replay(int _index);
	void volumeAdd(int _index);
	void volumeSub(int _index);
	void mute(int _index);
	void unmute(int _index);
	void playNextMoive(int _index);
	void playPrevMoive(int _index);
	void setActive(int _index,bool _state);

	string getIP(int _index)const;

	vector<string> getIPs(int _index)const;

	int size()const;
private:
	bool checkOut(int _index)const;			//Check out of range

	vector<vector<ofxRemoteVideoControl *>> controler;
};

