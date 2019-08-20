#pragma once
#include "pageBase.h"
/************************************************************************/
/* project name: 罗甸玉互动飞屏软件
/* file describe: 界面转场效果类
/* author:hui
/* date:2016/12/19
/************************************************************************/
class pageSwitchBase
{
public:
	pageSwitchBase();
	virtual ~pageSwitchBase(void);

	virtual void setup(pageBase * _removePage,pageBase * _mainPage){
		removePage = _removePage;
		if (removePage)
		{
			removePage->begin();
		}
		
		mainPage = _mainPage;
		mainPage->begin();
	}
	virtual void update(){
		mainPage->cusupdate();
	}
	virtual void draw(){
		if (removePage)
		{
			removePage->cusdraw();
		}
		
		mainPage->cusdraw();
	}

	virtual void keyPressed(int key){
		mainPage->cuskeyPressed(key);
	}
	virtual void keyReleased(int key){
		mainPage->cuskeyReleased(key);
	}
	virtual void mouseMoved(int x, int y ){
		mainPage->cusmouseMoved(x,y);
	}
	virtual void mouseDragged(int x, int y, int button){
		mainPage->cusmouseDragged(x,y,button);
	}
	virtual void mousePressed(int x, int y, int button){
		mainPage->cusmousePressed(x,y,button);
	}
	virtual void mouseReleased(int x, int y, int button){
		mainPage->cusmouseReleased(x,y,button);
	}

	virtual bool isDied(){
		return false;
	}

	pageBase * getMainPage(){
		return mainPage;
	}

protected:
	pageBase * removePage;		//离场页
	pageBase * mainPage;		//主页
};

