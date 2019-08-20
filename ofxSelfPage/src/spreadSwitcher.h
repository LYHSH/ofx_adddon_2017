#pragma once
#include "pageSwitchBase.h"
/************************************************************************/
/* project name: 罗甸玉互动飞屏软件
/* file describe: 界面转场效果类-扩散展开
/* author:hui
/* date:2016/12/19
/************************************************************************/
class spreadSwitcher : public pageSwitchBase
{
public:
	spreadSwitcher(void);
	~spreadSwitcher(void);

	virtual void setup(pageBase * _removePage,pageBase * _mainPage){
		pageSwitchBase::setup(_removePage,_mainPage);
		removePage->begin();
		mainPage->begin();
		initGlsl();

		width = _mainPage->getStageRect().getWidth();
		height = _mainPage->getStageRect().getHeight();

		maskFbo.allocate(width,height);
		fbo.allocate(width,height);

		fbo1.allocate(width,height);
		fbo2.allocate(width,height);


		maskFbo.begin();
		ofClear(0,0,0,255);
		maskFbo.end();

		fbo.begin();
		ofClear(0,0,0,255);
		fbo.end();
	}
	virtual void update(){
		removePage->cusupdate();
		mainPage->cusupdate();

		fbo1.begin();
		removePage->cusdraw();
		fbo1.end();

		fbo2.begin();
		mainPage->cusdraw();
		fbo2.end();

		
		if (!maskRect.inside(mainPage->getStageRect()))
		{
			maskRect.scaleFromCenter(1.1f);
		}
		else
		{
			if (removePage->isActiving() && removePage != mainPage)
			{
				removePage->end();
			}
		}

		maskFbo.begin();
		ofRect(maskRect);
		maskFbo.end();


		// HERE the shader-masking happends
		//
		fbo.begin();
		// Cleaning everthing with alpha mask on 0 in order to make it transparent for default
		ofClear(0, 0, 0, 0); 

		shader.begin();
		shader.setUniformTexture("maskTex", maskFbo.getTextureReference(), 1 );

		//mainPage->cusdraw();
		fbo2.draw(0,0,width,height);

		shader.end();
		fbo.end();
	}
	virtual void draw(){
 		fbo1.draw(0,0,width,height);
 		fbo.draw(0,0);
	} 

	void setMaskRect(ofRectangle _rect){
		maskRect = _rect;
	}

protected:
	bool initGlsl();
	float width,height;
	ofFbo       maskFbo;
	ofFbo       fbo;

	ofShader    shader;
	string vertex;
	string fragment;

	ofRectangle maskRect;

	ofFbo fbo1;
	ofFbo fbo2;

};

