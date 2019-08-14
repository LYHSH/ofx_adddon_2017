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

	//ͶӰ
	void setup(int _drawwidth, int _drawheight);
	void startOffScreen();
	void endOffScreen();
	void initFBOTexture();

	//��ȡԭ��Ļ�Ŀ�Ⱥ͸߶�
	int drawwidth;
	int drawheight;

	//FBO & Texture ID
	GLuint glfboID, glfboTexID, depthbuffer;

	//��ȡǰƫ��
	int Xoffset;
	int Yoffset;
};
