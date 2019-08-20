#pragma once
/************************************************************************/
/* Project name:中控软件
/* File describe:基本显示页面
/* Author:hui
/* Date:2017.4-2017.11
/* Update:2017.11.2
/************************************************************************/
#include "wordButton.h"
#include "ofxXmlSettings.h"
#include "pageBase.h"
#include "ofxTrueTypeFontUC.h"
class btnsShowPage : public pageBase
{
public:
	btnsShowPage();
	virtual ~btnsShowPage();
	virtual void setup(string _file,int _startOrder);
	virtual void update();
	virtual void draw();

	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void addChildPage(btnsShowPage * _page);
	void removeChildPage(btnsShowPage * _page);
protected:
	virtual void loadSetting(string _file);
	virtual void saveSetting(string _file);
	string settingFile;

	ofImage backImg;
	vector<wordButton*> btns;
	string titleWord;
	string titleWord1;

	int startOrder;

	vector<btnsShowPage *> childPages;

	static ofxTrueTypeFontUC font;
	static void init();
};

