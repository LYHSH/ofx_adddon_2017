#pragma once
#include "ofxRelaysMgr.h"
#include "storageXml.h"
class ofxRelayTiming
{
public:
	ofxRelayTiming();
	~ofxRelayTiming();

	void setup(string _fileName);
	void update(int _videoIndex, int _frame);
	void draw();

	void reset();
	void setAllOn();
	void setAllOff();
private:

	ofxRelaysMgr mgr;
	ofxRelaysBase * relayer;

	vector<storageXml> timingDatas;

	vector<int> ids;
};

