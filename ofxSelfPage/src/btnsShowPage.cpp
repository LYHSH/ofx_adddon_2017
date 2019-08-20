#include "btnsShowPage.h"
#include "secondTipPage.h"

ofxTrueTypeFontUC btnsShowPage::font;
btnsShowPage::btnsShowPage()
{
	init();
}


btnsShowPage::~btnsShowPage()
{
	
}

void btnsShowPage::setup(string _file,int _startOrder)
{
	setDataDir("");
	settingFile = _file;
	startOrder = _startOrder;

	loadSetting(settingFile);
}

void btnsShowPage::update()
{

}

void btnsShowPage::draw()
{
	ofPushMatrix();
	ofPushStyle();

	backImg.draw(getStageRect());
	font.drawString(titleWord,157,125);
	font.drawString(titleWord1, 157, 225);
	
	for (int i = 0; i < btns.size(); i++)
	{
		btns[i]->draw();
	}
	ofPopStyle();
	ofPopMatrix();
}

void btnsShowPage::keyPressed(int key)
{
	switch (key)
	{
	case 's':
		saveSetting(settingFile);
		break;
	default:
		break;
	}
}

void btnsShowPage::mouseDragged(int x, int y, int button)
{
	for (int i = 0; i < btns.size(); i++)
	{
		wordButton * var = btns[i];
		var->dragged(x, y);
	}
}

void btnsShowPage::mousePressed(int x, int y, int button)
{
	for (int i = 0; i < btns.size(); i++)
	{
		wordButton * var = btns[i];
		var->touch(x, y);
	}
}

void btnsShowPage::mouseReleased(int x, int y, int button)
{
	for (int i = 0; i < btns.size(); i++)
	{
		wordButton * var = btns[i];
		if (var->release(x, y))
		{
			secondTipPage::begin(var->getOrderID(), var);
		}
	}
}

void btnsShowPage::addChildPage(btnsShowPage * _page)
{
	bool flag = true;
	for (int i = 0; i < childPages.size(); i++)
	{
		if (_page == childPages[i])
		{
			flag = false;
		}
	}

	if (flag)
	{
		childPages.push_back(_page);
	}
}

void btnsShowPage::removeChildPage(btnsShowPage * _page)
{
	for (int i = 0; i < childPages.size(); i++)
	{
		if (_page == childPages[i])
		{
			childPages.erase(childPages.begin() + i);
			return;
		}
	}
}

void btnsShowPage::loadSetting(string _file)
{
	ofxXmlSettings xml;
	xml.loadFile(_file);

	setDataDir(xml.getValue("dataDir", ""));


	titleWord = xml.getValue("title", "");
	titleWord1 = xml.getValue("title1", "");
	backImg.loadImage(getDataDir() + xml.getValue("backTex",""));

	int btnNums = xml.getNumTags("btn");
	btns.resize(btnNums);

	for (int i = 0; i < btnNums; i++)
	{
		xml.pushTag("btn", i);
		ofVec2f pos;
		pos.x = xml.getValue("x", 0.0f);
		pos.y = xml.getValue("y", 0.0f);

		string name = xml.getValue("name", "btn");
		string texName = getDataDir() +  xml.getValue("tex", "");

		btns[i] = new wordButton();
		if ("" != texName)
		{
			ofImage tex;
			tex.load(texName);
			btns[i]->setup(tex, pos);
		}
		else
		{
			BTN_TYPE btnType = (BTN_TYPE)xml.getValue("type", 0);
			btns[i]->setup(name, pos, btnType);
		}
		
		
		btns[i]->setOrderID(startOrder + i);
		xml.popTag();
	}
}

void btnsShowPage::saveSetting(string _file)
{
	ofxXmlSettings xml;
	xml.loadFile(_file);

	for (int i = 0; i < btns.size(); i++)
	{
		xml.pushTag("btn", i);
		ofVec2f pos = btns[i]->getPos();
		xml.setValue("x", pos.x);
		xml.setValue("y", pos.y);
		xml.popTag();
	}

	xml.saveFile();
}

void btnsShowPage::init()
{
	static bool first = true;
	if (first)
	{
		font.loadFont("fonts/title1.TTF", 50);
		first = false;
	}
}
