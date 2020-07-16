#include "ofxRelayTiming.h"



ofxRelayTiming::ofxRelayTiming()
{
}


ofxRelayTiming::~ofxRelayTiming()
{
}

void ofxRelayTiming::setup(string _fileName)
{
	mgr.setup(_fileName);

	if (mgr.size())
	{
		relayer = mgr.getRelayer(0);
	}



#pragma region 读取舞台灯光配置数据
	ofDirectory dir;
	dir.listDir("xml/models");
	dir.sort();

	timingDatas.resize(dir.numFiles());

	for (int i = 0; i < timingDatas.size(); i++)
	{
		timingDatas[i].setup(dir.getPath(i));
		vector<int> temp = timingDatas[i].getAllId();
		ids.insert(ids.end(),temp.begin(),temp.end());
	}

	sort(ids.begin(), ids.end());
	ids.erase(unique(ids.begin(), ids.end()), ids.end());

	for (int i = 0;i < ids.size();i++)
	{
		cout << ids[i] << " " << endl;
	}
	cout << endl;
#pragma endregion
}

void ofxRelayTiming::update(int _videoIndex, int _frame)
{
	if (!relayer)
	{
		ofLogError(OF_FUNCTION_NAME) << "relayer not instantiated,point to NULL" << endl;
		return;
	}
	if (_videoIndex < 0 || _videoIndex >= timingDatas.size())
	{
		ofLogError(OF_FUNCTION_NAME) << "_videoIndex = "<<_videoIndex <<" is out of range" << endl;
		return;
	}
	storageXml & modelStorage = timingDatas[_videoIndex];
	mylight modelData;
	if (modelStorage.getLight(_frame, modelData))
	{
		if (modelData.onOff)
		{
			if (modelData.lightId[0] == 1000)
			{
				relayer->setAllOn();
			}
			else
			{
				relayer->setMultOn(modelData.lightId);
			}
		}
		else
		{
			if (modelData.lightId[0] == 1000)
			{
				relayer->setAllOff();
			}
			else
			{
				relayer->setMultOff(modelData.lightId);
			}

		}
	}
}

void ofxRelayTiming::draw()
{

}

void ofxRelayTiming::reset()
{
	for (int i = 0; i < timingDatas.size(); i++)
	{
		timingDatas[i].reset();
	}
}

void ofxRelayTiming::setAllOn()
{
	for (int i = 0; i < timingDatas.size();i++)
	{
		if (relayer)
		{
			cout << "set all on" << endl;
			relayer->setMultOn(ids);
		}
	}
	
}

void ofxRelayTiming::setAllOff()
{
	for (int i = 0; i < timingDatas.size(); i++)
	{
		if (relayer)
		{
			cout << "set all off" << endl;
			relayer->setMultOff(ids);
		}
	}
}
