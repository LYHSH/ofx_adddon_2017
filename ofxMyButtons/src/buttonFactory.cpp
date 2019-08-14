#include "buttonFactory.h"
#include "rectButton.h"
#include "texRectButton.h"
#include "texTextRectButton.h"
#include "doubleStateButton.h"

buttonFactory::buttonFactory(void)
{
}


buttonFactory::~buttonFactory(void)
{
}

button * buttonFactory::createButton(const int & _id /* = -1 */,const string & _name /* = "" */){
	button * btn = new button();
	btn->setName(_name);
	btn->setId(_id);

	return btn;
}

button * buttonFactory::createRectButton(const ofRectangle & _rect,const int & _id /* = -1 */,const string & _name /* = "" */){
	rectButton * btn = new rectButton();
	btn->setName(_name);
	btn->setId(_id);
	btn->setRect(_rect);
	return btn;
}

button * buttonFactory::createTexRectButton(const ofRectangle & _rect,const ofImage & _tex,
											const int & _id /* = -1 */,const string & _name /* = "" */)
{
	texRectButton * btn = new texRectButton();
	btn->setName(_name);
	btn->setId(_id);
	btn->setRect(_rect);
	btn->setTex(_tex);
	return btn;
}

button * buttonFactory::createTexTextRectButton(const ofRectangle & _rect, const ofImage & _tex,const string & _text,
	const int & _id /* = -1 */, const string & _name /* = "" */)
{
	static bool first = true;
	if (first)
	{
		texTextRectButton::loadFont("fonts/msyh.ttc");
		first = false;
	}

	texTextRectButton * btn = new texTextRectButton();
	btn->setName(_name);
	btn->setId(_id);
	btn->setRect(_rect);
	btn->setTex(_tex);
	btn->setText(_text);
	return btn;
}

button * buttonFactory::createDoubleStateButton(const ofRectangle & _rect, const ofImage & _showTex, const ofImage & _touchTex,
	const int & _id /* = -1 */, const string & _name /* = "" */)
{
	doubleStateButton * btn = new doubleStateButton();
	btn->setName(_name);
	btn->setId(_id);
	btn->setRect(_rect);
	btn->setTex(_showTex,_touchTex);
	return btn;
}