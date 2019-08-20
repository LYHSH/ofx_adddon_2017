#pragma once
#include "ofMain.h"
#include "pageSwitchBase.h"
#include "pageBase.h"
/************************************************************************/
/* project name:
/* file describe: 界面显示控制器
/* author:hui
/* date:2016/12/19
/* udpate:2017.9.20
/************************************************************************/


class unattendedEventArgs : public ofEventArgs {
public:
};

class pageControler
{
public:
	static pageControler & getInstance();
	static ofEvent<unattendedEventArgs> 		unattendedEvent;

	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void noSwitch(pageBase * _page,int _index = 0);
	void leftLeaveSwitch(pageBase * _removePage,pageBase * _mainPage, int _index = 0);
	void rightLeaveSwitch(pageBase * _removePage,pageBase * _mainPage, int _index = 0);
	void upLeaveSwitch(pageBase * _removePage, pageBase * _mainPage, int _index = 0);
	void downLeaveSwitch(pageBase * _removePage, pageBase * _mainPage, int _index = 0);
	void leftLeaveSwitch(pageBase * _mainPage, int _index = 0);
	void rightLeaveSwitch(pageBase * _mainPage, int _index = 0);
	void upLeaveSwitch(pageBase * _mainPage, int _index = 0);
	void downLeaveSwitch(pageBase * _mainPage, int _index = 0);
	void rectSpreadSwitch(pageBase * _removePage,pageBase * _mainPage,ofRectangle _SrcRect, int _index = 0);
	pageBase * getMainPage(int _index = 0);

	int getNewIndex();

	void setFboRect(ofRectangle _fboRect,int _index = 0);
	void setUseFbo(bool _use, int _index = 0);
	void setDrawRect(ofRectangle _drawRect, int _index = 0);

	void addNewSwitcher();

	void setUnattendedTimeLen(float _timeLen);
private:
	pageControler(void);
	~pageControler(void);
	void setup();
	bool checkOutRange(int _index);
	bool checkUnattended();
	void updateUnattended();
	void notifyUnattendedEvent();

	vector<pageSwitchBase *> switchers;
	vector<ofFbo *> fbos;
	vector<bool> useFboFlags;
	vector<ofRectangle> fboRects;
	vector<ofRectangle> drawRects;

	float lastTouchTime = 0.0f;
	float unattendedTimeLen = 300.0f;			//无人值守触发时间长度值			
};

