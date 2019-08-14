#include "ofxPJcontrolFactory.h"
#include "ofxpjlinkPJcontrol.h"
#include "ofxCannon33336PJcontrol.h"
#include "ofxCannonComPJcontrol.h"
#include "ofxCannon33336PJ2.h"
#include "ofxVivitekComProject.h"
#include "ofxSonyNetProject.h"
#include "ofxDLPproject.h"
#include "ofxChangShaPJ1.h"
#include "ofxChangShaPJ2.h"

ofxPJcontrolFactory::ofxPJcontrolFactory()
{
}


ofxPJcontrolFactory::~ofxPJcontrolFactory()
{
}

ofxPJcontrolBase * ofxPJcontrolFactory::createPJbyType(PROJECT_TYPE _type,string _ipOrCom)
{
	switch (_type)
	{
	case PJ_TYPE_PJLINK:
		return createPjlinkPJ(_ipOrCom);
		break;
	case PJ_TYPE_CANNON_33336:
		return createCannon33336PJ(_ipOrCom);
		break;
	case PJ_TYPE_CANNON_33336_TYPE2:
		return createCannon33336PJ2(_ipOrCom);
		break;
	case PJ_TYPE_CANNON_COM:
		return NULL;
		break;
	case PJ_TYPE_VIVITEK_COM:
		return createVivitekComPJ(_ipOrCom);
		break;
	case PJ_TYPE_SONY_NET:
		return createSonyNetPJ(_ipOrCom);
		break;
	case PJ_TYPE_SML_NET:
		return createSmlNetPJ(_ipOrCom);
		break;
	case PJ_TYPE_DLP_NET:
		return createDLPNetPJ(_ipOrCom);
		break;
	case PJ_TYPE_CS_MOON_NET_1:
		return createCSmoonNetPJ1(_ipOrCom);
		break;
	case PJ_TYPE_CS_MOON_NET_2:
		return createCSmoonNetPJ2(_ipOrCom);
		break;
	default:
		return NULL;
		break;
	}
}

ofxPJcontrolBase * ofxPJcontrolFactory::createPjlinkPJ(string _ip)
{
	ofxpjlinkPJcontrol * object = new ofxpjlinkPJcontrol();
	object->setup(_ip);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createCannon33336PJ(string _ip)
{
	ofxCannon33336PJcontrol * object = new ofxCannon33336PJcontrol();
	object->setup(_ip);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createCannonComPJ(string _comName)
{
	ofxCannonComPJcontrol * object = new ofxCannonComPJcontrol();
	object->setup(_comName);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createCannon33336PJ2(string _ip)
{
	ofxCannon33336PJ2 * object = new ofxCannon33336PJ2();
	object->setup(_ip);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createVivitekComPJ(string _comName)
{
	ofxVivitekComProject * object = new ofxVivitekComProject();
	object->setup(_comName);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createSonyNetPJ(string _ip)
{
	ofxSonyNetProject * object = new ofxSonyNetProject();
	object->setup(_ip);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createSmlNetPJ(string _ip)
{
	ofxDLPproject * object = new ofxDLPproject();
	object->setup(_ip);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createDLPNetPJ(string _ip)
{
	ofxDLPproject * object = new ofxDLPproject();
	object->setup(_ip);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createCSmoonNetPJ1(string _ip)
{
	ofxChangShaPJ1 * object = new ofxChangShaPJ1();
	object->setup(_ip);

	return object;
}

ofxPJcontrolBase * ofxPJcontrolFactory::createCSmoonNetPJ2(string _ip)
{
	ofxChangShaPJ2 * object = new ofxChangShaPJ2();
	object->setup(_ip);

	return object;
}

