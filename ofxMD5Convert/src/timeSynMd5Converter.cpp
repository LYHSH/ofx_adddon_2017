#include "timeSynMd5Converter.h"
#include "ofUtils.h"


timeSynMd5Converter::timeSynMd5Converter()
{
}


timeSynMd5Converter::~timeSynMd5Converter()
{
}

timeSynMd5Converter * timeSynMd5Converter::getInstance()
{
	static timeSynMd5Converter * object = new timeSynMd5Converter();
	return object;
}

string timeSynMd5Converter::getCmd(string _cmd)
{
	string srcStr = "huameilingw38475jfghieyrfjduerejvjh";
	srcStr += _cmd;
	srcStr += "ferdcfutfhgfuufdh,.,.fekfsj.;lpfg";
	srcStr += ofGetYear();
	srcStr += "123fuw,.,noglyootbl";
	srcStr += ofGetMonth();
	srcStr += ",m,kngto569cm,bft";
	srcStr += ofGetDay();
	srcStr += "4596kvokqs.;[km;j";

	return getMD5str(srcStr);
}
