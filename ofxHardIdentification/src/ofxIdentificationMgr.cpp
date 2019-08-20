#include "ofxIdentificationMgr.h"
#include "ofxHardIdentification.h"

bool ofxIdentificationMgr::isRegistered = false;
int ofxIdentificationMgr::checkKey = -1;
ofxIdentificationMgr::ofxIdentificationMgr()
{
}


ofxIdentificationMgr::~ofxIdentificationMgr()
{
}

void ofxIdentificationMgr::setup()
{
	generateIdentification();
	
	isRegistered = check();

	if (!isRegistered)
	{
		if (-1 != checkKey)
		{
			ofLogError() << "checkKey = " << checkKey << endl;
		}
		
		if (MessageBox(HWND_DESKTOP, "本主机尚未注册或注册码错误，请在指定主机上运行软件，或者联系软件供应商！", "Error", MB_OK | MB_ICONEXCLAMATION))
		{
			ofExit(-3);
		}
	}
}

void ofxIdentificationMgr::update()
{
	
}

void ofxIdentificationMgr::generateIdentification()
{
	cout << "硬件信息生成中..." << endl;
	string str = "";
	str = ofxHardIdentification::getIdentification();
	
	ofxXmlSettings xml;
	xml.addValue("SOURCE", str);
	xml.save("identificationSource.xml");
}

bool ofxIdentificationMgr::check()
{
	ofxXmlSettings xml;
	
	xml.load("identificationResult.xml");
	string result = xml.getValue("RESULT", "00000000000000000000000000000000");

	return ofxHardIdentification::check(result);
}

void ofxIdentificationMgr::generateCheckStr()
{
	generateCheckStr("identificationSource.xml");
}

void ofxIdentificationMgr::generateCheckStr(string _filename)
{
	ofxXmlSettings xml;
	if (!xml.load(_filename))
	{
		ofLogError("ofxIdentificationMgr") << "load " << _filename << " failed" << endl;
	}
	string source = xml.getValue("SOURCE", "00000000000000000000000000000000");

	string result = ofxHardIdentification::getCheckStr(source);

	xml.clear();
	xml.addValue("RESULT", result);
	xml.save("identificationResult.xml");

	ofLogNotice() << "SOURCE:" << source << endl;
	ofLogNotice() << "RESULT:" << result << endl;
	ofLogNotice() << "build sucess" << endl;
}

void ofxIdentificationMgr::generateCheckStr(string _filename, string _dir)
{
	ofxXmlSettings xml;
	if (!xml.load(_dir + _filename))
	{
		ofLogError("ofxIdentificationMgr") << "load " << _dir << _filename << " failed" << endl;
	}
	string source = xml.getValue("SOURCE", "00000000000000000000000000000000");

	string result = ofxHardIdentification::getCheckStr(source);

	xml.clear();
	xml.addValue("RESULT", result);
	xml.save(_dir + "identificationResult.xml");

	ofLogNotice() << "SOURCE:" << source << endl;
	ofLogNotice() << "RESULT:" << result << endl;
	ofLogNotice() << "build sucess" << endl;
}

void ofxIdentificationMgr::setExtraInfo(string _extraInfoStr)
{
	checkKey = ofToInt(_extraInfoStr);
	ofxHardIdentification::setExtraInfo(_extraInfoStr);
}