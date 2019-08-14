#pragma once
#include "ofxRelayFactory.h"
#include "ofxXmlSettings.h"
#include "ofxDataSenderMgr.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:�̵���������
/* date:2018.2.8
/* author:hui
/************************************************************************/
class ofxRelaysMgr
{
public:
	ofxRelaysMgr();
	~ofxRelaysMgr();

	void setup(const string & _filename);
	void setupWithDataSender(const string & _filename);
	void setupWithHistory(const string & _filename);

	ofxRelaysBase * getRelayer(int _index);

	void begin(int _relayIndex);
	void setOn(int _id);
	void setOff(int _id);

	void setMultOn(vector<int> & _ids);			//�鿪�����ౣ��ԭ״̬
	void setMultOff(vector<int> & _ids);		//��أ����ౣ��ԭ״̬

	void setSingleOn(int _id);					//��·��������ر�
	void setSingleOn(vector<int> & _ids);

	void setAllOn();
	void setAllOff();

	void stepAllOn();
	void stepAllOff();

	int loopSize();

	void end();

	int size()const;
private:
	bool checkOut(int _index)const;			//Check out of range

	ofxRelaysBase * tempRelay;

	vector<ofxRelaysBase *> relays;

	ofxDataSenderMgr senderMgr;
};

