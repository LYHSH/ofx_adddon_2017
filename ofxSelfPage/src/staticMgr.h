#pragma once
/************************************************************************/
/* Project name:
/* Class description：UI界面类静态管理器
/* Author: Hui
/* Date:2016/8/31
/************************************************************************/
#include "ofMain.h"
class pageBase;
class staticMgr
{
public:
	static staticMgr & getInstance();

	void push(string _name, pageBase * _obj);
	void pop(string _name);

	void push(int _id, pageBase * _obj);
	void pop(int _id);
	
	pageBase * findUIobject(string _name);
	pageBase * findUIobject(int _id);

	int size();
	pageBase * getPageByIndex(int _index);
private:
	void exit(ofEventArgs & e);
	vector<string> names;
	vector<pageBase *> objs;

	vector<int> ids;
	vector<pageBase *> idObjs;

	staticMgr(void);
	~staticMgr(void);
};

