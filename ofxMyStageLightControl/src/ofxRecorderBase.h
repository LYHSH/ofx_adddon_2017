#pragma once
/************************************************************************/
/* project name:录播控制器
/* file describe:基类
/* author:hui
/* date:2018.3.19
/************************************************************************/
class ofxRecorderBase
{
public:
	ofxRecorderBase();
	virtual ~ofxRecorderBase();

	virtual void play(int _id) = 0;

	virtual void play();
	virtual void pause();
	virtual void stop();

	void setAddress(unsigned char _addressCode);
	unsigned char getAddress()const;

private:
	unsigned char address;			//板卡地址
};

