#pragma once
#include "ofxSplicingScreenControl.h"
class ofxSplicingScreenControlMgr
{
public:
	ofxSplicingScreenControlMgr();
	~ofxSplicingScreenControlMgr();

	void setup(const string & _filename);

	void setOn(int _index);
	void setOff(int _index);

	void setAllOn();
	void setAllOff();

	string getIP(int _index)const;

	int size()const;
private:
	bool checkOut(int _index)const;			//Check out of range

	vector<vector<ofxSplicingScreenControl *>> controler;
};

