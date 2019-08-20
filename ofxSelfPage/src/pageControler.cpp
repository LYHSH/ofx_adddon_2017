#include "pageControler.h"
#include "flipSwitcher.h"
#include "spreadSwitcher.h"
#include "rightFlipSwitcher.h"
#include "upFlipSwitcher.h"
#include "downFlipSwitcher.h"
ofEvent <unattendedEventArgs> pageControler::unattendedEvent;
pageControler::pageControler(void)
{
	updateUnattended();
}


pageControler::~pageControler(void)
{
}


pageControler & pageControler::getInstance(){
	static bool first = true;
	static pageControler controler;
	if (first)
	{
		//执行必要的初始化操作
		controler.setup();
		first = false;
	}
	return controler;
}

void pageControler::setup(){
}

void pageControler::update(){
    
    for (int i = 0; i < switchers.size(); i++) {
        if (switchers[i]) {
            switchers[i]->update();
        }
    }
//	for each (auto obj in switchers)
//	{
//		if (obj)
//		{
//			obj->update();
//		}
//	}

	checkUnattended();
}

void pageControler::draw(){
	for (int i = 0; i < switchers.size(); i++)
	{
		if (switchers[i])
		{
			if (useFboFlags[i])
			{
				
				fbos[i]->begin();
				ofClear(0, 0, 0, 0);
				ofPushMatrix();
				ofTranslate(-fboRects[i].getTopLeft());
				switchers[i]->draw();
				ofPopMatrix();
				fbos[i]->end();
				

				fbos[i]->draw(drawRects[i]);
			}
			else
			{
				switchers[i]->draw();
			}
		}
	}
}

void pageControler::keyPressed(int key){
    for (int i = 0; i < switchers.size(); i++) {
        if (switchers[i]) {
            switchers[i]->keyPressed(key);
        }
    }

	updateUnattended();
}

void pageControler::keyReleased(int key){
    for (int i = 0; i < switchers.size(); i++) {
        if (switchers[i]) {
            switchers[i]->keyReleased(key);
        }
    }

	updateUnattended();
}

void pageControler::mouseMoved(int x, int y ){
	for (int i = 0; i < switchers.size(); i++)
	{
		if (switchers[i])
		{
			ofVec2f offset = ofVec2f(fboRects[i].getTopLeft() - drawRects[i].getTopLeft());
			x += offset.x;
			y += offset.y;
			switchers[i]->mouseMoved(x, y);
		}
	}

	updateUnattended();
}

void pageControler::mouseDragged(int x, int y, int button){
	for (int i = 0; i < switchers.size(); i++)
	{
		if (switchers[i])
		{
			ofVec2f offset = ofVec2f(fboRects[i].getTopLeft() - drawRects[i].getTopLeft());
			x += offset.x;
			y += offset.y;
			switchers[i]->mouseDragged(x, y, button);
		}
	}

	updateUnattended();
}

void pageControler::mousePressed(int x, int y, int button){
	for (int i = 0; i < switchers.size(); i++)
	{
		if (switchers[i])
		{
			ofVec2f offset = ofVec2f(fboRects[i].getTopLeft() - drawRects[i].getTopLeft());
			x += offset.x;
			y += offset.y;
			switchers[i]->mousePressed(x, y, button);
		}
	}

	updateUnattended();
}

void pageControler::mouseReleased(int x, int y, int button){
	for (int i = 0; i < switchers.size(); i++)
	{
		if (switchers[i])
		{
			ofVec2f offset = ofVec2f(fboRects[i].getTopLeft() - drawRects[i].getTopLeft());
			x += offset.x;
			y += offset.y;
			switchers[i]->mouseReleased(x, y, button);
		}
	}

	updateUnattended();
}

void pageControler::noSwitch(pageBase * _page,int _index /* = 0 */){
	if (_index < 0) { return; }
	else if (_index >= switchers.size())
	{
		addNewSwitcher();
	}
	else
	{
		if (getMainPage(_index))
		{
			getMainPage(_index)->end();
		}

		if (switchers[_index])
		{
			delete switchers[_index];
			switchers[_index] = NULL;
		}
	}
	

	switchers[_index] = new pageSwitchBase();
	switchers[_index]->setup(_page,_page);
}

void pageControler::leftLeaveSwitch(pageBase * _removePage,pageBase * _mainPage, int _index /* = 0 */){
	if (_index < 0) { return; }
	else if (_removePage == _mainPage) { return; }
	else if (_index >= switchers.size())
	{
		addNewSwitcher();
	}
	else
	{
		if (switchers[_index])
		{
			delete switchers[_index];
			switchers[_index] = NULL;
		}
	}

	switchers[_index] = new flipSwitcher();
	switchers[_index]->setup(_removePage,_mainPage);
}

void pageControler::leftLeaveSwitch(pageBase * _mainPage, int _index /* = 0 */)
{
	leftLeaveSwitch(getMainPage(_index), _mainPage, _index);
}

void pageControler::rightLeaveSwitch(pageBase * _removePage,pageBase * _mainPage, int _index /* = 0 */){
	if (_index < 0) { return; }
	else if (_removePage == _mainPage) { return; }
	else if (_index >= switchers.size())
	{
		addNewSwitcher();
	}
	else
	{
		if (switchers[_index])
		{
			delete switchers[_index];
			switchers[_index] = NULL;
		}
	}


	switchers[_index] = new rightFlipSwitcher();
	switchers[_index]->setup(_removePage, _mainPage);
}

void pageControler::upLeaveSwitch(pageBase * _removePage, pageBase * _mainPage, int _index /* = 0 */) {
	if (_index < 0) { return; }
	else if (_removePage == _mainPage) { return; }
	else if (_index >= switchers.size())
	{
		addNewSwitcher();
	}
	else
	{
		if (switchers[_index])
		{
			delete switchers[_index];
			switchers[_index] = NULL;
		}
	}


	switchers[_index] = new upFlipSwitcher();
	switchers[_index]->setup(_removePage, _mainPage);
}

void pageControler::downLeaveSwitch(pageBase * _removePage, pageBase * _mainPage, int _index /* = 0 */) {
	if (_index < 0) { return; }
	else if (_removePage == _mainPage) { return; }
	else if (_index >= switchers.size())
	{
		addNewSwitcher();
	}
	else
	{
		if (switchers[_index])
		{
			delete switchers[_index];
			switchers[_index] = NULL;
		}
	}


	switchers[_index] = new downFlipSwitcher();
	switchers[_index]->setup(_removePage, _mainPage);
}

void pageControler::rightLeaveSwitch(pageBase * _mainPage, int _index /* = 0 */)
{
	rightLeaveSwitch(getMainPage(_index), _mainPage,_index);
}

void pageControler::upLeaveSwitch(pageBase * _mainPage, int _index /* = 0 */)
{
	upLeaveSwitch(getMainPage(_index), _mainPage, _index);
}

void pageControler::downLeaveSwitch(pageBase * _mainPage, int _index /* = 0 */)
{
	downLeaveSwitch(getMainPage(_index), _mainPage, _index);
}

void pageControler::rectSpreadSwitch(pageBase * _removePage,pageBase * _mainPage,ofRectangle _SrcRect, int _index /* = 0 */){
	if (_index < 0) { return; }
	else if (_index >= switchers.size())
	{
		addNewSwitcher();
	}
	else
	{
		if (switchers[_index])
		{
			delete switchers[_index];
			switchers[_index] = NULL;
		}
	}

	spreadSwitcher * temp = new spreadSwitcher();
	temp->setup(_removePage,_mainPage);
	temp->setMaskRect(_SrcRect);

	switchers[_index] = temp;

	temp = NULL;
	
}

pageBase * pageControler::getMainPage(int _index /* = 0 */)
{
	if (_index < 0) { return NULL; }
	else if (_index >= switchers.size())
	{
		return NULL;
	}
	else
	{
		return switchers[_index]->getMainPage();
	}
}

int pageControler::getNewIndex()
{
	return switchers.size();
}

void pageControler::setFboRect(ofRectangle _fboRect, int _index /* = 0 */)
{
	if (!checkOutRange(_index))return;

	fboRects[_index] = _fboRect;

	fbos[_index]->destroy();

	fbos[_index]->allocate(fboRects[_index].getWidth(), fboRects[_index].getHeight(), GL_RGBA);
}

void pageControler::setUseFbo(bool _use, int _index /* = 0 */)
{
	if (!checkOutRange(_index))return;

	useFboFlags[_index] = _use;
}

void pageControler::setDrawRect(ofRectangle _drawRect, int _index /* = 0 */)
{
	if (!checkOutRange(_index))return;

	drawRects[_index] = _drawRect;
}

void pageControler::addNewSwitcher()
{
	switchers.push_back(NULL);
	fbos.push_back(new ofFbo());
	useFboFlags.push_back(false);
	fboRects.push_back(ofRectangle());
	drawRects.push_back(ofRectangle());
}

void pageControler::setUnattendedTimeLen(float _timeLen)
{
	unattendedTimeLen = _timeLen;
}

bool pageControler::checkOutRange(int _index)
{
	if (_index >=0 && _index < switchers.size())
	{
		return true;
	}
	return false;
}

bool pageControler::checkUnattended()
{
	if (ofGetElapsedTimef() - lastTouchTime > unattendedTimeLen)
	{
// 		ofLogNotice() << "last:" << lastTouchTime << endl;
// 		ofLogNotice() << "now:" << ofGetElapsedTimef() << endl;
		lastTouchTime = ofGetElapsedTimef();
		notifyUnattendedEvent();
		return true;
	}
	return false;
}

void pageControler::updateUnattended()
{
	lastTouchTime = ofGetElapsedTimef();
}

void pageControler::notifyUnattendedEvent()
{
	unattendedEventArgs args;
	ofNotifyEvent(pageControler::unattendedEvent, args);
}
