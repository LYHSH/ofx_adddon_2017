#include "ofxRelayThreadDecoration.h"



ofxRelayThreadDecoration::ofxRelayThreadDecoration(ofxRelaysBase * _pRelay)
{
	pRelay = _pRelay;
}


ofxRelayThreadDecoration::~ofxRelayThreadDecoration()
{
	close();
	if (pRelay)
	{
		delete pRelay;
		pRelay = NULL;
	}
}

void ofxRelayThreadDecoration::setup()
{
	startThread();
}

void ofxRelayThreadDecoration::setOn(int _id)
{
	threadOrder order;
	order.type = 0;
	order.onoff = true;
	order.id = _id;
	orders.push(order);
}

void ofxRelayThreadDecoration::setOff(int _id)
{
	threadOrder order;
	order.type = 0;
	order.onoff = false;
	order.id = _id;
	orders.push(order);
}

void ofxRelayThreadDecoration::setMultOn(vector<int> & _ids)
{
	threadOrder order;
	order.type = 1;
	order.onoff = true;
	order.ids = _ids;
	orders.push(order);
}

void ofxRelayThreadDecoration::setMultOff(vector<int> & _ids)
{
	threadOrder order;
	order.type = 1;
	order.onoff = false;
	order.ids = _ids;
	orders.push(order);
}

void ofxRelayThreadDecoration::setSingleOn(vector<int> & _ids)
{
	threadOrder order;
	order.type = 3;
	order.onoff = true;
	order.ids = _ids;
	orders.push(order);
}

void ofxRelayThreadDecoration::setAllOn()
{
	threadOrder order;
	order.type = 0;
	order.onoff = true;
	order.id = ID_ALL;
	orders.push(order);
}

void ofxRelayThreadDecoration::setAllOff()
{
	threadOrder order;
	order.type = 0;
	order.onoff = false;
	order.id = ID_ALL;
	orders.push(order);
}

void ofxRelayThreadDecoration::close()
{
	waitForThread();
	pRelay->close();
}

int ofxRelayThreadDecoration::size()
{
	return pRelay->size();
}

void ofxRelayThreadDecoration::threadedFunction()
{
	while (isThreadRunning())
	{
		while (orders.size())
		{
			lock();
			threadOrder order = orders.front();
			orders.pop();
			unlock();
			if (0 == order.type)
			{
				if (order.onoff)
				{
					if (ID_ALL == order.id)
					{
						pRelay->setAllOn();
					}
					else
					{
						pRelay->setOn(order.id);
					}
				}
				else
				{
					if (ID_ALL == order.id)
					{
						pRelay->setAllOff();
					}
					else
					{
						pRelay->setOff(order.id);
					}
				}
			}
			else if (1 == order.type)
			{
				if (order.onoff)
				{
					pRelay->setMultOn(order.ids);
				}
				else
				{
					pRelay->setMultOff(order.ids);
				}
			}
			else if (2 == order.type)
			{
				pRelay->setSingleOn(order.id);
			}
			else if (3 == order.type)
			{
				pRelay->setSingleOn(order.ids);
			}
		}
		sleep(10);
	}
}
