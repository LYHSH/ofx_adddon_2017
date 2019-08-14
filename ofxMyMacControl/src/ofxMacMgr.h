#pragma once
#include "ofxMacPowControl.h"
#include "ofMain.h"
#include "ofxMyConstants.h"
/************************************************************************/
/* File describe:�������ع�����
/* Author:hui
/* Date:2017.6.24
/* update:2018.11.12
/************************************************************************/
class ofxMacMgr
{
public:
	ofxMacMgr();
	~ofxMacMgr();

	void setup(const string & _filename);

	//������������
	void setOn(int _index);
	void setOff(int _index);

	//���еĵ�̨��������
	void setOn(int _index,int _cellIndex);
	void setOff(int _index, int _cellIndex);

	//��̨��������
	void setSingleOn(int _index);
	void setSingleOff(int _index);

	//ȫ����������
	void setAllOn();
	void setAllOff();

	string getIP(int _index)const;
	vector<string> getIPs(int _index)const;
	string getMAC(int _index)const;
	vector<string> getMACs(int _index)const;

	int size()const;				//�����ܹ��ж���������
	int macSize()const;				//�����ܹ��ж�������
private:
	bool checkOut(int _index)const;			//Check out of range

	ofxMacPowControl controler;

	vector<map<string, string>> ipMacs;

	struct MAC_IP_NODE
	{
		string macStr;
		string ipStr;
	};
	vector<MAC_IP_NODE> ipMacVectors;
};

