#pragma once
#include "ofxRealRelayBase.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:2000ϵ�м̵������˿�2000��
/* date:2017.8.11
/* author:hui
/* update:2018.1.29
/************************************************************************/
class ofx2000seriesRelays : public ofxRealRelayBase
{
public:
	ofx2000seriesRelays();
	~ofx2000seriesRelays();

	void setOn(int _id) override;
	void setOff(int _id) override;

	void setAllOn() override;
	void setAllOff() override;
private:
};

