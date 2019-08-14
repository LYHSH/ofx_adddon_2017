#include "ofxVirtualRelayBase.h"



ofxVirtualRelayBase::ofxVirtualRelayBase()
{
}


ofxVirtualRelayBase::~ofxVirtualRelayBase()
{
}

bool ofxVirtualRelayBase::convert(int & _relayIndex, int & _loopIndex, int _inputIndex)
{
	if (_inputIndex < 0 || _inputIndex >= size())
	{
		return false;
	}

	int sum = 0;
	for (int i = 0; i < getRelayNums(); i++)
	{
		sum += getRelaySize(i);
		if (_inputIndex < sum)
		{
			_relayIndex = i;
			_loopIndex = _inputIndex + getRelaySize(i) - sum;
			return true;
		}
	}
	return false;
}

void ofxVirtualRelayBase::multConvert(map<int, vector<int>> & _multIds, const vector<int> & inputIds)
{
	vector<int> nullVector;
	//ÿ��ģ�鶼ָ��һ���յ�����������û��ӳ�䵽��ģ��ִ�в���������singleon�����У��յ�ģ��ҲҪִ��һ�ι�ָ�
	for (int i = 0; i < getRelayNums(); i++)
	{
		_multIds[i] = nullVector;
	}

	for each (auto inputInex in inputIds)
	{
		int relayIndex = 0;
		int loopIndex = 0;
		convert(relayIndex, loopIndex, inputInex);
		_multIds[relayIndex].push_back(loopIndex);
	}
}
