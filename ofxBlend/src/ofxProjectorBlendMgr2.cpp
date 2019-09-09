#include "ofxProjectorBlendMgr2.h"



ofxProjectorBlendMgr2::ofxProjectorBlendMgr2()
{
	dir = "";
}


ofxProjectorBlendMgr2::~ofxProjectorBlendMgr2()
{
}

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


//--------------------------------------------------------------
void ofxProjectorBlendMgr2::setup() {


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

	blender.setup(singleScreenW, singleScreenH, horProjectNums,200,verProjectNums, 200);

	//µ˜ ‘Õº∆¨
	settingImage = new ofImage[6];

	settingImage[0].load(("settingPic/color.png"));
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

	allColor = 2.0f;
	luminance = 0.0f;
	blendPower = 1.0f;
	horOverLayout = 200.0f;
	verOverLayout = 200.0f;

	settingImgIndex = 0;

	loadSetting(getDirPath("gui.xml"));
#pragma endregion UI

	//≥ı ºªØFBO
	video.allocate(getCanvasWidth(), getCanvasHeight(), GL_RGB);
}

//--------------------------------------------------------------
void ofxProjectorBlendMgr2::update() {

}

//--------------------------------------------------------------
void ofxProjectorBlendMgr2::draw() {
	draw(ofVec2f::zero());
}

void ofxProjectorBlendMgr2::draw(ofVec2f _offset)
{
	FBO.begin();
	blender.begin();
	//±≥æ∞Õº
	ofPushMatrix();
	ofClear(0, 0, 0, 0);
	if (-1 != settingImageOrder)
	{
		settingImage[settingImageOrder].draw(0, 0, blender.getCanvasWidth(), blender.getCanvasHeight());
	}
	else
	{
		video.draw(0, 0, blender.getCanvasWidth(), blender.getCanvasHeight());
	}

	ofPopMatrix();
	blender.end();
	blender.draw();
	FBO.end();

	//∆¡ƒªŒ∆¿ÌΩÿ»°
	for (int i = 0; i < verProjectNums; i++)
	{
		for (int j = 0; j < horProjectNums; j++)
		{
			int index = i * horProjectNums + j;
			ofPushStyle();
			fbo[index]->startOffScreen();

			ofClear(0, 0, 0, 0);
			ofPushMatrix();
			ofTranslate(-singleScreenW * j, -singleScreenH * i);
			FBO.draw(0,0);
			ofPopMatrix();
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
}

//--------------------------------------------------------------
void ofxProjectorBlendMgr2::keyPressed(int key) {

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

void ofxProjectorBlendMgr2::setDir(string _dir)
{
	dir = _dir;
}

string ofxProjectorBlendMgr2::getDirPath(string _path)
{
	return dir + _path;
}

void ofxProjectorBlendMgr2::startGrabScreen()
{
	video.begin();
	ofClear(0, 0, 0);
}

void ofxProjectorBlendMgr2::endGrabScreen()
{
	video.end();
}

int ofxProjectorBlendMgr2::getCanvasWidth()
{
	return blender.getCanvasWidth();
}

int ofxProjectorBlendMgr2::getCanvasHeight()
{
	return blender.getCanvasHeight();
}

int ofxProjectorBlendMgr2::getWidth()
{
	return horProjectNums * singleScreenW;
}

int ofxProjectorBlendMgr2::getHeight()
{
	return verProjectNums * singleScreenH;
}

int ofxProjectorBlendMgr2::getChannelNums()
{
	return horProjectNums * verProjectNums;
}

void ofxProjectorBlendMgr2::enableBlendChanged(bool & _value)
{
	blender.showBlend = _value;
}

void ofxProjectorBlendMgr2::allColorChanged(float & _value)
{
	blender.gammaR = _value;
	blender.gammaG = _value;
	blender.gammaB = _value;
	blender.gammaR2 = _value;
	blender.gammaG2 = _value;
	blender.gammaB2 = _value;
}

void ofxProjectorBlendMgr2::luminanceChanged(float & _value)
{
	blender.luminance = _value;
	blender.luminance2 = _value;
}

void ofxProjectorBlendMgr2::blendPowerChanged(float & _value)
{
	blender.blendPower = _value;
	blender.blendPower2 = _value;
}

void ofxProjectorBlendMgr2::horOverLayoutChanged(float & _value)
{
	blender.setHorPixelOverlap(_value);

	video.clear();
	video.allocate(getCanvasWidth(), getCanvasHeight(), GL_RGB);
}

void ofxProjectorBlendMgr2::verOverLayoutChanged(float & _value)
{
	blender.setVerPixelOverlap(_value);

	video.clear();
	video.allocate(getCanvasWidth(), getCanvasHeight(), GL_RGB);
}

void ofxProjectorBlendMgr2::settingImgIndexChanged(int & _order)
{
	settingImageOrder = _order - 1;
}

void ofxProjectorBlendMgr2::loadSetting(string _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);
	EnableBlend = xml.getValue("EDGE_BLEND", EnableBlend);

	allColor = xml.getValue("ALL_COLOR", allColor);
	luminance = xml.getValue("LUMINANCE", luminance);
	blendPower = xml.getValue("BLEND_POWER", blendPower);
	horOverLayout = xml.getValue("HOR_LAYOUT", horOverLayout);
	verOverLayout = xml.getValue("VER_LAYOUT", verOverLayout);

	overLapFlags.resize(xNum);
	for (int i = 0; i < xNum; i++)
	{
		int horIndex = i % horProjectNums;
		int verIndex = i / horProjectNums;
		xml.pushTag("OVER_LAP_FLAG", i);
		bool isLeft = true;
		if (horIndex == 0)
		{
			isLeft = xml.getValue("LEFT", 0);
		}
		else
		{
			isLeft = xml.getValue("LEFT", 1);
		}

		bool isRight = true;
		if (horIndex == (xNum-1)%horProjectNums)
		{
			isRight = xml.getValue("RIGHT", 0);
		}
		else
		{
			isRight = xml.getValue("RIGHT", 1);
		}
		
		bool isTop = true;
		if (verIndex == 0)
		{
			isTop = xml.getValue("TOP", 0);
		}
		else
		{
			isTop = xml.getValue("TOP", 1);
		}
		
		bool isBottom = true;
		if (verIndex == (xNum-1) / horProjectNums)
		{
			isBottom = xml.getValue("BOTTOM", 0);
		}
		else
		{
			isBottom = xml.getValue("BOTTOM", 1);
		}

		blender.setLeftOverLapFlag(i, isLeft);
		blender.setRightOverLapFlag(i, isRight);
		blender.setTopOverLapFlag(i, isTop);
		blender.setBottomOverLapFlag(i, isBottom);

		overLapFlags[i].isLeftOverLap = isLeft;
		overLapFlags[i].isRightOverLap = isRight;
		overLapFlags[i].isTopOverLap = isTop;
		overLapFlags[i].isBottomOverLap = isBottom;

		xml.popTag();
	}


	enableBlendChanged(EnableBlend);
	allColorChanged(allColor);
	luminanceChanged(luminance);
	blendPowerChanged(blendPower);
	horOverLayoutChanged(horOverLayout);
	verOverLayoutChanged(verOverLayout);
}

void ofxProjectorBlendMgr2::saveSetting(string _filename)
{
	ofxXmlSettings xml;
	xml.addValue("EDGE_BLEND", EnableBlend ? 1 : 0);

	xml.addValue("ALL_COLOR", allColor);
	xml.addValue("LUMINANCE", luminance);
	xml.addValue("BLEND_POWER", blendPower);
	xml.addValue("HOR_LAYOUT", horOverLayout);
	xml.addValue("VER_LAYOUT", verOverLayout);

	for (int i = 0; i < overLapFlags.size(); i++)
	{
		xml.addTag("OVER_LAP_FLAG");
		xml.pushTag("OVER_LAP_FLAG", i);
		xml.addValue("LEFT", overLapFlags[i].isLeftOverLap ? 1 : 0);
		xml.addValue("RIGHT", overLapFlags[i].isRightOverLap ? 1 : 0);
		xml.addValue("TOP", overLapFlags[i].isTopOverLap ? 1 : 0);
		xml.addValue("BOTTOM", overLapFlags[i].isBottomOverLap ? 1 : 0);
		xml.popTag();
	}

	xml.save(_filename);
}

void ofxProjectorBlendMgr2::showSettingWindow(bool & _bOpen)
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

	if (ImGui::CollapsingHeader("setting"))
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(1 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("AllColor", &allColor, 0.0f, 4.0f))
		{
			allColorChanged(allColor);
		}
		ImGui::PopStyleColor(2);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(2 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("Luminance", &luminance, -1.0f, 1.0f))
		{
			luminanceChanged(luminance);
		}
		ImGui::PopStyleColor(2);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("BlendPower", &blendPower, 0.0f, 5.0f))
		{
			blendPowerChanged(blendPower);
		}
		ImGui::PopStyleColor(2);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("horLayout", &horOverLayout, 0.0f, blender.singleChannelWidth))
		{
			horOverLayoutChanged(horOverLayout);
		}
		ImGui::PopStyleColor(2);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(5 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f));
		if (ImGui::SliderFloat("verLayout", &verOverLayout, 0.0f, blender.singleChannelHeight))
		{
			verOverLayoutChanged(verOverLayout);
		}
		ImGui::PopStyleColor(2);
	}

	const char* items[] = { "VIDEO", "COLOR", "GRID","WHITE", "RED","GREEN","BLUE" };
	if (ImGui::Combo("Combo", &settingImgIndex, items, IM_ARRAYSIZE(items)))
	{
		settingImgIndexChanged(settingImgIndex);
	}

	if (ImGui::TreeNode("SINGLE_SCREEN_INDEX"))
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
				blender.setLeftOverLapFlag(editOrder, overLapFlags[editOrder].isLeftOverLap);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("right", &overLapFlags[editOrder].isRightOverLap))
			{
				blender.setRightOverLapFlag(editOrder, overLapFlags[editOrder].isRightOverLap);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("top", &overLapFlags[editOrder].isTopOverLap))
			{
				blender.setTopOverLapFlag(editOrder, overLapFlags[editOrder].isTopOverLap);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("bottom", &overLapFlags[editOrder].isBottomOverLap))
			{
				blender.setBottomOverLapFlag(editOrder, overLapFlags[editOrder].isBottomOverLap);
			}

		}

		ImGui::EndChild();

		ImGui::TreePop();
	}



	if (ImGui::TreeNode("SHOW_SETTING"))
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

