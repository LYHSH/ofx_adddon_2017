#pragma once
#include "flipSwitcher.h"
/************************************************************************/
/* project name: 
/* file describe: 界面转场效果类-上飞行
/* author:hui
/* date:2018/06/21
/************************************************************************/
class upFlipSwitcher : public flipSwitcher
{
public:
	upFlipSwitcher();
	~upFlipSwitcher();

	virtual void setup(pageBase * _removePage, pageBase * _mainPage) {
		flipSwitcher::setup(_removePage, _mainPage);

		if (removePage)
		{
			removePage->begin();
		}

		mainPage->begin();

		if (removePage)
		{
			removeMove = _removePage->getStageRect().getTopLeft();
			removeMoveto = removeMove;
			removeMoveto.y -= _removePage->getStageRect().getHeight();
		}


		mainMove = _mainPage->getStageRect().getTopLeft();
		mainMove.y += mainPage->getStageRect().getHeight();
		mainMoveto = mainMove;
		mainMoveto.y -= _mainPage->getStageRect().getHeight();
	}
};

