#pragma once
#include "ofxRealRelayBase.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:55系列继电器（控制码数据头尾0X55）
/* date:2017.7.16
/* author:hui
/* update:2018.1.29
/* uddate:2018.11.12
/************************************************************************/
class ofx55seriesRelays : public ofxRealRelayBase
{
public:
	ofx55seriesRelays();
	~ofx55seriesRelays();

	void setOn(int _id) override;
	void setOff(int _id) override;

	void setMultOn(vector<int> & _ids) override;			//组开，其余保持原状态
	void setMultOff(vector<int> & _ids) override;		//组关，其余保持原状态

	void setSingleOn(vector<int> & _ids) override;

	void setAllOn() override;
	void setAllOff() override;
};

