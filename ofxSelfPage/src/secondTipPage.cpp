#include "secondTipPage.h"
#include "orderHandler.h"

bool secondTipPage::bActive =false;
int secondTipPage::order = -1000;
float secondTipPage::beginTime = 0.0f;
vector<wordButton*> secondTipPage::btns;
button *secondTipPage::touchBtn;
vector<int> secondTipPage::seceodConfirmIds;
secondTipPage::secondTipPage()
{
	bActive = false;
}


secondTipPage::~secondTipPage()
{
}

void secondTipPage::begin(int _order,button * btn)
{
	bool flag = false;
	for (auto orderId : seceodConfirmIds)
	{
		if (orderId == _order)
		{
			flag = true;
			break;
		}
	}

	if (flag)
	{
		init();
		order = _order;
		touchBtn = btn;
		bActive = true;
		beginTime = ofGetElapsedTimef();
	}
	else
	{
		orderHandler::getInstance().handleOrder(_order);
	}
	
}

bool secondTipPage::isActiving()
{
	return bActive;
}

void secondTipPage::draw()
{
	if (!bActive)return;
		
	ofPushMatrix();
	ofPushStyle();
	ofRectangle rect;
	rect.setFromCenter(1024, 768, 2048,1536);
	ofFill();
	ofSetColor(128, 128, 128, 150);
	ofRect(rect);
	ofPopStyle();

	for (int i = 0; i < btns.size(); i++)
	{
		btns[i]->draw();
	}
	
	ofPopMatrix();
}

void secondTipPage::mousePressed(int x, int y)
{
	if (!bActive)
	{
		return;
	}
	for (int i = 0; i < btns.size(); i++)
	{
		btns[i]->touch(x, y);
	}

}

void secondTipPage::mouseReleased(int x, int y)
{
	if (!bActive)
	{
		return;
	}
	for (int i = 0; i < btns.size(); i++)
	{
		//避免两个页面之间同位置的按钮的连续误触发
		if (((ofGetElapsedTimef() - beginTime) > 0.5f) && btns[i]->release(x,y))
		{
			if (i == BTN_OK)
			{
				orderHandler::getInstance().handleOrder(order);
				//touchBtn->sleep();
			}
			bActive = false;
		}
	}
}

void secondTipPage::addSecondConfirmId(int _id)
{
	seceodConfirmIds.push_back(_id);
}

void secondTipPage::init()
{
	static bool first = true;
	if (first)
	{
		bActive = false;
		beginTime = ofGetElapsedTimef();
		ofxXmlSettings xml;
		xml.loadFile("xml/btn.xml");

		string datadir = xml.getValue("dataDir", "");

		int btnNums = xml.getNumTags("btn");
		btns.resize(btnNums);

		for (int i = 0; i < btnNums; i++)
		{
			xml.pushTag("btn", i);
			ofVec2f pos;
			pos.x = xml.getValue("x", 0.0f);
			pos.y = xml.getValue("y", 0.0f);

			string name = xml.getValue("name", "btn");
			string texName = datadir + xml.getValue("tex", "");

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


			btns[i]->setOrderID(0 + i);
			xml.popTag();
		}
		first = false;
	}
}
