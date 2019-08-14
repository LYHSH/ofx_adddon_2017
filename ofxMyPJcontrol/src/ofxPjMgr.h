#pragma once
/************************************************************************/
/* Project name:�п����
/* File describe:ͶӰ�����ƹ�����
/* Author:hui
/* Date:2017.11.2
/************************************************************************/
#include "ofxPJcontrolFactory.h"
#include "ofMain.h"
#include "ofxMyConstants.h"
class ofxPjMgr
{
public:
	ofxPjMgr();
	~ofxPjMgr();

	void setup(const string & _filename);

	//���ؿ���
	void setOn(int _index);
	void setOff(int _index);

	//ȫ��ȫ��
	void setAllOn();
	void setAllOff();

	//�ź��л�
	void setDVI(int _index);
	void setRGB2(int _index);
	void setHMDI1(int _index);
	void setHMDI2(int _index);

	string getIP(int _index)const;
	vector<string> getIPs(int _index)const;

	int size()const;
private:
	bool checkOut(int _index)const;			//Check out of range

	vector<vector<ofxPJcontrolBase *>> controler;
};

