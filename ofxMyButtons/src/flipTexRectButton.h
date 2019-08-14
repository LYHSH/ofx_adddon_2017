#pragma once
#include "ofMain.h"
#include "texRectButton.h"
/************************************************************************/
/* file describe:矩形纹理按钮类(可实现滑动效果)
/* author:hui
/* date:2016/12/18
/************************************************************************/
class flipTexRectButton : public texRectButton
{
public:
	flipTexRectButton(void);
	~flipTexRectButton(void);

	bool touch(int _x,int _y);
	bool release(int _x,int _y);

	void draw();
	void setOffsetX(float _x);
	void setOffsetY(float _y);
	const ofVec2f & getOffSet()const;

	ofRectangle  getDrawRect();
private:
	ofVec2f offset;
};

