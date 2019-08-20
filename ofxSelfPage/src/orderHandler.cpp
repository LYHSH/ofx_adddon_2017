#include "orderHandler.h"
#include "pageControler.h"
#include "staticMgr.h"


orderHandler::orderHandler()
{
}


orderHandler::~orderHandler()
{
	
}

orderHandler & orderHandler::getInstance()
{
	static orderHandler mgr;
	return mgr;
}

queue<int> & orderHandler::getOrderQueue()
{
	return orderQueue;
}

void orderHandler::handleOrder(int _order)
{

	bool flag = true;

	for (int i = 0;i < staticMgr::getInstance().size(); i++)
	{
		pageBase * page = staticMgr::getInstance().getPageByIndex(i);
		if (page->pageTouch(_order))
		{
			flag = false;
		}
	}

	//flag ? orderQueue.push(_order) : NULL;
	orderQueue.push(_order);
}