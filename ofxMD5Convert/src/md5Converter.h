#pragma once
#include <string>
#include <algorithm>
using namespace std;
/************************************************************************/
/* project name:通讯指令加密接口库
/* file describe:指令转换器(固定字符串)
/* author:hui
/* date:2017.9.15
/************************************************************************/
class md5Converter
{
public:
	md5Converter();
	virtual ~md5Converter();
	static md5Converter * getInstance();
	virtual string getCmd(string _cmd);			//将明文指令转换成密文

protected:
	static string getMD5str(string _srcStr);

	static string toLower(string _src);
};

