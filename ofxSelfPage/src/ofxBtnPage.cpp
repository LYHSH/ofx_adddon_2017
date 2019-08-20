#include "ofxBtnPage.h"
#include "ofxImagePageBack.h"
#include "ofxVideoPageBack.h"
#include "ofxNullPageBack.h"
#include "secondTipPage.h"

ofxBtnPage::ofxBtnPage()
{
	pageBack = NULL;
}


ofxBtnPage::~ofxBtnPage()
{
}

ofxBtnPage * ofxBtnPage::createPage(int _controlIndex)
{
	switch (_controlIndex)
	{
	case MAIN_PAGE_INDEX:
		return createMainPage();
		break;
	case SECOND_PAGE_INDEX:
		return createSecondPage();
		break;
	case THIRD_PAGE_INDEX:
		return createThirdPage();
		break;
	default:
		return NULL;
		break;
	}
}

ofxBtnPage * ofxBtnPage::createMainPage()
{
	ofxBtnPage * page = new ofxBtnPage();
	page->setControlIndex(MAIN_PAGE_INDEX);
	
	return page;
}

ofxBtnPage * ofxBtnPage::createSecondPage()
{
	ofxBtnPage * page = new ofxBtnPage();
	page->setControlIndex(SECOND_PAGE_INDEX);

	return page;
}

ofxBtnPage * ofxBtnPage::createThirdPage()
{
	ofxBtnPage * page = new ofxBtnPage();
	page->setControlIndex(THIRD_PAGE_INDEX);

	return page;
}

void ofxBtnPage::setup(string _file, int _startOrder)
{
	setDataDir("");
	settingFile = _file;
	startOrder = _startOrder;

	loadSetting(settingFile,startOrder);
}

void ofxBtnPage::update()
{
	pageBack->update();
}

void ofxBtnPage::draw()
{
	ofPushMatrix();
	ofPushStyle();

	pageBack->draw(getStageRect());
	

	for (int i = 0; i < btns.size(); i++)
	{
		btns[i]->draw();
	}
	ofPopStyle();
	ofPopMatrix();
}

void ofxBtnPage::keyPressed(int key)
{
	
}

void ofxBtnPage::mouseDragged(int x, int y, int button)
{
	
}

void ofxBtnPage::mousePressed(int x, int y, int button)
{
	for (int i = 0; i < btns.size(); i++)
	{
		auto & btn = btns[i];
		btn->touch(x, y);
	}
}

void ofxBtnPage::mouseReleased(int x, int y, int button)
{
	for (int i = 0; i < btns.size(); i++)
	{
		auto & btn = btns[i];
		if (btn->release(x, y))
		{
			//orderHandler::getInstance().handleOrder(btn->getId());
			secondTipPage::begin(btn->getId(), btn);
		}
	}
}

void ofxBtnPage::loadSetting(string _file,int _startOrder)
{
	ofxXmlSettings xml;
	xml.loadFile(_file);

	setDataDir(xml.getValue("dataDir", ""));

	if (xml.tagExists("backTex"))
	{
		pageBack = new ofxImagePageBack();
		pageBack->setup(getDataDir() + xml.getValue("backTex", ""));
	}
	else if (xml.tagExists("backVideo"))
	{
		pageBack = new ofxVideoPageBack();
		pageBack->setup(getDataDir() + xml.getValue("backVideo", ""));
	}
	else
	{
		pageBack = new ofxNullPageBack();
		pageBack->setup("");
	}
	
	

	int btnNums = xml.getNumTags("btn");
	btns.resize(btnNums);

	for (int i = 0; i < btnNums; i++)
	{
		xml.pushTag("btn", i);
		ofVec2f btnPos;
		btnPos.x = xml.getValue("x", 0.0f);
		btnPos.y = xml.getValue("y", 0.0f);

		int texNums = xml.getNumTags("tex");
		if (1 == texNums)
		{
			string btnTexName = getDataDir() + xml.getValue("tex", "");

			ofImage btnTex;
			btnTex.load(btnTexName);

			int btnId = startOrder + i;
			btns[i] = createButton(btnTex, btnPos, btnId);
		}
		else if (2 == texNums)
		{
			string showTexName = getDataDir() + xml.getValue("tex", "",0);
			string touchTexName = getDataDir() + xml.getValue("tex", "", 1);

			ofImage showTex;
			showTex.load(showTexName);
			ofImage touchTex;
			touchTex.load(touchTexName);

			int btnId = startOrder + i;
			btns[i] = createButton(showTex, touchTex, btnPos, btnId);
		}
		

		xml.popTag();
	}
 
}

button * ofxBtnPage::createButton(const ofImage & _tex, ofVec2f _pos,int _btnId)
{
	ofRectangle rect(_pos.x, _pos.y, _tex.getWidth(), _tex.getHeight());
	rect.setFromCenter(_pos.x, _pos.y, _tex.getWidth(), _tex.getHeight());

   
	string btnName = "button" +  ofToString(_btnId);

	return buttonFactory::createTexRectButton(rect, _tex, _btnId, btnName);
}

button * ofxBtnPage::createButton(const ofImage & _showTex, const ofImage & _touchTex, ofVec2f _centerPos, int _btnId)
{
	ofRectangle rect;
	rect.setFromCenter(_centerPos, _showTex.getWidth(), _showTex.getHeight());

	string btnName = "button" +  ofToString(_btnId);

	return buttonFactory::createDoubleStateButton(rect, _showTex,_touchTex, _btnId, btnName);
}
