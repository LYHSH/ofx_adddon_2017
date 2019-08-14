#include "ofxRelaysMgr.h"



ofxRelaysMgr::ofxRelaysMgr()
{
	tempRelay = NULL;
}


ofxRelaysMgr::~ofxRelaysMgr()
{
	/*for (auto ite = relays.begin(); ite != relays.end(); ++ite)
	{
		(*ite)->close();
		delete (*ite);
		*ite = NULL;
	}

	relays.clear();*/
}

void ofxRelaysMgr::setup(const string & _filename) 
{
	senderMgr.setup(_filename);

	if (senderMgr.size())			//使用新接口
	{
		setupWithDataSender(_filename);
	}
	else
	{
		setupWithHistory(_filename);		//保持原有接口正常使用
	}
}

void ofxRelaysMgr::setupWithDataSender(const string & _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);

	int nums = xml.getNumTags("RELAY");
	relays.resize(nums);

	if (nums != senderMgr.size())
	{
		ofLogError(OF_FUNCTION_NAME) << "dataSender nums ="<<senderMgr.size() <<"  relay nums = "<<nums << endl;
		ofLogError(OF_FUNCTION_NAME) << "dataSender nums not equal to relays nums" << endl;
	}

	for (int i = 0; i < nums; ++i)
	{
		xml.pushTag("RELAY", i);
		int type = xml.getValue("type", 0);

		int componentNums = xml.getNumTags("COMPONENT");
		vector<SERIES_ADD_RELAY> components;
		for (int componentIndex = 0; componentIndex < componentNums; ++componentIndex)
		{
			xml.pushTag("COMPONENT", componentIndex);
			string address = xml.getValue("ADDRESS", "0X01");
			int size = xml.getValue("SIZE", 0);

			components.push_back(SERIES_ADD_RELAY(ofHexToInt(address), size));

			xml.popTag();
		}

		RELAY_TYPE relayType = RELAY_TYPE(type);

		relays[i] = ofxRelayFactory::createRelay(relayType, senderMgr.getSender(i), components);

		xml.popTag();
	}
}

void ofxRelaysMgr::setupWithHistory(const string & _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);

	int nums = xml.getNumTags("RELAY");
	relays.resize(nums);

	for (int i = 0; i < nums; ++i)
	{
		xml.pushTag("RELAY", i);
		int type = xml.getValue("type", 0);

		int componentNums = xml.getNumTags("COMPONENT");
		vector<SERIES_ADD_RELAY> components;
		for (int componentIndex = 0; componentIndex < componentNums; ++componentIndex)
		{
			xml.pushTag("COMPONENT", componentIndex);
			string address = xml.getValue("ADDRESS", "0X01");
			int size = xml.getValue("SIZE", 0);

			components.push_back(SERIES_ADD_RELAY(ofHexToInt(address), size));

			xml.popTag();
		}

		RELAY_TYPE relayType = RELAY_TYPE(type);

		if (xml.tagExists("IP"))
		{
			string ip = xml.getValue("IP", "");

			relays[i] = ofxRelayFactory::createRelay(relayType, ip, components);
		}
		else if (xml.tagExists("COM"))
		{
			int nCom = xml.getValue("COM", 4);

			relays[i] = ofxRelayFactory::createRelay(relayType, nCom, components);
		}

		xml.popTag();
	}
}

ofxRelaysBase * ofxRelaysMgr::getRelayer(int _index)
{
	if (!checkOut(_index))return NULL;

	return relays[_index];
}

void ofxRelaysMgr::begin(int _relayIndex) 
{
	if (!checkOut(_relayIndex))return;

	tempRelay = relays[_relayIndex];
}

void ofxRelaysMgr::setOn(int _id) 
{
	if (tempRelay)
	{
		tempRelay->setOn(_id);
	}
}

void ofxRelaysMgr::setOff(int _id) 
{
	if (tempRelay)
	{
		tempRelay->setOff(_id);
	}
}

void ofxRelaysMgr::setMultOn(vector<int> & _ids)
{
	if (tempRelay)
	{
		tempRelay->setMultOn(_ids);
	}
}

void ofxRelaysMgr::setMultOff(vector<int> & _ids)
{
	if (tempRelay)
	{
		tempRelay->setMultOff(_ids);
	}
}

void ofxRelaysMgr::setSingleOn(int _id)
{
	if (tempRelay)
	{
		tempRelay->setSingleOn(_id);
	}
}

void ofxRelaysMgr::setSingleOn(vector<int> & _ids)
{
	if (tempRelay)
	{
		tempRelay->setSingleOn(_ids);
	}
}

void ofxRelaysMgr::setAllOn() 
{
	if (tempRelay)
	{
		tempRelay->setAllOn();
	}
}

void ofxRelaysMgr::setAllOff() 
{
	if (tempRelay)
	{
		tempRelay->setAllOff();
	}
}

void ofxRelaysMgr::stepAllOn()
{
	for (int i = 0; i < loopSize(); i++)
	{
		setOn(i);
		Sleep(100);
	}
}

void ofxRelaysMgr::stepAllOff()
{
	for (int i = 0; i < loopSize(); i++)
	{
		setOff(i);
		Sleep(100);
	}
}

int ofxRelaysMgr::loopSize()
{
	if (tempRelay)
	{
		return tempRelay->size();
	}
	return 0;
}

void ofxRelaysMgr::end() 
{
	tempRelay = NULL;
}

int ofxRelaysMgr::size()const
{
	return relays.size();
}

bool ofxRelaysMgr::checkOut(int _index)const
{
	bool res = true;
	res &= _index >= 0;
	res &= _index < size();
	return res;
}