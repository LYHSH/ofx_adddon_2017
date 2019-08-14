#include "ofxRecordMgr.h"



ofxRecordMgr::ofxRecordMgr()
{
}


ofxRecordMgr::~ofxRecordMgr()
{
}

void ofxRecordMgr::setup(const string & _filename)
{
	ofxXmlSettings xml;
	xml.load(_filename);

	senderMgr.setup(_filename);

	int nums = xml.getNumTags("RECORD");
	recorders.resize(nums);

	if (nums != senderMgr.size())
	{
		ofLogError(OF_FUNCTION_NAME) << "dataSender nums not equal to record nums" << endl;
	}

	for (int i = 0; i < nums; ++i)
	{
		xml.pushTag("RECORD", i);

		int type = xml.getValue("TYPE", 0);
		recorders[i] = ofxRecorderFactory::createcontroler((RECORD_TYPE)type,senderMgr.getSender(i));
		xml.popTag();
	}
}

ofxRecorderBase * ofxRecordMgr::getRecorder(int _index)
{
	if (!checkOut(_index))return NULL;

	return recorders[_index];
}

int ofxRecordMgr::size()const
{
	return recorders.size();
}

bool ofxRecordMgr::checkOut(int _index)const
{
	bool res = true;
	res &= _index >= 0;
	res &= _index < size();
	return res;
}
