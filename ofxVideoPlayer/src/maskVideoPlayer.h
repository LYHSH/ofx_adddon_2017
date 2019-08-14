#pragma once
#include "videoPlayer.h"
/************************************************************************/
/* project name:
/* file describe:视频加遮罩效果
/* author:hui
/* date:2018.10.7
/************************************************************************/
class maskVideoPlayer: public videoPlayer
{
public:
	maskVideoPlayer();
	~maskVideoPlayer();

	void draw(float x, float y, float width, float height) final;

	void reloadVideo(int _index)final;

	void keyPressed(int key)final;
private:
	ofImage maskImg;

	vector<string> maskimgPaths;

	float angle;
	float scale;
};

