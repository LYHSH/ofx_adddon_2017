#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name:�п����
/* file describe:��ťָ�����
/* author:hui
/* date:2017.5.9
/************************************************************************/
class orderHandler
{
public:
	~orderHandler();

	static orderHandler & getInstance();

	queue<int>  & getOrderQueue();
	void handleOrder(int _order);
private:
	orderHandler();

	queue<int> orderQueue;

};

