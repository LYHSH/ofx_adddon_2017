#include "ofxRelaysBase.h"

ofxRelaysBase::ofxRelaysBase()
{
}


ofxRelaysBase::~ofxRelaysBase()
{
}

void ofxRelaysBase::setSingleOn(int _id)
{
	vector<int> arrs;
	arrs.push_back(_id);
	setSingleOn(arrs);
}

void ofxRelaysBase::setAddress(unsigned char _addressCode)
{
	address = _addressCode;
}

unsigned char ofxRelaysBase::getAddress()const
{
	return address;
}

void ofxRelaysBase::setSize(int _loopsize)
{
	loopSize = _loopsize;
}

int ofxRelaysBase::size()
{
	return loopSize;
}
