#pragma once
/************************************************************************/
/* file describe:ʱ��ڵ��
/* date:2018.11.12
/* author:hui
/************************************************************************/
#include"ofMain.h"
#include"ofxXmlSettings.h"

#define PORT_NUM 48


struct mylight
{
	int frame;
	vector<int> lightId;
	bool onOff;
	bool isDone;
};
class storageXml
{
public:
	storageXml(void);
	~storageXml(void);

	void setup(string _xmlFile);					

	bool getLight(int _frame,mylight & _object);

	void reset();
private:
	
	void readSetting(vector<mylight> & _object,string _xmlFile);
	
 	vector<mylight> lights;
	int lastFrame;

};
