#pragma once

#include "fboTexture.h"
#include "Surfaces.h"
#include "ofxProjectorBlend2.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"
#include "ofMain.h"
/************************************************************************/
/* project name:FBO�ںϹ�����2
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

	int getCanvasWidth();				//�ںϻ����-����ǰ
	int getCanvasHeight();				//�ںϻ����-����ǰ


	int getWidth();						//��ʾ�����-�����
	int getHeight();					//��ʾ�����-�����

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

	//����ͼƬ
	ofImage *settingImage;
	int settingImageOrder;

	//����
	ofFbo FBO;
	vector<Surfaces*> sf;
	vector<bool *> sfShows;
	int editOrder;
	vector<fboTexture*> fbo;
	int xNum;

	//��������
	HWND thiswnd;

	bool EnableBlend;			//�ںϿ���/��
	void enableBlendChanged(bool & _value);

	float allColor;	//٤��ֵ
	void allColorChanged(float & _value);

	float luminance;	//����
	void luminanceChanged(float & _value);
	float blendPower;	//ǿ��
	void blendPowerChanged(float & _value);
	float horOverLayout;		//�����ںϴ����
	void horOverLayoutChanged(float & _value);
	float verOverLayout;		//�����ںϴ����
	void verOverLayoutChanged(float & _value);

	int settingImgIndex;
	void settingImgIndexChanged(int & _order);

	void loadSetting(string _filename);
	void saveSetting(string _filename);

	vector<overLapData> overLapFlags;

	//ӰƬ
	ofFbo video;
};

