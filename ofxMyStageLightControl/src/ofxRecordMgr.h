#pragma once
#include "ofxRecorderFactory.h"
#include "ofxXmlSettings.h"
#include "ofxDataSenderMgr.h"
/************************************************************************/
/* project name:¼���������ӿڿ�
/* file describe:¼��������������
/* date:2018.1.1
/* author:hui
/************************************************************************/
class ofxRecordMgr
{
public:
	ofxRecordMgr();
	~ofxRecordMgr();

	void setup(const string & _filename);

	ofxRecorderBase * getRecorder(int _index);

	int size()const;
private:
	bool checkOut(int _index)const;			//Check out of range
	vector<ofxRecorderBase *> recorders;

	ofxDataSenderMgr senderMgr;
};

