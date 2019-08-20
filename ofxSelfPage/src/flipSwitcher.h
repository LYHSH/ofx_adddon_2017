#pragma once
#include "pageSwitchBase.h"
/************************************************************************/
/* project name: 罗甸玉互动飞屏软件
/* file describe: 界面转场效果类-左飞行离场
/* author:hui
/* date:2016/12/19
/************************************************************************/
class flipSwitcher : public pageSwitchBase
{
public:
	flipSwitcher(void);
	virtual ~flipSwitcher(void);

	virtual void setup(pageBase * _removePage,pageBase * _mainPage){
		pageSwitchBase::setup(_removePage,_mainPage);

		if (removePage)
		{
			removePage->begin();

			removeMove = _removePage->getStageRect().getTopLeft();
			removeMoveto = removeMove;
			removeMoveto.x -= _removePage->getStageRect().getWidth();
		}
		
		mainPage->begin();

		

		mainMove = _mainPage->getStageRect().getTopRight();
		mainMoveto = mainMove;
		mainMoveto.x -= _mainPage->getStageRect().getWidth();
	}
	virtual void update(){
		removePage->cusupdate();
		mainPage->cusupdate();

		if (ofDist(removeMoveto.x,removeMoveto.y,removeMove.x,removeMove.y) > 0.1f)
		{
			removeMove += (removeMoveto - removeMove) * 0.2f;
		}
		else
		{
			removeMove = removeMoveto;
			if (removePage && removePage->isActiving() && removePage != mainPage)
			{
				removePage->end();
			}
		}

		if (ofDist(mainMoveto.x,mainMoveto.y,mainMove.x,mainMove.y) > 0.1f)
		{
			mainMove += (mainMoveto - mainMove) * 0.2f;
		}
		else
		{
			mainMove = mainMoveto;
		}
	}
	virtual void draw(){
		ofPushMatrix();
		ofTranslate(removeMove);
		removePage->cusdraw();
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(mainMove);
		mainPage->cusdraw();
		ofPopMatrix();
	} 

protected:
	ofVec2f removeMoveto;
	ofVec2f removeMove;

	ofVec2f mainMoveto;
	ofVec2f mainMove;
};

