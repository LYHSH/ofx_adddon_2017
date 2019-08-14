#pragma once
#include "md5Converter.h"
/************************************************************************/
/* project name:通讯指令加密接口库
/* file describe:指令转换器(什么也不做)
/* author:hui
/* date:2017.9.16
/************************************************************************/
class nullConverter : public md5Converter
{
public:
	nullConverter();
	~nullConverter();

	static nullConverter * getInstance();
	string getCmd(string _cmd) override final;			//将明文指令转换成密文
};

