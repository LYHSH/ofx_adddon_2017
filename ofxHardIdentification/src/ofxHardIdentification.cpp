#include "ofxHardIdentification.h"
#include "ofxCPU.h"
#include "ofxBaseBoard.h"
#include "md5Converter.h"
string ofxHardIdentification::extraInfoStr = "";
ofxHardIdentification::ofxHardIdentification()
{
}


ofxHardIdentification::~ofxHardIdentification()
{
}

string ofxHardIdentification::getIdentification()
{
	string totalIdStr = "";
	char cpuId[128] = "";
	{
		bool flag = false;
		int count = 0;
		while (!flag)
		{
			memset(cpuId, 0, 128);
			GetCpuByCmd(cpuId);
			string msg = cpuId;
			flag = (msg != "");
			count++;
			cout << count << endl;
		}
	}
	
	string cpuStr = cpuId;
	cout << "CPU:" << cpuId << endl;

	totalIdStr += "cpu:" + cpuStr;			//���CPU���

	char baseBoardId[128] = "";
	memset(baseBoardId, 0, 128);
	{
		bool flag = false;
		int count = 0;
		while (!flag)
		{
			memset(cpuId, 0, 128);
			GetBaseBoardByCmd(baseBoardId);
			string msg = baseBoardId;
			flag = (msg != "");
			count++;
			cout << count << endl;
		}
	}
	
	string baseBoardStr = baseBoardId;
	totalIdStr += "baseBoard:" + baseBoardStr;		//����������

	cout << "BASEBOARD:" << baseBoardId << endl;

	//cout << "total:"<<totalIdStr << endl;
	return md5Converter::getInstance()->getCmd(totalIdStr);
}

string ofxHardIdentification::getCheckStr(string _identification)
{
	string res = md5Converter::getInstance()->getCmd(_identification + extraInfoStr);
	return res;
}

bool ofxHardIdentification::check(string _checkStr)
{
	cout << "����У���У���ȴ�......" << endl;;
	Sleep(1000);
	string answerStr = getCheckStr(getIdentification());
	bool flag = (answerStr == _checkStr);
	cout << "У�����" << endl;
	return flag;
}

void ofxHardIdentification::setExtraInfo(string _extraInfoStr)
{
	extraInfoStr = _extraInfoStr;
}
