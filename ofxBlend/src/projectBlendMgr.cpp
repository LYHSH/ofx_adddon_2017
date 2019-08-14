#include "projectBlendMgr.h"



projectBlendMgr::projectBlendMgr()
{
	dir = "";
}


projectBlendMgr::~projectBlendMgr()
{
}


#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


//--------------------------------------------------------------
void projectBlendMgr::setup() {


	ofxXmlSettings blendxml;
	if (!blendxml.load(getDirPath("blend.xml")))
	{
		int res = MessageBox(NULL, TEXT("»⁄∫œ≈‰÷√Œƒº˛»± ß£°£°£°"), TEXT("¥ÌŒÛæØ∏Ê"), MB_OK);
		if (res)
		{
			ofExit(-1);
		}
	}

	horProjectNums = blendxml.getValue("H_PROJECT_NUMS", 1);
	verProjectNums = blendxml.getValue("V_PROJECT_NUMS", 1);
	singleScreenW = blendxml.getValue("SINGLE_SCREEN_WIDTH", 1920.0f);
	singleScreenH = blendxml.getValue("SINGLE_SCREEN_HEIGHT", 1080.0f);
	initXml = blendxml.getValue("INIT_XML", 0);
	showScale = blendxml.getValue("SHOW_SCALE", 1.0f);
	gridPicPath = blendxml.getValue("GRID_PIC", "settingPic / grid.png");

	blenderH.setup(singleScreenW, singleScreenH * verProjectNums, horProjectNums, 200, ofxProjectorBlend_Horizontal);
	blenderV.setup(singleScreenW * horProjectNums, singleScreenH, verProjectNums, 200, ofxProjectorBlend_Vertical);

	//µ˜ ‘Õº∆¨
	settingImage = new ofImage[6];
// 	settingImage[0].loadImage(getDirPath("settingPic/color.png"));
// //	settingImage[1].loadImage(getDirPath("settingPic/grid.png"));
// 	settingImage[1].loadImage(getDirPath(gridPicPath));
// 	settingImage[2].loadImage(getDirPath("settingPic/white.png"));
// 	settingImage[3].loadImage(getDirPath("settingPic/red.png"));
// 	settingImage[4].loadImage(getDirPath("settingPic/green.png"));
// 	settingImage[5].loadImage(getDirPath("settingPic/blue.png"));

	settingImage[0].load(("settingPic/color.png"));
	//	settingImage[1].loadImage(getDirPath("settingPic/grid.png"));
	settingImage[1].load((gridPicPath));
	settingImage[2].load(("settingPic/white.png"));
	settingImage[3].load(("settingPic/red.png"));
	settingImage[4].load(("settingPic/green.png"));
	settingImage[5].load(("settingPic/blue.png"));
	settingImageOrder = -1;

	//«˙√Ê
	xNum = horProjectNums * verProjectNums;
	sf.resize(xNum);
	for (int i = 0; i < verProjectNums; i++)
	{
		for (int j = 0; j < horProjectNums; j++)
		{
			int index = i * horProjectNums + j;
			sf[index] = new Surfaces();
			if (initXml)
			{
				sf[index]->initSurfacePara(getDirPath("surface/surface" + ofToString(index) + ".xml"), 2, 2,
					j * singleScreenW, i * singleScreenH, (j + 1) * singleScreenW, (i + 1) * singleScreenH);
			}
			else
			{
				sf[index]->readFromXML(getDirPath("surface/surface" + ofToString(index) + ".xml"));
			}

			sf[index]->displayControlPoint(false);
		}
	}
	editOrder = -1;

	FBO.allocate(singleScreenW * horProjectNums, singleScreenH * verProjectNums, GL_RGB);
	verFBO.allocate(singleScreenW * horProjectNums, singleScreenH * verProjectNums, GL_RGB);
	fbo.resize(xNum);
	for (int i = 0; i < xNum; i++)
	{
		fbo[i] = new fboTexture();
		fbo[i]->setup(singleScreenW, singleScreenH);
		fbo[i]->initFBOTexture();
	}

	sfShows.resize(xNum);
	for (int i = 0; i < xNum; i++)
	{
		sfShows[i] = new bool;
		*sfShows[i] = true;
	}
#pragma region UI

	EnableBlend = true;

	horAllColor = 2.0f;
	horLuminance = 0.0f;
	horBlendPower = 1.0f;
	horLayout = 200.0f;


	verAllColor = 2.0f;
	verLuminance = 0.0f;
	verBlendPower = 1.0f;
	verLayout = 200.0f;

	settingImgIndex = 0;

	loadSetting(getDirPath("gui.xml"));
#pragma endregion UI

	//≥ı ºªØFBO
	video.allocate(getCanvasWidth(), getCanvasHeight(), GL_RGB);
}

//--------------------------------------------------------------
void projectBlendMgr::update() {
	
}

//--------------------------------------------------------------
void projectBlendMgr::draw() {
	draw(ofVec2f::zero());
}

void projectBlendMgr::draw(ofVec2f _offset)
{
	FBO.begin();
	blenderV.begin();
	//±≥æ∞Õº
	ofPushMatrix();
	ofClear(0, 0, 0, 0);
	if (-1 != settingImageOrder)
	{
		settingImage[settingImageOrder].draw(0, 0, blenderV.getCanvasWidth(), blenderV.getCanvasHeight());
	}
	else
	{
		video.draw(0, 0, blenderV.getCanvasWidth(), blenderV.getCanvasHeight());
		//video.draw(0, 0);
	}

	ofPopMatrix();
	blenderV.end();
	blenderV.draw();
	FBO.end();


	verFBO.begin();
	blenderH.begin();
	ofPushMatrix();
	FBO.draw(0, 0, blenderH.getCanvasWidth(), blenderH.getCanvasHeight());
	ofPopMatrix();
	blenderH.end();
	blenderH.draw();
	verFBO.end();

	//∆¡ƒªŒ∆¿ÌΩÿ»°
	for (int i = 0; i < verProjectNums; i++)
	{
		for (int j = 0; j < horProjectNums; j++)
		{
			int index = i * horProjectNums + j;
			ofPushStyle();
			fbo[index]->startOffScreen();

			ofClear(0, 0, 0, 0);
			blenderH.draw(-singleScreenW*j, -singleScreenH * i);

			fbo[index]->endOffScreen();
			ofPopStyle();
		}
	}
	//œ‘ æ
	ofPushMatrix();
	ofScale(showScale, showScale);
	ofTranslate(_offset);

	for (int i = 0; i < xNum; i++)
	{
		if (*sfShows[i])
		{
			sf[i]->updateSurface();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, fbo[i]->glfboTexID);
			sf[i]->drawSurface();
			glDisable(GL_TEXTURE_2D);
		}
	}
	ofPopMatrix();

//	showSettingWindow(bShowGui);
}

//--------------------------------------------------------------
void projectBlendMgr::keyPressed(int key) {

	if (sf.size() && editOrder >= 0 && editOrder < (int)sf.size())
	{
		sf[editOrder]->keyPressed(key);

	}
	if (key == '`' || key == '~')
	{
		editOrder = -1;
	}
	else
	{
		for (size_t i = 0; i < sf.size(); i++)
		{
			if (('1' + i) == key)
			{
				editOrder = i;
			}
		}
	}
}

void projectBlendMgr::setDir(string _dir)
{
	dir = _dir;
}

string projectBlendMgr::getDirPath(string _path)
{
	return dir + _path;
}

void projectBlendMgr::startGrabScreen()
{
	video.begin();
	ofClear(0, 0, 0);
}

void projectBlendMgr::endGrabScreen()
{
	video.end();
}

int projectBlendMgr::getCanvasWidth()
{
	return blenderV.getCanvasWidth();
}

int projectBlendMgr::getCanvasHeight()
{
	return blenderV.getCanvasHeight();
}

int projectBlendMgr::getWidth()
{
	return horProjectNums * singleScreenW;
}

int projectBlendMgr::getHeight()
{
	return verProjectNums * singleScreenH;
}

int projectBlendMgr::getChannelNums()
{
	return horProjectNums * verProjectNums;
}

void projectBlendMgr::enableBlendChanged(bool & _value)
{
	blenderH.showBlend = _value;
	blenderV.showBlend = _value;
}

void projectBlendMgr::horAllColorChanged(float & _value)
{
	blenderH.gammaR = _value;
	blenderH.gammaG = _value;
	blenderH.gammaB = _value;
	blenderH.gammaR2 = _value;
	blenderH.gammaG2 = _value;
	blenderH.gammaB2 = _value;
}

void projectBlendMgr::horLuminanceChanged(float & _value)
{
	blenderH.luminance = _value;
	blenderH.luminance2 = _value;
}

void projectBlendMgr::horBlendPowerChanged(float & _value)
{
	blenderH.blendPower = _value;
	blenderH.blendPower2 = _value;
}

void projectBlendMgr::horhorLayoutChanged(float & _value)
{
	blenderH.setPixelOverlap(_value);

	video.clear();
	video.allocate(getCanvasWidth(), getCanvasHeight(), GL_RGB);
}

void projectBlendMgr::verAllColorChanged(float & _value)
{
	blenderV.gammaR = _value;
	blenderV.gammaG = _value;
	blenderV.gammaB = _value;
	blenderV.gammaR2 = _value;
	blenderV.gammaG2 = _value;
	blenderV.gammaB2 = _value;
}

void projectBlendMgr::verLuminanceChanged(float & _value)
{
	blenderV.luminance = _value;
	blenderV.luminance2 = _value;
}

void projectBlendMgr::verBlendPowerChanged(float & _value)
{
	blenderV.blendPower = _value;
	blenderV.blendPower2 = _value;
}

void projectBlendMgr::verhorLayoutChanged(float & _value)
{
	blenderV.setPixelOverlap(_value);

	video.clear();
	video.allocate(getCanvasWidth(), getCanvasHeight(), GL_RGB);
}

void projectBlendMgr::settingImgIndexChanged(int & _order)
{
	settingImageOrder = _order - 1;
}

void projectBlendMgr::loadSetting(string _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);
	EnableBlend = xml.getValue("EDGE_BLEND", EnableBlend);

	horAllColor = xml.getValue("HOR_ALL_COLOR", horAllColor);
	horLuminance = xml.getValue("HOR_LUMINANCE", horLuminance);
	horBlendPower = xml.getValue("HOR_BLEND_POWER", horBlendPower);
	horLayout = xml.getValue("HOR_LAYOUT", horLayout);

	verAllColor = xml.getValue("VER_ALL_COLOR", verAllColor);
	verLuminance = xml.getValue("VER_LUMINANCE", verLuminance);
	verBlendPower = xml.getValue("VER_BLEND_POWER", verBlendPower);
	verLayout = xml.getValue("VER_LAYOUT", verLayout);

	overLapFlags.resize(xNum);
	for (int i = 0; i< xNum;i++)
	{
		xml.pushTag("OVER_LAP_FLAG", i);
		bool isLeft = xml.getValue("LEFT", 0);
		bool isRight = xml.getValue("RIGHT", 0);
		bool isTop = xml.getValue("TOP", 0);
		bool isBottom = xml.getValue("BOTTOM", 0);

		blenderH.setLeftOverLapFlag(i, isLeft);
		blenderH.setRightOverLapFlag(i,isRight);

		blenderV.setTopOverLapFlag(i, isTop);
		blenderV.setBottomOverLapFlag(i, isBottom);

		overLapFlags[i].isLeftOverLap = isLeft;
		overLapFlags[i].isRightOverLap = isRight;
		overLapFlags[i].isTopOverLap = isTop;
		overLapFlags[i].isBottomOverLap = isBottom;
		xml.popTag();
	}


	enableBlendChanged(EnableBlend);
	horAllColorChanged(horAllColor);
	horLuminanceChanged(horLuminance);
	horBlendPowerChanged(horBlendPower);
	horhorLayoutChanged(horLayout);

	verAllColorChanged(verAllColor);
	verLuminanceChanged(verLuminance);
	verBlendPowerChanged(verBlendPower);
	verhorLayoutChanged(verLayout);
}

void projectBlendMgr::saveSetting(string _filename)
{
	ofxXmlSettings xml;
	xml.addValue("EDGE_BLEND", EnableBlend ? 1 : 0);

	xml.addValue("HOR_ALL_COLOR", horAllColor);
	xml.addValue("HOR_LUMINANCE", horLuminance);
	xml.addValue("HOR_BLEND_POWER", horBlendPower);
	xml.addValue("HOR_LAYOUT", horLayout);

	xml.addValue("VER_ALL_COLOR", verAllColor);
	xml.addValue("VER_LUMINANCE", verLuminance);
	xml.addValue("VER_BLEND_POWER", verBlendPower);
	xml.addValue("VER_LAYOUT", verLayout);

	for (int i = 0; i < overLapFlags.size(); i++)
	{
		xml.addTag("OVER_LAP_FLAG");
		xml.pushTag("OVER_LAP_FLAG", i);
		xml.addValue("LEFT", overLapFlags[i].isLeftOverLap?1:0);
		xml.addValue("RIGHT", overLapFlags[i].isRightOverLap ? 1 : 0);
		xml.addValue("TOP", overLapFlags[i].isTopOverLap ? 1 : 0);
		xml.addValue("BOTTOM", overLapFlags[i].isBottomOverLap ? 1 : 0);
		xml.popTag();
	}

	xml.save(_filename);
}

void projectBlendMgr::showSettingWindow(bool & _bOpen)
{
	if (!_bOpen)return;
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
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
	if (no_close)     _bOpen = NULL; // Don't pass our bool* to Begin

	ImGui::SetNextWindowSize(ImVec2(400, 480), ImGuiSetCond_Once);

	string guiName = getDirPath("blendMgr");
	ImGui::Begin(guiName.c_str(), &_bOpen, window_flags);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("MENU"))
		{
			if (ImGui::MenuItem("save", NULL))
			{
				saveSetting(getDirPath("gui.xml"));
				for (size_t i = 0; i < sf.size(); i++)
				{
					sf[i]->saveToXML();
				}
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}


	ImGui::Text("Press 'h' show UI");
	ImGui::Text("FPS:%.3f", ofGetFrameRate());

	if (ImGui::Checkbox("edgeBlend", &EnableBlend))
	{
		enableBlendChanged(EnableBlend);
	}

	if (horProjectNums > 0 && ImGui::CollapsingHeader("horizontal"))
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(1 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("horAllColor", &horAllColor, 0.0f, 4.0f))
		{
			horAllColorChanged(horAllColor);
		}
		ImGui::PopStyleColor(2);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(2 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("horLuminance", &horLuminance, -1.0f, 1.0f))
		{
			horLuminanceChanged(horLuminance);
		}
		ImGui::PopStyleColor(2);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("horBlendPower", &horBlendPower, 0.0f, 5.0f))
		{
			horBlendPowerChanged(horBlendPower);
		}
		ImGui::PopStyleColor(2);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("horLayout", &horLayout, 0.0f, blenderH.singleChannelWidth))
		{
			horhorLayoutChanged(horLayout);
		}
		ImGui::PopStyleColor(2);
	}

	if (verProjectNums > 1 && ImGui::CollapsingHeader("vertical"))
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(1 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("verAllColor", &verAllColor, 0.0f, 4.0f))
		{
			verAllColorChanged(verAllColor);
		}
		ImGui::PopStyleColor(2);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(2 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("verLuminance", &verLuminance, -1.0f, 1.0f))
		{
			verLuminanceChanged(verLuminance);
		}
		ImGui::PopStyleColor(2);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("verBlendPower", &verBlendPower, 0.0f, 5.0f))
		{
			verBlendPowerChanged(verBlendPower);
		}
		ImGui::PopStyleColor(2);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));

		if (ImGui::SliderFloat("verLayout", &verLayout, 0.0f, blenderV.singleChannelHeight))
		{
			verhorLayoutChanged(verLayout);
		}
		ImGui::PopStyleColor(2);
	}

	const char* items[] = { "VIDEO", "COLOR", "GRID","WHITE", "RED","GREEN","BLUE" };
	if (ImGui::Combo("Combo", &settingImgIndex, items, IM_ARRAYSIZE(items)))
	{
		settingImgIndexChanged(settingImgIndex);
	}

	if (ImGui::TreeNode("SETTING_SCALE"))
	{
		ImGui::BeginChild("#colors", ImVec2(400, 120), true, ImGuiWindowFlags_HorizontalScrollbar);
		for (int i = 0; i < verProjectNums; i++)
		{
			for (int j = 0; j < horProjectNums; j++)
			{
				int index = i * horProjectNums + j;
				string name = "project:" + ofToString(index + 1);
				bool & bshow = *sfShows[index];
				ImGui::RadioButton(name.c_str(), &editOrder, index);
				ImGui::SameLine();
			}
			ImGui::NewLine();
		}

		if (editOrder != -1)
		{
			if (ImGui::Checkbox("left", &overLapFlags[editOrder].isLeftOverLap))
			{
				blenderH.setLeftOverLapFlag(editOrder, overLapFlags[editOrder].isLeftOverLap);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("right", &overLapFlags[editOrder].isRightOverLap))
			{
				blenderH.setRightOverLapFlag(editOrder, overLapFlags[editOrder].isRightOverLap);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("top", &overLapFlags[editOrder].isTopOverLap))
			{
				blenderH.setTopOverLapFlag(editOrder, overLapFlags[editOrder].isTopOverLap);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("bottom", &overLapFlags[editOrder].isBottomOverLap))
			{
				blenderH.setBottomOverLapFlag(editOrder, overLapFlags[editOrder].isBottomOverLap);
			}
			
		}

		ImGui::EndChild();

		ImGui::TreePop();
	}

	

	if (ImGui::TreeNode("SHOW_CONTROLE"))
	{
		ImGui::BeginChild("#colors1", ImVec2(400, 120), true, ImGuiWindowFlags_HorizontalScrollbar);
		for (int i = 0; i < verProjectNums; i++)
		{
			for (int j = 0; j < horProjectNums; j++)
			{
				int index = i * horProjectNums + j;
				string name = "project:" + ofToString(index + 1);
				bool & bshow = *sfShows[index];
				ImGui::Checkbox(name.c_str(), &bshow);
				ImGui::SameLine();
			}
			ImGui::NewLine();
		}
		ImGui::EndChild();

		ImGui::TreePop();
	}

	ImGui::End();
}

