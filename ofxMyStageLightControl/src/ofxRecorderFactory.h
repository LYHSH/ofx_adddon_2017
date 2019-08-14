#pragma once
#include "ofxRecorderBase.h"
#include "ofxDataSender.h"
#include "ofMain.h"
typedef enum
{
	RECORD_TYPE_DMX_512 = 0,
	RECORD_TYPE_HUANG = 1,
}RECORD_TYPE;
/************************************************************************/
/* project name:录播控制器接口库
/* file describe:工厂类
/* date:2018.1.1
/* author:hui
/************************************************************************/
class ofxRecorderFactory
{
public:
	ofxRecorderFactory();
	~ofxRecorderFactory();

	

	static ofxRecorderBase * createcontroler(RECORD_TYPE _type,ofxDataSender * _sender);

	static ofxRecorderBase * createDMX512controler(string _ip,int _port);
	static ofxRecorderBase * createDMX512controler(int _nCom, int _nbaud);
	static ofxRecorderBase * createDMX512controler(ofxDataSender * _sender);

	static ofxRecorderBase * createHuangControler(string _ip, int _port);
	static ofxRecorderBase * createHuangControler(int _nCom, int _nbaud);
	static ofxRecorderBase * createHuangControler(ofxDataSender * _sender);

	static ofxRecorderBase * createUdpRealTimeControler(string _ip, int _port);
};

