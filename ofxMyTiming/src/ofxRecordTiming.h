#pragma once
#include "ofxRecordMgr.h"
#include "ofxXmlSettings.h"
#include "storageXml.h"
/************************************************************************/
/* project name:视频时间轴控制接口库
/* file describe:录播控制器时间轴控制类
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

	int resetOrder;    ///复位指令编号

	vector<storageXml> timingDatas;
};

