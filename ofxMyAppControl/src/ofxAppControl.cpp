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

	//标注是否获取到有效数据
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

	//自动创建配置文件
	{
		ofFile file(filePath);
		if (!file.exists())
		{
			file.create();
			file.close();
		}
	}

	//自动为配置文件填充数据
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
