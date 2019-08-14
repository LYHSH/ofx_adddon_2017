#include "ofxRelayEqualComponent.h"



ofxRelayEqualComponent::ofxRelayEqualComponent()
{
}


ofxRelayEqualComponent::~ofxRelayEqualComponent()
{
}

void ofxRelayEqualComponent::setOn(int _id)
{
	int relayIndex = 0;
	int loopIndex = 0;
	if (convert(relayIndex, loopIndex, _id))
	{
		relays[relayIndex]->setOn(loopIndex);
	}
}

void ofxRelayEqualComponent::setOff(int _id)
{
	int relayIndex = 0;
	int loopIndex = 0;
	if (convert(relayIndex, loopIndex, _id))
	{
		relays[relayIndex]->setOff(loopIndex);
	}
}

void ofxRelayEqualComponent::setMultOn(vector<int> & _ids)
{
	map<int, vector<int>> multIds;
	multConvert(multIds, _ids);

	map<int, vector<int>>::iterator ite;
	for (ite = multIds.begin(); ite != multIds.end(); ++ite)
	{
		relays[ite->first]->setMultOn(ite->second);
	}
}

void ofxRelayEqualComponent::setMultOff(vector<int> & _ids)
{
	map<int, vector<int>> multIds;
	multConvert(multIds, _ids);

	map<int, vector<int>>::iterator ite;
	for (ite = multIds.begin(); ite != multIds.end(); ++ite)
	{
		relays[ite->first]->setMultOff(ite->second);
	}
}

void ofxRelayEqualComponent::setSingleOn(vector<int> & _ids)
{
	map<int, vector<int>> multIds;
	multConvert(multIds, _ids);

	map<int, vector<int>>::iterator ite;
	for (ite = multIds.begin(); ite != multIds.end(); ++ite)
	{
		relays[ite->first]->setSingleOn(ite->second);
	}
}

void ofxRelayEqualComponent::setAllOn()
{
	for each (auto var in relays)
	{
		var->setAllOn();
	}
}

void ofxRelayEqualComponent::setAllOff()
{
	for each (auto var in relays)
	{
		var->setAllOff();
	}
}

void ofxRelayEqualComponent::close()
{
	for (auto ite = relays.begin(); ite != relays.end(); ++ite)
	{
		(*ite)->close();
	}
}

int ofxRelayEqualComponent::size()
{
	int totalSize = 0;
	for (int i = 0; i < relays.size(); i++)
	{
		totalSize += getRelaySize(i);
	}
	return totalSize;
}

void ofxRelayEqualComponent::relayAdd(ofxRelaysBase * _relay)
{
	if (NULL == _relay)return;
	
	relays.push_back(_relay);
}

void ofxRelayEqualComponent::relayRemove(ofxRelaysBase * _relay)
{
	for (int i = 0; i < relays.size(); i++)
	{
		if (relays[i] == _relay)
		{
			relays.erase(relays.begin() + i);
			return;
		}
	}
}


unsigned char ofxRelayEqualComponent::getAddress(int _index)
{
	if (_index < 0 || _index > relays.size())
	{
		return 0x00;
	}
	return relays[_index]->getAddress();
}



int ofxRelayEqualComponent::getRelaySize(int _index)
{
	if (_index < 0 || _index > relays.size())
	{
		return 0;
	}
	return relays[_index]->size();
}

int ofxRelayEqualComponent::getRelayNums()
{
	return relays.size();
}

