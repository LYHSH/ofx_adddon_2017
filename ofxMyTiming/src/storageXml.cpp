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
			temp.lightId.push_back(ofToInt(strs[j]));
		}

		temp.isDone = false;
		_object.push_back(temp);
		xml.popTag();
	}
}