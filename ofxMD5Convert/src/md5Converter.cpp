#include "md5Converter.h"
#include "md5.h"

md5Converter::md5Converter()
{
}


md5Converter::~md5Converter()
{
}

md5Converter * md5Converter::getInstance()
{
	static md5Converter * object = new md5Converter();
	return object;
}

string md5Converter::getCmd(string _cmd)
{
	string srcStr = "huameilingw38475jfghieyrfjduerejvjh";
	srcStr += _cmd;
	srcStr += "ferdcfutfhgfuufdh,.,.fekfsj.;lpfg";

	return getMD5str(srcStr);
}

string md5Converter::getMD5str(string _srcStr)
{
	CmyMD5 md5;
	MD5_CTX context;
	md5.MD5Init(&context);
	md5.MD5Update(&context, (unsigned char *)_srcStr.c_str(), _srcStr.size());
	md5.MD5Final(&context);

	string res = md5.MD5Trans(context);			//密文
	res = toLower(res);						//转换成小写

	return res;
}

string md5Converter::toLower(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}