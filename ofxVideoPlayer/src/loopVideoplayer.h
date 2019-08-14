#pragma once
#include "videoPlayer.h"
/************************************************************************/
/* project name:
/* file describe:待机视频循环播放
/* author:hui
/* date:2016/12/17
/************************************************************************/
class loopVideoplayer : public videoPlayer
{
public:
	loopVideoplayer();
	~loopVideoplayer();

	void update();

private:

	float lastTime;
	float synTimeLen;
};

