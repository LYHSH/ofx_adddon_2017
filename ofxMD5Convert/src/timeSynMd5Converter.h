#pragma once
#include "md5Converter.h"
/************************************************************************/
/* project name:ͨѶָ����ܽӿڿ�
/* file describe:ָ��ת����(ʱ��ͬ��У��)
/* author:hui
/* date:2017.9.15
/************************************************************************/
class timeSynMd5Converter : public md5Converter
{
public:
	timeSynMd5Converter();
	~timeSynMd5Converter();

	static timeSynMd5Converter * getInstance();
	string getCmd(string _cmd) override final;			//������ָ��ת��������
};

