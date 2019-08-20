#include "staticMgr.h"
#include "pageBase.h"

staticMgr::staticMgr(void)
{
	ofAddListener(ofEvents().exit, this, &staticMgr::exit);
}


staticMgr::~staticMgr(void)
{
}

staticMgr & staticMgr::getInstance()
{
	static staticMgr mgr;
	return mgr;
}

void staticMgr::push(string _name, pageBase * _obj)
{
	bool flag = true;
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i] == _name)
		{
			flag = false;
			break;
		}
	}

	if (flag)
	{
		names.push_back(_name);
		objs.push_back(_obj);
	}
}

void staticMgr::pop(string _name)
{
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i] == _name)
		{
			names.erase(names.begin() + i);
			objs.erase(objs.begin() + i);
			break;
		}
	}
}

void staticMgr::push(int _id, pageBase * _obj)
{
	bool flag = true;
	for (int i = 0; i < ids.size(); i++)
	{
		if (ids[i] == _id)
		{
			flag = false;
			break;
		}
	}

	if (flag)
	{
		ids.push_back(_id);
		idObjs.push_back(_obj);
	}
}

void staticMgr::pop(int _id)
{
	for (int i = 0; i < ids.size(); i++)
	{
		if (ids[i] == _id)
		{
			ids.erase(ids.begin() + i);
			idObjs.erase(idObjs.begin() + i);
			break;
		}
	}
}

pageBase * staticMgr::findUIobject(string _name)
{
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i] == _name)
		{
			return objs[i];
		}
	}

	return NULL;
}

pageBase * staticMgr::findUIobject(int _id)
{
	for (int i = 0; i < ids.size(); i++)
	{
		if (ids[i] == _id)
		{
			return idObjs[i];
		}
	}

	return NULL;
}

int staticMgr::size()
{
	return idObjs.size();
}

pageBase * staticMgr::getPageByIndex(int _index)
{
	if (_index >= 0 && _index < idObjs.size())
	{
		return idObjs[_index];
	}
	return NULL;
}

void staticMgr::exit(ofEventArgs & e)
{
	ofRemoveListener(ofEvents().exit, this, &staticMgr::exit);

	for (auto obj : idObjs)
	{
		delete obj;
		obj = NULL;
	}
	for (auto obj : objs)
	{
		delete obj;
		obj = NULL;
	}
	idObjs.clear();
	objs.clear();

	ids.clear();
	names.clear();
}

