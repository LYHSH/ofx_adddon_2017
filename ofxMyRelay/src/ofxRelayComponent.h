#pragma once
#include "ofxVirtualRelayBase.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:继电器组件模块(将不同地址码的地址串接到一起)
/* date:2017.7.16
/* author:hui
/* update:2018.11.12(增加虚拟继电器基类接口)
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
	ofxRelaysBase * relayLeader;						//继电器实体
};

