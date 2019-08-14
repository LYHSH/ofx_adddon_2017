#include "fboTexture.h"

fboTexture::fboTexture(void)
{
}

fboTexture::~fboTexture(void)
{
}

void fboTexture::setup(int _drawwidth, int _drawheight)
{
	//截取的宽度和高度
	drawwidth = _drawwidth;
	drawheight = _drawheight;
	//加载参数
	/*ofxXmlSettings OffScreen;
	OffScreen.loadFile("OffScreen.xml");
	OffScreen.pushTag("OffScreen");
	Xoffset = OffScreen.getValue("xoff",0,0);
	Yoffset = OffScreen.getValue("yoff",0,0);
	OffScreen.popTag();*/

	Xoffset = 0;
	Yoffset = 0;

}

//FBO Texture　截屏处理
void fboTexture::initFBOTexture()
{
	//生成FBO
	glGenFramebuffersEXT(1, &glfboID);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, glfboID);
	//生成纹理
	glGenTextures(1, &glfboTexID);
	glBindTexture(GL_TEXTURE_2D, glfboTexID);
	//过滤器
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//生成动态纹理
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, drawwidth, drawheight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//绑定纹理和FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, glfboTexID, 0);
	//建立深度缓存
	glGenRenderbuffersEXT(1, &depthbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, drawwidth, drawheight);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);
	//恢复当前FBO
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void fboTexture::startOffScreen()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, glfboID);

	glViewport(0, 0, drawwidth, drawheight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除缓存

	int w, h;
	w = drawwidth;
	h = drawheight;

	float halfFov, theTan, screenFov, aspect;
	screenFov 		= 60.0f;

	float eyeX 		= (float)w / 2.0;
	float eyeY 		= (float)h / 2.0;
	halfFov 		= PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;
	float farDist 	= dist * 10.0;
	aspect 			= (float)w/(float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(screenFov, aspect, nearDist, farDist);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	ofTranslate(Xoffset, Yoffset);
}

void fboTexture::endOffScreen()
{
	glPopMatrix();

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glViewport(0, 0, ofGetWidth(), ofGetHeight());
	ofSetupScreen();
}
