#include "ofxPageSwitchMgr.h"



ofxPageSwitchMgr::ofxPageSwitchMgr()
{
}


ofxPageSwitchMgr::~ofxPageSwitchMgr()
{
}

ofxPageSwitchMgr & ofxPageSwitchMgr::getInstance()
{
	static ofxPageSwitchMgr mgr;
	return mgr;
}

bool ofxPageSwitchMgr::pageSwitch(pageBase * _page, PAGE_SWITCH_MODE _mode)
{
	bool res = true;
	pageBase * nextPage = _page;
	int controlIndex = nextPage->getControlIndex();

	switch (_mode)
	{
	case NO_SWITCH_MODE:
	{
		pageControler::getInstance().noSwitch(nextPage,controlIndex);
	}
	break;
	case LEFT_LEAVE_SWITCH_MODE:
	{
		pageControler::getInstance().leftLeaveSwitch(nextPage, controlIndex);
	}
	break;
	case RIGHT_LEAVE_SWITCH_MODE:
	{
		pageControler::getInstance().rightLeaveSwitch(nextPage, controlIndex);
	}
	break;
	case UP_LEAVE_SWITCH_MODE:
	{
		pageControler::getInstance().upLeaveSwitch(nextPage, controlIndex);
	}
	break;
	case DOWN_LEAVE_SWITCH_MODE:
	{
		pageControler::getInstance().downLeaveSwitch(nextPage, controlIndex);
	}
	break;
	default:
		break;
	}

	return res;
}
