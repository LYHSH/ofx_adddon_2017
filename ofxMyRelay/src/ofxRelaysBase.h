#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name:�̵������ƽӿڿ�
/* file describe:�̵������ƻ���   
/* date:2017.6.9
/* author:hui
/************************************************************************/


//����ģ��ṹ
struct SERIES_ADD_RELAY
{
	SERIES_ADD_RELAY()
	{
		address = 0x00;
		size = 0;
	}
	SERIES_ADD_RELAY(unsigned char _address,int _size)
	{
		address = _address;
		size = _size;
	}
	unsigned char address;			//��ַ
	int size;						//��·��Ŀ
};


class ofxRelaysBase
{
public:
	ofxRelaysBase();
	virtual ~ofxRelaysBase();
	static int const ID_ALL = 1000;

	void setAddress(unsigned char _addressCode);
	unsigned char getAddress()const;
	void setSize(int _loopsize);

	virtual void setOn(int _id) {};				//��·��Ŵ�0��ʼ
	virtual void setOff(int _id) {};			//��·��Ŵ�0��ʼ

	virtual void setMultOn(vector<int> & _ids) {};		//�鿪�����ౣ��ԭ״̬
	virtual void setMultOff(vector<int> & _ids) {};		//��أ����ౣ��ԭ״̬

	void setSingleOn(int _id);

	virtual void setSingleOn(vector<int> & _ids) {};   //�鿪������Ͽ�

	virtual void setAllOn() {};					//ȫ��
	virtual void setAllOff() {};				//ȫ��

	virtual void close() {};

	virtual int size();			//���ر��̵������ƻ�·��
private:
	int loopSize;
	unsigned char address;			//�忨��ַ
};

