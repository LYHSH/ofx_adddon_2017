#pragma once
/************************************************************************/
/* file describe:��������ť��
/* author:hui
/* date:2016/12/9
/************************************************************************/
#include "rectButton.h"
class texRectButton : public rectButton
{
public:
	texRectButton(void);
	virtual ~texRectButton(void);

	virtual void draw();

	void setTex(const ofImage & _tex);
	ofImage & getTex();
	void setPos(ofVec2f _pos);
	protected:
	ofImage tex;
};

