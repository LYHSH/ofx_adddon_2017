#pragma once

#include "fboTexture.h"
#include "Surfaces.h"
#include "ofxProjectorBlend2.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"
#include "ofMain.h"
/************************************************************************/
/* project name:FBO融合管理器2
/* author:hui
/* date:2019.9.6
/************************************************************************/

class ofxProjectorBlendMgr2
{
public:
	ofxProjectorBlendMgr2();
	~ofxProjectorBlendMgr2();

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

	ofxProjectorBlend2 blender;
	int layoutH;
	int layoutV;

	//调试图片
	ofImage *settingImage;
	int settingImageOrder;

	//曲面
	ofFbo FBO;
	vector<Surfaces*> sf;
	vector<bool *> sfShows;
	int editOrder;
	vector<fboTexture*> fbo;
	int xNum;

	//窗口设置
	HWND thiswnd;

	bool EnableBlend;			//融合开启/关
	void enableBlendChanged(bool & _value);

	float allColor;	//伽玛值
	void allColorChanged(float & _value);

	float luminance;	//亮度
	void luminanceChanged(float & _value);
	float blendPower;	//强度
	void blendPowerChanged(float & _value);
	float horOverLayout;		//横向融合带宽度
	void horOverLayoutChanged(float & _value);
	float verOverLayout;		//纵向融合带宽度
	void verOverLayoutChanged(float & _value);

	int settingImgIndex;
	void settingImgIndexChanged(int & _order);

	void loadSetting(string _filename);
	void saveSetting(string _filename);

	vector<overLapData> overLapFlags;

	//影片
	ofFbo video;
};

