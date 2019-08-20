#include "ofxBtnPageV2.h"
#include "ofxImagePageBack.h"
#include "ofxVideoPageBack.h"
#include "ofxNullPageBack.h"


ofxBtnPageV2::ofxBtnPageV2()
{
	pageBack = NULL;
}


ofxBtnPageV2::~ofxBtnPageV2()
{
}

ofxBtnPageV2 * ofxBtnPageV2::createPage(int _controlIndex)
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

ofxBtnPageV2 * ofxBtnPageV2::createMainPage()
{
	ofxBtnPageV2 * page = new ofxBtnPageV2();
	page->setControlIndex(MAIN_PAGE_INDEX);

	return page;
}

ofxBtnPageV2 * ofxBtnPageV2::createSecondPage()
{
	ofxBtnPageV2 * page = new ofxBtnPageV2();
	page->setControlIndex(SECOND_PAGE_INDEX);

	return page;
}

ofxBtnPageV2 * ofxBtnPageV2::createThirdPage()
{
	ofxBtnPageV2 * page = new ofxBtnPageV2();
	page->setControlIndex(THIRD_PAGE_INDEX);

	return page;
}

void ofxBtnPageV2::setup(string _file, int _startOrder)
{
	setDataDir("");
	settingFile = _file;
	startOrder = _startOrder;

	loadSetting(settingFile, startOrder);
}

void ofxBtnPageV2::update()
{
	pageBack->update();
}

void ofxBtnPageV2::draw()
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

void ofxBtnPageV2::keyPressed(int key)
{

}

void ofxBtnPageV2::mouseDragged(int x, int y, int button)
{

}

void ofxBtnPageV2::mousePressed(int x, int y, int button)
{
	for (int i = 0; i < btns.size(); i++)
	{
		auto & btn = btns[i];
		btn->touch(x, y);
	}
}

void ofxBtnPageV2::mouseReleased(int x, int y, int button)
{
	for (int i = 0; i < btns.size(); i++)
	{
		auto & btn = btns[i];
		if (btn->release(x, y))
		{
			orderHandler::getInstance().handleOrder(btn->getId());
		}
	}
}

void ofxBtnPageV2::loadSetting(string _file, int _startOrder)
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
			string showTexName = getDataDir() + xml.getValue("tex", "", 0);
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

button * ofxBtnPageV2::createButton(const ofImage & _tex, ofVec2f _centerPos, int _btnId)
{
	ofRectangle rect;
	rect.setFromCenter(_centerPos, _tex.getWidth(), _tex.getHeight());

	string btnName = "button" + _btnId;

	return buttonFactory::createTexRectButton(rect, _tex, _btnId, btnName);
}

button * ofxBtnPageV2::createButton(const ofImage & _showTex, const ofImage & _touchTex, ofVec2f _centerPos, int _btnId)
{
	ofRectangle rect;
	rect.setFromCenter(_centerPos, _showTex.getWidth(), _showTex.getHeight());

	string btnName = "button" + _btnId;

	return buttonFactory::createDoubleStateButton(rect, _showTex, _touchTex, _btnId, btnName);
}

