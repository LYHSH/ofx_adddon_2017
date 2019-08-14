#pragma once
#include "ofMain.h"
#include "ofxPJcontrolBase.h"
/************************************************************************/
/* project name:投影机控制接口库
/* file describe:投影机控制工厂
/* date:2017.12.28
/* author:hui
/************************************************************************/

typedef enum
{
	PJ_TYPE_PJLINK = 0,
	PJ_TYPE_CANNON_33336 = 1,
	PJ_TYPE_CANNON_COM = 2,
	PJ_TYPE_CANNON_33336_TYPE2 = 3,
	PJ_TYPE_VIVITEK_COM = 4,
	PJ_TYPE_SONY_NET = 5,
	PJ_TYPE_SML_NET = 6,
	PJ_TYPE_DLP_NET = 7,
	PJ_TYPE_CS_MOON_NET_1 = 8,
	PJ_TYPE_CS_MOON_NET_2 = 9
}PROJECT_TYPE;
class ofxPJcontrolFactory
{
public:
	ofxPJcontrolFactory();
	~ofxPJcontrolFactory();
	static ofxPJcontrolBase * createPJbyType(PROJECT_TYPE _type,string _ipOrCom);

	static ofxPJcontrolBase * createPjlinkPJ(string _ip);
	static ofxPJcontrolBase * createCannon33336PJ(string _ip);
	static ofxPJcontrolBase * createCannonComPJ(string _comName);
	static ofxPJcontrolBase * createCannon33336PJ2(string _ip);
	static ofxPJcontrolBase * createVivitekComPJ(string _comName);
	static ofxPJcontrolBase * createSonyNetPJ(string _ip);
	static ofxPJcontrolBase * createSmlNetPJ(string _ip);
	static ofxPJcontrolBase * createDLPNetPJ(string _ip);

	static ofxPJcontrolBase * createCSmoonNetPJ1(string _ip);
	static ofxPJcontrolBase * createCSmoonNetPJ2(string _ip);


};

