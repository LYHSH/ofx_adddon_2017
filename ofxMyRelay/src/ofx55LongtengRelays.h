#pragma once
#include "ofxRealRelayBase.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:55ϵ�м̵���������������ͷβ0X55-���ڸ߿Ƶİ��ӣ�
/* date:2017.10.24
/* author:hui
/* update:2018.1.29
/* uddate:2018.11.12
/************************************************************************/
class ofx55LongtengRelays : public ofxRealRelayBase
{
public:
	ofx55LongtengRelays();
	~ofx55LongtengRelays();

	void setOn(int _id) override;
	void setOff(int _id) override;

	void setMultOn(vector<int> & _ids) override;			//�鿪�����ౣ��ԭ״̬
	void setMultOff(vector<int> & _ids) override;		//��أ����ౣ��ԭ״̬

	void setSingleOn(vector<int> & _ids) override;

	void setAllOn() override;
	void setAllOff() override;
private:
};

