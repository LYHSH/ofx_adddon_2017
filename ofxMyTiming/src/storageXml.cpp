#include "storageXml.h"

storageXml::storageXml(void)
{
}


storageXml::~storageXml(void)
{
}

void storageXml::setup(string _xmlFile)
{
	lastFrame = -200;
	readSetting(lights, _xmlFile);
}


bool storageXml::getLight(int _frame,mylight & _object)
{
	for (int i = 0; i< lights.size();i++)
	{ 		
		mylight & curLight = lights[i];
		if ( _frame > curLight.frame && !curLight.isDone)
		{
			curLight.isDone = true;
			_object = curLight;
			lastFrame = curLight.frame;
			return true;
		}
	}

	return false;
}

void storageXml::reset()
{
	lastFrame = -200;
	for (int i = 0; i < lights.size(); i++)
	{
		lights[i].isDone = false;
	}
}

int storageXml::size()const
{
	return lights.size();
}

bool storageXml::getLightByIndex(int _index, mylight & _object)
{
	bool flag = false;
	for (int i = 0; i < lights.size(); i++)
	{
		if (i == _index)
		{
			flag = true;
			_object = lights[i];
		}
		
	}

	return flag;
}

const vector<int> & storageXml::getAllId()
{
	return allIds;
}

void storageXml::readSetting(vector<mylight> & _object, string _xmlFile)
{
	ofxXmlSettings xml;
	xml.loadFile(_xmlFile);
	int nums = xml.getNumTags("light");
	for (int i = 0; i < nums; i++)
	{
		mylight temp;
		xml.pushTag("light", i);
		temp.frame = xml.getValue("frame", 0);
		temp.onOff = xml.getValue("on", 0);

		string idstr = xml.getValue("id", "");
		vector<string> strs = ofSplitString(idstr, ",");
		for (int j = 0; j < strs.size(); j++)
		{
			int id = ofToInt(strs[j]);
			temp.lightId.push_back(id);
			allLightIds[id] = true;
		}

		temp.isDone = false;
		_object.push_back(temp);
		xml.popTag();
	}


	for (auto ite = allLightIds.begin();ite != allLightIds.end();ite++)
	{
		allIds.push_back(ite->first);
	}

	ofLogNotice() << "all light nums:" << allIds.size();
}