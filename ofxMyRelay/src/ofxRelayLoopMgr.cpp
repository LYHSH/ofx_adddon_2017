#include "ofxRelayLoopMgr.h"



ofxRelayLoopMgr::ofxRelayLoopMgr()
{
}


ofxRelayLoopMgr::~ofxRelayLoopMgr()
{
}

void ofxRelayLoopMgr::setup()
{
	relayMgr.setup("control/relay.xml");

	loadLightSetting();

	{
		ofxXmlSettings xml;
		xml.load("control/setting.xml");
		bReverse = xml.getValue("bReverse", 0);
	}

	for (int i = 0;i < size(); i++)
	{
		onOffs.push_back(false);
	}
}

void ofxRelayLoopMgr::setOn(int _id)
{
	if (!checkOut(_id))return;

	onOffLight(lightIndexs[_id], bReverse?false:true,_id);
}

void ofxRelayLoopMgr::setOff(int _id)
{
	if (!checkOut(_id))return;

	onOffLight(lightIndexs[_id], !bReverse ? false : true,_id);
}

void ofxRelayLoopMgr::setAllOn()
{
	for (int i = 0; i < lightIndexs.size(); i++)
	{
		onOffLight(lightIndexs[i], bReverse ? false : true,i);
		ofMyCmdSendSleep();
	}
}

void ofxRelayLoopMgr::setAllOff()
{
	for (int i = 0; i < lightIndexs.size(); i++)
	{
		onOffLight(lightIndexs[i], !bReverse ? false : true,i);
		ofMyCmdSendSleep();
	}
}

int ofxRelayLoopMgr::size()
{
	return lightIndexs.size();
}

bool ofxRelayLoopMgr::isOn(int _id)
{
	if (!checkOut(_id))return false;
	return onOffs[_id];
}

bool ofxRelayLoopMgr::checkOut(int _index)const
{
	bool res = true;
	res &= _index >= 0;
	res &= _index < lightIndexs.size();
	return res;
}

void ofxRelayLoopMgr::loadLightSetting()
{
	ofxXmlSettings xml;
	xml.load("control/light.xml");

	int nums = xml.getNumTags("light");

	for (int i = 0; i < nums; i++)
	{
		xml.pushTag("light", i);

		vector<lightNode> indexArr;
		int nodeNums = xml.getNumTags("node");
		indexArr.resize(nodeNums);

		for (int nodeIndex = 0; nodeIndex < nodeNums; nodeIndex++)
		{
			xml.pushTag("node", nodeIndex);
			indexArr[nodeIndex].relayIndex = xml.getValue("relay_index", 0);
			indexArr[nodeIndex].loopIndex = xml.getValue("loop_index", 0);
			xml.popTag();
		}

		lightIndexs[i] = indexArr;												//´æ´¢µ½ÄÚ´æ
		xml.popTag();
	}
}

void ofxRelayLoopMgr::onOffLight(const vector<lightNode> & _indexs, bool _state,int _id)
{
	int nums = _indexs.size();

	int index = _id;

	if (_state)
	{
		for (int i = 0; i < nums; i++)
		{
			lightNode  node = _indexs[i];
			relayMgr.begin(node.relayIndex);
			relayMgr.setOn(node.loopIndex);
			relayMgr.end();
			ofMyCmdSendSleep();
		}

		if (-1 != index)
		{
			onOffs[index] = true;
		}
	}
	else
	{
		for (int i = 0; i < nums; i++)
		{
			lightNode  node = _indexs[i];
			relayMgr.begin(node.relayIndex);
			relayMgr.setOff(node.loopIndex);
			relayMgr.end();
			ofMyCmdSendSleep();
		}

		if (-1 != index)
		{
			onOffs[index] = false;
		}
	}

	relayMgr.end();
}
