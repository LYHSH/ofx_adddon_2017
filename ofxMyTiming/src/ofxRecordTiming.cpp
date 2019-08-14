#include "ofxRecordTiming.h"



ofxRecordTiming::ofxRecordTiming()
{
	recorder = NULL;
	resetOrder = 0;
}


ofxRecordTiming::~ofxRecordTiming()
{
}

void ofxRecordTiming::setup(string _fileName)
{
	mgr.setup(_fileName);

	if (mgr.size())
	{
		recorder = mgr.getRecorder(0);
	}

	{
		ofxXmlSettings xml;
		xml.load(_fileName);
		resetOrder = xml.getValue("RESET_ORDER", 5);
	}

#pragma region 读取舞台灯光配置数据
	ofDirectory dir;
	dir.listDir("xml/lights");
	dir.sort();

	timingDatas.resize(dir.numFiles());

	for (int i = 0; i < timingDatas.size(); i++)
	{
		timingDatas[i].setup(dir.getPath(i));
	}
#pragma endregion
}

void ofxRecordTiming::update(int _videoIndex, int _frame)
{
	if (_videoIndex < 0 || _videoIndex >= timingDatas.size())
	{
		ofLogError(OF_FUNCTION_NAME) << "_videoIndex = " << _videoIndex << " is out of range" << endl;
		return;
	}
	storageXml & myStorage = timingDatas[_videoIndex];

	mylight wave;
	if (myStorage.getLight(_frame, wave))
	{
		for (int i = 0; i < wave.lightId.size(); i++)
		{
			recordPlay(wave.lightId[i]);
		}
	}
}

void ofxRecordTiming::draw()
{
	
}

void ofxRecordTiming::reset()
{
	for (int i = 0; i < timingDatas.size(); i++)
	{
		timingDatas[i].reset();
	}

	recordPlay(resetOrder);
}

void ofxRecordTiming::setResetOrder(int _value)
{
	resetOrder = _value;
}

void ofxRecordTiming::recordPlay(int _order)
{
	if (recorder)
	{
		recorder->play(_order);
	}
	else
	{
		ofLogError(OF_FUNCTION_NAME) << "recorder not instantiated,point to NULL" << endl;
	}
}

void ofxRecordTiming::play()
{
	if (recorder)
	{
		recorder->play();
	}
	else
	{
		ofLogError(OF_FUNCTION_NAME) << "recorder not instantiated,point to NULL" << endl;
	}
}

void ofxRecordTiming::pause()
{
	if (recorder)
	{
		recorder->pause();
	}
	else
	{
		ofLogError(OF_FUNCTION_NAME) << "recorder not instantiated,point to NULL" << endl;
	}
}

void ofxRecordTiming::stop()
{
	if (recorder)
	{
		recorder->stop();
	}
	else
	{
		ofLogError(OF_FUNCTION_NAME) << "recorder not instantiated,point to NULL" << endl;
	}
}