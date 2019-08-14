#pragma once
/************************************************************************/
/* project name
/* file describe:Ò³Ãæ±³¾°¹¤³§
/* author:hui
/* date:2019.1.29
/************************************************************************/
#include "ofxPageBack.h"
class ofxPageBackFactory
{
public:
	ofxPageBackFactory();
	~ofxPageBackFactory();

	static ofxPageBack * createVideoPageBack(string _videoPath);
	static ofxPageBack * createImagePageBack(string _imgPath);
	static ofxPageBack * createNullPageBack(string _path);
};

