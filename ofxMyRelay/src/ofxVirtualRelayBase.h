#pragma once
#include "ofxRelaysBase.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:����̵�������
/* date:2018.11.12
/* author:hui
/************************************************************************/
class ofxVirtualRelayBase : public ofxRelaysBase
{
public:
	ofxVirtualRelayBase();
	~ofxVirtualRelayBase();

protected:
	virtual int getRelaySize(int _index) = 0;				//����ָ���ż̵����Ļ�·��Ŀ
	virtual int getRelayNums() = 0;							//���ؼ̵���ģ����Ŀ
	bool convert(int & _relayIndex, int & _loopIndex, int _inputIndex);		//���ⲿ�����·���ת����ʵ�ʼ̵������
	void multConvert(map<int, vector<int>> & _multIds, const vector<int> & inputIds);	//���ⲿ������ת���ɶ�Ӧʵ�ʼ̵�����
};

