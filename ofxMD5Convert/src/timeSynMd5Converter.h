#pragma once
#include "md5Converter.h"
/************************************************************************/
/* project name:通讯指令加密接口库
/* file describe:指令转换器(时间同步校验)
/* author:hui
/* date:2017.9.15
/************************************************************************/
class timeSynMd5Converter : public md5Converter
{
public:
	timeSynMd5Converter();
	~timeSynMd5Converter();

	static timeSynMd5Converter * getInstance();
	string getCmd(string _cmd) override final;			//将明文指令转换成密文
};

