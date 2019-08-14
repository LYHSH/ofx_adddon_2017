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
	//每个模块都指定一个空的容器，避免没有映射到的模块执行不到。（在singleon控制中，空的模块也要执行一次关指令）
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
