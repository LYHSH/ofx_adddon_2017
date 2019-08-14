#pragma once

#include "fboTexture.h"
#include "Surfaces.h"
#include "ofxProjectorBlend.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"
#include "ofMain.h"
/************************************************************************/
/* project name:FBO融合管理器
/* author:hui
/* date:2017.9.27
/************************************************************************/
class projectBlendMgr
{
public:
	projectBlendMgr();
	~projectBlendMgr();

	void setup();
	void update();
	void draw();
	void draw(ofVec2f _offset);

	void keyPressed(int key);

	void setDir(string _dir);
	string getDirPath(string _path);

	void startGrabScreen();
	void endGrabScreen();

	int getCanvasWidth();				//融合画面宽-处理前
	int getCanvasHeight();				//融合画面高-处理前


	int getWidth();						//显示画面宽-处理后
	int getHeight();					//显示画面高-处理后

	int getChannelNums();

	void showSettingWindow(bool & _bOpen);
private:
	string dir;

	float singleScreenW;
	float singleScreenH;
	int horProjectNums;
	int verProjectNums;
	bool initXml;
	float showScale;
	string gridPicPath;

	ofxProjectorBlend blenderH;//水平
	ofxProjectorBlend blenderV;//垂直
	int layoutH;
	int layoutV;

	//调试图片
	ofImage *settingImage;
	int settingImageOrder;

	//曲面
	ofFbo FBO;
	ofFbo verFBO;
	vector<Surfaces*> sf;
	vector<bool *> sfShows;
	int editOrder;
	vector<fboTexture*> fbo;
	int xNum;

	//窗口设置
	HWND thiswnd;

	bool EnableBlend;			//融合开启/关
	void enableBlendChanged(bool & _value);

	float horAllColor;	//横向伽玛值
	void horAllColorChanged(float & _value);

	float horLuminance;	//横向亮度
	void horLuminanceChanged(float & _value);
	float horBlendPower;	//横向强度
	void horBlendPowerChanged(float & _value);
	float horLayout;		//横向融合带宽度
	void horhorLayoutChanged(float & _value);


	float verAllColor;	//纵向伽玛值
	void verAllColorChanged(float & _value);
	float verLuminance;	//纵向亮度
	void verLuminanceChanged(float & _value);
	float verBlendPower;	//纵向强度
	void verBlendPowerChanged(float & _value);
	float verLayout;		//纵向融合带宽度
	void verhorLayoutChanged(float & _value);

	int settingImgIndex;
	void settingImgIndexChanged(int & _order);

	void loadSetting(string _filename);
	void saveSetting(string _filename);

	vector<overLapData> overLapFlags;

	//影片
	ofFbo video;
};

