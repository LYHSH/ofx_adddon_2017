#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofVec2f.h"
#include <gl/GLU.h>

class fboTexture
{
public:
	fboTexture(void);
	~fboTexture(void);

	//投影
	void setup(int _drawwidth, int _drawheight);
	void startOffScreen();
	void endOffScreen();
	void initFBOTexture();

	//截取原屏幕的宽度和高度
	int drawwidth;
	int drawheight;

	//FBO & Texture ID
	GLuint glfboID, glfboTexID, depthbuffer;

	//截取前偏移
	int Xoffset;
	int Yoffset;
};
