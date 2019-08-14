#include "ofxPjMgr.h"
#include "ofxXmlSettings.h"


ofxPjMgr::ofxPjMgr()
{
	
}


ofxPjMgr::~ofxPjMgr()
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

void ofxPjMgr::setup(const string & _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);

	int nums = xml.getNumTags("group");
	controler.resize(nums);
	for (int i = 0; i < controler.size(); i++)
	{
		xml.pushTag("group", i);

		int pjNums = xml.getNumTags("project");
		for (int pjIndex = 0; pjIndex < pjNums; pjIndex++)
		{
			xml.pushTag("project", pjIndex);

			int type = xml.getValue("type",0);
			string nameStr = "";
			if (xml.tagExists("IP"))
			{
				nameStr = xml.getValue("IP", "");

			}
			else if (xml.tagExists("COM"))
			{
				nameStr = "COM" + ofToString(xml.getValue("COM", 0));
			}

			ofxPJcontrolBase * pjObject = ofxPJcontrolFactory::createPJbyType(
				(PROJECT_TYPE)type, nameStr);
			controler[i].push_back(pjObject);

			xml.popTag();
		}
		
		xml.popTag();
	}

	ofLogNotice(OF_FUNCTION_NAME) << "PJ NUMS:" << controler.size() << endl;
}

void ofxPjMgr::setOn(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setOn();
		Sleep(1000);
	}
}

void ofxPjMgr::setOff(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setOff();
		Sleep(1000);
	}
}

void ofxPjMgr::setAllOn()
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

void ofxPjMgr::setAllOff()
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

void ofxPjMgr::setDVI(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setDVI();
		Sleep(1000);
	}
}

void ofxPjMgr::setRGB2(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setRGB2();
		Sleep(1000);
	}
}

void ofxPjMgr::setHMDI1(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setHDMI1();
		Sleep(1000);
	}
}

void ofxPjMgr::setHMDI2(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setHDMI2();
		Sleep(1000);
	}
}

string ofxPjMgr::getIP(int _index)const
{
	if (!checkOut(_index))return "";
	return controler[_index][0]->getName();
}

vector<string> ofxPjMgr::getIPs(int _index)const
{
	vector<string> strVec;
	if (!checkOut(_index)) return strVec;

	auto & macGroup = controler[_index];
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
		strVec.push_back((*iter)->getName());
	}
	return strVec;
}

int ofxPjMgr::size()const
{
	return controler.size();
}

bool ofxPjMgr::checkOut(int _index)const
{
	bool res = true;
	res &= (_index >= 0);
	res &= (_index < size());
	return res;
}
