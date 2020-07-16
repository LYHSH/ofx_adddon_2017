#include "ofxRemoteVideoControlMgr.h"
#include "ofxXmlSettings.h"


ofxRemoteVideoControlMgr::ofxRemoteVideoControlMgr()
{
}


ofxRemoteVideoControlMgr::~ofxRemoteVideoControlMgr()
{
	for (unsigned int  i = 0; i < controler.size(); i++)
	{
		auto & arrObj = controler[i];
		for each (auto var in arrObj)
		{
			delete var;
			var = NULL;
		}
	}
	controler.clear();
}

void ofxRemoteVideoControlMgr::setup(const string & _filename)
{
	ofxXmlSettings xml;
	bool isLoad =  xml.load(_filename);
	if (!isLoad)
	{
		xml.addTag("video");
		xml.pushTag("video", 0);
		xml.addValue("IP", "127.0.0.1");
		xml.popTag();
		xml.saveFile(_filename);

		return;
	}


	int nums = xml.getNumTags("video");
	controler.resize(nums);
	for (unsigned int i = 0; i < controler.size(); i++)
	{
		xml.pushTag("video", i);
		int ipNums = xml.getNumTags("IP");
		controler[i].resize(ipNums);
		for (int ipIndex = 0; ipIndex < ipNums; ipIndex++)
		{
			controler[i][ipIndex] = new ofxRemoteVideoControl();
			controler[i][ipIndex]->setup(xml.getValue("IP", "",ipIndex));
		}
		
		xml.popTag();
	}

	ofLogNotice(OF_FUNCTION_NAME) << "REMOTE VIDEO NUMS:" << controler.size() << endl;
}

void ofxRemoteVideoControlMgr::play(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->play();
	}
}

void ofxRemoteVideoControlMgr::play(int _index, int _videoIndex)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->play(_videoIndex);
	}
}

void ofxRemoteVideoControlMgr::pause(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->pause();
	}
}

void ofxRemoteVideoControlMgr::stop(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->stop();
	}
}

void ofxRemoteVideoControlMgr::replay(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->rePlay();
	}
}

void ofxRemoteVideoControlMgr::volumeAdd(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->volumeAdd();
	}
}

void ofxRemoteVideoControlMgr::volumeSub(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->volumeSub();
	}
}

void ofxRemoteVideoControlMgr::mute(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->mute();
	}
}

void ofxRemoteVideoControlMgr::unmute(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->unMute();
	}
}

void ofxRemoteVideoControlMgr::playNextMoive(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->playNextMovie();
	}
}

void ofxRemoteVideoControlMgr::playPrevMoive(int _index)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->playPrevMovie();
	}
}

void ofxRemoteVideoControlMgr::setActive(int _index, bool _state)
{
	if (!checkOut(_index))return;

	auto & arrObj = controler[_index];
	for each (auto var in arrObj)
	{
		var->setActive(_state);
	}
}



string ofxRemoteVideoControlMgr::getIP(int _index)const
{
	if (!checkOut(_index))return "";

	auto & arrObj = controler[_index];
	return arrObj[0]->getIP();
}

vector<string> ofxRemoteVideoControlMgr::getIPs(int _index)const
{
	vector<string> ips;
	if (!checkOut(_index))return ips;

	auto & arrObj = controler[_index];

	for (unsigned int i = 0; i< arrObj.size(); i++)
	{
		ips.push_back(arrObj[i]->getIP());
	}
	return ips;
}

int ofxRemoteVideoControlMgr::size()const
{
	return controler.size();
}

bool ofxRemoteVideoControlMgr::checkOut(int _index)const
{
	bool res = true;
	res &= _index >= 0;
	res &= _index < size();
	return res;
}
