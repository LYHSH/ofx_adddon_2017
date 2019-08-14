#include "ofxRelayComponent.h"



ofxRelayComponent::ofxRelayComponent(ofxRelaysBase * _leader)
{
	relayLeader = _leader;
}


ofxRelayComponent::~ofxRelayComponent()
{
	close();
	if (relayLeader)
	{
		delete relayLeader;
		relayLeader = NULL;
	}
}

void ofxRelayComponent::setOn(int _id)
{
	int relayIndex = 0;
	int loopIndex = 0;
	convert(relayIndex, loopIndex, _id);

	relayLeader->setAddress(getAddress(relayIndex));
	relayLeader->setOn(loopIndex);
}

void ofxRelayComponent::setOff(int _id)
{
	int relayIndex = 0;
	int loopIndex = 0;
	convert(relayIndex, loopIndex, _id);
	
	relayLeader->setAddress(getAddress(relayIndex));
	relayLeader->setOff(loopIndex);
}

void ofxRelayComponent::setMultOn(vector<int> & _ids)
{
	map<int, vector<int>> multIds;
	multConvert(multIds, _ids);

	map<int, vector<int>>::iterator ite;
	for (ite = multIds.begin(); ite != multIds.end(); ++ite)
	{
		relayLeader->setAddress(getAddress(ite->first));
		relayLeader->setMultOn(ite->second);
	}
}

void ofxRelayComponent::setMultOff(vector<int> & _ids)
{
	map<int, vector<int>> multIds;
	multConvert(multIds,_ids);

	map<int, vector<int>>::iterator ite;
	for (ite = multIds.begin(); ite != multIds.end(); ++ite)
	{
		relayLeader->setAddress(getAddress(ite->first));
		relayLeader->setMultOff(ite->second);
	}
}


void ofxRelayComponent::setSingleOn(vector<int> & _ids)
{
	map<int, vector<int>> multIds;
	multConvert(multIds, _ids);

	map<int, vector<int>>::iterator ite;
	for (ite = multIds.begin(); ite != multIds.end(); ++ite)
	{
		relayLeader->setAddress(getAddress(ite->first));
		relayLeader->setSingleOn(ite->second);
	}
}

void ofxRelayComponent::setAllOn()
{
	for each (auto var in relays)
	{
		relayLeader->setAddress(var.address);
		relayLeader->setAllOn();
	}
}

void ofxRelayComponent::setAllOff()
{
	for each (auto var in relays)
	{
		relayLeader->setAddress(var.address);
		relayLeader->setAllOff();
	}
}

void ofxRelayComponent::close()
{
	relayLeader->close();

	relays.clear();
}

int ofxRelayComponent::size()
{
	int totalSize = 0;
	for (int i = 0; i < relays.size(); i++)
	{
		totalSize += getRelaySize(i);
	}
	return totalSize;
}

void ofxRelayComponent::seriesAdd(SERIES_ADD_RELAY & _relay)
{
	relays.push_back(_relay);
}

void ofxRelayComponent::seriesRemove(SERIES_ADD_RELAY & _relay)
{
	for (int i = 0; i < relays.size() ;i++)
	{
		if (relays[i].address == _relay.address)
		{
			relays.erase(relays.begin() + i);
		}
	}
}

unsigned char ofxRelayComponent::getAddress(int _index)
{
	if (_index < 0 || _index > relays.size())
	{
		return 0x00;
	}
	return relays[_index].address;
}

int ofxRelayComponent::getRelaySize(int _index)
{
	if (_index < 0 || _index > relays.size())
	{
		return 0;
	}
	return relays[_index].size;
}

int ofxRelayComponent::getRelayNums()
{
	return relays.size();
}
