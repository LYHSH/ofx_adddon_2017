#pragma once
/************************************************************************/
/* file describe:矩形按钮抽象类
/* author:hui
/* date:2016/12/8
/************************************************************************/
#include "button.h"
class rectButton : public button
{
public:
	rectButton(void);
	virtual ~rectButton(void);

	virtual bool touch(int _x,int _y);
	virtual bool release(int _x,int _y);

	virtual void draw();

	void setRect(const ofRectangle & _rect);
	const ofRectangle & getRect()const;
	ofRectangle & getRect();
private:
	ofRectangle rect;
};

