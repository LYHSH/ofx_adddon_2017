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
#ifdef UNICODE
		if (MessageBox(HWND_DESKTOP, L"��������δע���ע�����������ָ�����������������������ϵ�����Ӧ�̣�", L"Error", MB_OK | MB_ICONEXCLAMATION))
		{
			ofExit(-3);
		}
#else
		if (MessageBox(HWND_DESKTOP, "��������δע���ע�����������ָ�����������������������ϵ�����Ӧ�̣�", "Error", MB_OK | MB_ICONEXCLAMATION))
		{
			ofExit(-3);
		}
#endif // !UNICODE
		
	}
}

void ofxIdentificationMgr::update()
{
	
}

void ofxIdentificationMgr::generateIdentification()
{
	cout << "Ӳ����Ϣ������..." << endl;
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
	ofxXmlSettings xml;
	xml.load("identificationSource.xml");
	string source = xml.getValue("SOURCE", "00000000000000000000000000000000");

	string result = ofxHardIdentification::getCheckStr(source);

	xml.clear();
	xml.addValue("RESULT", result);
	xml.save("identificationResult.xml");
}

void ofxIdentificationMgr::setExtraInfo(string _extraInfoStr)
{
	checkKey = ofToInt(_extraInfoStr);
	ofxHardIdentification::setExtraInfo(_extraInfoStr);
}