#pragma once
#include "ofMain.h"
#include "ofxRelaysBase.h"
#include "ofxDataSender.h"
/************************************************************************/
/* project name:继电器控制接口库
/* file describe:继电器创建工厂
/* date:2017.7.16
/* author:hui
/************************************************************************/
typedef enum
{
	RELAY_TYPE_LONG_TENG_GAO_KE_NETWORK = 0,
	RELAY_TYPE_LONG_TENG_GAO_KE_COM = 1,
	RELAY_TYPE_LIGHTING_MODULE_NETWORK = 2,
	RELAY_TYPE_LIGHTING_MODULE_COM = 3,
	RELAY_TYPE_2000_NETWORK = 4,
	RELAY_TYPE_2000_COM = 5,
	RELAY_TYPE_LONG_TENG_GAO_KE_UDP_NETWORK = 6,
	RELAY_TYPE_55_SERIES_NETWORK = 7,
	RELAY_TYPE_55_SERIES_COM = 8,
	RELAY_TYPE_LIGHTING_MODULE_UDP_NETWORK = 9,
	RELAY_TYPE_55_SERIES_UDP_NETWORK = 10,
	RELAY_TYPE_HENG_YANG_2_SERIAL = 11,

	RELAY_TYPE_LONG_TENG_GAO_KE,
	RELAY_TYPE_55_SERIES,
	RELAY_TYPE_LIGHTING_ZHONG_YI,

}RELAY_TYPE;
class ofxRelayFactory
{
public:
	ofxRelayFactory();
	~ofxRelayFactory();

	static ofxRelaysBase * createRelay(RELAY_TYPE _type, string _ip, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * createRelay(RELAY_TYPE _type, int _nCom, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * createRelay(RELAY_TYPE _type, ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components);
	//创建龙腾高科继电器
	static ofxRelaysBase * createLongtengRelay(string _ip, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * createLongtengRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * createLongtengUdpRelay(string _ip, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * createLongtengRelay(ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components);

	//创建55系列继电器
	static ofxRelaysBase * create55seriesRelay(string _ip, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * create55seriesRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * create55seriesUdpRelay(string _ip, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * create55seriesRelay(ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components);
	//创建2000系列继电器
	static ofxRelaysBase * create2000seriesRelay(string _ip, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * create2000seriesRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * create2000seriesRelay(ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components);
	//创建智能照明模块继电器
	static ofxRelaysBase * createLightingRelay(int _nCom,const vector<int> &componentAddrs);
	static ofxRelaysBase * createLightingRelay(string _ip, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * createLightingRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * createUdpLightingRelay(string _ip, const vector<SERIES_ADD_RELAY> &components);
	static ofxRelaysBase * createLightingRelay(ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components);

	static ofxRelaysBase * createHengYangSerialRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components);
private:
	static ofxRelaysBase * buildRelay(ofxRelaysBase * _pLeader, const vector<SERIES_ADD_RELAY> &components);
};

