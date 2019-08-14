#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "Surfaces.h"
/************************************************************************/
/* project name:����Ƶ�ں�-�ںϲ�����ʼ�����
/* file describe:�ںϲ�����ʼ����
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

	int resolutionIndex = 0;					//�ֱ���ѡ�����
	void handleResolutionSetting(string _theme);	//ͶӰ�ֱ������ô���
	void handleDataSave();						//���ݱ��洦��

	string gridPicPath;
};

