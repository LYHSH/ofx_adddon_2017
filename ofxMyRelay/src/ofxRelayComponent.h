#pragma once
#include "ofxVirtualRelayBase.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:�̵������ģ��(����ͬ��ַ��ĵ�ַ���ӵ�һ��)
/* date:2017.7.16
/* author:hui
/* update:2018.11.12(��������̵�������ӿ�)
/************************************************************************/
class ofxRelayComponent : public ofxVirtualRelayBase
{
public:
	ofxRelayComponent(ofxRelaysBase * _leader);
	~ofxRelayComponent();

	void setOn(int _id) override final;
	void setOff(int _id) override final;

	void setMultOn(vector<int> & _ids) override final;
	void setMultOff(vector<int> & _ids) override final;

	void setSingleOn(vector<int> & _ids) override final;

	void setAllOn() override final;
	void setAllOff() override final;

	void close() override final;

	int size()override;

	void seriesAdd(SERIES_ADD_RELAY & _relay);
	void seriesRemove(SERIES_ADD_RELAY & _relay);
private:
	int getRelaySize(int _index)override final;
	int getRelayNums()override final;
	unsigned char getAddress(int _index);

	vector<SERIES_ADD_RELAY> relays;
	ofxRelaysBase * relayLeader;						//�̵���ʵ��
};

