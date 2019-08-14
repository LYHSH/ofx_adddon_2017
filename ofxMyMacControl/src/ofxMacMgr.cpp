#include "ofxMacMgr.h"
#include "ofxXmlSettings.h"

ofxMacMgr::ofxMacMgr()
{
}


ofxMacMgr::~ofxMacMgr()
{
}

void ofxMacMgr::setup(const string & _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);

	if (xml.tagExists("GROUP"))
	{
		int groupNums = xml.getNumTags("GROUP");
		ipMacs.resize(groupNums);
		for (int groupIndex = 0; groupIndex < groupNums; groupIndex++)
		{
			xml.pushTag("GROUP", groupIndex);
			int macNums = xml.getNumTags("COMPUTER");
			auto & macArr = ipMacs[groupIndex];
			for (int macIndex = 0; macIndex < macNums; macIndex++)
			{
				xml.pushTag("COMPUTER", macIndex);
				string ip = xml.getValue("IP", "192.168.8.20");
				string mac = xml.getValue("MAC", "00-00-00-00-00-00");
				macArr[mac] = ip;

				MAC_IP_NODE node;
				node.macStr = mac;
				node.ipStr = ip;

				ipMacVectors.push_back(node);
				xml.popTag();
			}
			xml.popTag();
		}
	}
	else
	{
		int groupNums = xml.getNumTags("IP");
		ipMacs.resize(groupNums);
		for (int groupIndex = 0; groupIndex < groupNums; groupIndex++)
		{
			auto & macArr = ipMacs[groupIndex]; 
			string ip = xml.getValue("IP", "192.168.8.20", groupIndex);
			string mac = xml.getValue("MAC", "00-00-00-00-00-00", groupIndex);
			macArr[mac] = ip;

			MAC_IP_NODE node;
			node.macStr = mac;
			node.ipStr = ip;

			ipMacVectors.push_back(node);
		}
	}
	controler.setup();

	ofLogNotice(OF_FUNCTION_NAME) << "MAC NUMS:" << ipMacs.size() << endl;
}

void ofxMacMgr::setOn(int _index)
{
	if (!checkOut(_index))return;

	auto & macGroup = ipMacs[_index];
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
			controler.powOn(iter->first);
	}
}

void ofxMacMgr::setOff(int _index)
{
	if (!checkOut(_index))return;

	auto & macGroup = ipMacs[_index];
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
		controler.powOff(iter->second);
	}
}

void ofxMacMgr::setOn(int _index,int _cellIndex)
{
	if (!checkOut(_index))return;

	auto & macGroup = ipMacs[_index];

	cout << macGroup.size()<<"   cellindex:"<<_cellIndex << endl;
	int count = 0;
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
		if (count == _cellIndex)
		{
			controler.powOn(iter->first);
			break;
		}
		count++;
	}
}

void ofxMacMgr::setOff(int _index, int _cellIndex)
{
	if (!checkOut(_index))return;

	auto & macGroup = ipMacs[_index];

	cout << macGroup.size() << "   cellindex:" << _cellIndex << endl;
	int count = 0;
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
		if (count == _cellIndex)
		{
			controler.powOff(iter->second);
			break;
		}
		count++;
	}
}

void ofxMacMgr::setSingleOn(int _index)
{
	if (_index <0 || _index >= ipMacVectors.size())return;
	
	controler.powOn(ipMacVectors[_index].macStr);
}

void ofxMacMgr::setSingleOff(int _index)
{
	if (_index < 0 || _index >= ipMacVectors.size())return;
	
	controler.powOff(ipMacVectors[_index].ipStr);
}

void ofxMacMgr::setAllOn()
{
	for (auto & macGroup : ipMacs)
	{
		for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
		{
			controler.powOn(iter->first);
			Sleep(100);
		}
	}
}

void ofxMacMgr::setAllOff()
{
	for (auto & macGroup : ipMacs)
	{
		for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
		{
			controler.powOff(iter->second);
			Sleep(100);
		}
	}
}

string ofxMacMgr::getIP(int _index)const
{
	if (!checkOut(_index)) return "";
	
	auto & macGroup = ipMacs[_index];
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
		return iter->second;
	}

	return "";
}

vector<string> ofxMacMgr::getIPs(int _index)const
{
	vector<string> strVec;
	if (!checkOut(_index)) return strVec;

	auto & macGroup = ipMacs[_index];
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
		strVec.push_back(iter->second);
	}
	return strVec;
}

string ofxMacMgr::getMAC(int _index)const
{
	if (!checkOut(_index)) return "";

	auto & macGroup = ipMacs[_index];
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
		return iter->first;
	}

	return "";
}

vector<string> ofxMacMgr::getMACs(int _index)const
{
	vector<string> strVec;
	if (!checkOut(_index)) return strVec;

	auto & macGroup = ipMacs[_index];
	for (auto iter = macGroup.begin(); iter != macGroup.end(); iter++)
	{
		strVec.push_back(iter->first);
	}
	return strVec;
}

int ofxMacMgr::size()const
{
	return ipMacs.size();
}

int ofxMacMgr::macSize()const
{
	return ipMacVectors.size();
}

bool ofxMacMgr::checkOut(int _index)const
{
	bool res = true;
	res &= _index >= 0;
	res &= _index < size();
	return res;
}