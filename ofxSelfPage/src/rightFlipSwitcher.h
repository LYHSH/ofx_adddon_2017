#pragma once
#include "flipSwitcher.h"
/************************************************************************/
/* project name: 罗甸玉互动飞屏软件
/* file describe: 界面转场效果类-右飞行离场
/* author:hui
/* date:2016/12/21
/************************************************************************/
class rightFlipSwitcher : public flipSwitcher
{
public:
	rightFlipSwitcher(void);
	~rightFlipSwitcher(void);

	virtual void setup(pageBase * _removePage,pageBase * _mainPage){
		flipSwitcher::setup(_removePage,_mainPage);

		if (removePage)
		{
			removePage->begin();
		}
		
		mainPage->begin();

		if (removePage)
		{
			removeMove = _removePage->getStageRect().getTopLeft();
			removeMoveto = removeMove;
			removeMoveto.x += _removePage->getStageRect().getWidth();
		}
		

		mainMove = _mainPage->getStageRect().getTopLeft();
		mainMove.x -= mainPage->getStageRect().getWidth();
		mainMoveto = mainMove;
		mainMoveto.x += _mainPage->getStageRect().getWidth();
	}
};

