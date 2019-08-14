#include "button.h"


button::button(void)
{
	name = "";
	id = -1;
	bTouched = false;
	bEnable = true;
}


button::~button(void)
{
}

void button::setName(const string & _name){
	name = _name;
}

string button::getName()const{
	return name;
}

void button::setId(const int & _id){
	id = _id;
}

int button::getId()const{
	return id;
}

void button::enable()
{
	bEnable = true;
}

void button::disable()
{
	bEnable = false;
}

bool button::isEnable()
{
	return bEnable;
}