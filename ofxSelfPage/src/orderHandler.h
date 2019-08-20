#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name:中控软件
/* file describe:按钮指令处理类
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

