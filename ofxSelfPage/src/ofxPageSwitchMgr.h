#pragma once
#include "pageControler.h"
#include "staticMgr.h"
/************************************************************************/
/* Project name:
/* Class description：界面切换管理器
/* Author: Hui
/* Date:2016/1/18
/************************************************************************/
class ofxPageSwitchMgr
{
public:

	static ofxPageSwitchMgr & getInstance();

	bool pageSwitch(pageBase * _page, PAGE_SWITCH_MODE _mode);

private:
	ofxPageSwitchMgr();
	~ofxPageSwitchMgr();
};

