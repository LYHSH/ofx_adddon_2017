#include "ofxSplicingScreenControlMgr.h"
#include "ofxXmlSettings.h"


ofxSplicingScreenControlMgr::ofxSplicingScreenControlMgr()
{
}


ofxSplicingScreenControlMgr::~ofxSplicingScreenControlMgr()
{
	for (int i = 0; i < controler.size(); i++)
	{
		auto & arrObj = controler[i];
		for each (auto var in arrObj)
		{
			delete var;
			var = NULL;
		}
	}
	controler.clear();
}

void ofxSplicingScreenControlMgr::setup(const string & _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);

	int nums = xml.getNumTags("screen");
	controler.resize(nums);
	for (int i = 0; i < controler.size(); i++)
	{
		xml.pushTag("screen", i);
		int ipNums = xml.getNumTags("IP");
		controler[i].resize(ipNums);
		for (int ipIndex = 0; ipIndex < ipNums; ipIndex++)
		{
			controler[i][ipIndex] = new ofxSplicingScreenControl();
			controler[i][ipIndex]->setup(xml.getValue("IP", "", ipIndex));
		}

		xml.popTag();
	}

	ofLogNotice(OF_FUNCTION_NAME) << "REMOTE SPLICING SCREEN NUMS:" << controler.size() << endl;
}

void ofxSplicingScreenControlMgr::setOn(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setOn();
	}
}

void ofxSplicingScreenControlMgr::setOff(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setOff();
	}
}

void ofxSplicingScreenControlMgr::setAllOn()
{
	for (int i = 0; i < controler.size(); i++)
	{
		auto & arrObj = controler[i];
		for each (auto var in arrObj)
		{
			var->setOn();
			Sleep(1000);
		}
	}
}

void ofxSplicingScreenControlMgr::setAllOff()
{
	for (int i = 0; i < controler.size(); i++)
	{
		auto & arrObj = controler[i];
		for each (auto var in arrObj)
		{
			var->setOff();
			Sleep(1000);
		}
	}
}

string ofxSplicingScreenControlMgr::getIP(int _index)const
{
	if (!checkOut(_index))return "";

	auto & arrObj = controler[_index];
	return arrObj[0]->getIP();
}

int ofxSplicingScreenControlMgr::size()const
{
	return controler.size();
}

bool ofxSplicingScreenControlMgr::checkOut(int _index)const
{
	bool res = true;
	res &= _index >= 0;
	res &= _index < size();
	return res;
}