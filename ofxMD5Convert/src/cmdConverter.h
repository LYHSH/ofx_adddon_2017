#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name:通讯指令加密接口库
/* file describe:指令加密转换器
/* author:hui
/* date:2017.9.19
/************************************************************************/
class cmdConverter
{
public:
	cmdConverter();
	~cmdConverter();

	static string getEncryCmd(string _srcCmd);

private:
};

