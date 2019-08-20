#pragma once
#include "pageBase.h"
#include "buttonFactory.h"
#include "ofxXmlSettings.h"
#include "ofxMyConstants.h"
#include "orderHandler.h"
#include "ofxPageBack.h"
/************************************************************************/
/* Project name:UI界面模块
/* Class description：基本按钮页面
/* Author: Hui
/* Date:2018.2.8
/************************************************************************/
class ofxBtnPage : public pageBase
{
public:
	static ofxBtnPage * createPage(int _controlIndex);
	static ofxBtnPage * createMainPage();
	static ofxBtnPage * createSecondPage();
	static ofxBtnPage * createThirdPage();

	void setup(string _file, int _startOrder);
	void update();
	void draw();

	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	static int const MAIN_PAGE_INDEX = 0;
	static int const SECOND_PAGE_INDEX = 1;
	static int const THIRD_PAGE_INDEX = 2;
private:
	ofxBtnPage();
	~ofxBtnPage();

	void loadSetting(string _file,int _startOrder);

	button * createButton(const ofImage & _tex, ofVec2f _pos,int _btnId);
	button * createButton(const ofImage & _showTex, const ofImage & _touchTex, ofVec2f _centerPos, int _btnId);
	string settingFile;

	ofxPageBack * pageBack;
	vector<button*> btns;

	int startOrder;
};

