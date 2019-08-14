#include "ofxAppControl.h"


string ofxAppControl::fileDir = "ofxAppControl/";
HWND ofxAppControl::thiswnd = nullptr;
bool ofxAppControl::bShow = false;
ofxAppControl::ofxAppControl()
{
}


ofxAppControl::~ofxAppControl()
{
}

void ofxAppControl::setup(string _titleName)
{
	string filePath = fileDir + "setting.xml";
	bool loadSucess = true;
	ofxXmlSettings xml;

	//��ע�Ƿ��ȡ����Ч����
	loadSucess &= xml.load(filePath);
	loadSucess &= (xml.getNumTags("SHOW") > 0);

	bShow = xml.getValue("SHOW", 1);

	if (!bShow)
	{
		thiswnd = WindowFromDC(wglGetCurrentDC());
		ShowWindow(thiswnd, SW_HIDE);
		UpdateWindow(thiswnd);
		FreeConsole();

		ofLogToFile("log.log");
	}
	else
	{
		ofSetWindowTitle(_titleName);
	}

	//�Զ����������ļ�
	{
		ofFile file(filePath);
		if (!file.exists())
		{
			file.create();
			file.close();
		}
	}

	//�Զ�Ϊ�����ļ��������
	{
		if (!loadSucess)
		{
			ofxXmlSettings xml;
			xml.addValue("SHOW", 1);
			xml.save(filePath);
		}
	}
	

}

void ofxAppControl::udpate()
{
	if (!bShow)
	{
		ShowWindow(thiswnd, SW_HIDE);
		UpdateWindow(thiswnd);
	}
}

bool ofxAppControl::isShowing()
{
	return bShow;
}
