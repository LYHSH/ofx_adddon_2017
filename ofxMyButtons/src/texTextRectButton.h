#pragma once
#include "texRectButton.h"
#include "ofxTrueTypeFontUC.h"
/************************************************************************/
/* file describe:矩形纹理文字按钮类
/* author:hui
/* date:2016/11/21
/************************************************************************/
class texTextRectButton : public texRectButton
{
public:
	texTextRectButton();
	~texTextRectButton();

	static void loadFont(string _path);

	void setText(string _text);
	string getText()const;

	void setOffset(float _x,float _y);
	void setColor(ofColor _color);

	void draw();
protected:
	string text;
	ofRectangle textRect;
	ofVec2f textOffset;
	ofColor textColor;
	static ofxTrueTypeFontUC font;
};

