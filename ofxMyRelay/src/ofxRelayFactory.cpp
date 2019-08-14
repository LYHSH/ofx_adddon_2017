#include "ofxRelayFactory.h"
#include "ofxRelayComponent.h"
#include "ofx55seriesRelays.h"
#include "ofxRelayThreadDecoration.h"
#include "ofx2000seriesRelays.h"
#include "ofxLightingRelays.h"
#include "ofx55LongtengRelays.h"
#include "ofxHengYang2Relay.h"


ofxRelayFactory::ofxRelayFactory()
{
}


ofxRelayFactory::~ofxRelayFactory()
{
}

ofxRelaysBase * ofxRelayFactory::createRelay(RELAY_TYPE _type, string _ip, const vector<SERIES_ADD_RELAY> &components)
{
	ofxRelaysBase * relay = NULL;
	switch (_type)
	{
	case RELAY_TYPE_LONG_TENG_GAO_KE_NETWORK:
		relay = createLongtengRelay(_ip, components);
		break;
	case RELAY_TYPE_LIGHTING_MODULE_NETWORK:
		relay = createLightingRelay(_ip, components);
		break;
	case RELAY_TYPE_2000_NETWORK:
		relay = create2000seriesRelay(_ip, components);
		break;
	case RELAY_TYPE_LONG_TENG_GAO_KE_UDP_NETWORK:
		relay = createLongtengUdpRelay(_ip, components);
		break;
	case RELAY_TYPE_55_SERIES_NETWORK:
		relay = create55seriesRelay(_ip, components);
		break;
	case RELAY_TYPE_LIGHTING_MODULE_UDP_NETWORK:
		relay = createUdpLightingRelay(_ip, components);
		break;
	case RELAY_TYPE_55_SERIES_UDP_NETWORK:
		relay = create55seriesUdpRelay(_ip, components);
		break;
	default:
		break;
	}

	return relay;
}

ofxRelaysBase * ofxRelayFactory::createRelay(RELAY_TYPE _type, int _nCom, const vector<SERIES_ADD_RELAY> &components)
{
	ofxRelaysBase * relay = NULL;
	switch (_type)
	{
	case RELAY_TYPE_LONG_TENG_GAO_KE_COM:
		relay = createLongtengRelay(_nCom, components);
		break;
	case RELAY_TYPE_LIGHTING_MODULE_COM:
		relay = createLightingRelay(_nCom, components);
		break;
	case RELAY_TYPE_2000_COM:
		relay = create2000seriesRelay(_nCom, components);
		break;
	case RELAY_TYPE_55_SERIES_COM:
		relay = create55seriesRelay(_nCom, components);
		break;
	case RELAY_TYPE_HENG_YANG_2_SERIAL:
		relay = createHengYangSerialRelay(_nCom, components);
		break;
	default:
		break;
	}

	return relay;
}

ofxRelaysBase * ofxRelayFactory::createRelay(RELAY_TYPE _type, ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components)
{
	ofxRelaysBase * relay = NULL;
	switch (_type)
	{
	case RELAY_TYPE_LONG_TENG_GAO_KE_NETWORK:
	case RELAY_TYPE_LONG_TENG_GAO_KE_COM:
	case RELAY_TYPE_LONG_TENG_GAO_KE_UDP_NETWORK:
	case RELAY_TYPE_LONG_TENG_GAO_KE:
		relay = createLongtengRelay(_sender, components);
		break;
	case RELAY_TYPE_LIGHTING_MODULE_NETWORK:
	case RELAY_TYPE_LIGHTING_MODULE_COM:
	case RELAY_TYPE_LIGHTING_MODULE_UDP_NETWORK:
	case RELAY_TYPE_LIGHTING_ZHONG_YI:
		relay = createLightingRelay(_sender, components);
		break;
	case RELAY_TYPE_55_SERIES_NETWORK:
	case RELAY_TYPE_55_SERIES_COM:
	case RELAY_TYPE_55_SERIES_UDP_NETWORK:
	case RELAY_TYPE_55_SERIES:
		relay = createLongtengRelay(_sender, components);
		break;
	default:
		break;
	}

	return relay;
}

ofxRelaysBase * ofxRelayFactory::createLongtengRelay(string _ip, const vector<SERIES_ADD_RELAY> &components)
{
	ofx55LongtengRelays * pRelayLeader = new ofx55LongtengRelays();
	pRelayLeader->setup(_ip, 3000, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::createLongtengRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components)
{
	ofx55LongtengRelays * pRelayLeader = new ofx55LongtengRelays();
	pRelayLeader->setup(_nCom, 9600, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::createLongtengUdpRelay(string _ip, const vector<SERIES_ADD_RELAY> &components)
{
	ofx55LongtengRelays * pRelayLeader = new ofx55LongtengRelays();
	pRelayLeader->udpSetup(_ip, 55555, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::createLongtengRelay(ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components)
{
	ofx55LongtengRelays * pRelayLeader = new ofx55LongtengRelays();
	pRelayLeader->setup(_sender, 0x01);

	return buildRelay(pRelayLeader, components);
}


ofxRelaysBase * ofxRelayFactory::create55seriesRelay(string _ip, const vector<SERIES_ADD_RELAY> &components)
{
	ofx55seriesRelays * pRelayLeader = new ofx55seriesRelays();
	pRelayLeader->setup(_ip, 6000, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::create55seriesRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components)
{
	ofx55seriesRelays * pRelayLeader = new ofx55seriesRelays();
	pRelayLeader->setup(_nCom, 9600, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::create55seriesUdpRelay (string _ip, const vector<SERIES_ADD_RELAY> &components)
{
	ofx55seriesRelays * pRelayLeader = new ofx55seriesRelays();
	pRelayLeader->udpSetup(_ip, 55555, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::create55seriesRelay(ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components)
{
	ofx55seriesRelays * pRelayLeader = new ofx55seriesRelays();
	pRelayLeader->setup(_sender, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::create2000seriesRelay(string _ip, const vector<SERIES_ADD_RELAY> &components)
{
	ofx2000seriesRelays * pRelayLeader = new ofx2000seriesRelays();
	pRelayLeader->setup(_ip, 2000, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::create2000seriesRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components)
{
	ofx2000seriesRelays * pRelayLeader = new ofx2000seriesRelays();
	pRelayLeader->setup(_nCom, 9600, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::create2000seriesRelay(ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components)
{
	ofx2000seriesRelays * pRelayLeader = new ofx2000seriesRelays();
	pRelayLeader->setup(_sender, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::createLightingRelay(int _nCom,const vector<int> &componentAddrs)
{
	ofxLightingRelays * pRelayLeader = new ofxLightingRelays();
	pRelayLeader->setup(_nCom, 9600);

	int numsComponent = componentAddrs.size();

	ofxRelayComponent * pRelayComponent = new ofxRelayComponent(pRelayLeader);

	for (int i = 0; i < numsComponent; i++)
	{
		SERIES_ADD_RELAY seriesRalay;
		seriesRalay.address = 0x00 + componentAddrs[i];
		seriesRalay.size = 12;
		pRelayComponent->seriesAdd(seriesRalay);
	}

	ofxRelayThreadDecoration * pThreadRelay = new ofxRelayThreadDecoration(pRelayComponent);
	pThreadRelay->setup();
	return pThreadRelay;
}

ofxRelaysBase * ofxRelayFactory::createLightingRelay(string _ip, const vector<SERIES_ADD_RELAY> &components)
{
	ofxLightingRelays * pRelayLeader = new ofxLightingRelays();
	pRelayLeader->setup(_ip, 3000);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::createUdpLightingRelay(string _ip, const vector<SERIES_ADD_RELAY> &components)
{
	ofxLightingRelays * pRelayLeader = new ofxLightingRelays();
	pRelayLeader->udpSetup(_ip, 55555);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::createLightingRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components)
{
	ofxLightingRelays * pRelayLeader = new ofxLightingRelays();
	pRelayLeader->setup(_nCom, 9600);

	return buildRelay(pRelayLeader, components);
}


ofxRelaysBase * ofxRelayFactory::createLightingRelay(ofxDataSender * _sender, const vector<SERIES_ADD_RELAY> &components)
{
	ofxLightingRelays * pRelayLeader = new ofxLightingRelays();
	pRelayLeader->setup(_sender, 0x01);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::createHengYangSerialRelay(int _nCom, const vector<SERIES_ADD_RELAY> &components)
{
	ofxHengYang2Relay * pRelayLeader = new ofxHengYang2Relay();
	pRelayLeader->setup(_nCom, 9600);

	return buildRelay(pRelayLeader, components);
}

ofxRelaysBase * ofxRelayFactory::buildRelay(ofxRelaysBase * _pLeader, const vector<SERIES_ADD_RELAY> &components)
{
	int numsComponent = components.size();

	ofxRelayComponent * pRelayComponent = new ofxRelayComponent(_pLeader);

	for (int i = 0; i < numsComponent; i++)
	{
		SERIES_ADD_RELAY seriesRalay;
		seriesRalay.address = components[i].address;
		seriesRalay.size = components[i].size;
		pRelayComponent->seriesAdd(seriesRalay);
	}

	ofxRelayThreadDecoration * pThreadRelay = new ofxRelayThreadDecoration(pRelayComponent);
	pThreadRelay->setup();
	return pThreadRelay;
}

