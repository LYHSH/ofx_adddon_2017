#include "nullConverter.h"



nullConverter::nullConverter()
{
}


nullConverter::~nullConverter()
{
}

nullConverter * nullConverter::getInstance()
{
	static nullConverter * object = new nullConverter();
	return object;
}

string nullConverter::getCmd(string _cmd)
{
	return _cmd;
}