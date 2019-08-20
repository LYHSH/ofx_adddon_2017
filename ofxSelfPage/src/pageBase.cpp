#include "pageBase.h"
#include "ofxPageSwitchMgr.h"

pageBase::pageBase(void)
{
	bActive = false;
	dataDir = "";
	beginTime = 0.0f;
	parent = NULL;
	childer = NULL;
	controlIndex = 0;
	setStageRect(ofRectangle(0,0,ofGetWidth(),ofGetHeight()));
}


pageBase::~pageBase(void)
{
	parent = NULL;
	childer = NULL;
}

void pageBase::setId(int _id)
{
	pageId = _id;
}

int pageBase::getId()const
{
	return pageId;
}

void pageBase::addTouchId(int _id, PAGE_SWITCH_MODE _mode)
{
	touchIds[_id] = _mode;
}

void pageBase::removeTouchId(int _id)
{
	map<int, PAGE_SWITCH_MODE>::iterator ite;
	for (ite = touchIds.begin(); ite != touchIds.end(); ++ite)
	{
		if (_id == ite->first)
		{
			ite = touchIds.erase(ite);
			return;
		}
	}
}

bool pageBase::pageTouch(int _id)
{
	map<int, PAGE_SWITCH_MODE>::iterator ite;
	for (ite = touchIds.begin(); ite != touchIds.end(); ++ite)
	{
		if (_id == ite->first)
		{
			ofxPageSwitchMgr::getInstance().pageSwitch(this, ite->second);
			return true;
		}
	}

	return false;
}