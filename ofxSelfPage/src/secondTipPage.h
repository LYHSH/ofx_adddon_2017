#pragma once
#include "ofMain.h"
#include "button.h"
#include "wordButton.h"
#include "ofxXmlSettings.h"
/************************************************************************/
/* project name:中控软件
/* file describe: 二次确认界面
/* author:hui
/* date:2016/12/19
/* udpate:2017.9.20
/************************************************************************/
class secondTipPage
{
public:
	secondTipPage();
	~secondTipPage();

	static void begin(int _order,button * btn);

	static bool isActiving();

	static void draw();

	static void mousePressed(int x,int y);
	static void mouseReleased(int x,int y);

	static void addSecondConfirmId(int _id);		//添加二次确认id
private:
	enum
	{
		BTN_OK,
		BTN_CANCEL,
		BTN_NUMS
	};

	static bool bActive;
	static int order;
	static float beginTime;

	static void init();
	static vector<wordButton*> btns;
	static button *touchBtn;

	static vector<int> seceodConfirmIds;			//需要进行二次确认的按钮ID数组
};

