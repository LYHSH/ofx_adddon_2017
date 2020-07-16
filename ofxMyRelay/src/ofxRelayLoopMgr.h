#pragma once
#include "ofxRelaysMgr.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:继电器回路组控制器
/* date:2018.11.20
/* author:hui
/************************************************************************/
class ofxRelayLoopMgr
{
public:
	ofxRelayLoopMgr();
	~ofxRelayLoopMgr();

	struct lightNode
	{
		int relayIndex;
		int loopIndex;
	};

	void setup(string _file);
	void setup();
	void setOn(int _id);
	void setOff(int _id);

	void setAllOn();
	void setAllOff();

	void setRealAllOn();
	void setRealAllOff();

	int size();
	bool isOn(int _id);
private:
	bool checkOut(size_t _index)const;			//Check out of range

	ofxRelaysMgr relayMgr;
	string relayConfigStr;

	map<int, vector<lightNode>> lightIndexs;
	void loadLightSetting();
	void onOffLight(const vector<lightNode> & _indexs, bool _state,int _id);
	bool bReverse;			//指令反转

	vector<bool> onOffs;

	void sleep();
};

