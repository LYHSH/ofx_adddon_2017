#pragma once
#include "rectButton.h"
class doubleStateButton : public rectButton
{
public:
	doubleStateButton();
	~doubleStateButton();

	void setTex(const ofImage & _showTex,const ofImage & _touchTex);

	void draw()override final;
private:
	ofImage showTex;
	ofImage touchTex;
};

