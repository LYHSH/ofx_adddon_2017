#pragma once
#include "videoPlayer.h"
/************************************************************************/
/* project name:
/* file describe:������Ƶѭ������
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

