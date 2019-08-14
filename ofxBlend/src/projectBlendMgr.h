#pragma once

#include "fboTexture.h"
#include "Surfaces.h"
#include "ofxProjectorBlend.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"
#include "ofMain.h"
/************************************************************************/
/* project name:FBO�ںϹ�����
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

	ofxProjectorBlend blenderH;//ˮƽ
	ofxProjectorBlend blenderV;//��ֱ
	int layoutH;
	int layoutV;

	//����ͼƬ
	ofImage *settingImage;
	int settingImageOrder;

	//����
	ofFbo FBO;
	ofFbo verFBO;
	vector<Surfaces*> sf;
	vector<bool *> sfShows;
	int editOrder;
	vector<fboTexture*> fbo;
	int xNum;

	//��������
	HWND thiswnd;

	bool EnableBlend;			//�ںϿ���/��
	void enableBlendChanged(bool & _value);

	float horAllColor;	//����٤��ֵ
	void horAllColorChanged(float & _value);

	float horLuminance;	//��������
	void horLuminanceChanged(float & _value);
	float horBlendPower;	//����ǿ��
	void horBlendPowerChanged(float & _value);
	float horLayout;		//�����ںϴ����
	void horhorLayoutChanged(float & _value);


	float verAllColor;	//����٤��ֵ
	void verAllColorChanged(float & _value);
	float verLuminance;	//��������
	void verLuminanceChanged(float & _value);
	float verBlendPower;	//����ǿ��
	void verBlendPowerChanged(float & _value);
	float verLayout;		//�����ںϴ����
	void verhorLayoutChanged(float & _value);

	int settingImgIndex;
	void settingImgIndexChanged(int & _order);

	void loadSetting(string _filename);
	void saveSetting(string _filename);

	vector<overLapData> overLapFlags;

	//ӰƬ
	ofFbo video;
};

