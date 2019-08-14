#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "Surfaces.h"
/************************************************************************/
/* project name:多视频融合-融合参数初始化软件
/* file describe:融合参数初始化类
/* author:hui
/* date:2019.01.31
/************************************************************************/
class projectBlendIniter
{
public:
	projectBlendIniter();
	~projectBlendIniter();

	void setup();
	void update();
	void draw();

	void setDir(string _dir);
	string getDir();
	string getDirPath(string _path);
	void setTitle(string _str);
	void setVisible(bool _flag);

	void showGui(bool & _flag);
private:
	string dataDir;
	bool bVisible;

	string titleStr;

	int singleScreenW;
	int singleScreenH;
	int horProjectNums;
	int verProjectNums;

	int resolutionIndex = 0;					//分辨率选项序号
	void handleResolutionSetting(string _theme);	//投影分辨率设置处理
	void handleDataSave();						//数据保存处理

	string gridPicPath;
};

