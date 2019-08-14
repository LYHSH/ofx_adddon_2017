#include "ofxRecorderFactory.h"
#include "ofxDMX512controler.h"
#include "ofxHuangControler.h"
#include "ofxRealTimeDMXcontroler.h"


ofxRecorderFactory::ofxRecorderFactory()
{
}


ofxRecorderFactory::~ofxRecorderFactory()
{
}

ofxRecorderBase * ofxRecorderFactory::createcontroler(RECORD_TYPE _type,ofxDataSender * _sender)
{
	switch (_type)
	{
	case RECORD_TYPE_DMX_512:
		return createDMX512controler(_sender);
		break;
	case RECORD_TYPE_HUANG:
		return createHuangControler(_sender);
		break;
	default:
		return NULL;
		break;
	}
}

ofxRecorderBase * ofxRecorderFactory::createDMX512controler(string _ip,int _port)
{
	ofxDMX512controler * controler = new ofxDMX512controler();
	controler->setup(_ip, _port);

	return controler;
}

ofxRecorderBase * ofxRecorderFactory::createDMX512controler(int _nCom, int _nbaud)
{
	ofxDMX512controler * controler = new ofxDMX512controler();
	controler->setup(_nCom, _nbaud);

	return controler;
}

ofxRecorderBase * ofxRecorderFactory::createDMX512controler(ofxDataSender * _sender)
{
	ofxDMX512controler * controler = new ofxDMX512controler();
	controler->setup(_sender);

	return controler;
}



ofxRecorderBase * ofxRecorderFactory::createHuangControler(string _ip, int _port)
{
	ofxHuangControler * controler = new ofxHuangControler();
	controler->setup(_ip, _port);

	return controler;
}

ofxRecorderBase * ofxRecorderFactory::createHuangControler(int _nCom, int _nbaud)
{
	ofxHuangControler * controler = new ofxHuangControler();
	controler->setup(_nCom, _nbaud);

	return controler;
}

ofxRecorderBase * ofxRecorderFactory::createHuangControler(ofxDataSender * _sender)
{
	ofxHuangControler * controler = new ofxHuangControler();
	controler->setup(_sender);

	return controler;
}

ofxRecorderBase * ofxRecorderFactory::createUdpRealTimeControler(string _ip, int _port)
{
	ofxRealTimeDMXcontroler * controler = new ofxRealTimeDMXcontroler();
	controler->setupUdp(_ip,_port);

	return controler;
}

