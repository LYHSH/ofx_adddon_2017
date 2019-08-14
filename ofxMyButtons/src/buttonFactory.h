#pragma once
/************************************************************************/
/* file describe:按钮工厂抽象类
/* author:hui
/* date:2016/12/8
/************************************************************************/
#include "ofMain.h"
#include "button.h"
class buttonFactory
{
public:
	buttonFactory(void);
	~buttonFactory(void);

	static button * createButton(const int & _id = -1,const string & _name = "");
	static button * createRectButton(const ofRectangle & _rect,const int & _id = -1,const string & _name = "");
	static button * createTexRectButton(const ofRectangle & _rect,const ofImage & _tex,
		const int & _id = -1,const string & _name = "");

	static button * createTexTextRectButton(const ofRectangle & _rect, const ofImage & _tex,const string & _text,
		const int & _id = -1, const string & _name = "");

	static button * createDoubleStateButton(const ofRectangle & _rect, const ofImage & _showTex, const ofImage & _touchTex,
		const int & _id = -1, const string & _name = "");
};

