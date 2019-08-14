#pragma once
#include "ofxRelaysBase.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:虚拟继电器基类
/* date:2018.11.12
/* author:hui
/************************************************************************/
class ofxVirtualRelayBase : public ofxRelaysBase
{
public:
	ofxVirtualRelayBase();
	~ofxVirtualRelayBase();

protected:
	virtual int getRelaySize(int _index) = 0;				//返回指令编号继电器的回路数目
	virtual int getRelayNums() = 0;							//返回继电器模块数目
	bool convert(int & _relayIndex, int & _loopIndex, int _inputIndex);		//将外部虚拟回路编号转换成实际继电器编号
	void multConvert(map<int, vector<int>> & _multIds, const vector<int> & inputIds);	//将外部虚拟组转换成对应实际继电器组
};

