#include "maskVideoPlayer.h"



maskVideoPlayer::maskVideoPlayer()
{
	ofDirectory maskImgDir;
	maskImgDir.listDir("mask/");
	maskImgDir.sort();
	maskimgPaths.resize(maskImgDir.size());
	for (int i = 0; i < maskimgPaths.size(); i++)
	{
		maskimgPaths[i] = maskImgDir.getPath(i);
	}
	if (maskimgPaths.size())
	{
		maskImg.loadImage(maskimgPaths[0]);
	}


	{
		ofxXmlSettings xml;
		xml.load("rotate.xml");
		angle = xml.getValue("angle", 0);
		scale = xml.getValue("scale", 1.0f);
	}
}


maskVideoPlayer::~maskVideoPlayer()
{
}

void maskVideoPlayer::draw(float x, float y, float width, float height)
{
	ofPushMatrix();
 	ofTranslate(x + width / 2.0f, y + height / 2.0f);
 	ofRotateZ(angle);
	ofScale(scale, scale);
 	ofTranslate(x- width / 2.0f, y-height / 2.0f);
// 	
	videoPlayer::draw(x, y, width, height);
	ofPopMatrix();
	
	if (maskImg.isAllocated())
	{
		maskImg.draw(x, y, width, height);
	}
	
}

void maskVideoPlayer::reloadVideo(int _index)
{
	videoPlayer::reloadVideo(_index);
	if (_index >= 0 && _index < maskimgPaths.size())
	{
		maskImg.clear();
		maskImg.load(maskimgPaths[_index]);
	}
}

void maskVideoPlayer::keyPressed(int key)
{
	videoPlayer::keyPressed(key);
	if ('i' == key)
	{
		//rotateAngle = ofClamp(++rotateAngle,0,360);
		angle++;
	}
	else if ('o' == key)
	{
		//rotateAngle = ofClamp(--rotateAngle, 0, 360);
		angle--;
	}
	if ('y' == key)
	{
		//rotateAngle = ofClamp(++rotateAngle,0,360);
		scale += 0.01f;
	}
	else if ('u' == key)
	{
		//rotateAngle = ofClamp(--rotateAngle, 0, 360);
		scale -= 0.01f;
	}
	else if ('s' == key)
	{
		ofxXmlSettings xml;
		xml.load("rotate.xml");
		xml.setValue("angle", angle);
		xml.setValue("scale", scale);
		xml.saveFile();
	}
}
