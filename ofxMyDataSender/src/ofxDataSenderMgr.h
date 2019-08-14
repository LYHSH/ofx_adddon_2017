#pragma once
#include "ofMain.h"
#include "ofxDataSenderFacory.h"
#include "ofxXmlSettings.h"
/************************************************************************/
/* project name:dataSender�ӿڿ�
/* file describe:dataSender������
/* date:2019.3.1
/* author:hui
/************************************************************************/
class ofxDataSenderMgr
{
public:
	ofxDataSenderMgr();
	~ofxDataSenderMgr();

	void setup(const string & _filename);

	ofxDataSender * getSender(int _index);

	int size()const;
private:
	bool checkOut(int _index)const;			//Check out of range
	vector<ofxDataSender *> senders;
};

