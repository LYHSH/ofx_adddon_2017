#pragma once
#include <string>
#include <algorithm>
using namespace std;
/************************************************************************/
/* project name:ͨѶָ����ܽӿڿ�
/* file describe:ָ��ת����(�̶��ַ���)
/* author:hui
/* date:2017.9.15
/************************************************************************/
class md5Converter
{
public:
	md5Converter();
	virtual ~md5Converter();
	static md5Converter * getInstance();
	virtual string getCmd(string _cmd);			//������ָ��ת��������

protected:
	static string getMD5str(string _srcStr);

	static string toLower(string _src);
};

