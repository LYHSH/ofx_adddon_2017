#include "ofxPageBackFactory.h"
#include "ofxImagePageBack.h"
#include "ofxVideoPageBack.h"
#include "ofxNullPageBack.h"


ofxPageBackFactory::ofxPageBackFactory()
{
}


ofxPageBackFactory::~ofxPageBackFactory()
{
}

ofxPageBack * ofxPageBackFactory::createVideoPageBack(string _videoPath)
{
	ofxVideoPageBack * back = new ofxVideoPageBack();
	back->setup(_videoPath);
	return back;
}

ofxPageBack * ofxPageBackFactory::createImagePageBack(string _imgPath)
{
	ofxImagePageBack * back = new ofxImagePageBack();
	back->setup(_imgPath);
	return back;
}

ofxPageBack * ofxPageBackFactory::createNullPageBack(string _path)
{
	ofxNullPageBack * back = new ofxNullPageBack();
	back->setup(_path);
	return back;
}