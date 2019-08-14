#pragma once
#include "ofxRecordMgr.h"
#include "ofxXmlSettings.h"
#include "storageXml.h"
/************************************************************************/
/* project name:��Ƶʱ������ƽӿڿ�
/* file describe:¼��������ʱ���������
/* date:2018.3.1
/* author:hui
/************************************************************************/
class ofxRecordTiming
{
public:
	ofxRecordTiming();
	~ofxRecordTiming();

	void setup(string _fileName);
	void update(int _videoIndex,int _frame);
	void draw();

	void reset();
	void setResetOrder(int _value);

	void play();
	void pause();
	void stop();
private: 

	ofxRecordMgr mgr;
	ofxRecorderBase * recorder;
	void recordPlay(int _order);

	int resetOrder;    ///��λָ����

	vector<storageXml> timingDatas;
};

