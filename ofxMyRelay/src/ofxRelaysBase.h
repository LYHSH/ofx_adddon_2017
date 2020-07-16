#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:继电器控制基类   
/* date:2017.6.9
/* author:hui
/************************************************************************/


//串接模块结构
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
	unsigned char address;			//地址
	int size;						//回路数目
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

	virtual void setOn(int _id) {};				//回路编号从0开始
	virtual void setOff(int _id) {};			//回路编号从0开始

	virtual void setMultOn(vector<int> & _ids) {};		//组开，其余保持原状态
	virtual void setMultOff(vector<int> & _ids) {};		//组关，其余保持原状态

	void setSingleOn(int _id);

	virtual void setSingleOn(vector<int> & _ids) {};   //组开，其余断开

	virtual void setAllOn() {};					//全开
	virtual void setAllOff() {};				//全关

	virtual void close() {};

	virtual int size();			//返回本继电器控制回路数
private:
	int loopSize;
	unsigned char address;			//板卡地址
};

