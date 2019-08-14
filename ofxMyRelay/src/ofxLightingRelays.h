#pragma once
#include "ofxRealRelayBase.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:智能照明模块
/* date:2018.1.4
/* author:hui
/* update:2018.1.29
/************************************************************************/

#define ONE_AND_ONE
class ofxLightingRelays : public ofxRealRelayBase
{
public:
	ofxLightingRelays();
	~ofxLightingRelays();

	void setOn(int _id) override;
	void setOff(int _id) override;

	void setAllOn() override;
	void setAllOff() override;

	void setMultOn(vector<int> & _ids);
	void setMultOff(vector<int> & _ids);
private:
	static int const MAX_LOOPS = 12;
};

