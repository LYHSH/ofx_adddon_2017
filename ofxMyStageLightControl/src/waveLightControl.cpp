#include "waveLightControl.h"


waveLightControl::waveLightControl(void)
{
}


waveLightControl::~waveLightControl(void)
{
}

void waveLightControl::setup(int comNum)
{
	string comStr = "COM" + ofToString(comNum);
	if (!serial.setup(comStr, 9600))
	{
	}
	

	startThread();
	ofAddListener(ofEvents().exit,this,&waveLightControl::exit);
}

void waveLightControl::setOrder(int _id)
{
	ofLogNotice("waveLightControl::setOrder(int _id)") << _id<< endl;
	static int const codeNums = 12;
	static const unsigned char initCodes[codeNums] = { 0x68, 0x06, 0x00, 0xFF, 0xFF, 0x05, 0x04, 0x30, 0x31, 0x6E, 0xC3, 0x16 };
	unsigned char codes[codeNums] = {0x00};
	memcpy(codes, initCodes, codeNums);
	if (_id >= 1 && _id < 10)
	{
		codes[7] = 0x30;
		codes[8] = 0x31;
		codes[9] = 0x6E;
	}
	else if (_id >= 11 && _id < 20)
	{
		_id -= 10;
		codes[7] = 0x31;
		codes[8] = 0x31;
		codes[9] = 0x6F;
	}
	else if (_id >= 21 && _id < 30)
	{
		_id -= 20;
		codes[7] = 0x32;
		codes[8] = 0x31;
		codes[9] = 0x70;
	}
	else if (_id >= 31 && _id < 40)
	{
		_id -= 30;
		codes[7] = 0x33;
		codes[8] = 0x31;
		codes[9] = 0x71;
	}
	else if (_id >= 41 && _id < 50)
	{
		_id -= 40;
		codes[7] = 0x34;
		codes[8] = 0x31;
		codes[9] = 0x72;
	}
	else if (_id >= 51 && _id < 60)
	{
		_id -= 50;
		codes[7] = 0x35;
		codes[8] = 0x31;
		codes[9] = 0x73;
	}
	codes[8] += (_id - 1);
	codes[9] += (_id - 1);

	for (int i = 0; i < 12; i++)
	{
		printf("0x%x    ", codes[i]);
	}
	printf("\n");
	serial.writeBytes(codes,codeNums);
	sleep(0);
}

void waveLightControl::addOrder(int _loopIndex)
{
	lock();
	orders.push(_loopIndex);
	unlock();
}

void waveLightControl::exit(ofEventArgs &e)
{
	waitForThread();

	ofRemoveListener(ofEvents().exit,this,&waveLightControl::exit);
}

void waveLightControl::threadedFunction()
{
	while (isThreadRunning())
	{
		while (orders.size() > 0)
		{
			int id = orders.front();
			orders.pop();
			setOrder(id);
			sleep(100);
		}

		sleep(20);
	}
}
