#include "projectBlendIniter.h"
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

string const RES_1024x768 = "1024x768";
string const RES_768x1024 = "768x1024";
string const RES_1400x1050 = "1400x1050";
string const RES_1050x1400 = "1050x1400";
string const RES_1440x900 = "1440x900";
string const RES_900x1440 = "900x1440";
string const RES_1920x1080 = "1920x1080";
string const RES_1080x1920 = "1080x1920";
string const RES_1920x1200 = "1920x1200";
string const RES_1200x1920 = "1200x1920";


projectBlendIniter::projectBlendIniter()
{
}


projectBlendIniter::~projectBlendIniter()
{
}

void projectBlendIniter::setup()
{


	horProjectNums = 1;
	verProjectNums = 1;
	singleScreenW = 1024;
	singleScreenH = 768;
	gridPicPath = "gridPic/";

	bVisible = false;
}

void projectBlendIniter::update()
{

}

void projectBlendIniter::draw()
{
	ImGui::SetNextWindowSize(ImVec2(400, 480), ImGuiSetCond_FirstUseEver);
	ImGui::Begin(titleStr.c_str(),&bVisible);
	ImGui::NewLine();
	ImGui::NewLine();

	const char* items[] = {
		RES_1024x768.c_str(), RES_768x1024.c_str(),
		RES_1400x1050.c_str(),RES_1050x1400.c_str(),
		RES_1440x900.c_str(),RES_900x1440.c_str(),
		RES_1920x1080.c_str(),RES_1080x1920.c_str(),
		RES_1920x1200.c_str(), RES_1200x1920.c_str()
	};
	ImGui::Spacing();
	ImGui::SliderInt("hor project nums:", &horProjectNums, 1, 9);
	ImGui::Spacing();
	ImGui::SliderInt("ver project nums:", &verProjectNums, 1, 4);
	ImGui::Spacing();
	if (ImGui::Combo("Resolution", &resolutionIndex, items, IM_ARRAYSIZE(items)))
	{
		handleResolutionSetting(items[resolutionIndex]);
	}
	ImGui::NewLine();
	ImGui::NewLine();
	if (ImGui::Button("generate", ofVec2f(200, 100)))
	{
		int res = MessageBox(NULL, TEXT("原有数据将会被覆盖，确认初始化数据么？"), TEXT("提示"), MB_OKCANCEL);
		if (res == IDOK)
		{
			handleDataSave();
		}
	}
	ImGui::NewLine();
	ImGui::NewLine();
	if (ImGui::Button("return", ofVec2f(200, 100)))
	{
		ofSendMessage("return_btn_touch");
	}

	ImGui::End();
}

void projectBlendIniter::setDir(string _dir)
{
	dataDir = _dir;
}

string projectBlendIniter::getDir()
{
	return dataDir;
}

string projectBlendIniter::getDirPath(string _path)
{
	return dataDir + _path;
}

void projectBlendIniter::setTitle(string _str)
{
	titleStr = _str;
}

void projectBlendIniter::setVisible(bool _flag)
{
	bVisible = _flag;
}

void projectBlendIniter::showGui(bool & _flag)
{
	if (!_flag)return;

	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = true;
	static bool no_resize = true;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)       window_flags |= ImGuiWindowFlags_NoNav;
	if (no_close)     _flag = NULL; // Don't pass our bool* to Begin


	ImGui::SetNextWindowSize(ImVec2(400, 480), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(450, 20), ImGuiCond_Always);
	ImGui::Begin(titleStr.c_str(), &_flag, window_flags);
	ImGui::NewLine();
	ImGui::NewLine();

	const char* items[] = {
		RES_1024x768.c_str(), RES_768x1024.c_str(),
		RES_1400x1050.c_str(),RES_1050x1400.c_str(),
		RES_1440x900.c_str(),RES_900x1440.c_str(),
		RES_1920x1080.c_str(),RES_1080x1920.c_str(),
		RES_1920x1200.c_str(), RES_1200x1920.c_str()
	};
	ImGui::Spacing();
	ImGui::SliderInt("hor project nums:", &horProjectNums, 1, 9);
	ImGui::Spacing();
	ImGui::SliderInt("ver project nums:", &verProjectNums, 1, 4);
	ImGui::Spacing();
	if (ImGui::Combo("Resolution", &resolutionIndex, items, IM_ARRAYSIZE(items)))
	{
		handleResolutionSetting(items[resolutionIndex]);
	}
	ImGui::NewLine();
	ImGui::NewLine();

	if (ImGui::Button("generate", ofVec2f(200, 100)))
	{
		int res = MessageBox(NULL, TEXT("原有数据将会被覆盖，确认初始化数据么？"), TEXT("提示"), MB_OKCANCEL);
		if (res == IDOK)
		{
			handleDataSave();
		}
		
	}

	ImGui::End();
}

void projectBlendIniter::handleResolutionSetting(string _theme)
{
	if (_theme == RES_1024x768)
	{
		singleScreenW = 1024;
		singleScreenH = 768;
	}
	else if (_theme == RES_768x1024)
	{
		singleScreenW = 768;
		singleScreenH = 1024;
	}
	else if (_theme == RES_1400x1050)
	{
		singleScreenW = 1400;
		singleScreenH = 1050;
	}
	else if (_theme == RES_1050x1400)
	{
		singleScreenW = 1050;
		singleScreenH = 1400;
	}
	else if (_theme == RES_1440x900)
	{
		singleScreenW = 1440;
		singleScreenH = 900;
	}
	else if (_theme == RES_900x1440)
	{
		singleScreenW = 900;
		singleScreenH = 1440;
	}
	else if (_theme == RES_1920x1080)
	{
		singleScreenW = 1920;
		singleScreenH = 1080;
	}
	else if (_theme == RES_1080x1920)
	{
		singleScreenW = 1080;
		singleScreenH = 1920;
	}
	else if (_theme == RES_1920x1200)
	{
		singleScreenW = 1920;
		singleScreenH = 1200;
	}
	else if (_theme == RES_1200x1920)
	{
		singleScreenW = 1200;
		singleScreenH = 1920;
	}
}

void projectBlendIniter::handleDataSave()
{
	//删除旧有数据
	ofFile file(getDir());
	if (file.exists())
	{
		file.remove(true);
	}

	ofDirectory dir;
	dir.listDir(getDir());
	if (!dir.exists())
	{
		dir.create(true);
	}
	//网格数据
	{
		ofDirectory dir;
		dir.listDir(getDirPath("surface/"));
		if (!dir.exists())
		{
			dir.create(true);
		}
		vector<Surfaces> sfs;
		int xNum = horProjectNums * verProjectNums;
		sfs.resize(xNum);
		for (int i = 0; i < verProjectNums; i++)
		{
			for (int j = 0; j < horProjectNums; j++)
			{
				int index = i * horProjectNums + j;
				sfs[index].initSurfacePara(getDirPath("surface/surface" + ofToString(index) + ".xml"), 2, 2,
					j * singleScreenW, i * singleScreenH, (j + 1) * singleScreenW, (i + 1) * singleScreenH);

				sfs[index].saveToXML();
			}
		}
	}


	{
		//融合基础配置
		ofxXmlSettings blendxml;
		if (blendxml.load(getDirPath("blend.xml")))
		{
			blendxml.setValue("H_PROJECT_NUMS", horProjectNums);
			blendxml.setValue("V_PROJECT_NUMS", verProjectNums);
			blendxml.setValue("SINGLE_SCREEN_WIDTH", singleScreenW);
			blendxml.setValue("SINGLE_SCREEN_HEIGHT", singleScreenH);

			gridPicPath = "gridPic/" + ofToString(horProjectNums) + "x" + ofToString(verProjectNums) + ".png";
			blendxml.setValue("GRID_PIC", gridPicPath);

			blendxml.saveFile();
		}
		else
		{
			blendxml.addValue("H_PROJECT_NUMS", horProjectNums);
			blendxml.addValue("V_PROJECT_NUMS", verProjectNums);
			blendxml.addValue("SINGLE_SCREEN_WIDTH", singleScreenW);
			blendxml.addValue("SINGLE_SCREEN_HEIGHT", singleScreenH);

			blendxml.addValue("SHOW_SCALE", 1.0f);

			gridPicPath = "gridPic/" + ofToString(horProjectNums) + "x" + ofToString(verProjectNums) + ".png";
			blendxml.addValue("GRID_PIC", gridPicPath);
			blendxml.save(getDirPath("blend.xml"));
		}
	}

}
