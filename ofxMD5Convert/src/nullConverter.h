#pragma once
#include "md5Converter.h"
/************************************************************************/
/* project name:ͨѶָ����ܽӿڿ�
/* file describe:ָ��ת����(ʲôҲ����)
/* author:hui
/* date:2017.9.16
/************************************************************************/
class nullConverter : public md5Converter
{
public:
	nullConverter();
	~nullConverter();

	static nullConverter * getInstance();
	string getCmd(string _cmd) override final;			//������ָ��ת��������
};

