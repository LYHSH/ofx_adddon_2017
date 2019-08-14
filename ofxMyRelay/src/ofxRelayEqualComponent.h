#pragma once
#include "ofxVirtualRelayBase.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:继电器组件模块(将不同IP或者串口的继电器模块组合)
/* date:2018.3.6
/* author:hui
/* update:2018.11.12(增加虚拟继电器基类接口)
/************************************************************************/
class ofxRelayEqualComponent : public ofxVirtualRelayBase
{
public:
	ofxRelayEqualComponent();
	~ofxRelayEqualComponent();

	void setOn(int _id) override final;
	void setOff(int _id) override final;

	void setMultOn(vector<int> & _ids) override final;
	void setMultOff(vector<int> & _ids) override final;

	void setSingleOn(vector<int> & _ids)override final;   

	void setAllOn() override final;
	void setAllOff() override final;

	void close() override final;

	int size()override final;

	void relayAdd(ofxRelaysBase * _relay);
	void relayRemove(ofxRelaysBase * _relay);

private:
	unsigned char getAddress(int _index);
	int getRelaySize(int _index) override final;
	int getRelayNums()override final;

	vector<ofxRelaysBase *> relays;
};

