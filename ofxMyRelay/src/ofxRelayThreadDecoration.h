#pragma once
#include "ofxRelaysBase.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:�̵����߳�װ����
/* date:2017.7.16
/* author:hui
/* update:2018.11.12  ����ֱ�Ӽ̳и���
/************************************************************************/

struct threadOrder
{
	int type;				//0 single order; 1 mutl order;2 singleon order;3 multsingle order
	bool onoff;
	int id;
	vector<int> ids;
};

class ofxRelayThreadDecoration : public ofxRelaysBase,public ofThread
{
public:
	ofxRelayThreadDecoration(ofxRelaysBase * _pRelay);
	~ofxRelayThreadDecoration();
	void setup();

	void setOn(int _id) override final;
	void setOff(int _id) override final;

	void setMultOn(vector<int> & _ids) override final;
	void setMultOff(vector<int> & _ids) override final;

	void setSingleOn(vector<int> & _ids) override final;

	void setAllOn() override final;
	void setAllOff() override final;

	void close() override final;

	int size() override final;
private:
	void threadedFunction()override final;
	ofxRelaysBase * pRelay;

	queue<threadOrder> orders;
};

